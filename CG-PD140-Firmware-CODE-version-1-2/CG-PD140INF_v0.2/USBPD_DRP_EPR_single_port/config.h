/**
 * @file config.h
 *
 * @brief @{Header file that enables/disables various CCG firmware features.
 *
 * This file also provides mapping to the implementation for hardware dependent
 * functions like FET control, voltage selection etc.
 *
 * This current implementation matches the CY4531 EVK from Cypress. This can be
 * updated by users to match their hardware implementation.@}
 */

/*
 * Copyright (2014-2022), Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All rights reserved.
 *
 * This software, including source code, documentation and related materials
 * (“Software”), is owned by Cypress Semiconductor Corporation or one of its
 * subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
 * protection (United States and foreign), United States copyright laws and
 * international treaty provisions. Therefore, you may use this Software only
 * as provided in the license agreement accompanying the software package from
 * which you obtained this Software (“EULA”).
 *
 * If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
 * non-transferable license to copy, modify, and compile the Software source
 * code solely for use in connection with Cypress’s integrated circuit
 * products. Any reproduction, modification, translation, compilation, or
 * representation of this Software except as specified above is prohibited
 * without the express written permission of Cypress. Disclaimer: THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress reserves the
 * right to make changes to the Software without notice. Cypress does not
 * assume any liability arising out of the application or use of the Software
 * or any product or circuit described in the Software. Cypress does not
 * authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death (“High Risk Product”). By
 * including Cypress’s product in a High Risk Product, the manufacturer of such
 * system or application assumes all risk of such use and in doing so agrees to
 * indemnify Cypress against all liability.
 */
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "cybsp.h"
#include "ncp81239.h"
#include "cy_sw_timer_id.h"

/*******************************************************************************
 * Header files including
 ******************************************************************************/
#define DEBUG_LOG        (0u)

#ifndef CY_PD_SINK_ONLY
/* Restrict PD stack to sink operation. */
#define CY_PD_SINK_ONLY                           (0u)
#endif /* CY_PD_SINK_ONLY */

#ifndef NO_OF_TYPEC_PORTS
#define NO_OF_TYPEC_PORTS                         (CY_IP_MXUSBPD_INSTANCES)
#endif /* NO_OF_TYPEC_PORTS */

/*******************************************************************************
 * Enable PD spec Rev 3 support
 ******************************************************************************/
#ifndef CY_PD_REV3_ENABLE
#define CY_PD_REV3_ENABLE                        (1u)
#endif /* CY_PD_REV3_ENABLE */

#if CY_PD_REV3_ENABLE
    #define CY_PD_FRS_RX_ENABLE                   (0u)
    #define CY_PD_FRS_TX_ENABLE                   (0u)
    #define CY_PD_PPS_SRC_ENABLE                  (0u)
#endif /* CY_PD_REV3_ENABLE */

#define CCG_PROG_SOURCE_ENABLE                    (1u)


/* Enable hardware based DRP toggle for additional power saving. */
#define CY_PD_HW_DRP_TOGGLE_ENABLE                (0u)

/*
 * Macro defines additional delay in milliseconds before the PD stack starts sending
 * SRC_CAP message. This may be required to work with some non-compliant sink devices
 * which require more start up time for PD.
 */
#define DELAY_SRC_CAP_START_MS                  (100u)

#define PD_PDO_SEL_ALGO                         (0u)

/* This firmware supports only CCG controlled DP/USB switch operation. */
#define MUX_TYPE                                (3u)

/*******************************************************************************
 * PSOURCE controls for PD port 1.
 ******************************************************************************/

#define REGULATOR_REQUIRE_STABLE_ON_TIME           (0)
#define REGULATOR_ENABLE(port)                      false //UCK_BOOST_EN_C_Write(0)
#define REGULATOR_DISABLE(port)                     false //BUCK_BOOST_EN_C_Write(1)

#define REGULATOR_STATUS(port)                      false //(!BUCK_BOOST_EN_C_Read())

#define REGULATOR_TURN_ON_DELAY                     (50)    

/* VBUS PGDO FET Control selection based on the FET control pin used in the system hardware */
#define VBUS_FET_CTRL_0                             (1u)
#define VBUS_FET_CTRL_1                             (0u)

