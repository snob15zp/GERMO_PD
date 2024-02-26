/*******************************************************************************
* File Name: cyhal_clock.c
*
* Description:
* Provides an implementation for high level interface for interacting with the
* Infineon Clocks. This is a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "cy_sysclk.h"
#include "cy_utils.h"
#include "cyhal_clock.h"
#include "cyhal_utils.h"
#include "cyhal_hwmgr.h"

#if (CYHAL_DRIVER_AVAILABLE_CLOCK)

#if defined(__cplusplus)
extern "C"
{
#endif

#define PLL_LOCK_TIME (10000UL)

/******************************************************************************
 ****************************** Clock Resources *******************************
 *****************************************************************************/
const cyhal_clock_tolerance_t CYHAL_TOLERANCE_0_P = {CYHAL_TOLERANCE_PERCENT, 0};
const cyhal_clock_tolerance_t CYHAL_TOLERANCE_1_P = {CYHAL_TOLERANCE_PERCENT, 1};
const cyhal_clock_tolerance_t CYHAL_TOLERANCE_5_P = {CYHAL_TOLERANCE_PERCENT, 5};

const cyhal_resource_inst_t CYHAL_CLOCK_RSC_IMO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_IMO, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_EXT = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_EXT, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ILO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ILO, 0 };

#if defined(CY_IP_M0S8EXCO)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ECO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ECO, 0 };
#endif
#if defined(CY_IP_M0S8WCO)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_WCO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_WCO, 0 };
#if (WCO_WDT_EN == 1)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_WDCSEL = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_WDCSEL, 0 };
#endif
#endif

#if (EXCO_PLL_PRESENT > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLLSEL = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLLSEL, 0 };
#endif

const cyhal_resource_inst_t CYHAL_CLOCK_RSC_LF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_LF, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_HF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PUMP = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PUMP, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_SYS = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_SYS, 0 };

/******************************************************************************
 ***************************** Support Functions*******************************
 *****************************************************************************/
static cy_rslt_t _cyhal_clock_compute_div(uint32_t input_hz, uint32_t desired_hz, uint32_t divider_bits, const cyhal_clock_tolerance_t *tolerance, uint32_t *div)
{
    uint32_t max_div = (1 << divider_bits);
    *div = (input_hz + (desired_hz / 2)) / desired_hz;
    if (*div > max_div)
        *div = max_div;

    uint32_t diff = (tolerance != NULL)
                    ? (uint32_t)abs(_cyhal_utils_calculate_tolerance(tolerance->type, desired_hz, input_hz / *div))
                    : 0;
    return (tolerance != NULL && (diff > tolerance->value))
        ? CYHAL_CLOCK_RSLT_ERR_FREQ
        : CY_RSLT_SUCCESS;
}

static void cyhal_update_system_state(bool before_change, uint32_t old_hfclk_freq_hz, uint32_t new_hfclk_freq_hz)
{
    // If increasing the clock frequency we need to update the speeds
    // before the change. If decreasing the frequency we need to update
    // after the change.
    if ((before_change == (bool)(new_hfclk_freq_hz > old_hfclk_freq_hz)) ||
        (!before_change == (new_hfclk_freq_hz < old_hfclk_freq_hz)))
    {
        Cy_SysLib_SetWaitStates(new_hfclk_freq_hz / 1000000);
    }

    // If after the change, update the clock
    if (!before_change)
        SystemCoreClockUpdate();
}

static uint32_t cyhal_get_path_freq(cy_en_sysclk_clkhf_src_t clk, bool current_n_future)
{
#if !defined(EXCO_PLL_PRESENT) || (EXCO_PLL_PRESENT == 0)
    CY_UNUSED_PARAMETER(current_n_future);
#endif /* !defined(EXCO_PLL_PRESENT) || (EXCO_PLL_PRESENT == 0) */
    switch (clk)
    {
        case CY_SYSCLK_CLKHF_IN_IMO:
            return Cy_SysClk_ImoGetFrequency();
        case CY_SYSCLK_CLKHF_IN_EXTCLK:
#if (EXCO_PLL_PRESENT > 0)
            if (current_n_future && (CY_SYSCLK_PLL_BYP_PLL == Cy_SysClk_PllGetBypassState(0)))
            {
                return Cy_SysClk_PllGetFrequency(0);
            }
#endif
            return Cy_SysClk_ExtClkGetFrequency();
#if defined(CY_IP_M0S8EXCO)
        case CY_SYSCLK_CLKHF_IN_ECO:
            return Cy_SysClk_EcoGetFrequency();
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CY_SYSCLK_CLKHF_IN_PLL:
            CY_ASSERT(!current_n_future); // Should only occur if changing to the PLL
            return Cy_SysClk_PllGetFrequency(0);
#endif
        default:
            return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }
}

