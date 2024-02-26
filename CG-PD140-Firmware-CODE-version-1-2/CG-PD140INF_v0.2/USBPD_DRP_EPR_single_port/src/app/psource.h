/******************************************************************************
* File Name: psource.h
*
* Description: This header file defines function prototypes for power provider
*              path control and fault detection as part of the PMG1 MCU USB-PD
*              DRP Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef _PSOURCE_H_
#define _PSOURCE_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/
#include <stdint.h>
#include "cybsp.h"
#include "config.h"
#include "psink.h"
#include "app.h"
#include "cy_sw_timer.h"
#include "cy_sw_timer_id.h"
#include "cy_usbpd_vbus_ctrl.h"
#define PPS_CF_VBUS_DECREMENT_STEP     (200u)   /**< VBUS decrement value on each Current foldback event */

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/

/**
 * @brief This function sets the VBus source voltage to the desired value. It
 * also updates the voltage thresholds associated with protection schemes such
 * as OVP and UVP.
 *
 * @param port Port index the function is performed for.
 * @param volt_mV Voltage in mV units.
 *
 * @return None
 */
void psrc_set_voltage(cy_stc_pdstack_context_t * context, uint16_t volt_mV);

/**
 * @brief This function gets the VBus source voltage that is currently
 * configured. This is different from the vbus_get_value() function which
 * measures the actual VBus voltage.
 *
 * @param port Port index the function is performed for.
 * @return Voltage in mV units.
 */
uint32_t psrc_get_voltage (cy_stc_pdstack_context_t *context);

/**
 * @brief This function sets the VBus source current limit. The current limits
 * are used to configure the current sensing circuits to trigger fault indication
 * in case of overload.
 *
 * @param port Port index the function is performed for.
 * @param cur_10mA Current in 10mA units.
 * @return None
 */
void psrc_set_current (cy_stc_pdstack_context_t *context, uint16_t cur_10mA);

/**
 * @brief This function enables the VBus power supply. The voltage and current
 * to be supplied would have been specified through the psrc_set_voltage() and
 * psrc_set_current() calls before the supply is enabled. The function returns
 * as soon as the supply enable operation has been started. The pwr_ready_handler
 * is expected to be called once VBus voltage has stabilized at the desired level.
 *
 * @param port Port index the function is performed for.
 * @param pwr_ready_handler Application handler callback function.
 * @return None
 */
void psrc_enable (cy_stc_pdstack_context_t * context,
        cy_pdstack_pwr_ready_cbk_t pwr_ready_handler);

/**
 * @brief This function disables the VBus power supply. If a non-NULL
 * pwr_ready_handler callback is specified, the function can return after
 * starting the VBus disable operation. The callback will be called once
 * the VBus voltage has been safely brought to vSafe0V. If the callback
 * is NULL, the function is expected to return after shutting down the supply
 * without initiating any VBus discharge sequence.
 *
 * @param port Port index the function is performed for.
 * @param pwr_ready_handler Application handler callback function.
 *
 * @return None
 */
void psrc_disable(cy_stc_pdstack_context_t * context, cy_pdstack_pwr_ready_cbk_t pwr_ready_handler);

#endif /* _PSOURCE_H_ */

/* End of File */