#define VBUS_FET_CTRL                               (VBUS_FET_CTRL_0)
/*
 * CCTRL is used for controlling the SRC direction as well. So using the
 * corresponding FET configuration. In source mode operation, OCP is controlled
 * by firmware and should not be controlled via PWM. So keep it disabled.
 */
#define APP_VBUS_SRC_FET_ON_P1()                    \
{                                                   \
    pd_internal_cfet_on(0, false);                  \
}

#if (!defined (CY_DEVICE_PMG1S3))
#define APP_VBUS_SET_VOLT_P1(volt_mV)               vbus_ctrl_fb_set_volt(TYPEC_PORT_0_IDX, volt_mV)
#endif /* (!defined (CY_DEVICE_PMG1S3)) */

#define APP_VBUS_SRC_FET_OFF_P1()                   \
{                                                   \
    pd_internal_cfet_off(0, false);                 \
}

/* Function/Macro to turn VBUS_DISCHARGE FET for P1 ON. */
#define APP_DISCHARGE_FET_ON_P1()                   pd_internal_vbus_discharge_on(0)

/* Function/Macro to turn VBUS_DISCHARGE FET for P1 OFF. */
#define APP_DISCHARGE_FET_OFF_P1()                  pd_internal_vbus_discharge_off(0)

/*******************************************************************************
 * PSOURCE controls for Port 2 (TYPE A port).
 ******************************************************************************/

#define APP_VBUS_SRC_FET_ON_P2()                    vbus_ctrl_pwm_turn_on(TYPEC_PORT_1_IDX)

#define APP_VBUS_SRC_FET_OFF_P2()                   //vbus_ctrl_pwm_turn_off(TYPEC_PORT_1_IDX)

/* Function/Macro to turn VBUS_DISCHARGE FET for P1 ON. */
#define APP_DISCHARGE_FET_ON_P2()                   ((void)0)

/* Function/Macro to turn VBUS_DISCHARGE FET for P2 OFF. */
#define APP_DISCHARGE_FET_OFF_P2()                  ((void)0)

#define APP_VBUS_POLL_ADC_ID                    (CY_USBPD_ADC_ID_0)

#define APP_VBUS_POLL_ADC_INPUT                 (CY_USBPD_ADC_INPUT_AMUX_B)


/*******************************************************************************
 * Power Sink (PSINK) controls for PD port 1.
 ******************************************************************************/

/* Function/Macro to turn consumer FET for P1 ON. */

/* Enable consumer direction, turn on Consumer FETs and enable Buck Boost converter. */
#define APP_VBUS_SNK_FET_ON_P1()                    \
{                                                   \
    pd_internal_cfet_on(0, false);                  \
}

/* Function/Macro to turn consumer FET for P1 OFF. */

/*
 * Disbale Buck Boost converter, turn off Consumer FETs, set direction to provider mode
 * and turn off PWM I which limits current consumption.
 */
#define APP_VBUS_SNK_FET_OFF_P1()                   \
{                                                   \
    pd_internal_cfet_off(0, false);                 \
}

#define APP_SINK_SET_CURRENT_P1(cur_10mA)           pb_typec_set_current(cur_10mA)



/*
 * Maximum voltage step in mV transition that can happen in one change when
 * upward voltage transition above 5V.
 */
#define VBUS_CTRL_ABOVE_5V_UP_MAX_STEP          (20000u)

/*
 * Maximum voltage step in mV transition that can happen in one change when
 * downward voltage transition above 5V.
 */
#define VBUS_CTRL_ABOVE_5V_DOWN_MAX_STEP        (20000u)

/*
 * Maximum voltage step in mV transition that can happen in one change when
 * upward voltage transition below 5V.
 */
#define VBUS_CTRL_BELOW_5V_UP_MAX_STEP          (5000u)

/*
 * Maximum voltage step in mV transition that can happen in one change when
 * downward voltage transition below 5V.
 */
#define VBUS_CTRL_BELOW_5V_DOWN_MAX_STEP        (5000u)

/* 
 * Enable this macro if the interval between steps need to be done in micro-
 * seconds. This may be required if the regulator is very sensitive to feedback
 * node change. This will allow for smaller feedback voltage step size. When
 * enabling this feature, a TCPWM timer should be added with TC interrupt 
 * configured for one-shot timer interrupting with the required interval as
 * period. The minimum interval allowed is 200us. Use this only if you need step
 * interval between 200us and 1ms. If this is disabled, the step size is assumed
 * to be 1ms.
 *
 * Most direct feedback based regulators are fast and does not require this. So
 * this is left disabled by default.
 */
