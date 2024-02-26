/***************************************************************************//**
* \file cyhal_ccg7d_68_qfn.h
*
* \brief
* CCG7D device GPIO HAL header for 68-QFN package
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

#ifndef _CYHAL_CCG7D_68_QFN_H_
#define _CYHAL_CCG7D_68_QFN_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_ccg7d_68_qfn CCG7D 68-QFN
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the CCG7D 68-QFN package.
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** Gets a pin definition from the provided port and pin numbers */
#define CYHAL_GET_GPIO(port, pin)   ((((uint8_t)(port)) << 3U) + ((uint8_t)(pin)))

/** Macro that, given a gpio, will extract the pin number */
#define CYHAL_GET_PIN(pin)          ((uint8_t)(((uint8_t)pin) & 0x07U))
/** Macro that, given a gpio, will extract the port number */
#define CYHAL_GET_PORT(pin)         ((uint8_t)((((uint8_t)pin) >> 3U) & 0x1FU))

/** Definitions for all of the pins that are bonded out on in the 68-QFN package for the CCG7D series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1
    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2
    P0_3 = CYHAL_GET_GPIO(CYHAL_PORT_0, 3), //!< Port 0 Pin 3
    P0_4 = CYHAL_GET_GPIO(CYHAL_PORT_0, 4), //!< Port 0 Pin 4

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_4 = CYHAL_GET_GPIO(CYHAL_PORT_1, 4), //!< Port 1 Pin 4
    P1_5 = CYHAL_GET_GPIO(CYHAL_PORT_1, 5), //!< Port 1 Pin 5
    P1_6 = CYHAL_GET_GPIO(CYHAL_PORT_1, 6), //!< Port 1 Pin 6

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3
    P3_4 = CYHAL_GET_GPIO(CYHAL_PORT_3, 4), //!< Port 3 Pin 4
} cyhal_gpio_ccg7d_68_qfn_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_ccg7d_68_qfn_t cyhal_gpio_t;

/* Connection type definition */
/** Represents an association between a pin and a resource */
typedef struct
{
    uint8_t         block_num;   //!< The block number of the resource with this connection
    uint8_t         channel_num; //!< The channel number of the block with this connection
    cyhal_gpio_t    pin;         //!< The GPIO pin the connection is with
    en_hsiom_sel_t  hsiom;       //!< The HSIOM configuration value
} cyhal_resource_pin_mapping_t;

/* Pin connections */
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[4];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[4];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[4];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[4];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[4];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[4];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[4];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[4];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[4];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[4];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[4];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[4];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[4];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[4];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[12];
/** Indicates that a pin map exists for tcpwm_tr_compare_match*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_COMPARE_MATCH (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_tr_compare_match signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[8];
/** Indicates that a pin map exists for tcpwm_tr_overflow*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_OVERFLOW (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_tr_overflow signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_overflow[8];
/** Indicates that a pin map exists for usbpd_adc_cmp_out_gpio*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_ADC_CMP_OUT_GPIO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_adc_cmp_out_gpio signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[3];
/** Indicates that a pin map exists for usbpd_afc_tx_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_AFC_TX_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_afc_tx_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[2];
/** Indicates that a pin map exists for usbpd_afc_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_AFC_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_afc_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[2];
/** Indicates that a pin map exists for usbpd_ext_hs1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_HS1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_hs1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hs1[2];
/** Indicates that a pin map exists for usbpd_ext_hs2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_HS2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_hs2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hs2[2];
/** Indicates that a pin map exists for usbpd_ext_hsrcp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_HSRCP (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_hsrcp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hsrcp[2];
/** Indicates that a pin map exists for usbpd_ext_ls1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_LS1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_ls1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_ls1[2];
/** Indicates that a pin map exists for usbpd_ext_ls2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_LS2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_ls2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_ls2[2];
/** Indicates that a pin map exists for usbpd_ext_lszcd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_LSZCD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_lszcd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_lszcd[2];
/** Indicates that a pin map exists for usbpd_ext_pwm_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_PWM_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_pwm_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_pwm_out[2];
/** Indicates that a pin map exists for usbpd_ext_rst_sw1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_RST_SW1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_rst_sw1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_rst_sw1[2];
/** Indicates that a pin map exists for usbpd_ext_scap_rst*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_SCAP_RST (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_scap_rst signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_scap_rst[2];
/** Indicates that a pin map exists for usbpd_ext_scomp_out_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_SCOMP_OUT_EN (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_scomp_out_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_scomp_out_en[2];
/** Indicates that a pin map exists for usbpd_ext_set_boost*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_SET_BOOST (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_set_boost signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_set_boost[2];
/** Indicates that a pin map exists for usbpd_ext_set_buck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_EXT_SET_BUCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ext_set_buck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_set_buck[2];
/** Indicates that a pin map exists for usbpd_fault_gpio0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_FAULT_GPIO0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_fault_gpio0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio0[2];
/** Indicates that a pin map exists for usbpd_fault_gpio1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_FAULT_GPIO1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_fault_gpio1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio1[2];
/** Indicates that a pin map exists for usbpd_gpio_ddft0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_GPIO_DDFT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_gpio_ddft0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[2];
/** Indicates that a pin map exists for usbpd_gpio_ddft1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_GPIO_DDFT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_gpio_ddft1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[2];
/** Indicates that a pin map exists for usbpd_hpd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_HPD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_hpd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[4];
/** Indicates that a pin map exists for usbpd_pad_bat2gnd_pulldn*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_BAT2GND_PULLDN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_bat2gnd_pulldn signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_bat2gnd_pulldn[2];
/** Indicates that a pin map exists for usbpd_pad_lscsa_inp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_LSCSA_INP (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_lscsa_inp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_lscsa_inp[2];
/** Indicates that a pin map exists for usbpd_pad_lscsa_vgnd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_LSCSA_VGND (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_lscsa_vgnd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_lscsa_vgnd[2];
/** Indicates that a pin map exists for usbpd_swapt_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SWAPT_IN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_swapt_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[2];
/** Indicates that a pin map exists for usbpd_tx_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[2];
/** Indicates that a pin map exists for usbpd_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[2];
/** Indicates that a pin map exists for usbpd_usbphy_dm_bch_det*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_USBPHY_DM_BCH_DET (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_usbphy_dm_bch_det signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dm_bch_det[2];
/** Indicates that a pin map exists for usbpd_usbphy_dp_bch_det*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_USBPHY_DP_BCH_DET (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_usbphy_dp_bch_det signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dp_bch_det[2];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_CCG7D_68_QFN_H_ */


/* [] END OF FILE */
