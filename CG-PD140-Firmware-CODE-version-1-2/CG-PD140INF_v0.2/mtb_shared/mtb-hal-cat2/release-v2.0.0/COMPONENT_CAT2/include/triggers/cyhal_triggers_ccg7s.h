/***************************************************************************//**
* \file cyhal_triggers_ccg7s.h
*
* \brief
* CCG7S family HAL triggers header
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

#ifndef _CYHAL_TRIGGERS_CCG7S_H_
#define _CYHAL_TRIGGERS_CCG7S_H_

/**
 * \addtogroup group_hal_impl_triggers_ccg7s CCG7S
 * \ingroup group_hal_impl_triggers
 * \{
 * Trigger connections for ccg7s
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** \cond INTERNAL */
/** @brief Name of each input trigger. */
typedef enum
{
    _CYHAL_TRIGGER_CPUSS_ZERO = 0, //!< cpuss.zero
    _CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE = 1, //!< pass[0].dsi_sar_sample_done
    _CYHAL_TRIGGER_PASS0_TR_SAR_OUT = 2, //!< pass[0].tr_sar_out
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0 = 3, //!< tcpwm.tr_compare_match[0]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1 = 4, //!< tcpwm.tr_compare_match[1]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2 = 5, //!< tcpwm.tr_compare_match[2]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3 = 6, //!< tcpwm.tr_compare_match[3]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0 = 7, //!< tcpwm.tr_overflow[0]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1 = 8, //!< tcpwm.tr_overflow[1]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2 = 9, //!< tcpwm.tr_overflow[2]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3 = 10, //!< tcpwm.tr_overflow[3]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0 = 11, //!< tcpwm.tr_underflow[0]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1 = 12, //!< tcpwm.tr_underflow[1]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2 = 13, //!< tcpwm.tr_underflow[2]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3 = 14, //!< tcpwm.tr_underflow[3]
    _CYHAL_TRIGGER_USBPD0_TR_OUT_0 = 15, //!< usbpd[0].tr_out_0
    _CYHAL_TRIGGER_USBPD0_TR_OUT_1 = 16, //!< usbpd[0].tr_out_1
    _CYHAL_TRIGGER_USBPD0_TR_OUT_2 = 17, //!< usbpd[0].tr_out_2
    _CYHAL_TRIGGER_USBPD0_TR_OUT_3 = 18, //!< usbpd[0].tr_out_3
    _CYHAL_TRIGGER_USBPD0_TR_OUT_4 = 19, //!< usbpd[0].tr_out_4
    _CYHAL_TRIGGER_USBPD0_TR_OUT_5 = 20, //!< usbpd[0].tr_out_5
    _CYHAL_TRIGGER_USBPD0_TR_OUT_6 = 21, //!< usbpd[0].tr_out_6
} _cyhal_trigger_source_ccg7s_t;

/** Typedef for internal device family specific trigger source to generic trigger source */
typedef _cyhal_trigger_source_ccg7s_t cyhal_internal_source_t;

/** @brief Get a public source signal type (cyhal_trigger_source_ccg7s_t) given an internal source signal and signal type */
#define _CYHAL_TRIGGER_CREATE_SOURCE(src, type)    ((src) << 1 | (type))
/** @brief Get an internal source signal (_cyhal_trigger_source_ccg7s_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_SIGNAL(src)      ((cyhal_internal_source_t)((src) >> 1))
/** @brief Get the signal type (cyhal_signal_type_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_TYPE(src)        ((cyhal_signal_type_t)((src) & 1))
/** \endcond */

