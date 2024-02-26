/***************************************************************************//**
* \file cyhal_triggers_psoc4000s.c
*
* \brief
* PSoC4000S family HAL triggers header
*
********************************************************************************
* \copyright
* (c) (2016-2021), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

#include "cy_device_headers.h"
#include "cyhal_hw_types.h"

#ifdef CY_DEVICE_PSOC4AS1
#include "triggers/cyhal_triggers_psoc4000s.h"

const uint16_t cyhal_sources_per_mux[1] =
{
    18, 
};

const bool cyhal_is_mux_1to1[1] =
{
    false, 
};

const _cyhal_trigger_source_psoc4000s_t cyhal_mux0_sources[18] =
{
    _CYHAL_TRIGGER_CPUSS_ZERO,
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0,
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1,
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2,
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3,
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4,
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0,
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1,
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2,
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3,
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4,
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0,
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1,
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2,
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3,
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4,
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT0,
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT1,
};

const _cyhal_trigger_source_psoc4000s_t* cyhal_mux_to_sources[1] =
{
    cyhal_mux0_sources, 
};

const uint8_t cyhal_dest_to_mux[2] =
{
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN12 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN13 */
};

const uint8_t cyhal_mux_dest_index[2] =
{
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN12 */
    1, /* CYHAL_TRIGGER_TCPWM_TR_IN13 */
};

#endif /* CY_DEVICE_PSOC4AS1 */