#define VBUS_CTRL_STEP_US_ENABLE                (0u)

/* 
 * Period (in ms) to debounce the VBUS stable detection. VBUS change is detected
 * using ADC over the specified duration.
 */
#define VBUS_CTRL_SLOPE_DEBOUNCE_PERIOD         (5u)

/* 
 * Minimum period (in ms) for vbus to settle after reaching stable slope. This
 * is imposed to ensure that we provide a minimum time before indicating ready.
 */
#define VBUS_CTRL_SETTLE_TIME_PERIOD            (15u)

/*
 * Enable this macro to allow the VBUS voltage to be corrected based on ADC
 * readings. This allows for better accuracy in direct feedback systems. This
 * should not be enabled for opto-isolator designs.
 */
#define VBUS_CTRL_ADC_ADJUST_ENABLE             (1u)

/* 
 * Allow VBUS_IN discharge below 5V.
 * When VBUS_IN_DISCHARGE_EN macro is enabled, VBUS_IN discharge is enabled for all
 * VBUS downward transitions above 5V, but is disabled for transitions below 5V.
 * Because, for VBUS_IN powered solutions, VBUS_IN should not be accidently
 * brought to the low voltage where system behavior is undefined. 
 * VBUS_IN discharge below 5V may be required for solutions where regulator
 * requires higher discharge strength to set voltage below 5V.
 * It is recommended to enable this feature only for solution which are not
 * VBUS_IN powered.
 */
#define VBUS_IN_DISCH_BELOW_5V_EN               (0u)

/* VBUS discharge drive strength settings. */
#define VBUS_IN_DISCHG_DS                       (4u)

/* 
 * Enable / disable charge pump.
 * Charge pump is not needed for solutions with Vddd of 5V.
 */
#define PUMP_DISABLE                            (1u)

/*******************************************************************************
 * Power Source (PSOURCE) Configuration.
 ******************************************************************************/

/* Time (in ms) allowed for source voltage to become valid. */
#define APP_PSOURCE_EN_TIMER_PERIOD             (250u)

/* Period (in ms) of VBus validity checks after enabling the power source. */
#define APP_PSOURCE_EN_MONITOR_TIMER_PERIOD     (1u)

/* Time (in ms) between VBus valid and triggering of PS_RDY. */
#define APP_PSOURCE_EN_HYS_TIMER_PERIOD         (5u)

/* Time (in ms) for which the VBus_Discharge path will be enabled when turning power source OFF. */
#define APP_PSOURCE_DIS_TIMER_PERIOD            (600u)

/* Period (in ms) of VBus drop to VSAFE0 checks after power source is turned OFF. */
#define APP_PSOURCE_DIS_MONITOR_TIMER_PERIOD    (1u)

/* VBus Monitoring is done using internal resistor divider. */
#define VBUS_MON_INTERNAL                       (1u)

/* Period in ms for turning on VBus FET. */
#define APP_VBUS_FET_ON_TIMER_PERIOD           (5u)

/* Period in ms for turning off VBus FET. */
#define APP_VBUS_FET_OFF_TIMER_PERIOD           (1u)

/* Time (in ms) for which the VBus_Discharge path will be enabled when turning power source OFF. */
#define APP_PSOURCE_EPR_DIS_TIMER_PERIOD        (1260u)

/* Time (in ms) allowed for source voltage to become valid. */
#define APP_PSOURCE_EPR_EN_TIMER_PERIOD         (860u)

/* Enable / Disable VBUS soft start feature */
#define VBUS_SOFT_START_ENABLE                  (0u)

/* Function/Macro to set P1 source voltage to contract value. */
#define APP_VBUS_SET_VOLT_P1(mV)                    \
{                                                   \
    set_pd_ctrl_voltage(TYPEC_PORT_0_IDX, mV);      \
}
/* Function/Macro to set P2 source voltage to contract value. */
#define APP_VBUS_SET_VOLT_P2(mV)                    \
{                                                   \
    set_pd_ctrl_voltage(TYPEC_PORT_1_IDX, mV);      \
}

/*******************************************************************************
 * VBus monitor configuration.
 ******************************************************************************/

/* Allowed VBus valid margin as percentage of expected voltage. */
#define VBUS_TURN_ON_MARGIN                     (-20)

