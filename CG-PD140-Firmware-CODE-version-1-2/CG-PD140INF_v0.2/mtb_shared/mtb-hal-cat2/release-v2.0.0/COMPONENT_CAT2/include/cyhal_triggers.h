/***************************************************************************//**
* \file cyhal_triggers.h
*
* Description:
* Provides definitions for the triggers for each supported device family.
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
* \addtogroup group_hal_impl_triggers Triggers
* \ingroup group_hal_impl
* \{
* Trigger connections for supported device families
*/

#pragma once

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "cy_device.h"

#if defined(CY_DEVICE_PSOC4AS1)
#include "triggers/cyhal_triggers_psoc4000s.h"
#elif defined(CY_DEVICE_PSOC4AS2)
#include "triggers/cyhal_triggers_psoc4100s.h"
#elif defined(CY_DEVICE_PSOC4AS3)
#include "triggers/cyhal_triggers_psoc4100sp.h"
#elif defined(CY_DEVICE_PSOC4AS4)
#include "triggers/cyhal_triggers_psoc4100smax.h"
#elif defined(CY_DEVICE_PSOC4AMC)
#include "triggers/cyhal_triggers_psoc4100sp256kb.h"
#elif defined(CY_DEVICE_PMG1S3)
#include "triggers/cyhal_triggers_pmg1s3.h"
#elif defined(CY_DEVICE_CCG7S)
#include "triggers/cyhal_triggers_ccg7s.h"
#else
    /** Generic trigger source defined for devices that do not support trigger mux. */
    typedef uint32_t cyhal_source_t;

    /** Generic trigger destination defined for devices that do not support trigger mux. */
    typedef uint32_t cyhal_dest_t;
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_triggers */
