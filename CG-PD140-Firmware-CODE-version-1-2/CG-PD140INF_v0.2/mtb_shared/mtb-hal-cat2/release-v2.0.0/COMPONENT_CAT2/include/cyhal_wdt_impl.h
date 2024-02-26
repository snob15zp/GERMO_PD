/***************************************************************************//**
* \file cyhal_wdt_impl.h
*
* \brief
* CAT2 (PMG/PSoC™ 4) specific implementation for WDT API.
*
********************************************************************************
* \copyright
* Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
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

/**
* \addtogroup group_hal_impl_wdt WDT (Watchdog Timer)
* \ingroup group_hal_impl
* \{
* The CAT2 (PMG/PSoC™ 4) WDT is only capable of supporting certain timeout ranges below its maximum timeout.
* As a result, any unsupported timeouts given to the HAL WDT are rounded up to the nearest supported value.
* The following table describes the unsupported ranges and the timeout values they are rounded to.
*
* <table class="doxtable">
*   <tr><th>Range (ms)</th><th>Rounded Timeout (ms)</th></tr>
*   <tr>
*     <td>2458 - 3276</td>
*     <td>3277</td>
*   </tr>
*   <tr>
*     <td>1229 - 1638</td>
*     <td>1639</td>
*   </tr>
*   <tr>
*     <td>615 - 819</td>
*     <td>820</td>
*   </tr>
*   <tr>
*     <td>308 - 409</td>
*     <td>410</td>
*   </tr>
*   <tr>
*     <td>154 - 204</td>
*     <td>205</td>
*   </tr>
*   <tr>
*     <td>77 - 102</td>
*     <td>103</td>
*   </tr>
*   <tr>
*     <td>39 - 51</td>
*     <td>52</td>
*   </tr>
*   <tr>
*     <td>20 - 25</td>
*     <td>26</td>
*   </tr>
*   <tr>
*     <td>10 - 12</td>
*     <td>13</td>
*   </tr>
*   <tr>
*     <td>5 - 6</td>
*     <td>7</td>
*   </tr>
*   <tr>
*     <td>3 - 3</td>
*     <td>4</td>
*   </tr>
* </table>
* \} group_hal_impl_wdt
*/

#include "cyhal_wdt_impl_common.h"
#include "cyhal_hw_resources.h"

#if (CYHAL_DRIVER_AVAILABLE_WDT)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
* \cond INTERNAL
*/

// (2^16 * 3) * .025 ms
/** Maximum WDT timeout in milliseconds */
#define _CYHAL_WDT_MAX_TIMEOUT_MS 4915

/** Maximum number of ignore bits */
#define _CYHAL_WDT_MAX_IGNORE_BITS 12

/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // CYHAL_DRIVER_AVAILABLE_WDT
