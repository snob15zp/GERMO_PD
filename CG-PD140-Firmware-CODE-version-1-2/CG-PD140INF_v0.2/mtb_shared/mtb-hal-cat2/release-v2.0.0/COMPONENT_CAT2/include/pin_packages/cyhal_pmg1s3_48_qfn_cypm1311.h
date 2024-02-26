/***************************************************************************//**
* \file cyhal_pmg1s3_48_qfn_cypm1311.h
*
* \brief
* PMG1S3 device GPIO HAL header for 48-QFN-CYPM1311 package
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

#ifndef _CYHAL_PMG1S3_48_QFN_CYPM1311_H_
#define _CYHAL_PMG1S3_48_QFN_CYPM1311_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_pmg1s3_48_qfn_cypm1311 PMG1S3 48-QFN-CYPM1311
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the PMG1S3 48-QFN-CYPM1311 package.
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

/** Definitions for all of the pins that are bonded out on in the 48-QFN-CYPM1311 package for the PMG1S3 series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0

    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_4 = CYHAL_GET_GPIO(CYHAL_PORT_1, 4), //!< Port 1 Pin 4
    P1_5 = CYHAL_GET_GPIO(CYHAL_PORT_1, 5), //!< Port 1 Pin 5
    P1_6 = CYHAL_GET_GPIO(CYHAL_PORT_1, 6), //!< Port 1 Pin 6

    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_4 = CYHAL_GET_GPIO(CYHAL_PORT_2, 4), //!< Port 2 Pin 4

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3
    P3_5 = CYHAL_GET_GPIO(CYHAL_PORT_3, 5), //!< Port 3 Pin 5
    P3_6 = CYHAL_GET_GPIO(CYHAL_PORT_3, 6), //!< Port 3 Pin 6

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0
    P5_1 = CYHAL_GET_GPIO(CYHAL_PORT_5, 1), //!< Port 5 Pin 1
    P5_2 = CYHAL_GET_GPIO(CYHAL_PORT_5, 2), //!< Port 5 Pin 2
    P5_3 = CYHAL_GET_GPIO(CYHAL_PORT_5, 3), //!< Port 5 Pin 3
    P5_5 = CYHAL_GET_GPIO(CYHAL_PORT_5, 5), //!< Port 5 Pin 5

    P6_0 = CYHAL_GET_GPIO(CYHAL_PORT_6, 0), //!< Port 6 Pin 0
    P6_1 = CYHAL_GET_GPIO(CYHAL_PORT_6, 1), //!< Port 6 Pin 1
    P6_2 = CYHAL_GET_GPIO(CYHAL_PORT_6, 2), //!< Port 6 Pin 2
    P6_3 = CYHAL_GET_GPIO(CYHAL_PORT_6, 3), //!< Port 6 Pin 3

    USBDP = CYHAL_GET_GPIO(CYHAL_PORT_8, 0), //!< Port 8 Pin 0
    USBDM = CYHAL_GET_GPIO(CYHAL_PORT_8, 1), //!< Port 8 Pin 1
} cyhal_gpio_pmg1s3_48_qfn_cypm1311_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_pmg1s3_48_qfn_cypm1311_t cyhal_gpio_t;

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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_out_10x[1];
/** Indicates that a pin map exists for opamp_vin_m*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_M (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_vin_m signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_m[2];
/** Indicates that a pin map exists for opamp_vin_p0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P0 (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_vin_p0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p0[1];
/** Indicates that a pin map exists for opamp_vin_p1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P1 (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the opamp_vin_p1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p1[1];
/** Indicates that a pin map exists for pass_dsi_sar_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_DSI_SAR_DATA (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_dsi_sar_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data[8];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[4];
/** Indicates that a pin map exists for pass_tr_sar_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_TR_SAR_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_tr_sar_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_tr_sar_out[1];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[7];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[7];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[7];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[7];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[5];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[5];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[7];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[7];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[5];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[5];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[5];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[5];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[6];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[7];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[7];
/** Indicates that a pin map exists for tcpwm_tr_compare_match*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_COMPARE_MATCH (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_tr_compare_match signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[7];
/** Indicates that a pin map exists for tcpwm_tr_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_IN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the tcpwm_tr_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[7];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[1];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ddft0[1];
/** Indicates that a pin map exists for usbpd_ddft1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_DDFT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_ddft1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ddft1[1];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[2];
/** Indicates that a pin map exists for usbpd_gpio_ddft1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_GPIO_DDFT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_gpio_ddft1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[1];
/** Indicates that a pin map exists for usbpd_hpd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_HPD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the usbpd_hpd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[1];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_dbg1[1];
/** Indicates that a pin map exists for usbpd_sbu_dbg2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_DBG2 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_dbg2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_dbg2[1];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_lsrx[1];
/** Indicates that a pin map exists for usbpd_sbu_lstx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_SBU_LSTX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_sbu_lstx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_lstx[1];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[2];
/** Indicates that a pin map exists for usbpd_tx_data_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USBPD_TX_DATA_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the usbpd_tx_data_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[1];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_PMG1S3_48_QFN_CYPM1311_H_ */


/* [] END OF FILE */