/** @brief Name of each input trigger. */
typedef enum
{
    CYHAL_TRIGGER_CPUSS_ZERO_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.zero
    CYHAL_TRIGGER_CPUSS_ZERO_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_LEVEL), //!< cpuss.zero
    CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].dsi_sar_sample_done
    CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].dsi_sar_sample_done
    CYHAL_TRIGGER_PASS0_TR_SAR_OUT_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_OUT, CYHAL_SIGNAL_TYPE_EDGE), //!< pass[0].tr_sar_out
    CYHAL_TRIGGER_PASS0_TR_SAR_OUT_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_PASS0_TR_SAR_OUT, CYHAL_SIGNAL_TYPE_LEVEL), //!< pass[0].tr_sar_out
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[0]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[0]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[1]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[1]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[2]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[2]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[3]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[3]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[0]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[0]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[1]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[1]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[2]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[2]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[3]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[3]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[0]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[0]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[1]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[1]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[2]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[2]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[3]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[3]
    CYHAL_TRIGGER_USBPD0_TR_OUT_0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_0, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_0
    CYHAL_TRIGGER_USBPD0_TR_OUT_0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_0, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_0
    CYHAL_TRIGGER_USBPD0_TR_OUT_1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_1, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_1
    CYHAL_TRIGGER_USBPD0_TR_OUT_1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_1, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_1
    CYHAL_TRIGGER_USBPD0_TR_OUT_2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_2, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_2
    CYHAL_TRIGGER_USBPD0_TR_OUT_2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_2, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_2
    CYHAL_TRIGGER_USBPD0_TR_OUT_3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_3, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_3
    CYHAL_TRIGGER_USBPD0_TR_OUT_3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_3, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_3
    CYHAL_TRIGGER_USBPD0_TR_OUT_4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_4, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_4
    CYHAL_TRIGGER_USBPD0_TR_OUT_4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_4, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_4
    CYHAL_TRIGGER_USBPD0_TR_OUT_5_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_5, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_5
    CYHAL_TRIGGER_USBPD0_TR_OUT_5_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_5, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_5
    CYHAL_TRIGGER_USBPD0_TR_OUT_6_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_6, CYHAL_SIGNAL_TYPE_EDGE), //!< usbpd[0].tr_out_6
    CYHAL_TRIGGER_USBPD0_TR_OUT_6_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_USBPD0_TR_OUT_6, CYHAL_SIGNAL_TYPE_LEVEL), //!< usbpd[0].tr_out_6
} cyhal_trigger_source_ccg7s_t;

/** Typedef from device family specific trigger source to generic trigger source */
typedef cyhal_trigger_source_ccg7s_t cyhal_source_t;

/** Deprecated defines for signals that can be either level or edge. */
#define CYHAL_TRIGGER_CPUSS_ZERO (CYHAL_TRIGGER_CPUSS_ZERO_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE (CYHAL_TRIGGER_PASS0_DSI_SAR_SAMPLE_DONE_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_PASS0_TR_SAR_OUT (CYHAL_TRIGGER_PASS0_TR_SAR_OUT_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_0 (CYHAL_TRIGGER_USBPD0_TR_OUT_0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_1 (CYHAL_TRIGGER_USBPD0_TR_OUT_1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_2 (CYHAL_TRIGGER_USBPD0_TR_OUT_2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_3 (CYHAL_TRIGGER_USBPD0_TR_OUT_3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_4 (CYHAL_TRIGGER_USBPD0_TR_OUT_4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_5 (CYHAL_TRIGGER_USBPD0_TR_OUT_5_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_USBPD0_TR_OUT_6 (CYHAL_TRIGGER_USBPD0_TR_OUT_6_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.

/** @brief Name of each output trigger. */
typedef enum
{
    CYHAL_TRIGGER_PASS0_TR_SAR_IN = 0, //!< PASS Triggers - pass[0].tr_sar_in
    CYHAL_TRIGGER_TCPWM_TR_IN8 = 1, //!< TCPWM Triggers - tcpwm.tr_in[8]
    CYHAL_TRIGGER_TCPWM_TR_IN9 = 2, //!< TCPWM Triggers - tcpwm.tr_in[9]
    CYHAL_TRIGGER_TCPWM_TR_IN10 = 3, //!< TCPWM Triggers - tcpwm.tr_in[10]
    CYHAL_TRIGGER_TCPWM_TR_IN11 = 4, //!< TCPWM Triggers - tcpwm.tr_in[11]
    CYHAL_TRIGGER_TCPWM_TR_IN12 = 5, //!< TCPWM Triggers - tcpwm.tr_in[12]
    CYHAL_TRIGGER_TCPWM_TR_IN13 = 6, //!< TCPWM Triggers - tcpwm.tr_in[13]
} cyhal_trigger_dest_ccg7s_t;

/** Typedef from device family specific trigger dest to generic trigger dest */
typedef cyhal_trigger_dest_ccg7s_t cyhal_dest_t;

/** \cond INTERNAL */
/** Table of number of inputs to each mux. */
extern const uint16_t cyhal_sources_per_mux[2];

/** Table indicating whether mux is 1to1. */
extern const bool cyhal_is_mux_1to1[2];

/** Table pointing to each mux source table. The index of each source in the table is its mux input index. */
extern const _cyhal_trigger_source_ccg7s_t* cyhal_mux_to_sources [2];

/** Maps each cyhal_destination_t to a mux index.
 * If bit 8 of the mux index is set, this denotes that the trigger is a
 * one to one trigger.
 */
extern const uint8_t cyhal_dest_to_mux[7];

/* Maps each cyhal_destination_t to a specific output in its mux */
extern const uint8_t cyhal_mux_dest_index[7];
/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/** \} group_hal_impl_triggers_ccg7s */
#endif /* _CYHAL_TRIGGERS_CCG7S_H_ */


/* [] END OF FILE */
