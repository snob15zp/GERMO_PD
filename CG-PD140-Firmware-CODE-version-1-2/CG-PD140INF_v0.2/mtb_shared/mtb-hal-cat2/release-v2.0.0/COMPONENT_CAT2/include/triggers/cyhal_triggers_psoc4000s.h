/***************************************************************************//**
* \file cyhal_triggers_psoc4000s.h
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

#ifndef _CYHAL_TRIGGERS_PSOC4000S_H_
#define _CYHAL_TRIGGERS_PSOC4000S_H_

/**
 * \addtogroup group_hal_impl_triggers_psoc4000s PSOC4000S
 * \ingroup group_hal_impl_triggers
 * \{
 * Trigger connections for psoc4000s
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** \cond INTERNAL */
/** @brief Name of each input trigger. */
typedef enum
{
    _CYHAL_TRIGGER_CPUSS_ZERO = 0, //!< cpuss.zero
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT0 = 1, //!< lpcomp.comp_out[0]
    _CYHAL_TRIGGER_LPCOMP_COMP_OUT1 = 2, //!< lpcomp.comp_out[1]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0 = 3, //!< tcpwm.tr_compare_match[0]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1 = 4, //!< tcpwm.tr_compare_match[1]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2 = 5, //!< tcpwm.tr_compare_match[2]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3 = 6, //!< tcpwm.tr_compare_match[3]
    _CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4 = 7, //!< tcpwm.tr_compare_match[4]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0 = 8, //!< tcpwm.tr_overflow[0]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1 = 9, //!< tcpwm.tr_overflow[1]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2 = 10, //!< tcpwm.tr_overflow[2]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3 = 11, //!< tcpwm.tr_overflow[3]
    _CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4 = 12, //!< tcpwm.tr_overflow[4]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0 = 13, //!< tcpwm.tr_underflow[0]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1 = 14, //!< tcpwm.tr_underflow[1]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2 = 15, //!< tcpwm.tr_underflow[2]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3 = 16, //!< tcpwm.tr_underflow[3]
    _CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4 = 17, //!< tcpwm.tr_underflow[4]
} _cyhal_trigger_source_psoc4000s_t;

/** Typedef for internal device family specific trigger source to generic trigger source */
typedef _cyhal_trigger_source_psoc4000s_t cyhal_internal_source_t;

/** @brief Get a public source signal type (cyhal_trigger_source_psoc4000s_t) given an internal source signal and signal type */
#define _CYHAL_TRIGGER_CREATE_SOURCE(src, type)    ((src) << 1 | (type))
/** @brief Get an internal source signal (_cyhal_trigger_source_psoc4000s_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_SIGNAL(src)      ((cyhal_internal_source_t)((src) >> 1))
/** @brief Get the signal type (cyhal_signal_type_t) given a public source signal. */
#define _CYHAL_TRIGGER_GET_SOURCE_TYPE(src)        ((cyhal_signal_type_t)((src) & 1))
/** \endcond */

/** @brief Name of each input trigger. */
typedef enum
{
    CYHAL_TRIGGER_CPUSS_ZERO_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_EDGE), //!< cpuss.zero
    CYHAL_TRIGGER_CPUSS_ZERO_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_ZERO, CYHAL_SIGNAL_TYPE_LEVEL), //!< cpuss.zero
    CYHAL_TRIGGER_LPCOMP_COMP_OUT0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_LPCOMP_COMP_OUT0, CYHAL_SIGNAL_TYPE_EDGE), //!< lpcomp.comp_out[0]
    CYHAL_TRIGGER_LPCOMP_COMP_OUT0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_LPCOMP_COMP_OUT0, CYHAL_SIGNAL_TYPE_LEVEL), //!< lpcomp.comp_out[0]
    CYHAL_TRIGGER_LPCOMP_COMP_OUT1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_LPCOMP_COMP_OUT1, CYHAL_SIGNAL_TYPE_EDGE), //!< lpcomp.comp_out[1]
    CYHAL_TRIGGER_LPCOMP_COMP_OUT1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_LPCOMP_COMP_OUT1, CYHAL_SIGNAL_TYPE_LEVEL), //!< lpcomp.comp_out[1]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[0]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[0]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[1]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[1]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[2]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[2]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[3]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[3]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_compare_match[4]
    CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_compare_match[4]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[0]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[0]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[1]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[1]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[2]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[2]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[3]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[3]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_overflow[4]
    CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_overflow[4]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[0]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[0]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[1]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[1]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[2]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[2]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[3]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[3]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4_EDGE = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4, CYHAL_SIGNAL_TYPE_EDGE), //!< tcpwm.tr_underflow[4]
    CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4_LEVEL = _CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4, CYHAL_SIGNAL_TYPE_LEVEL), //!< tcpwm.tr_underflow[4]
} cyhal_trigger_source_psoc4000s_t;

/** Typedef from device family specific trigger source to generic trigger source */
typedef cyhal_trigger_source_psoc4000s_t cyhal_source_t;

/** Deprecated defines for signals that can be either level or edge. */
#define CYHAL_TRIGGER_CPUSS_ZERO (CYHAL_TRIGGER_CPUSS_ZERO_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_LPCOMP_COMP_OUT0 (CYHAL_TRIGGER_LPCOMP_COMP_OUT0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_LPCOMP_COMP_OUT1 (CYHAL_TRIGGER_LPCOMP_COMP_OUT1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4 (CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4 (CYHAL_TRIGGER_TCPWM_TR_OVERFLOW4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW1_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW2_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW3_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.
#define CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4 (CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW4_LEVEL) //!< Legacy define. Instead, use the explicit _LEVEL or _EDGE version.

/** @brief Name of each output trigger. */
typedef enum
{
    CYHAL_TRIGGER_TCPWM_TR_IN12 = 0, //!< TCPWM Triggers - tcpwm.tr_in[12]
    CYHAL_TRIGGER_TCPWM_TR_IN13 = 1, //!< TCPWM Triggers - tcpwm.tr_in[13]
} cyhal_trigger_dest_psoc4000s_t;

/** Typedef from device family specific trigger dest to generic trigger dest */
typedef cyhal_trigger_dest_psoc4000s_t cyhal_dest_t;

/** \cond INTERNAL */
/** Table of number of inputs to each mux. */
extern const uint16_t cyhal_sources_per_mux[1];

/** Table indicating whether mux is 1to1. */
extern const bool cyhal_is_mux_1to1[1];

/** Table pointing to each mux source table. The index of each source in the table is its mux input index. */
extern const _cyhal_trigger_source_psoc4000s_t* cyhal_mux_to_sources [1];

/** Maps each cyhal_destination_t to a mux index.
 * If bit 8 of the mux index is set, this denotes that the trigger is a
 * one to one trigger.
 */
extern const uint8_t cyhal_dest_to_mux[2];

/* Maps each cyhal_destination_t to a specific output in its mux */
extern const uint8_t cyhal_mux_dest_index[2];
/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
/** \} group_hal_impl_triggers_psoc4000s */
#endif /* _CYHAL_TRIGGERS_PSOC4000S_H_ */


/* [] END OF FILE */
