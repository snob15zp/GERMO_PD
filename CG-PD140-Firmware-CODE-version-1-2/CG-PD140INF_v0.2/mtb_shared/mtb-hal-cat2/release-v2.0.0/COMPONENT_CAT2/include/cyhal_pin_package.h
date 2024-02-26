/***************************************************************************//**
* \file cyhal_pin_package.h
*
* Description:
* Provides definitions for the pinout for each supported device.
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

/**
* \addtogroup group_hal_impl_pin_package Pins
* \ingroup group_hal_impl
* \{
* Definitions for the pinout for each supported device
*/

#pragma once

#include "cy_gpio.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** Port definitions that individual pins can belong to. */
typedef enum {
    CYHAL_PORT_0  = 0x00,
    CYHAL_PORT_1  = 0x01,
    CYHAL_PORT_2  = 0x02,
    CYHAL_PORT_3  = 0x03,
    CYHAL_PORT_4  = 0x04,
    CYHAL_PORT_5  = 0x05,
    CYHAL_PORT_6  = 0x06,
    CYHAL_PORT_7  = 0x07,
    CYHAL_PORT_8  = 0x08,
    CYHAL_PORT_9  = 0x09,
    CYHAL_PORT_10 = 0x0A,
    CYHAL_PORT_11 = 0x0B,
    CYHAL_PORT_12 = 0x0C,
    CYHAL_PORT_13 = 0x0D,
    CYHAL_PORT_14 = 0x0E,
    CYHAL_PORT_15 = 0x0F,
    CYHAL_PORT_16 = 0x10,
    CYHAL_PORT_17 = 0x11,
    CYHAL_PORT_18 = 0x12,
    CYHAL_PORT_19 = 0x13,
    CYHAL_PORT_20 = 0x14,
} cyhal_port_t;

#include "cy_device.h"

