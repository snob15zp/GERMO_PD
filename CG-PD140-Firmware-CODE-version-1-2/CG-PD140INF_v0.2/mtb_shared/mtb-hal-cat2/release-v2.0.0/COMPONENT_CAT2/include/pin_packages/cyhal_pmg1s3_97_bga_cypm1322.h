/***************************************************************************//**
* \file cyhal_pmg1s3_97_bga_cypm1322.h
*
* \brief
* PMG1S3 device GPIO HAL header for 97-BGA-CYPM1322 package
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

#ifndef _CYHAL_PMG1S3_97_BGA_CYPM1322_H_
#define _CYHAL_PMG1S3_97_BGA_CYPM1322_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_pmg1s3_97_bga_cypm1322 PMG1S3 97-BGA-CYPM1322
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the PMG1S3 97-BGA-CYPM1322 package.
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

/** Definitions for all of the pins that are bonded out on in the 97-BGA-CYPM1322 package for the PMG1S3 series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1
    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2
    P0_3 = CYHAL_GET_GPIO(CYHAL_PORT_0, 3), //!< Port 0 Pin 3
    P0_4 = CYHAL_GET_GPIO(CYHAL_PORT_0, 4), //!< Port 0 Pin 4
    P0_5 = CYHAL_GET_GPIO(CYHAL_PORT_0, 5), //!< Port 0 Pin 5
    P0_6 = CYHAL_GET_GPIO(CYHAL_PORT_0, 6), //!< Port 0 Pin 6
    P0_7 = CYHAL_GET_GPIO(CYHAL_PORT_0, 7), //!< Port 0 Pin 7

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_4 = CYHAL_GET_GPIO(CYHAL_PORT_1, 4), //!< Port 1 Pin 4
    P1_5 = CYHAL_GET_GPIO(CYHAL_PORT_1, 5), //!< Port 1 Pin 5
    P1_6 = CYHAL_GET_GPIO(CYHAL_PORT_1, 6), //!< Port 1 Pin 6

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_4 = CYHAL_GET_GPIO(CYHAL_PORT_2, 4), //!< Port 2 Pin 4
    P2_5 = CYHAL_GET_GPIO(CYHAL_PORT_2, 5), //!< Port 2 Pin 5
    P2_6 = CYHAL_GET_GPIO(CYHAL_PORT_2, 6), //!< Port 2 Pin 6
    P2_7 = CYHAL_GET_GPIO(CYHAL_PORT_2, 7), //!< Port 2 Pin 7

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3
    P3_4 = CYHAL_GET_GPIO(CYHAL_PORT_3, 4), //!< Port 3 Pin 4
    P3_5 = CYHAL_GET_GPIO(CYHAL_PORT_3, 5), //!< Port 3 Pin 5
    P3_6 = CYHAL_GET_GPIO(CYHAL_PORT_3, 6), //!< Port 3 Pin 6
    P3_7 = CYHAL_GET_GPIO(CYHAL_PORT_3, 7), //!< Port 3 Pin 7

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0
    P5_1 = CYHAL_GET_GPIO(CYHAL_PORT_5, 1), //!< Port 5 Pin 1
    P5_2 = CYHAL_GET_GPIO(CYHAL_PORT_5, 2), //!< Port 5 Pin 2
    P5_3 = CYHAL_GET_GPIO(CYHAL_PORT_5, 3), //!< Port 5 Pin 3
    P5_4 = CYHAL_GET_GPIO(CYHAL_PORT_5, 4), //!< Port 5 Pin 4
    P5_5 = CYHAL_GET_GPIO(CYHAL_PORT_5, 5), //!< Port 5 Pin 5

    P6_0 = CYHAL_GET_GPIO(CYHAL_PORT_6, 0), //!< Port 6 Pin 0
    P6_1 = CYHAL_GET_GPIO(CYHAL_PORT_6, 1), //!< Port 6 Pin 1
    P6_2 = CYHAL_GET_GPIO(CYHAL_PORT_6, 2), //!< Port 6 Pin 2
    P6_3 = CYHAL_GET_GPIO(CYHAL_PORT_6, 3), //!< Port 6 Pin 3

    P7_0 = CYHAL_GET_GPIO(CYHAL_PORT_7, 0), //!< Port 7 Pin 0
    P7_1 = CYHAL_GET_GPIO(CYHAL_PORT_7, 1), //!< Port 7 Pin 1
    P7_2 = CYHAL_GET_GPIO(CYHAL_PORT_7, 2), //!< Port 7 Pin 2
    P7_3 = CYHAL_GET_GPIO(CYHAL_PORT_7, 3), //!< Port 7 Pin 3
    P7_4 = CYHAL_GET_GPIO(CYHAL_PORT_7, 4), //!< Port 7 Pin 4
    P7_5 = CYHAL_GET_GPIO(CYHAL_PORT_7, 5), //!< Port 7 Pin 5
    P7_6 = CYHAL_GET_GPIO(CYHAL_PORT_7, 6), //!< Port 7 Pin 6

    USBDP = CYHAL_GET_GPIO(CYHAL_PORT_8, 0), //!< Port 8 Pin 0
    USBDM = CYHAL_GET_GPIO(CYHAL_PORT_8, 1), //!< Port 8 Pin 1
    VSSIO_5 = CYHAL_GET_GPIO(CYHAL_PORT_8, 2), //!< Port 8 Pin 2
} cyhal_gpio_pmg1s3_97_bga_cypm1322_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_pmg1s3_97_bga_cypm1322_t cyhal_gpio_t;

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
/** Indicates that a pin map exists for lpcomp_dsi_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_DSI_COMP (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the lpcomp_dsi_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_dsi_comp[2];
/** Indicates that a pin map exists for lpcomp_inn_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_INN_COMP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the lpcomp_inn_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inn_comp[2];
/** Indicates that a pin map exists for lpcomp_inp_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_INP_COMP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the lpcomp_inp_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inp_comp[2];
/** Indicates that a pin map exists for opamp_dsi_ctb_cmp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_DSI_CTB_CMP (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the opamp_dsi_ctb_cmp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_dsi_ctb_cmp[2];
/** Indicates that a pin map exists for opamp_out_10x*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_OUT_10X (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_out_10x signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_out_10x[2];
/** Indicates that a pin map exists for opamp_vin_m*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_M (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_vin_m signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_m[2];
/** Indicates that a pin map exists for opamp_vin_p0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P0 (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_vin_p0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p0[2];
/** Indicates that a pin map exists for opamp_vin_p1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P1 (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_vin_p1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p1[2];
/** Indicates that a pin map exists for pass_dsi_sar_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_DSI_SAR_DATA (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_dsi_sar_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data[12];
/** Indicates that a pin map exists for pass_dsi_sar_data_valid*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_DSI_SAR_DATA_VALID (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_dsi_sar_data_valid signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data_valid[1];
/** Indicates that a pin map exists for pass_dsi_sar_sample_done*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_DSI_SAR_SAMPLE_DONE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_dsi_sar_sample_done signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_sample_done[1];
/** Indicates that a pin map exists for pass_sar_ext_vref0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_VREF0 (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the pass_sar_ext_vref0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref0[1];
/** Indicates that a pin map exists for pass_sar_ext_vref1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_VREF1 (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the pass_sar_ext_vref1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref1[1];
/** Indicates that a pin map exists for pass_sarmux_pads*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the pass_sarmux_pads signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[8];
/** Indicates that a pin map exists for pass_tr_sar_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_TR_SAR_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_tr_sar_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_tr_sar_out[1];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[8];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[8];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[8];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[8];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[8];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[8];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[8];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[8];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[8];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[8];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[8];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[8];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[8];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[8];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[8];
/** Indicates that a pin map exists for tcpwm_tr_compare_match*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_COMPARE_MATCH (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_tr_compare_match signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[8];
/** Indicates that a pin map exists for tcpwm_tr_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_IN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the tcpwm_tr_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[8];
/** Indicates that a pin map exists for usb_dm*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USB_DM (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the usb_dm signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_dm[1];
/** Indicates that a pin map exists for usb_dp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USB_DP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the usb_dp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_dp[1];
/** Indicates that a pin map exists for usb_vbus_det*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USB_VBUS_DET (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usb_vbus_det signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_vbus_det[1];
/** Indicates that a pin map exists for usb_vbus_valid*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USB_VBUS_VALID (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usb_vbus_valid signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_vbus_valid[1];
/** Indicates that a pin map exists for usbpd_adc_cmp_out_gpio*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_ADC_CMP_OUT_GPIO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_adc_cmp_out_gpio signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[2];
/** Indicates that a pin map exists for usbpd_afc_tx_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_AFC_TX_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_afc_tx_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[2];
/** Indicates that a pin map exists for usbpd_afc_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_AFC_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_afc_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[2];
/** Indicates that a pin map exists for usbpd_ddft0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_DDFT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ddft0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ddft0[2];
/** Indicates that a pin map exists for usbpd_ddft1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_DDFT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ddft1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ddft1[2];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[2];
/** Indicates that a pin map exists for usbpd_pad_usbphy_dm_bch_det*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_USBPHY_DM_BCH_DET (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_usbphy_dm_bch_det signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_usbphy_dm_bch_det[1];
/** Indicates that a pin map exists for usbpd_pad_usbphy_dp_bch_det*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_PAD_USBPHY_DP_BCH_DET (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_pad_usbphy_dp_bch_det signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_usbphy_dp_bch_det[1];
/** Indicates that a pin map exists for usbpd_sbu_dbg1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_DBG1 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_dbg1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_dbg1[2];
/** Indicates that a pin map exists for usbpd_sbu_dbg2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_DBG2 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_dbg2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_dbg2[2];
/** Indicates that a pin map exists for usbpd_sbu_io1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_IO1 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_io1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_io1[2];
/** Indicates that a pin map exists for usbpd_sbu_io2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_IO2 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_io2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_io2[2];
/** Indicates that a pin map exists for usbpd_sbu_lsrx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_LSRX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_lsrx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_lsrx[2];
/** Indicates that a pin map exists for usbpd_sbu_lstx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_LSTX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_lstx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_lstx[2];
/** Indicates that a pin map exists for usbpd_swapt_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SWAPT_IN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_swapt_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[2];
/** Indicates that a pin map exists for usbpd_swapt_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SWAPT_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_swapt_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_out[4];
/** Indicates that a pin map exists for usbpd_tx_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[2];
/** Indicates that a pin map exists for usbpd_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[2];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_PMG1S3_97_BGA_CYPM1322_H_ */


/* [] END OF FILE */
