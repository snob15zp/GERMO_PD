/***************************************************************************//**
* \file cyhal_ccg7s_40_qfn.c
*
* \brief
* CCG7S device GPIO HAL header for 40-QFN package
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

#if defined(_GPIO_CCG7S_40_QFN_H_)
#include "pin_packages/cyhal_ccg7s_40_qfn.h"

/* Pin connections */
/* Connections for: pass_dsi_sar_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data[5] = {
    {0u, 11u, P0_0, P0_0_PASS0_DSI_SAR_DATA11},
    {0u, 10u, P0_1, P0_1_PASS0_DSI_SAR_DATA10},
    {0u, 2u, P2_2, P2_2_PASS0_DSI_SAR_DATA2},
    {0u, 1u, P3_0, P3_0_PASS0_DSI_SAR_DATA1},
    {0u, 0u, P3_1, P3_1_PASS0_DSI_SAR_DATA0},
};

/* Connections for: pass_dsi_sar_data_valid */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data_valid[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: pass_dsi_sar_sample_done */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_sample_done[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sar_ext_vref0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref0[1] = {
    {0u, 0u, P2_2, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sar_ext_vref1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref1[1] = {
    {0u, 0u, P2_2, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sarmux_pads */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[5] = {
    {0u, 0u, P1_0, HSIOM_SEL_GPIO},
    {0u, 1u, P1_1, HSIOM_SEL_GPIO},
    {0u, 2u, P1_2, HSIOM_SEL_GPIO},
    {0u, 3u, P1_3, HSIOM_SEL_GPIO},
    {0u, 4u, P1_4, HSIOM_SEL_GPIO},
};

/* Connections for: pass_tr_sar_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_tr_sar_out[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[3] = {
    {2u, 0u, P1_1, P1_1_SCB2_I2C_SCL},
    {1u, 0u, P1_3, P1_3_SCB1_I2C_SCL},
    {0u, 0u, P3_1, P3_1_SCB0_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[3] = {
    {2u, 0u, P1_0, P1_0_SCB2_I2C_SDA},
    {1u, 0u, P1_2, P1_2_SCB1_I2C_SDA},
    {0u, 0u, P3_0, P3_0_SCB0_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[3] = {
    {2u, 0u, P0_1, P0_1_SCB2_SPI_CLK},
    {1u, 0u, P1_3, P1_3_SCB1_SPI_CLK},
    {0u, 0u, P3_1, P3_1_SCB0_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[3] = {
    {2u, 0u, P0_0, P0_0_SCB2_SPI_MISO},
    {1u, 0u, P1_2, P1_2_SCB1_SPI_MISO},
    {0u, 0u, P2_2, P2_2_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[3] = {
    {2u, 0u, P0_2, P0_2_SCB2_SPI_MOSI},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MOSI},
    {1u, 0u, P3_0, P3_0_SCB1_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[3] = {
    {2u, 0u, P0_3, P0_3_SCB2_SPI_SELECT0},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_SELECT0},
    {1u, 0u, P1_4, P1_4_SCB1_SPI_SELECT0},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[3] = {
    {2u, 0u, P0_1, P0_1_SCB2_SPI_CLK},
    {1u, 0u, P1_3, P1_3_SCB1_SPI_CLK},
    {0u, 0u, P3_1, P3_1_SCB0_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[3] = {
    {2u, 0u, P0_0, P0_0_SCB2_SPI_MISO},
    {1u, 0u, P1_2, P1_2_SCB1_SPI_MISO},
    {0u, 0u, P2_2, P2_2_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[3] = {
    {2u, 0u, P0_2, P0_2_SCB2_SPI_MOSI},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MOSI},
    {1u, 0u, P3_0, P3_0_SCB1_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[3] = {
    {2u, 0u, P0_3, P0_3_SCB2_SPI_SELECT0},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_SELECT0},
    {1u, 0u, P1_4, P1_4_SCB1_SPI_SELECT0},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[2] = {
    {0u, 0u, P1_0, P1_0_SCB0_UART_CTS},
    {1u, 0u, P2_2, P2_2_SCB1_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[2] = {
    {0u, 0u, P1_1, P1_1_SCB0_UART_RTS},
    {1u, 0u, P1_4, P1_4_SCB1_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[2] = {
    {1u, 0u, P1_3, P1_3_SCB1_UART_RX},
    {0u, 0u, P3_1, P3_1_SCB0_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[2] = {
    {1u, 0u, P1_2, P1_2_SCB1_UART_TX},
    {0u, 0u, P3_0, P3_0_SCB0_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[8] = {
    {0u, 0u, P0_2, P0_2_TCPWM_LINE0},
    {0u, 1u, P0_3, P0_3_TCPWM_LINE1},
    {0u, 2u, P0_5, P0_5_TCPWM_LINE2},
    {0u, 3u, P1_0, P1_0_TCPWM_LINE3},
    {0u, 4u, P1_1, P1_1_TCPWM_LINE4},
    {0u, 5u, P1_2, P1_2_TCPWM_LINE5},
    {0u, 6u, P1_3, P1_3_TCPWM_LINE6},
    {0u, 7u, P1_4, P1_4_TCPWM_LINE7},
};

/* Connections for: tcpwm_tr_compare_match */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[8] = {
    {0u, 0u, P0_2, P0_2_TCPWM_TR_COMPARE_MATCH0},
    {0u, 1u, P0_3, P0_3_TCPWM_TR_COMPARE_MATCH1},
    {0u, 2u, P0_5, P0_5_TCPWM_TR_COMPARE_MATCH2},
    {0u, 3u, P1_0, P1_0_TCPWM_TR_COMPARE_MATCH3},
    {0u, 4u, P1_1, P1_1_TCPWM_TR_COMPARE_MATCH4},
    {0u, 5u, P1_2, P1_2_TCPWM_TR_COMPARE_MATCH5},
    {0u, 6u, P1_3, P1_3_TCPWM_TR_COMPARE_MATCH6},
    {0u, 7u, P1_4, P1_4_TCPWM_TR_COMPARE_MATCH7},
};

/* Connections for: tcpwm_tr_in */
/* Since the GPIO pin is not tied to a particular TCPWM resource the channel_num has no value to
   how the connection works. However, the HAL driver needs to know the index of the tcpwm input
   line. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[5] = {
    {0u, 0u, P0_2, P0_2_TCPWM_TR_IN0},
    {0u, 1u, P0_3, P0_3_TCPWM_TR_IN1},
    {0u, 2u, P0_5, P0_5_TCPWM_TR_IN2},
    {0u, 7u, P1_4, P1_4_TCPWM_TR_IN7},
    {0u, 6u, P2_2, P2_2_TCPWM_TR_IN6},
};

/* Connections for: tcpwm_tr_overflow */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_overflow[8] = {
    {0u, 0u, P0_2, P0_2_TCPWM_TR_OVERFLOW0},
    {0u, 1u, P0_3, P0_3_TCPWM_TR_OVERFLOW1},
    {0u, 2u, P0_5, P0_5_TCPWM_TR_OVERFLOW2},
    {0u, 3u, P1_0, P1_0_TCPWM_TR_OVERFLOW3},
    {0u, 4u, P1_1, P1_1_TCPWM_TR_OVERFLOW4},
    {0u, 5u, P1_2, P1_2_TCPWM_TR_OVERFLOW5},
    {0u, 6u, P1_3, P1_3_TCPWM_TR_OVERFLOW6},
    {0u, 7u, P1_4, P1_4_TCPWM_TR_OVERFLOW7},
};

/* Connections for: usbpd_adc_cmp_out_gpio */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[2] = {
    {0u, 1u, P1_0, P1_0_USBPD0_ADC_CMP_OUT_GPIO1},
    {0u, 0u, P1_1, P1_1_USBPD0_ADC_CMP_OUT_GPIO0},
};

/* Connections for: usbpd_afc_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[1] = {
    {0u, 0u, P3_1, P3_1_USBPD0_AFC_TX_DATA0},
};

/* Connections for: usbpd_afc_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[1] = {
    {0u, 0u, P3_0, P3_0_USBPD0_AFC_TX_DATA_EN},
};

/* Connections for: usbpd_ext_hs1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hs1[1] = {
    {0u, 0u, P0_0, P0_0_USBPD0_EXT_HS1},
};

/* Connections for: usbpd_ext_hs2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hs2[1] = {
    {0u, 0u, P0_2, P0_2_USBPD0_EXT_HS2},
};

/* Connections for: usbpd_ext_hsrcp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hsrcp[1] = {
    {0u, 0u, P0_1, P0_1_USBPD0_EXT_HSRCP},
};

/* Connections for: usbpd_ext_ls1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_ls1[1] = {
    {0u, 0u, P0_1, P0_1_USBPD0_EXT_LS1},
};

/* Connections for: usbpd_ext_ls2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_ls2[1] = {
    {0u, 0u, P0_5, P0_5_USBPD0_EXT_LS2},
};

/* Connections for: usbpd_ext_lszcd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_lszcd[1] = {
    {0u, 0u, P2_2, P2_2_USBPD0_EXT_LSZCD},
};

/* Connections for: usbpd_ext_pwm_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_pwm_out[1] = {
    {0u, 0u, P0_0, P0_0_USBPD0_EXT_PWM_OUT},
};

/* Connections for: usbpd_ext_rst_sw1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_rst_sw1[1] = {
    {0u, 0u, P0_0, P0_0_USBPD0_EXT_RST_SW1},
};

/* Connections for: usbpd_ext_scap_rst */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_scap_rst[1] = {
    {0u, 0u, P0_1, P0_1_USBPD0_EXT_SCAP_RST},
};

/* Connections for: usbpd_ext_scomp_out_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_scomp_out_en[1] = {
    {0u, 0u, P2_2, P2_2_USBPD0_EXT_SCOMP_OUT_EN},
};

/* Connections for: usbpd_ext_set_boost */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_set_boost[1] = {
    {0u, 0u, P0_5, P0_5_USBPD0_EXT_SET_BOOST},
};

/* Connections for: usbpd_ext_set_buck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_set_buck[1] = {
    {0u, 0u, P0_3, P0_3_USBPD0_EXT_SET_BUCK},
};

/* Connections for: usbpd_fault_gpio0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio0[1] = {
    {0u, 0u, P0_5, P0_5_USBPD0_FAULT_GPIO0},
};

/* Connections for: usbpd_fault_gpio1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio1[1] = {
    {0u, 0u, P1_4, P1_4_USBPD0_FAULT_GPIO1},
};

/* Connections for: usbpd_gpio_ddft0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[1] = {
    {0u, 0u, P1_3, P1_3_USBPD0_GPIO_DDFT0},
};

/* Connections for: usbpd_gpio_ddft1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[1] = {
    {0u, 0u, P1_4, P1_4_USBPD0_GPIO_DDFT1},
};

/* Connections for: usbpd_hpd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[2] = {
    {0u, 0u, P0_3, P0_3_USBPD0_HPD},
    {0u, 0u, P1_2, P1_2_USBPD0_HPD},
};

/* Connections for: usbpd_pad_bat2gnd_pulldn */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_bat2gnd_pulldn[1] = {
    {0u, 0u, P0_5, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_pad_lscsa_inp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_lscsa_inp[1] = {
    {0u, 0u, P0_2, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_pad_lscsa_vgnd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_lscsa_vgnd[1] = {
    {0u, 0u, P0_3, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_swapt_in */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[1] = {
    {0u, 0u, P0_3, P0_3_USBPD0_SWAPT_IN},
};

/* Connections for: usbpd_swapt_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_out[2] = {
    {0u, 0u, P0_0, P0_0_USBPD0_SWAPT_OUT0},
    {0u, 1u, P0_1, P0_1_USBPD0_SWAPT_OUT1},
};

/* Connections for: usbpd_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[1] = {
    {0u, 0u, P3_1, P3_1_USBPD0_TX_DATA},
};

/* Connections for: usbpd_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[1] = {
    {0u, 0u, P3_0, P3_0_USBPD0_TX_DATA_EN},
};

/* Connections for: usbpd_usbphy_dm_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dm_bch_det[1] = {
    {0u, 0u, P0_1, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_usbphy_dp_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dp_bch_det[1] = {
    {0u, 0u, P0_0, HSIOM_SEL_GPIO},
};

#endif