/* Allowed VBus valid margin (as percentage of expected voltage) before detach detection is triggered. */
#define VBUS_TURN_OFF_MARGIN                    (-20)

/* Allowed margin over expected voltage (as percentage) for negative VBus voltage transitions. */
#define VBUS_DISCHARGE_MARGIN                   (10)

/* Allowed margin over 5V before the provider FET is turned OFF when discharging to VSAFE0. */
#define VBUS_DISCHARGE_TO_5V_MARGIN             (10)

/*******************************************************************************
 * VBus Monitor connection configuration for Port 1.
 ******************************************************************************/

/* CCG IO port to which the VBUS_MON_P1 pin corresponds. This is taken from the PSoC Creator Schematic. */
#define APP_VBUS_MON_PORT_NO_P1                 (VBUS_MON_P1__PORT)

/* CCG IO pin to which the VBUS_MON_P1 pin corresponds. This is taken from the PSoC Creator Schematic. */
#define APP_VBUS_MON_PIN_NO_P1                  (VBUS_MON_P1__SHIFT)

/* Combined Port+Pin representation for the VBUS_MON_P1 pin. */
#define APP_VBUS_MON_PORT_PIN_P1                ((VBUS_MON_P1__PORT << 4) | VBUS_MON_P1__SHIFT)

/*
 * IO setting to connect VBUS_MON_P1 to an internal comparator. This should be selected from:
 * a) HSIOM_MODE_AMUXA = 6, AMUXBUS A connection
 * b) HSIOM_MODE_AMUXB = 7, AMUXBUS B connection
 */
#define APP_VBUS_MON_AMUX_INPUT_P1              (6)

/*******************************************************************************
 * VBus Monitoring Controls for detach detection.
 ******************************************************************************/

/* Division factor applied between VBus and the voltage on VBUS_MON input. */
#define VBUS_MON_DIVIDER                            (11u)

/*******************************************************************************
 * VBus OCP fault GPIO connection configuration.
 ******************************************************************************/

/* CCG port to which the OCP_FAULT_P1 pin corresponds. This is derived from the PSoC Creator Schematic. */
#define APP_VBUS_OCP_FAULT_PORT_NO_P1               (OCP_FAULT_P1__PORT)

/* CCG pin to which the OCP_FAULT_P1 pin corresponds. This is derived from the PSoC Creator Schematic. */
#define APP_VBUS_OCP_FAULT_PIN_NO_P1                (OCP_FAULT_P1__SHIFT)

/* Combined Port+Pin representation for the OCP_FAULT_P1 pin. */
#define APP_VBUS_OCP_PORT_PIN_P1                    ((OCP_FAULT_P1__PORT << 4) | OCP_FAULT_P1__SHIFT)

/*******************************************************************************
 * VBUS_OVP_TRIP GPIO connection configuration.
 ******************************************************************************/

/* CCG port to which the VBUS_OVP_TRIP_P1 pin corresponds. */
#define APP_VBUS_OVP_TRIP_PORT_NO_P1                (VBUS_OVP_TRIP_P1__PORT)

/* CCG pin to which the VBUS_OVP_TRIP_P1 pin corresponds. */
#define APP_VBUS_OVP_TRIP_PIN_NO_P1                 (VBUS_OVP_TRIP_P1__SHIFT)

/* Combined Port+Pin representation of the VBUS_OVP_TRIP_P1 pin. */
#define APP_VBUS_OVP_TRIP_PORT_PIN_P1               ((VBUS_OVP_TRIP_P1__PORT << 4) | VBUS_OVP_TRIP_P1__SHIFT)

/* CCG IO mode corresponding to the VBUS_OVP_TRIP functionality. This should be set to 12. */
#define APP_VBUS_OVP_TRIP_HSIOM_P1                  (12)

/*******************************************************************************
 * VConn Monitor connection configuration for Port 1.
 * This section is optional as VConn monitoring is not enabled in the stack.
 ******************************************************************************/

/* CCG IO port to which the VCONN_MON_P1 pin corresponds. This is taken from the PSoC Creator Schematic. */
#define APP_VCONN_MON_PORT_NO_P1                    (VCONN_MON_P1__PORT)

/* CCG IO pin to which the VCONN_MON_P1 pin corresponds. This is taken from the PSoC Creator Schematic. */
#define APP_VCONN_MON_PIN_NO_P1                     (VCONN_MON_P1__SHIFT)

