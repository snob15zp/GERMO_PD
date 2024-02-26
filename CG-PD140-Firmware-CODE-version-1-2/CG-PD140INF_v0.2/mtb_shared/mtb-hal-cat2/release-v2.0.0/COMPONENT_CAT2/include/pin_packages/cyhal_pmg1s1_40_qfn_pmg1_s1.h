/***************************************************************************//**
* \file cyhal_pmg1s1_40_qfn_pmg1_s1.h
*
* \brief
* PMG1S1 device GPIO HAL header for 40-QFN-PMG1-S1 package
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

#ifndef _CYHAL_PMG1S1_40_QFN_PMG1_S1_H_
#define _CYHAL_PMG1S1_40_QFN_PMG1_S1_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_pmg1s1_40_qfn_pmg1_s1 PMG1S1 40-QFN-PMG1-S1
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the PMG1S1 40-QFN-PMG1-S1 package.
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

/** Definitions for all of the pins that are bonded out on in the 40-QFN-PMG1-S1 package for the PMG1S1 series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_4 = CYHAL_GET_GPIO(CYHAL_PORT_1, 4), //!< Port 1 Pin 4

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0
    P5_1 = CYHAL_GET_GPIO(CYHAL_PORT_5, 1), //!< Port 5 Pin 1
} cyhal_gpio_pmg1s1_40_qfn_pmg1_s1_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_pmg1s1_40_qfn_pmg1_s1_t cyhal_gpio_t;

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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[2];
/** Indicates that a pin map exists for tcpwm_tr_compare_match*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_COMPARE_MATCH (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_tr_compare_match signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[2];
/** Indicates that a pin map exists for tcpwm_tr_overflow*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_OVERFLOW (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_tr_overflow signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_overflow[2];
/** Indicates that a pin map exists for usbpd_adc_cmp_out_gpio*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_ADC_CMP_OUT_GPIO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_adc_cmp_out_gpio signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[1];
/** Indicates that a pin map exists for usbpd_afc_tx_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_AFC_TX_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_afc_tx_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[1];
/** Indicates that a pin map exists for usbpd_afc_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_AFC_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_afc_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[1];
/** Indicates that a pin map exists for usbpd_fault_gpio0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_FAULT_GPIO0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_fault_gpio0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio0[1];
/** Indicates that a pin map exists for usbpd_fault_gpio1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_FAULT_GPIO1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_fault_gpio1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio1[1];
/** Indicates that a pin map exists for usbpd_gpio_ddft0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_GPIO_DDFT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_gpio_ddft0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[1];
/** Indicates that a pin map exists for usbpd_gpio_ddft1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_GPIO_DDFT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_gpio_ddft1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[1];
/** Indicates that a pin map exists for usbpd_hpd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_HPD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_hpd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[1];
/** Indicates that a pin map exists for usbpd_pad_dpdm_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_DPDM_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_dpdm_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_dpdm_uart_rx[1];
/** Indicates that a pin map exists for usbpd_pad_dpdm_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_DPDM_UART_TX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_dpdm_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_dpdm_uart_tx[1];
/** Indicates that a pin map exists for usbpd_sbu20_lsrx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU20_LSRX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu20_lsrx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu20_lsrx[1];
/** Indicates that a pin map exists for usbpd_sbu20_lstx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU20_LSTX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu20_lstx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu20_lstx[1];
/** Indicates that a pin map exists for usbpd_swapt_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SWAPT_IN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_swapt_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[1];
/** Indicates that a pin map exists for usbpd_swapt_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SWAPT_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_swapt_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_out[2];
/** Indicates that a pin map exists for usbpd_tx_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[1];
/** Indicates that a pin map exists for usbpd_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[1];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_PMG1S1_40_QFN_PMG1_S1_H_ */


/* [] END OF FILE */
