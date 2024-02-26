/*******************************************************************************
* File Name: cyhal_clock_impl.h
*
* Description:
* CAT2 (PMG/PSoC™ 4) specific implementation for clocks API.
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

#pragma once

#include "cyhal_hw_resources.h"

#if (CYHAL_DRIVER_AVAILABLE_CLOCK)

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * \addtogroup group_hal_impl_clock Clocks
 * \ingroup group_hal_impl
 * \{
 * Implementation specific interface for using the Clock driver. These items, while usable
 * within the HAL, are <b>not</b> necessarily portable between devices. The diagram below
 * shows how the clocks relate to each other. This is a superset of what is available. See
 * the device specific Data Sheet for the exact set of clocks that are available on a
 * specific device.
 *
 * \image html m0s8_clock_tree.png
 *
 * \section section_clock_snippets_impl Code snippets
 * \note Error handling code has been intentionally left out of snippets to highlight API usage.
 *
 * \subsection subsection_clock_snippet_5_impl Snippet: System initialization
 * The following snippet shows the clock driver can be used to initialize all clocks in the system.
 * \note This example is device specific.
 * \snippet hal_clock.c snippet_cyhal_clock_system_init_p4
 */

/** Internal Main Oscillator: This is a fixed-frequency clock that is commonly used as a general purpose source for clocks that do not require specific frequencies or very high accuracy. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_IMO;
/** Internal Main Oscillator: This is a fixed-frequency clock that is commonly used as a general purpose source for clocks that do not require specific frequencies or very high accuracy. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_IMO;

/** External Clock: This is an off-chip clock (not an oscillator). This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_EXT;
/** External Clock: This is an off-chip clock (not an oscillator). This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_EXT;

/** Internal Low Speed Oscillator: This is a low accuracy fixed-frequency clock in the kilohertz range that is available in sleep, deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_ILO;
/** Internal Low Speed Oscillator: This is a low accuracy fixed-frequency clock in the kilohertz range that is available in sleep, deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ILO;

#if defined(CY_IP_M0S8EXCO)
/** External Crystal Oscillator: This is an off-chip clock source that is used when specific frequencies and/or very high accuracy is required. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_ECO;
/** External Crystal Oscillator: This is an off-chip clock source that is used when specific frequencies and/or very high accuracy is required. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ECO;
#endif

#if defined(CY_IP_M0S8WCO)
/** Watch Crystal Oscillator: This source is driven from an off-chip watch crystal that provides an extremely accurate source. This clock is stopped in the hibernate power mode. */
extern const cyhal_clock_t CYHAL_CLOCK_WCO;
/** Watch Crystal Oscillator: This source is driven from an off-chip watch crystal that provides an extremely accurate source. This clock is stopped in the hibernate power mode. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_WCO;

#if (WCO_WDT_EN == 1)
/** WDC mux selection: A clock source for the Watch Dog Counters. It is recommended to stop any running LPTimer
    instances before changing this source. If this selection is changed while an LPTimer is running, call
    \ref cyhal_lptimer_reload after changing the source. */
extern const cyhal_clock_t CYHAL_CLOCK_WDCSEL;
/** WDC mux selection: A clock source for the Watch Dog Counters. It is recommended to stop any running LPTimer
    instances before changing this source. If this selection is changed while an LPTimer is running, call
    \ref cyhal_lptimer_reload after changing the source. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_WDCSEL;
#endif
#endif

#if (EXCO_PLL_PRESENT > 0)
/** Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_PLL;
/** Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL;

/** PLL mux selection: A clock source for the PLL. */
extern const cyhal_clock_t CYHAL_CLOCK_PLLSEL;
/** PLL mux selection: A clock source for the PLL. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLLSEL;
#endif

/** Low Frequency Clock: This clock is the source for the multi-counter watchdog timers (MCWDT), and can also be a source for the RTC. */
extern const cyhal_clock_t CYHAL_CLOCK_LF;
/** Low Frequency Clock: This clock is the source for the multi-counter watchdog timers (MCWDT), and can also be a source for the RTC. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_LF;

/** High Frequency Clock: A high-frequency clock output driving specific peripherals. */
extern const cyhal_clock_t CYHAL_CLOCK_HF;
/** High Frequency Clock: A high-frequency clock output driving specific peripherals. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_HF;

/** Analog Pump Clock: This clock ensures precision analog performance in low voltage applications. */
extern const cyhal_clock_t CYHAL_CLOCK_PUMP;
/** Analog Pump Clock: This clock ensures precision analog performance in low voltage applications. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PUMP;

/** System Clock: This is the source clock for any divided clock in the design. */
extern const cyhal_clock_t CYHAL_CLOCK_SYS;
/** System Clock: This is the source clock for any divided clock in the design. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_SYS;

/** \} group_hal_impl_clock */

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_CLOCK