/* Combined Port+Pin representation for the VCONN_MON_P1 pin. */
#define APP_VCONN_MON_PORT_PIN_P1                   ((VCONN_MON_P1__PORT << 4) | VCONN_MON_P1__SHIFT)

/*
 * IO setting to connect VCONN_MON_P1 to an internal comparator. This should be selected from:
 * a) HSIOM_MODE_AMUXA = 6, AMUXBUS A connection
 * b) HSIOM_MODE_AMUXB = 7, AMUXBUS B connection
 */
#define APP_VCONN_MON_AMUX_INPUT_P1                 (7)

/*******************************************************************************
 * VBUS offset voltage configuration.
 *
 * Offset voltage value is a configuration table parameter.
 ******************************************************************************/

/* VBUS offset voltage enable setting. */

/*******************************************************************************
 * Battery Charging Support Configuration
 ******************************************************************************/

#if BATTERY_CHARGING_ENABLE
#define  NO_OF_BC_PORTS                            (1u)
#define  BC_PORT_0_IDX                             (0u)
#define  BC_PORT_1_IDX                             (1u)
#endif /* BATTERY_CHARGING_ENABLE */

/*******************************************************************************
 * VBus Over-Voltage Protection Configuration.
 *
 * The VBus OVP feature uses an internal ADC in the CCG to measure the voltage
 * on the VBUS_MON input and uses the ADC output to detect over-voltage
 * conditions.
 *
 * The default implementation of OVP uses firmware ISRs to turn off the FETs
 * when OVP is detected. If quicker response is desired, there is the option of
 * using a direct OVP_TRIP output derived from a hardware comparator associated
 * with the ADC.
 ******************************************************************************/


/*******************************************************************************
 * PD CRC Error Handling Configuration.
 ******************************************************************************/

/* Enable/Disable PD CRC Error Handling */
#define CY_PD_CRC_ERR_HANDLING_ENABLE                  (1u)

/*******************************************************************************
 * System fault configuration features.
 ******************************************************************************/

/* 
 * Enable/Disable delay between fault retries for Type-C/PD faults.
 */
#define FAULT_RETRY_DELAY_EN                        (0u)

#if FAULT_RETRY_DELAY_EN

/* 
 * Delay between fault retries in mS.
 */
#define FAULT_RETRY_DELAY_MS                        (500u)

#endif /* FAULT_RETRY_DELAY_EN */

/* 
 * Enable/Disable delayed infinite fault recovery for Type-C/PD faults.
 * Fault recovery shall be tried with a fixed delay after configured 
 * fault retry count is elapsed. 
 */
#define FAULT_INFINITE_RECOVERY_EN                  (0u)

#if FAULT_INFINITE_RECOVERY_EN

/* 
 * Delayed fault recovery period in mS.
 */
#define FAULT_INFINITE_RECOVERY_DELAY_MS            (5000u)

#endif /* FAULT_INFINITE_RECOVERY_EN */

/* Enable watchdog hardware reset for CPU lock-up recovery */
#define WATCHDOG_HARDWARE_RESET_ENABLE              (1u)

/* Disable CCG device reset on error (watchdog expiry or hard fault). */
#define RESET_ON_ERROR_ENABLE                       (1u)

/* Enable reset reporting through HPI. */
#define HPI_WATCHDOG_RESET_ENABLE                   (0u)

/* Watchdog reset timer id. */
#define WATCHDOG_TIMER_ID                           (0xC2u)

/*
 * Watchdog reset period in ms. This should be set to a value greater than
 * 500 ms to avoid significant increase in power consumption.
 */
#define WATCHDOG_RESET_PERIOD_MS                    (750u)

/* Enable tracking of maximum stack usage. */
#define STACK_USAGE_CHECK_ENABLE                    (0u)

/* Set this to 1 to Shutdown the SNK FET in the application layer. */
#define SNK_FET_SHUTDOWN_ENABLE                     (1u)

/*
 * Enable function marker test code coverage.
 */
#define TEST_CODE_COVERAGE                          (0u)

/*******************************************************************************
 * Firmware feature configuration.
 ******************************************************************************/

/* Set to 1 if building a debug enabled binary with no boot-loader dependency. */
#define CCG_FIRMWARE_APP_ONLY                       (0u)