static cy_rslt_t cyhal_get_sysclk_div(uint32_t div_val, cy_en_sysclk_dividers_t *div)
{
    switch (div_val)
    {
        case 1:
            *div = CY_SYSCLK_NO_DIV;
            break;
        case 2:
            *div = CY_SYSCLK_DIV_2;
            break;
        case 4:
            *div = CY_SYSCLK_DIV_4;
            break;
        case 8:
            *div = CY_SYSCLK_DIV_8;
            break;
        default:
            return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }
    return CY_RSLT_SUCCESS;
}


#if (EXCO_PLL_PRESENT > 0)
static uint32_t cyhal_get_pll_in_freq(void)
{
    cy_en_sysclk_pll_src_t src = Cy_SysClk_PllGetSource(0);
    if (src == CY_SYSCLK_PLL_SRC_IMO)
        return Cy_SysClk_ImoGetFrequency();
    else
    {
#if defined(CY_IP_M0S8EXCO)
        return Cy_SysClk_EcoGetFrequency();
#else
        return 0;
#endif
    }
}

#endif


static cy_rslt_t _cyhal_clock_set_enabled_unsupported(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(enabled);
    CY_UNUSED_PARAMETER(wait_for_lock);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_set_frequency_unsupported(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(hz);
    CY_UNUSED_PARAMETER(tolerance);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_set_divider_unsupported(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(divider);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_set_source_unsupported(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(source);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static bool _cyhal_clock_is_enabled_true(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return true;
}
static cy_rslt_t _cyhal_clock_get_sources_none(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(sources);
    *count = 0;
    return CY_RSLT_SUCCESS;
}

static bool _cyhal_clock_is_enabled_imo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ImoIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_imo(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_ImoEnable();
    else
        Cy_SysClk_ImoDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_imo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ImoGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_frequency_imo(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    if ((hz < CY_SYSCLK_IMO_24MHZ) || (hz > CY_SYSCLK_IMO_48MHZ) || ((hz % 4000000) != 0))
        return CYHAL_CLOCK_RSLT_ERR_FREQ;

    uint32_t hf_freq = Cy_SysClk_ClkHfGetFrequency();
    uint32_t div = 1 << (uint8_t)Cy_SysClk_ClkHfGetDivider();
    if (Cy_SysClk_ClkHfGetSource() == CY_SYSCLK_CLKHF_IN_IMO)
        cyhal_update_system_state(true, hf_freq, hz / div);
    Cy_SysClk_ImoSetFrequency((cy_en_sysclk_imo_freq_t)hz);
    if (Cy_SysClk_ClkHfGetSource() == CY_SYSCLK_CLKHF_IN_IMO)
        cyhal_update_system_state(false, hf_freq, hz / div);
    return CY_RSLT_SUCCESS;
}

static bool _cyhal_clock_is_enabled_ext(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return (Cy_SysClk_ExtClkGetFrequency() > 0);
}
static uint32_t _cyhal_clock_get_frequency_ext(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ExtClkGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_frequency_ext(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    Cy_SysClk_ExtClkSetFrequency(hz);
    return CY_RSLT_SUCCESS;
}

static bool _cyhal_clock_is_enabled_ilo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_IloIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_ilo(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_IloEnable();
    else
        Cy_SysClk_IloDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_ilo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_ILO_FREQ;
}

static uint32_t _cyhal_clock_get_frequency_lf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_ILO_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_lf(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_LF[] =
    {
        &CYHAL_CLOCK_RSC_ILO,
    };

    *sources = CYHAL_CLOCK_SOURCE_LF;
    *count = sizeof(CYHAL_CLOCK_SOURCE_LF) / sizeof(CYHAL_CLOCK_SOURCE_LF[0]);
    return CY_RSLT_SUCCESS;
}

#if defined(CY_IP_M0S8EXCO)
static bool _cyhal_clock_is_enabled_eco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_EcoIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_eco(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);

    if (enabled)
    {
        if (Cy_SysClk_EcoIsEnabled())
        {
            // Already enabled
            if (wait_for_lock)
            {
                for (int t = 0; t < 3 && (Cy_SysClk_EcoGetStatus() != CY_SYSCLK_ECO_STABLE); ++t)
                {
                    Cy_SysLib_DelayUs(1000UL);
                }
                return (Cy_SysClk_EcoGetStatus() == CY_SYSCLK_ECO_STABLE)
                    ? CY_RSLT_SUCCESS
                    : CY_SYSCLK_TIMEOUT;
            }
            return CY_RSLT_SUCCESS;
        }
        else
        {
            return Cy_SysClk_EcoEnable(wait_for_lock ? 3000UL : 0UL);
        }
    }
    else
    {
        Cy_SysClk_EcoDisable();
        return CY_RSLT_SUCCESS;
    }
}
static uint32_t _cyhal_clock_get_frequency_eco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_EcoGetFrequency();
}
#endif

#if defined(CY_IP_M0S8WCO)
static bool _cyhal_clock_is_enabled_wco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_WcoIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_wco(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);

    if (enabled)
    {
        Cy_SysClk_WcoEnable(wait_for_lock ? CY_SYSCLK_WCO_TIMEOUT_US : 0UL);
        // Ignore CY_SYSCLK_TIMEOUT unless wait_for_lock is true
        return (wait_for_lock && !Cy_SysClk_WcoIsEnabled())
            ? CYHAL_CLOCK_RSLT_ERR_LOCK
            : CY_RSLT_SUCCESS;
    }
    else
    {
        Cy_SysClk_WcoDisable();
        return CY_RSLT_SUCCESS;
    }
}
static uint32_t _cyhal_clock_get_frequency_wco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_WCO_FREQ;
}

#if (WCO_WDT_EN == 1)
static uint32_t _cyhal_clock_get_frequency_wdcsel(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return (Cy_WDC_GetClockSource(WCO) == CY_WDC_CLOCK_ILO)
        ? CY_SYSCLK_ILO_FREQ
        : CY_SYSCLK_WCO_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_wdcsel(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_WDCSEL[] =
    {
        &CYHAL_CLOCK_RSC_ILO,
        &CYHAL_CLOCK_RSC_WCO,
    };

    *sources = CYHAL_CLOCK_SOURCE_WDCSEL;
    *count = sizeof(CYHAL_CLOCK_SOURCE_WDCSEL) / sizeof(CYHAL_CLOCK_SOURCE_WDCSEL[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_wdcsel(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    cy_en_wdc_clock_t new_source;
    if(source->block == CYHAL_CLOCK_BLOCK_ILO)
    {
        new_source = CY_WDC_CLOCK_ILO;
    }
    else if(source->block == CYHAL_CLOCK_BLOCK_WCO)
    {
        new_source = CY_WDC_CLOCK_WCO;
    }
    else
    {
        return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }

    Cy_WDC_SetClockSource(WCO, new_source);
    return CY_RSLT_SUCCESS;
}
#endif // (WCO_WDT_EN == 1)
#endif // defined(CY_IP_M0S8WCO)

#if (EXCO_PLL_PRESENT > 0)
static bool _cyhal_clock_is_enabled_pll(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_PllIsEnabled(0);
}
static cy_rslt_t _cyhal_clock_set_enabled_pll(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);

    cy_stc_sysclk_pll_manual_config_t cfg;
    Cy_SysClk_PllGetConfiguration(0, &cfg);

    uint32_t new_freq, old_freq;
    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
    uint32_t src_freq = cyhal_get_pll_in_freq();

    /* Calculate Pll output frequency */
    uint32_t pll_freq = CY_SYSLIB_DIV_ROUND(src_freq, 1UL + cfg.referenceDiv) * cfg.feedbackDiv;
    pll_freq = CY_SYSLIB_DIV_ROUND(pll_freq, 1UL << cfg.outputDiv);

    if (enabled)
    {
        new_freq = pll_freq >> div;
        old_freq = src_freq >> div;
    }
    else
    {
        new_freq = src_freq >> div;
        old_freq = pll_freq >> div;
    }

    bool pll_sources_hf = ((CY_SYSCLK_CLKHF_IN_ECO == Cy_SysClk_ClkHfGetSource()) &&
                           (CY_SYSCLK_PLL_BYP_ECO != Cy_SysClk_PllGetBypassState(0)));
    if (pll_sources_hf)
        cyhal_update_system_state(true, old_freq, new_freq);

    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    if (enabled)
        rslt = Cy_SysClk_PllEnable(0, wait_for_lock ? PLL_LOCK_TIME : 0UL);
    else
        Cy_SysClk_PllDisable(0);

    if (pll_sources_hf)
    {
        if (CY_RSLT_SUCCESS == rslt)
            cyhal_update_system_state(false, old_freq, new_freq);
        else // revert the change if there was one
            cyhal_update_system_state(false, new_freq, old_freq);
    }

    return rslt;
}
static uint32_t _cyhal_clock_get_frequency_pll(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_PllIsEnabled(0)
        ? Cy_SysClk_PllGetFrequency(0)
        : 0;
}
static cy_rslt_t _cyhal_clock_set_frequency_pll(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    cy_stc_sysclk_pll_manual_config_t cfg;
    Cy_SysClk_PllGetConfiguration(0, &cfg);

    bool enabled = Cy_SysClk_PllIsEnabled(0);
    if (enabled)
        Cy_SysClk_PllDisable(0);

    uint32_t new_freq = hz;
    uint32_t src_freq = cyhal_get_pll_in_freq();
    uint32_t old_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * (uint64_t)cfg.feedbackDiv, (uint32_t)cfg.referenceDiv * (uint32_t)cfg.outputDiv);

    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
    uint32_t old_hf_freq = old_freq >> div;
    uint32_t new_hf_freq = new_freq >> div;

    bool pll_sources_hf = ((CY_SYSCLK_CLKHF_IN_ECO == Cy_SysClk_ClkHfGetSource()) &&
                           (CY_SYSCLK_PLL_BYP_ECO != Cy_SysClk_PllGetBypassState(0)));
    if (pll_sources_hf)
        cyhal_update_system_state(true, old_hf_freq, new_hf_freq);

    cy_stc_sysclk_pll_config_t new_cfg =
    {
        .inputFreq = src_freq,
        .outputFreq = new_freq,
    };
    cy_rslt_t rslt = Cy_SysClk_PllConfigure(0, &new_cfg);

    if (enabled)
    {
        cy_rslt_t rslt2 = Cy_SysClk_PllEnable(0, PLL_LOCK_TIME);
        if (CY_RSLT_SUCCESS == rslt)
            rslt = rslt2;
    }

    if (pll_sources_hf)
    {
        if (CY_RSLT_SUCCESS == rslt)
            cyhal_update_system_state(false, old_hf_freq, new_hf_freq);
        else // revert the change if there was one
            cyhal_update_system_state(false, new_hf_freq, old_hf_freq);
    }

    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_pll(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PLL[] =
    {
        &CYHAL_CLOCK_RSC_PLLSEL,
    };

    *sources = CYHAL_CLOCK_SOURCE_PLL;
    *count = sizeof(CYHAL_CLOCK_SOURCE_PLL) / sizeof(CYHAL_CLOCK_SOURCE_PLL[0]);
    return CY_RSLT_SUCCESS;
}

static uint32_t _cyhal_clock_get_frequency_pllsel(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return cyhal_get_pll_in_freq();
}
static cy_rslt_t _cyhal_clock_get_sources_pllsel(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PLLSEL[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
        &CYHAL_CLOCK_RSC_ECO,
    };

    *sources = CYHAL_CLOCK_SOURCE_PLLSEL;
    *count = sizeof(CYHAL_CLOCK_SOURCE_PLLSEL) / sizeof(CYHAL_CLOCK_SOURCE_PLLSEL[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_pllsel(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    if (source->block == CYHAL_CLOCK_BLOCK_IMO)
    {
        Cy_SysClk_PllSetSource(0, CY_SYSCLK_PLL_SRC_IMO);
        return CY_RSLT_SUCCESS;
    }
    else if (source->block == CYHAL_CLOCK_BLOCK_ECO)
    {
        Cy_SysClk_PllSetSource(0, CY_SYSCLK_PLL_SRC_ECO);
        return CY_RSLT_SUCCESS;
    }
    else
        return CYHAL_CLOCK_RSLT_ERR_SOURCE;
}
#endif // (EXCO_PLL_PRESENT > 0)

static bool _cyhal_clock_is_enabled_pump(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return (CY_SYSCLK_PUMP_IN_GND != Cy_SysClk_ClkPumpGetSource());
}
static cy_rslt_t _cyhal_clock_set_enabled_pump(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_HFCLK);
    else
        Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_GND);
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_pump(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    switch (Cy_SysClk_ClkPumpGetSource())
    {
        case CY_SYSCLK_PUMP_IN_IMO:
            return Cy_SysClk_ImoGetFrequency();
        case CY_SYSCLK_PUMP_IN_HFCLK:
            return Cy_SysClk_ClkHfGetFrequency();
        case CY_SYSCLK_PUMP_IN_GND:
        default:
            return 0;
    }
}
static cy_rslt_t _cyhal_clock_get_sources_pump(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PUMP[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
        &CYHAL_CLOCK_RSC_HF,
    };

    *sources = CYHAL_CLOCK_SOURCE_PUMP;
    *count = sizeof(CYHAL_CLOCK_SOURCE_PUMP) / sizeof(CYHAL_CLOCK_SOURCE_PUMP[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_pump(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    if (source->block == CYHAL_CLOCK_BLOCK_IMO)
    {
        Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_IMO);
        return CY_RSLT_SUCCESS;
    }
    else if (source->block == CYHAL_CLOCK_BLOCK_HF)
    {
        Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_HFCLK);
        return CY_RSLT_SUCCESS;
    }
    else
        return CYHAL_CLOCK_RSLT_ERR_SOURCE;
}

static uint32_t _cyhal_clock_get_frequency_hf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkHfGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_divider_hf(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    cy_en_sysclk_dividers_t new_div;
    cy_rslt_t rslt = cyhal_get_sysclk_div(divider, &new_div);

    if (CY_RSLT_SUCCESS == rslt)
    {
        uint32_t old_div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
        cy_en_sysclk_clkhf_src_t src = Cy_SysClk_ClkHfGetSource();
        uint32_t path_freq = cyhal_get_path_freq(src, true);
        uint32_t old_freq = path_freq >> old_div;
        uint32_t new_freq = path_freq >> ((uint32_t)new_div);

        cyhal_update_system_state(true, old_freq, new_freq);
        Cy_SysClk_ClkHfSetDivider(new_div);
        cyhal_update_system_state(false, old_freq, new_freq);
    }

    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_hf(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_HF[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
        &CYHAL_CLOCK_RSC_EXT,
    #if defined(CY_IP_M0S8EXCO)
        &CYHAL_CLOCK_RSC_ECO,
    #if (EXCO_PLL_PRESENT > 0)
        &CYHAL_CLOCK_RSC_PLL,
    #endif
    #endif
    };

    *sources = CYHAL_CLOCK_SOURCE_HF;
    *count = sizeof(CYHAL_CLOCK_SOURCE_HF) / sizeof(CYHAL_CLOCK_SOURCE_HF[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_hf(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);
    cy_en_sysclk_clkhf_src_t new_src;
    switch (source->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            new_src = CY_SYSCLK_CLKHF_IN_IMO;
            break;
        case CYHAL_CLOCK_BLOCK_EXT:
            new_src = CY_SYSCLK_CLKHF_IN_EXTCLK;
            break;
#if defined(CY_IP_M0S8EXCO)
        case CYHAL_CLOCK_BLOCK_ECO:
            new_src = CY_SYSCLK_CLKHF_IN_ECO;
            break;
#endif
#if (EXCO_PLL_PRESENT > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            new_src = CY_SYSCLK_CLKHF_IN_PLL;
            break;
#endif
        default:
            return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }

    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider();
    cy_en_sysclk_clkhf_src_t old_src = Cy_SysClk_ClkHfGetSource();
    uint32_t old_freq = cyhal_get_path_freq(old_src, true) >> div;
    uint32_t new_freq = cyhal_get_path_freq(new_src, false) >> div;

    cyhal_update_system_state(true, old_freq, new_freq);
    Cy_SysClk_ClkHfSetSource(new_src);
    cyhal_update_system_state(false, old_freq, new_freq);

    return CY_RSLT_SUCCESS;
}

static uint32_t _cyhal_clock_get_frequency_sys(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkSysGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_divider_sys(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    cy_en_sysclk_dividers_t new_div = CY_SYSCLK_NO_DIV;
    cy_rslt_t rslt = cyhal_get_sysclk_div(divider, &new_div);
    if (CY_RSLT_SUCCESS == rslt)
    {
        Cy_SysClk_ClkSysSetDivider(new_div);
    }
    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_sys(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_SYS[] =
    {
        &CYHAL_CLOCK_RSC_HF,
    };

    *sources = CYHAL_CLOCK_SOURCE_SYS;
    *count = sizeof(CYHAL_CLOCK_SOURCE_SYS) / sizeof(CYHAL_CLOCK_SOURCE_SYS[0]);
    return CY_RSLT_SUCCESS;
}

static bool _cyhal_clock_is_enabled_peripheral(const cyhal_clock_t *clock)
{
    return _cyhal_utils_peri_pclk_is_divider_enabled((en_clk_dst_t)0, clock);
}
static cy_rslt_t _cyhal_clock_set_enabled_peripheral(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(wait_for_lock);

    return (enabled)
        ? _cyhal_utils_peri_pclk_enable_divider((en_clk_dst_t)0, clock)
        : _cyhal_utils_peri_pclk_disable_divider((en_clk_dst_t)0, clock);
}
static uint32_t _cyhal_clock_get_frequency_peripheral(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return _cyhal_utils_peri_pclk_get_frequency((en_clk_dst_t)0, clock);
}
static cy_rslt_t _cyhal_clock_set_frequency_peripheral(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    // blocks 0b00 & 0b01 are integer, 0b10 & 0b11 are fractional
    uint32_t div;
    uint32_t input_hz = Cy_SysClk_ClkSysGetFrequency();

    if ((clock->block & 0x02) == 0)
    {
        uint32_t bits = (clock->block == CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT) ? 8 : 16;
        cy_rslt_t rslt = _cyhal_clock_compute_div(input_hz, hz, bits, tolerance, &div);
        return (CY_RSLT_SUCCESS == rslt)
            ? _cyhal_utils_peri_pclk_set_divider((en_clk_dst_t)0, clock, (div - 1))
            : rslt;
    }
    else
    {
        // Multiply input by 32 so we can treat the 5 fractional bits as though they are extentions of the integer divider
        // Leave the the desired frequency alone, so we can just strip out the integer & fractional bits at the end.
        uint32_t bits = (clock->block == CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT) ? 21 : 29; // Integer bits + 5
        cy_rslt_t rslt = _cyhal_clock_compute_div(input_hz << 5, hz, bits, tolerance, &div);
        if (CY_RSLT_SUCCESS == rslt)
        {
            uint32_t div_int = (div >> 5) - 1;
            uint32_t div_frac = div & 0x1F;
            return _cyhal_utils_peri_pclk_set_frac_divider((en_clk_dst_t)0, clock, div_int, div_frac);
        }
        else
            return rslt;
    }
}
static cy_rslt_t _cyhal_clock_set_divider_peripheral(cyhal_clock_t *clock, uint32_t divider)
{
    // blocks 0b00 & 0b01 are integer, 0b10 & 0b11 are fractional
    return ((clock->block & 0x02) == 0)
        ? _cyhal_utils_peri_pclk_set_divider((en_clk_dst_t)0, clock, divider - 1)
        : _cyhal_utils_peri_pclk_set_frac_divider((en_clk_dst_t)0, clock, divider - 1, 0);
}
static cy_rslt_t _cyhal_clock_get_sources_peripheral(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *CYHAL_CLOCK_SOURCE_PERIPHERAL[] =
    {
        &CYHAL_CLOCK_RSC_SYS,
    };

    *sources = CYHAL_CLOCK_SOURCE_PERIPHERAL;
    *count = sizeof(CYHAL_CLOCK_SOURCE_PERIPHERAL) / sizeof(CYHAL_CLOCK_SOURCE_PERIPHERAL[0]);
    return CY_RSLT_SUCCESS;
}


/******************************************************************************
 ******************************* Clock Structs ********************************
 *****************************************************************************/

typedef struct
{
    bool (*is_enabled)(const cyhal_clock_t *clock);
    cy_rslt_t (*set_enabled)(cyhal_clock_t *clock, bool enabled, bool wait_for_lock);
    uint32_t (*get_frequency)(const cyhal_clock_t *clock);
    cy_rslt_t (*set_frequency)(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance);
    cy_rslt_t (*set_divider)(cyhal_clock_t *clock, uint32_t divider);
    cy_rslt_t (*get_sources)(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count);
    cy_rslt_t (*set_source)(cyhal_clock_t *clock, const cyhal_clock_t *source);
    cyhal_clock_feature_t features;
} cyhal_clock_funcs_t;

static const cyhal_clock_funcs_t FUNCS_IMO =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_imo,
    .set_enabled = _cyhal_clock_set_enabled_imo,
    .get_frequency = _cyhal_clock_get_frequency_imo,
    .set_frequency = _cyhal_clock_set_frequency_imo,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_EXT =
{
    .features = CYHAL_CLOCK_FEATURE_FREQUENCY,
    .is_enabled = _cyhal_clock_is_enabled_ext,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_ext,
    .set_frequency = _cyhal_clock_set_frequency_ext,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_ILO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_ilo,
    .set_enabled = _cyhal_clock_set_enabled_ilo,
    .get_frequency = _cyhal_clock_get_frequency_ilo,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};

#if defined(CY_IP_M0S8EXCO)
static const cyhal_clock_funcs_t FUNCS_ECO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_eco,
    .set_enabled = _cyhal_clock_set_enabled_eco,
    .get_frequency = _cyhal_clock_get_frequency_eco,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif
#if defined(CY_IP_M0S8WCO)
static const cyhal_clock_funcs_t FUNCS_WCO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_wco,
    .set_enabled = _cyhal_clock_set_enabled_wco,
    .get_frequency = _cyhal_clock_get_frequency_wco,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#if (WCO_WDT_EN == 1)
static const cyhal_clock_funcs_t FUNCS_WDCSEL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_wdcsel,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_wdcsel,
    .set_source = _cyhal_clock_set_source_wdcsel,
};
#endif
#endif

#if (EXCO_PLL_PRESENT > 0)
static const cyhal_clock_funcs_t FUNCS_PLL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_pll,
    .set_enabled = _cyhal_clock_set_enabled_pll,
    .get_frequency = _cyhal_clock_get_frequency_pll,
    .set_frequency = _cyhal_clock_set_frequency_pll,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_pll,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_PLLSEL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_pllsel,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_pllsel,
    .set_source = _cyhal_clock_set_source_pllsel,
};
#endif

static const cyhal_clock_funcs_t FUNCS_LF =
{
    .features = CYHAL_CLOCK_FEATURE_NONE,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_lf,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_lf,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_HF =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_hf,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_hf,
    .get_sources = _cyhal_clock_get_sources_hf,
    .set_source = _cyhal_clock_set_source_hf,
};

static const cyhal_clock_funcs_t FUNCS_PUMP =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_SOURCE),
    .is_enabled = _cyhal_clock_is_enabled_pump,
    .set_enabled = _cyhal_clock_set_enabled_pump,
    .get_frequency = _cyhal_clock_get_frequency_pump,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_pump,
    .set_source = _cyhal_clock_set_source_pump,
};

static const cyhal_clock_funcs_t FUNCS_SYS =
{
    .features = CYHAL_CLOCK_FEATURE_DIVIDER,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_sys,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_sys,
    .get_sources = _cyhal_clock_get_sources_sys,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_PERIPHERAL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_peripheral,
    .set_enabled = _cyhal_clock_set_enabled_peripheral,
    .get_frequency = _cyhal_clock_get_frequency_peripheral,
    .set_frequency = _cyhal_clock_set_frequency_peripheral,
    .set_divider = _cyhal_clock_set_divider_peripheral,
    .get_sources = _cyhal_clock_get_sources_peripheral,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t* _cyhal_clock_get_funcs_all(cyhal_clock_block_t block)
{
	switch (block)
	{
		case CYHAL_CLOCK_BLOCK_IMO:
			return &FUNCS_IMO;
		case CYHAL_CLOCK_BLOCK_EXT:
			return &FUNCS_EXT;
		case CYHAL_CLOCK_BLOCK_ILO:
			return &FUNCS_ILO;

#if defined(CY_IP_M0S8EXCO)
		case CYHAL_CLOCK_BLOCK_ECO:
			return &FUNCS_ECO;
#endif
#if defined(CY_IP_M0S8WCO)
		case CYHAL_CLOCK_BLOCK_WCO:
			return &FUNCS_WCO;
#if (WCO_WDT_EN == 1)
		case CYHAL_CLOCK_BLOCK_WDCSEL:
			return &FUNCS_WDCSEL;
#endif
#endif

#if (EXCO_PLL_PRESENT > 0)
		case CYHAL_CLOCK_BLOCK_PLL:
			return &FUNCS_PLL;
		case CYHAL_CLOCK_BLOCK_PLLSEL:
			return &FUNCS_PLLSEL;
#endif
		case CYHAL_CLOCK_BLOCK_LF:
			return &FUNCS_LF;
		case CYHAL_CLOCK_BLOCK_HF:
			return &FUNCS_HF;
		case CYHAL_CLOCK_BLOCK_PUMP:
			return &FUNCS_PUMP;
		case CYHAL_CLOCK_BLOCK_SYS:
			return &FUNCS_SYS;
		default:
			return &FUNCS_PERIPHERAL;
	}
}






#define _CYHAL_CLOCK_CREATE(x,y)	{ .block = (CYHAL_CLOCK_BLOCK_##x), .channel = (y), .reserved = false, .funcs = &(FUNCS_##x) }

const cyhal_clock_t CYHAL_CLOCK_IMO = _CYHAL_CLOCK_CREATE(IMO, 0);
const cyhal_clock_t CYHAL_CLOCK_EXT = _CYHAL_CLOCK_CREATE(EXT, 0);
const cyhal_clock_t CYHAL_CLOCK_ILO = _CYHAL_CLOCK_CREATE(ILO, 0);

#if defined(CY_IP_M0S8EXCO)
const cyhal_clock_t CYHAL_CLOCK_ECO = _CYHAL_CLOCK_CREATE(ECO, 0);
#endif
#if defined(CY_IP_M0S8WCO)
const cyhal_clock_t CYHAL_CLOCK_WCO = _CYHAL_CLOCK_CREATE(WCO, 0);
#if (WCO_WDT_EN == 1)
const cyhal_clock_t CYHAL_CLOCK_WDCSEL = _CYHAL_CLOCK_CREATE(WDCSEL, 0);
#endif
#endif

#if (EXCO_PLL_PRESENT > 0)
const cyhal_clock_t CYHAL_CLOCK_PLL = _CYHAL_CLOCK_CREATE(PLL, 0);
const cyhal_clock_t CYHAL_CLOCK_PLLSEL = _CYHAL_CLOCK_CREATE(PLLSEL, 0);
#endif

const cyhal_clock_t CYHAL_CLOCK_LF = _CYHAL_CLOCK_CREATE(LF, 0);
const cyhal_clock_t CYHAL_CLOCK_HF = _CYHAL_CLOCK_CREATE(HF, 0);
const cyhal_clock_t CYHAL_CLOCK_PUMP = _CYHAL_CLOCK_CREATE(PUMP, 0);
const cyhal_clock_t CYHAL_CLOCK_SYS = _CYHAL_CLOCK_CREATE(SYS, 0);


/******************************************************************************
 **************************** Public API (clocks) *****************************
 *****************************************************************************/

cy_rslt_t cyhal_clock_allocate(cyhal_clock_t *clock, cyhal_clock_block_t block)
{
    CY_ASSERT(NULL != clock);

    if (block > CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
    {
        return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
    }

    uint8_t maxChannels = (uint8_t)_cyhal_utils_get_clock_count(block);
    for (uint8_t i = 0; i < maxChannels; i++)
    {
        cyhal_resource_inst_t clock_resource = { CYHAL_RSC_CLOCK, block, i };
        if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&clock_resource))
        {
            clock->block = block;
            clock->channel = i;
            clock->reserved = true;
            clock->funcs = &FUNCS_PERIPHERAL;
            return CY_RSLT_SUCCESS;
        }
    }
    return CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
}


cy_rslt_t cyhal_clock_get(cyhal_clock_t *clock, const cyhal_resource_inst_t *resource)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(NULL != resource);
    CY_ASSERT(CYHAL_RSC_CLOCK == resource->type);

    clock->block = (cyhal_clock_block_t)resource->block_num;
    clock->channel = resource->channel_num;
    clock->reserved = false;
    clock->funcs = _cyhal_clock_get_funcs_all(clock->block);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_clock_reserve(cyhal_clock_t *clock, const cyhal_clock_t *clock_)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(NULL != clock_);

    cyhal_resource_inst_t clock_resource = { CYHAL_RSC_CLOCK, clock_->block, clock_->channel };
    cy_rslt_t rslt = cyhal_hwmgr_reserve(&clock_resource);
    if (CY_RSLT_SUCCESS == rslt)
    {
        memcpy(clock, clock_, sizeof(cyhal_clock_t));
        clock->reserved = true;
    }
    return rslt;
}

cyhal_clock_feature_t cyhal_clock_get_features(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY)
        : ((cyhal_clock_funcs_t*)clock->funcs)->features;
}

bool cyhal_clock_is_enabled(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? _cyhal_clock_is_enabled_peripheral(clock)
        : ((cyhal_clock_funcs_t*)clock->funcs)->is_enabled(clock);
}

cy_rslt_t cyhal_clock_set_enabled(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_ASSERT(NULL != clock);

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? _cyhal_clock_set_enabled_peripheral(clock, enabled, wait_for_lock)
        : ((cyhal_clock_funcs_t*)clock->funcs)->set_enabled(clock, enabled, wait_for_lock);
}

uint32_t cyhal_clock_get_frequency(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    if (cyhal_clock_is_enabled(clock))
    {
        return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
            ? _cyhal_clock_get_frequency_peripheral(clock)
            : ((cyhal_clock_funcs_t*)clock->funcs)->get_frequency(clock);
    }
    return 0;
}

cy_rslt_t cyhal_clock_set_frequency(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_ASSERT(NULL != clock);

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? _cyhal_clock_set_frequency_peripheral(clock, hz, tolerance)
        : ((cyhal_clock_funcs_t*)clock->funcs)->set_frequency(clock, hz, tolerance);
}

cy_rslt_t cyhal_clock_set_divider(cyhal_clock_t *clock, uint32_t divider)
{
    CY_ASSERT(NULL != clock);

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? _cyhal_clock_set_divider_peripheral(clock, divider)
        : ((cyhal_clock_funcs_t*)clock->funcs)->set_divider(clock, divider);
}

cy_rslt_t cyhal_clock_get_sources(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_ASSERT(NULL != clock);

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? _cyhal_clock_get_sources_peripheral(clock, sources, count)
        : ((cyhal_clock_funcs_t*)clock->funcs)->get_sources(clock, sources, count);
}

cy_rslt_t cyhal_clock_set_source(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_ASSERT((NULL != clock) && (NULL != source));

    return (clock->block <= CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT)
        ? _cyhal_clock_set_source_unsupported(clock, source)
        : ((cyhal_clock_funcs_t*)clock->funcs)->set_source(clock, source);
}

void cyhal_clock_free(cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(clock->reserved);

    cyhal_resource_inst_t rsc = { CYHAL_RSC_CLOCK, clock->block, clock->channel };
    cyhal_hwmgr_free(&rsc);
    clock->reserved = false;
}

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_CLOCK
