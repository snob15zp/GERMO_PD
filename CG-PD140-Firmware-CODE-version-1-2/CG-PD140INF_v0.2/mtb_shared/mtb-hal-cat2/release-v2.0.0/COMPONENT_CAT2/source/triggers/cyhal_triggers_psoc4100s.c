/***************************************************************************//**
* \file cyhal_triggers_psoc4100s.c
*
* \brief
* PSoC4100S family HAL triggers header
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

#ifdef CY_DEVICE_PSOC4AS2
#include "triggers/cyhal_triggers_psoc4100s.h"

const uint16_t cyhal_sources_per_mux[2] =
{
    22, 22, 
};

const bool cyhal_is_mux_1to1[2] =
{
    false, false, 
};

const _cyhal_trigger_source_psoc4100s_t cyhal_mux0_sources[22] =
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
    _CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE,
    _CYHAL_TRIGGER_PASS0_TR_SAR_OUT,
    _CYHAL_TRIGGER_PASS0_DSI_CTB_CMP0,
    _CYHAL_TRIGGER_PASS0_DSI_CTB_CMP1,
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT0,
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT1,
};

const _cyhal_trigger_source_psoc4100s_t cyhal_mux1_sources[22] =
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
    _CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE,
    _CYHAL_TRIGGER_PASS0_TR_SAR_OUT,
    _CYHAL_TRIGGER_PASS0_DSI_CTB_CMP0,
    _CYHAL_TRIGGER_PASS0_DSI_CTB_CMP1,
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT0,
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT1,
};

const _cyhal_trigger_source_psoc4100s_t* cyhal_mux_to_sources[2] =
{
    cyhal_mux0_sources, 
    cyhal_mux1_sources, 
};

const uint8_t cyhal_dest_to_mux[8] =
{
    1, /* CYHAL_TRIGGER_PASS0_TR_SAR_IN */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN7 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN8 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN9 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN10 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN11 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN12 */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN13 */
};

const uint8_t cyhal_mux_dest_index[8] =
{
    0, /* CYHAL_TRIGGER_PASS0_TR_SAR_IN */
    0, /* CYHAL_TRIGGER_TCPWM_TR_IN7 */
    1, /* CYHAL_TRIGGER_TCPWM_TR_IN8 */
    2, /* CYHAL_TRIGGER_TCPWM_TR_IN9 */
    3, /* CYHAL_TRIGGER_TCPWM_TR_IN10 */
    4, /* CYHAL_TRIGGER_TCPWM_TR_IN11 */
    5, /* CYHAL_TRIGGER_TCPWM_TR_IN12 */
    6, /* CYHAL_TRIGGER_TCPWM_TR_IN13 */
};

#endif /* CY_DEVICE_PSOC4AS2 */