#ifndef SYS_DEEPSLEEP_ENABLE
/* Enable CCG deep sleep to save power. */
#define SYS_DEEPSLEEP_ENABLE                        (0u)
#endif /* SYS_DEEPSLEEP_ENABLE */

/* Enable Alternate Mode support when CCG is DFP. */
#define DFP_ALT_MODE_SUPP                           (0u)

/* Enable DisplayPort Source support as DFP. */
#define DP_DFP_SUPP                                 (0u)

/* Enable Alt mode as UFP */
#define UFP_ALT_MODE_SUPP                           (0u)

/* Enable saving only SVIDs which are supported by CCG. */
#define SAVE_SUPP_SVID_ONLY                         (1u)

/*
 * Enable/Disable firmware active LED operation.
 *
 * The blinking LED is enabled by default but it is recommended to disable it
 * for production designs to save power.
 */
#define APP_FW_LED_ENABLE                           (0u)

/*
 * Timer ID allocation for various solution soft timers.
 */

/*
 * Activity indicator LED timer. The timer is used to indicate that the firmware
 * is functional. The feature is controlled by APP_FW_LED_ENABLE.
 */
#define LED_TIMER_ID                                (0xC0)
/*
 * The LED toggle period.
 */
#define LED_TIMER_PERIOD                            (1000)

/* Timer used to ensure I2C transfers to the MUX complete on time. */
#define MUX_I2C_TIMER                               (0xC1)
/* The MUX transfer timeout is set to 10 ms timeout period. */
#define MUX_I2C_TIMER_PERIOD                        (10u)

/* Timer ID allocation for various application timers.  */

/** Timer used for providing delay for VBUS FET ON. */
#define APP_VBUS_FET_ON_TIMER                       (APP_TIMERS_RESERVED_START_ID + 0u)

/** Timer used for providing delay for VBUS FET OFF. */
#define APP_VBUS_FET_OFF_TIMER                      (APP_TIMERS_RESERVED_START_ID + 1u)

/** Timer used for providing delay for VConn Gate Pull Up enable. */
#define APP_VCONN_TURN_ON_DELAY_TIMER               (APP_TIMERS_RESERVED_START_ID + 2u)

/** Timer used to control soft turn-on of power FET gate drivers. */
#define APP_FET_SOFT_START_TIMER_ID                 (APP_TIMERS_RESERVED_START_ID + 3u)
    
/** Timer period in ms for providing delay for VConn Gate Pull Up enable. */
#define APP_VCONN_TURN_ON_DELAY_PERIOD              (1u)

/* Timer used to initiate EPR entry after SPR contract negotiation complete */
#define APP_EPR_SNK_TIMER                           (APP_TIMERS_RESERVED_START_ID + 4u)
#define APP_EPR_SNK_ENTRY_TIMER_PERIOD              (100u)
#define APP_EPR_SNK_EXIT_TIMER_PERIOD               (10u)

/*******************************************************************************
 * Get Battery status and Get Battery configuration response configuration
 ******************************************************************************/
    
/* Valid battery_status response when source */
    
#define CCG_EXT_MSG_VALID_BAT_STAT_SRC              (0xffff0600)

/* Valid battery_status response when sink */
    
#define CCG_EXT_MSG_VALID_BAT_STAT_SNK              (0xffff0200)
    
/* Invalid battery_status response */
    
#define CCG_EXT_MSG_INVALID_BAT_REF                 (0xffff0100)

/* This macro defines the number of batteries */   
#define CCG_PB_NO_OF_BATT                           (1u)   

/* This macro defines the VID-PID for Power Bank */   
#define CCG_PB_VID_PID                              (0xf56504b4)

/* This macro defines the battery design capacity (in 0.1WH)
 * 0x0000 : Battery not present
 * 0xFFFF : Design capacity unknown
 */     
#define CCG_PB_BAT_DES_CAP                          (0xFFFF)
    
/* This macro defines the battery last full charge capacity (in 0.1WH)
 * 0x0000 : Battery not present
 * 0xFFFF : Last full charge capacity unknown
 */
#define CCG_PB_BAT_FUL_CHG_CAP                      (0xFFFF)

/***********************************************************************************/

/* Enable selection of data/power role preference. */
#define ROLE_PREFERENCE_ENABLE                      (0u)
#define POWER_ROLE_PREFERENCE_ENABLE                (0u)

#endif /* _CONFIG_H_ */

/* End of file [] */