#if defined(_GPIO_PSOC4000S_20_SSOP_H_)
#include "pin_packages/cyhal_psoc4000s_20_ssop.h"
#elif defined(_GPIO_PSOC4000S_24_QFN_H_)
#include "pin_packages/cyhal_psoc4000s_24_qfn.h"
#elif defined(_GPIO_PSOC4000S_25_WLCSP_H_)
#include "pin_packages/cyhal_psoc4000s_25_wlcsp.h"
#elif defined(_GPIO_PSOC4000S_28_SSOP_AUTO_H_)
#include "pin_packages/cyhal_psoc4000s_28_ssop_auto.h"
#elif defined(_GPIO_PSOC4000S_32_QFN_H_)
#include "pin_packages/cyhal_psoc4000s_32_qfn.h"
#elif defined(_GPIO_PSOC4000S_32_TQFP_H_)
#include "pin_packages/cyhal_psoc4000s_32_tqfp.h"
#elif defined(_GPIO_PSOC4000S_40_QFN_H_)
#include "pin_packages/cyhal_psoc4000s_40_qfn.h"
#elif defined(_GPIO_PSOC4000S_48_TQFP_H_)
#include "pin_packages/cyhal_psoc4000s_48_tqfp.h"
#elif defined(_GPIO_PSOC4100S_28_SSOP_AUTO_H_)
#include "pin_packages/cyhal_psoc4100s_28_ssop_auto.h"
#elif defined(_GPIO_PSOC4100S_32_QFN_H_)
#include "pin_packages/cyhal_psoc4100s_24_qfn.h"
#elif defined(_GPIO_PSOC4100S_35_WLCSP_H_)
#include "pin_packages/cyhal_psoc4100s_35_wlcsp.h"
#elif defined(_GPIO_PSOC4100S_35_WLCSP_2_H_)
#include "pin_packages/cyhal_psoc4100s_35_wlcsp_2.h"
#elif defined(_GPIO_PSOC4100S_40_QFN_AUTO_H_)
#include "pin_packages/cyhal_psoc4100s_40_qfn_auto.h"
#elif defined(_GPIO_PSOC4100S_40_QFN_H_)
#include "pin_packages/cyhal_psoc4100s_40_qfn.h"
#elif defined(_GPIO_PSOC4100S_44_TQFP_H_)
#include "pin_packages/cyhal_psoc4100s_44_tqfp.h"
#elif defined(_GPIO_PSOC4100S_48_TQFP_H_)
#include "pin_packages/cyhal_psoc4100s_48_tqfp.h"
#elif defined(_GPIO_PSOC4100SP_40_QFN_2_H_)
#include "pin_packages/cyhal_psoc4100sp_40_qfn_2.h"
#elif defined(_GPIO_PSOC4100SP_44_TQFP_H_)
#include "pin_packages/cyhal_psoc4100sp_44_tqfp.h"
#elif defined(_GPIO_PSOC4100SP_48_TQFP_H_)
#include "pin_packages/cyhal_psoc4100sp_48_tqfp.h"
#elif defined(_GPIO_PSOC4100SP_64_QFN_H_)
#include "pin_packages/cyhal_psoc4100sp_64_qfn.h"
#elif defined(_GPIO_PSOC4100SP_64_TQFP_H_)
#include "pin_packages/cyhal_psoc4100sp_64_tqfp.h"
#elif defined(_GPIO_PSOC4100SP256KB_48_TQFP_MC_H_)
#include "pin_packages/cyhal_psoc4100sp256kb_48_tqfp_mc.h"
#elif defined(_GPIO_PSOC4100SP256KB_48_TQFP_H_)
#include "pin_packages/cyhal_psoc4100sp256kb_48_tqfp.h"
#elif defined(_GPIO_PSOC4100SP256KB_64_TQFP_MC_H_)
#include "pin_packages/cyhal_psoc4100sp256kb_64_tqfp_mc.h"
#elif defined(_GPIO_PSOC4100SP256KB_64_TQFP_H_)
#include "pin_packages/cyhal_psoc4100sp256kb_64_tqfp.h"
#elif defined(_GPIO_PSOC4100SMAX_48_TQFP_H_)
#include "pin_packages/cyhal_psoc4100smax_48_tqfp.h"
#elif defined(_GPIO_PSOC4100SMAX_64_TQFP_H_)
#include "pin_packages/cyhal_psoc4100smax_64_tqfp.h"
#elif defined(_GPIO_PSOC4100SMAX_100_TQFP_H_)
#include "pin_packages/cyhal_psoc4100smax_100_tqfp.h"
#elif defined(_GPIO_PMG1S0_24_QFN_PMG1_S0_H_)
#include "pin_packages/cyhal_pmg1s0_24_qfn_pmg1_s0.h"
#elif defined(_GPIO_PMG1S1_40_QFN_PMG1_S1_H_)
#include "pin_packages/cyhal_pmg1s1_40_qfn_pmg1_s1.h"
#elif defined(_GPIO_PMG1S2_40_QFN_PMG1_S2_H_)
#include "pin_packages/cyhal_pmg1s2_40_qfn_pmg1_s2.h"
#elif defined(_GPIO_PMG1S2_42_CSP_PMG1_S2_H_)
#include "pin_packages/cyhal_pmg1s2_42_csp_pmg1_s2.h"
#elif defined(_GPIO_PMG1S3_48_QFN_CYPM1311_H_)
#include "pin_packages/cyhal_pmg1s3_48_qfn_cypm1311.h"
#elif defined(_GPIO_PMG1S3_97_BGA_CYPD8225_H_)
#include "pin_packages/cyhal_pmg1s3_97_bga_cypd8225.h"
#elif defined(_GPIO_PMG1S3_97_BGA_CYPM1322_H_)
#include "pin_packages/cyhal_pmg1s3_97_bga_cypm1322.h"
#elif defined(_GPIO_CCG7S_40_QFN_H_)
#include "pin_packages/cyhal_ccg7s_40_qfn.h"
#elif defined(_GPIO_CCG7D_68_QFN_H_)
#include "pin_packages/cyhal_ccg7d_68_qfn.h"
#else
#error "Unhandled Device/PinPackage combination"
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl */
