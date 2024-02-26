/***************************************************************************//**
* \file cyhal_pmg1s3_48_qfn_cypm1311.c
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

#include "cy_device_headers.h"
#include "cyhal_hw_types.h"

#if defined(_GPIO_PMG1S3_48_QFN_CYPM1311_H_)
#include "pin_packages/cyhal_pmg1s3_48_qfn_cypm1311.h"

/* Pin connections */
/* Connections for: lpcomp_dsi_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_dsi_comp[2] = {
    {0u, 1u, P5_2, P5_2_LPCOMP_COMP1},
    {0u, 0u, P5_3, P5_3_LPCOMP_COMP0},
};

/* Connections for: lpcomp_inn_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inn_comp[2] = {
    {0u, 1u, P1_2, HSIOM_SEL_GPIO},
    {0u, 0u, P1_5, HSIOM_SEL_GPIO},
};

/* Connections for: lpcomp_inp_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inp_comp[2] = {
    {0u, 1u, P1_1, HSIOM_SEL_GPIO},
    {0u, 0u, P1_6, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_dsi_ctb_cmp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_dsi_ctb_cmp[2] = {
    {0u, 0u, P5_2, P5_2_PASS0_DSI_CTB_CMP0},
    {0u, 1u, P5_3, P5_3_PASS0_DSI_CTB_CMP1},
};

/* Connections for: opamp_out_10x */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_out_10x[1] = {
    {0u, 0u, P3_5, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_vin_m */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_m[2] = {
    {0u, 1u, P3_3, HSIOM_SEL_GPIO},
    {0u, 0u, P3_6, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_vin_p0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p0[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_vin_p1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p1[1] = {
    {0u, 1u, P3_0, HSIOM_SEL_GPIO},
};

/* Connections for: pass_dsi_sar_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data[8] = {
    {0u, 2u, P1_5, P1_5_PASS0_DSI_SAR_DATA2},
    {0u, 7u, P3_6, P3_6_PASS0_DSI_SAR_DATA7},
    {0u, 3u, P4_0, P4_0_PASS0_DSI_SAR_DATA3},
    {0u, 4u, P4_1, P4_1_PASS0_DSI_SAR_DATA4},
    {0u, 6u, P5_0, P5_0_PASS0_DSI_SAR_DATA6},
    {0u, 5u, P5_1, P5_1_PASS0_DSI_SAR_DATA5},
    {0u, 0u, P6_0, P6_0_PASS0_DSI_SAR_DATA0},
    {0u, 1u, P6_1, P6_1_PASS0_DSI_SAR_DATA1},
};

/* Connections for: pass_dsi_sar_data_valid */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data_valid[1] = {
    {0u, 0u, P3_5, P3_5_PASS0_DSI_SAR_DATA_VALID},
};

/* Connections for: pass_dsi_sar_sample_done */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_sample_done[1] = {
    {0u, 0u, P1_1, P1_1_PASS0_DSI_SAR_SAMPLE_DONE},
};

/* Connections for: pass_sar_ext_vref0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref0[1] = {
    {0u, 0u, P3_0, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sar_ext_vref1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref1[1] = {
    {0u, 0u, P3_0, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sarmux_pads */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[4] = {
    {0u, 1u, P2_1, HSIOM_SEL_GPIO},
    {0u, 2u, P2_2, HSIOM_SEL_GPIO},
    {0u, 3u, P2_3, HSIOM_SEL_GPIO},
    {0u, 4u, P2_4, HSIOM_SEL_GPIO},
};

/* Connections for: pass_tr_sar_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_tr_sar_out[1] = {
    {0u, 0u, P1_2, P1_2_PASS0_TR_SAR_OUT},
};

/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[7] = {
    {3u, 0u, P1_1, P1_1_SCB3_I2C_SCL},
    {1u, 0u, P1_6, P1_6_SCB1_I2C_SCL},
    {5u, 0u, P2_3, P2_3_SCB5_I2C_SCL},
    {4u, 0u, P3_5, P3_5_SCB4_I2C_SCL},
    {0u, 0u, P4_0, P4_0_SCB0_I2C_SCL},
    {2u, 0u, P5_0, P5_0_SCB2_I2C_SCL},
    {6u, 0u, P6_1, P6_1_SCB6_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[7] = {
    {3u, 0u, P1_2, P1_2_SCB3_I2C_SDA},
    {1u, 0u, P1_5, P1_5_SCB1_I2C_SDA},
    {5u, 0u, P2_2, P2_2_SCB5_I2C_SDA},
    {4u, 0u, P3_6, P3_6_SCB4_I2C_SDA},
    {0u, 0u, P4_1, P4_1_SCB0_I2C_SDA},
    {2u, 0u, P5_1, P5_1_SCB2_I2C_SDA},
    {6u, 0u, P6_0, P6_0_SCB6_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[7] = {
    {3u, 0u, P1_1, P1_1_SCB3_SPI_CLK},
    {1u, 0u, P1_6, P1_6_SCB1_SPI_CLK},
    {5u, 0u, P2_3, P2_3_SCB5_SPI_CLK},
    {4u, 0u, P3_5, P3_5_SCB4_SPI_CLK},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_CLK},
    {2u, 0u, P5_0, P5_0_SCB2_SPI_CLK},
    {6u, 0u, P6_1, P6_1_SCB6_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[7] = {
    {3u, 0u, P1_2, P1_2_SCB3_SPI_MISO},
    {1u, 0u, P1_5, P1_5_SCB1_SPI_MISO},
    {5u, 0u, P2_2, P2_2_SCB5_SPI_MISO},
    {0u, 0u, P2_4, P2_4_SCB0_SPI_MISO},
    {4u, 0u, P3_6, P3_6_SCB4_SPI_MISO},
    {2u, 0u, P5_2, P5_2_SCB2_SPI_MISO},
    {6u, 0u, P6_0, P6_0_SCB6_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[5] = {
    {3u, 0u, P1_3, P1_3_SCB3_SPI_MOSI},
    {4u, 0u, P3_0, P3_0_SCB4_SPI_MOSI},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MOSI},
    {2u, 0u, P5_1, P5_1_SCB2_SPI_MOSI},
    {6u, 0u, P6_3, P6_3_SCB6_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[5] = {
    {3u, 0u, P1_4, P1_4_SCB3_SPI_SELECT0},
    {0u, 0u, P2_1, P2_1_SCB0_SPI_SELECT0},
    {4u, 0u, P3_3, P3_3_SCB4_SPI_SELECT0},
    {2u, 0u, P5_3, P5_3_SCB2_SPI_SELECT0},
    {6u, 0u, P6_2, P6_2_SCB6_SPI_SELECT0},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[7] = {
    {3u, 0u, P1_1, P1_1_SCB3_SPI_CLK},
    {1u, 0u, P1_6, P1_6_SCB1_SPI_CLK},
    {5u, 0u, P2_3, P2_3_SCB5_SPI_CLK},
    {4u, 0u, P3_5, P3_5_SCB4_SPI_CLK},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_CLK},
    {2u, 0u, P5_0, P5_0_SCB2_SPI_CLK},
    {6u, 0u, P6_1, P6_1_SCB6_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[7] = {
    {3u, 0u, P1_2, P1_2_SCB3_SPI_MISO},
    {1u, 0u, P1_5, P1_5_SCB1_SPI_MISO},
    {5u, 0u, P2_2, P2_2_SCB5_SPI_MISO},
    {0u, 0u, P2_4, P2_4_SCB0_SPI_MISO},
    {4u, 0u, P3_6, P3_6_SCB4_SPI_MISO},
    {2u, 0u, P5_2, P5_2_SCB2_SPI_MISO},
    {6u, 0u, P6_0, P6_0_SCB6_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[5] = {
    {3u, 0u, P1_3, P1_3_SCB3_SPI_MOSI},
    {4u, 0u, P3_0, P3_0_SCB4_SPI_MOSI},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MOSI},
    {2u, 0u, P5_1, P5_1_SCB2_SPI_MOSI},
    {6u, 0u, P6_3, P6_3_SCB6_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[5] = {
    {3u, 0u, P1_4, P1_4_SCB3_SPI_SELECT0},
    {0u, 0u, P2_1, P2_1_SCB0_SPI_SELECT0},
    {4u, 0u, P3_3, P3_3_SCB4_SPI_SELECT0},
    {2u, 0u, P5_3, P5_3_SCB2_SPI_SELECT0},
    {6u, 0u, P6_2, P6_2_SCB6_SPI_SELECT0},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[5] = {
    {3u, 0u, P1_3, P1_3_SCB3_UART_CTS},
    {0u, 0u, P2_4, P2_4_SCB0_UART_CTS},
    {4u, 0u, P3_0, P3_0_SCB4_UART_CTS},
    {2u, 0u, P5_2, P5_2_SCB2_UART_CTS},
    {6u, 0u, P6_3, P6_3_SCB6_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[5] = {
    {3u, 0u, P1_4, P1_4_SCB3_UART_RTS},
    {0u, 0u, P2_1, P2_1_SCB0_UART_RTS},
    {4u, 0u, P3_3, P3_3_SCB4_UART_RTS},
    {2u, 0u, P5_3, P5_3_SCB2_UART_RTS},
    {6u, 0u, P6_2, P6_2_SCB6_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[6] = {
    {3u, 0u, P1_1, P1_1_SCB3_UART_RX},
    {5u, 0u, P2_3, P2_3_SCB5_UART_RX},
    {4u, 0u, P3_5, P3_5_SCB4_UART_RX},
    {0u, 0u, P4_0, P4_0_SCB0_UART_RX},
    {2u, 0u, P5_0, P5_0_SCB2_UART_RX},
    {6u, 0u, P6_1, P6_1_SCB6_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[7] = {
    {3u, 0u, P1_2, P1_2_SCB3_UART_TX},
    {1u, 0u, P1_5, P1_5_SCB1_UART_TX},
    {5u, 0u, P2_2, P2_2_SCB5_UART_TX},
    {4u, 0u, P3_6, P3_6_SCB4_UART_TX},
    {0u, 0u, P4_1, P4_1_SCB0_UART_TX},
    {2u, 0u, P5_1, P5_1_SCB2_UART_TX},
    {6u, 0u, P6_0, P6_0_SCB6_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[7] = {
    {0u, 4u, P1_3, P1_3_TCPWM_LINE4},
    {0u, 5u, P1_4, P1_4_TCPWM_LINE5},
    {0u, 2u, P2_1, P2_1_TCPWM_LINE2},
    {0u, 3u, P2_4, P2_4_TCPWM_LINE3},
    {0u, 6u, P3_0, P3_0_TCPWM_LINE6},
    {0u, 7u, P3_3, P3_3_TCPWM_LINE7},
    {0u, 0u, P6_2, P6_2_TCPWM_LINE0},
};

/* Connections for: tcpwm_tr_compare_match */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[7] = {
    {0u, 4u, P1_3, P1_3_TCPWM_TR_COMPARE_MATCH4},
    {0u, 5u, P1_4, P1_4_TCPWM_TR_COMPARE_MATCH5},
    {0u, 2u, P2_1, P2_1_TCPWM_TR_COMPARE_MATCH2},
    {0u, 3u, P2_4, P2_4_TCPWM_TR_COMPARE_MATCH3},
    {0u, 6u, P3_0, P3_0_TCPWM_TR_COMPARE_MATCH6},
    {0u, 7u, P3_3, P3_3_TCPWM_TR_COMPARE_MATCH7},
    {0u, 0u, P6_2, P6_2_TCPWM_TR_COMPARE_MATCH0},
};

/* Connections for: tcpwm_tr_in */
/* Since the GPIO pin is not tied to a particular TCPWM resource the channel_num has no value to
   how the connection works. However, the HAL driver needs to know the index of the tcpwm input
   line. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[7] = {
    {0u, 4u, P1_3, P1_3_TCPWM_TR_IN4},
    {0u, 5u, P1_4, P1_4_TCPWM_TR_IN5},
    {0u, 2u, P2_1, P2_1_TCPWM_TR_IN2},
    {0u, 3u, P2_4, P2_4_TCPWM_TR_IN3},
    {0u, 6u, P3_0, P3_0_TCPWM_TR_IN6},
    {0u, 7u, P3_3, P3_3_TCPWM_TR_IN7},
    {0u, 0u, P6_2, P6_2_TCPWM_TR_IN0},
};

/* Connections for: usb_dm */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_dm[1] = {
    {0u, 0u, USBDM, HSIOM_SEL_GPIO},
};

/* Connections for: usb_dp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_dp[1] = {
    {0u, 0u, USBDP, HSIOM_SEL_GPIO},
};

/* Connections for: usb_vbus_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_vbus_det[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: usb_vbus_valid */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_vbus_valid[1] = {
    {0u, 0u, P3_3, P3_3_USB_VBUS_VALID},
};

/* Connections for: usbpd_adc_cmp_out_gpio */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[1] = {
    {0u, 0u, P1_3, P1_3_USBPD0_ADC_CMP_OUT_GPIO0},
};

/* Connections for: usbpd_afc_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[2] = {
    {0u, 0u, P2_3, P2_3_USBPD0_AFC_TX_DATA0},
    {0u, 0u, P3_0, P3_0_USBPD0_AFC_TX_DATA0},
};

/* Connections for: usbpd_afc_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[2] = {
    {0u, 0u, P2_2, P2_2_USBPD0_AFC_TX_DATA_EN},
    {0u, 0u, P2_4, P2_4_USBPD0_AFC_TX_DATA_EN},
};

/* Connections for: usbpd_ddft0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ddft0[1] = {
    {0u, 0u, P4_1, P4_1_USBPD0_DDFT0},
};

/* Connections for: usbpd_ddft1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ddft1[1] = {
    {0u, 0u, P4_0, P4_0_USBPD0_DDFT1},
};

/* Connections for: usbpd_fault_gpio0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio0[1] = {
    {0u, 0u, P1_5, P1_5_USBPD0_FAULT_GPIO0},
};

/* Connections for: usbpd_fault_gpio1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio1[1] = {
    {0u, 0u, P5_0, P5_0_USBPD0_FAULT_GPIO1},
};

/* Connections for: usbpd_gpio_ddft0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[2] = {
    {1u, 0u, P2_4, P2_4_USBPD1_GPIO_DDFT0},
    {0u, 0u, P3_0, P3_0_USBPD0_GPIO_DDFT0},
};

/* Connections for: usbpd_gpio_ddft1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[1] = {
    {0u, 0u, P1_2, P1_2_USBPD0_GPIO_DDFT1},
};

/* Connections for: usbpd_hpd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[1] = {
    {0u, 0u, P1_4, P1_4_USBPD0_HPD},
};

/* Connections for: usbpd_pad_usbphy_dm_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_usbphy_dm_bch_det[1] = {
    {0u, 0u, USBDM, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_pad_usbphy_dp_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_usbphy_dp_bch_det[1] = {
    {0u, 0u, USBDP, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_sbu_dbg1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_dbg1[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_sbu_dbg2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_dbg2[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_sbu_io1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_io1[2] = {
    {1u, 0u, P6_0, HSIOM_SEL_GPIO},
    {0u, 0u, P6_3, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_sbu_io2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_io2[2] = {
    {1u, 0u, P6_1, HSIOM_SEL_GPIO},
    {0u, 0u, P6_2, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_sbu_lsrx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_lsrx[1] = {
    {1u, 0u, P0_0, P0_0_USBPD1_SBU_LSRX},
};

/* Connections for: usbpd_sbu_lstx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_lstx[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_swapt_in */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[1] = {
    {0u, 0u, P2_1, P2_1_USBPD0_SWAPT_IN},
};

/* Connections for: usbpd_swapt_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_out[2] = {
    {0u, 0u, P5_2, P5_2_USBPD0_SWAPT_OUT0},
    {0u, 1u, P5_3, P5_3_USBPD0_SWAPT_OUT1},
};

/* Connections for: usbpd_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[2] = {
    {0u, 0u, P1_1, P1_1_USBPD0_TX_DATA},
    {1u, 0u, P5_1, P5_1_USBPD1_TX_DATA},
};

/* Connections for: usbpd_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[1] = {
    {0u, 0u, P5_5, P5_5_USBPD0_TX_DATA_EN},
};

#endif
