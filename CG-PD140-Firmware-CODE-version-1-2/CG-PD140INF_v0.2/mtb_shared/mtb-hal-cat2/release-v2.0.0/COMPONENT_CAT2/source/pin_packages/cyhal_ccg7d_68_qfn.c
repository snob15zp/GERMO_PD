/***************************************************************************//**
* \file cyhal_ccg7d_68_qfn.c
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

#include "cy_device_headers.h"
#include "cyhal_hw_types.h"

#if defined(_GPIO_CCG7D_68_QFN_H_)
#include "pin_packages/cyhal_ccg7d_68_qfn.h"

/* Pin connections */
/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[4] = {
    {2u, 0u, P0_3, P0_3_SCB2_I2C_SCL},
    {1u, 0u, P1_5, P1_5_SCB1_I2C_SCL},
    {0u, 0u, P2_1, P2_1_SCB0_I2C_SCL},
    {3u, 0u, P3_1, P3_1_SCB3_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[4] = {
    {2u, 0u, P0_4, P0_4_SCB2_I2C_SDA},
    {1u, 0u, P1_4, P1_4_SCB1_I2C_SDA},
    {0u, 0u, P2_0, P2_0_SCB0_I2C_SDA},
    {3u, 0u, P3_0, P3_0_SCB3_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[4] = {
    {2u, 0u, P0_3, P0_3_SCB2_SPI_CLK},
    {1u, 0u, P1_5, P1_5_SCB1_SPI_CLK},
    {0u, 0u, P2_1, P2_1_SCB0_SPI_CLK},
    {3u, 0u, P3_1, P3_1_SCB3_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[4] = {
    {2u, 0u, P0_1, P0_1_SCB2_SPI_MISO},
    {1u, 0u, P1_6, P1_6_SCB1_SPI_MISO},
    {0u, 0u, P2_0, P2_0_SCB0_SPI_MISO},
    {3u, 0u, P3_0, P3_0_SCB3_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[4] = {
    {2u, 0u, P0_2, P0_2_SCB2_SPI_MOSI},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MOSI},
    {1u, 0u, P1_4, P1_4_SCB1_SPI_MOSI},
    {3u, 0u, P3_2, P3_2_SCB3_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[4] = {
    {1u, 0u, P0_0, P0_0_SCB1_SPI_SELECT0},
    {2u, 0u, P0_4, P0_4_SCB2_SPI_SELECT0},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_SELECT0},
    {3u, 0u, P3_3, P3_3_SCB3_SPI_SELECT0},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[4] = {
    {2u, 0u, P0_3, P0_3_SCB2_SPI_CLK},
    {1u, 0u, P1_5, P1_5_SCB1_SPI_CLK},
    {0u, 0u, P2_1, P2_1_SCB0_SPI_CLK},
    {3u, 0u, P3_1, P3_1_SCB3_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[4] = {
    {2u, 0u, P0_1, P0_1_SCB2_SPI_MISO},
    {1u, 0u, P1_6, P1_6_SCB1_SPI_MISO},
    {0u, 0u, P2_0, P2_0_SCB0_SPI_MISO},
    {3u, 0u, P3_0, P3_0_SCB3_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[4] = {
    {2u, 0u, P0_2, P0_2_SCB2_SPI_MOSI},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MOSI},
    {1u, 0u, P1_4, P1_4_SCB1_SPI_MOSI},
    {3u, 0u, P3_2, P3_2_SCB3_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[4] = {
    {1u, 0u, P0_0, P0_0_SCB1_SPI_SELECT0},
    {2u, 0u, P0_4, P0_4_SCB2_SPI_SELECT0},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_SELECT0},
    {3u, 0u, P3_3, P3_3_SCB3_SPI_SELECT0},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[4] = {
    {1u, 0u, P0_0, P0_0_SCB1_UART_CTS},
    {2u, 0u, P0_2, P0_2_SCB2_UART_CTS},
    {0u, 0u, P1_0, P1_0_SCB0_UART_CTS},
    {3u, 0u, P3_2, P3_2_SCB3_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[4] = {
    {2u, 0u, P0_1, P0_1_SCB2_UART_RTS},
    {0u, 0u, P1_1, P1_1_SCB0_UART_RTS},
    {1u, 0u, P1_6, P1_6_SCB1_UART_RTS},
    {3u, 0u, P3_3, P3_3_SCB3_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[4] = {
    {2u, 0u, P0_3, P0_3_SCB2_UART_RX},
    {1u, 0u, P1_5, P1_5_SCB1_UART_RX},
    {0u, 0u, P2_1, P2_1_SCB0_UART_RX},
    {3u, 0u, P3_1, P3_1_SCB3_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[4] = {
    {2u, 0u, P0_4, P0_4_SCB2_UART_TX},
    {1u, 0u, P1_4, P1_4_SCB1_UART_TX},
    {0u, 0u, P2_0, P2_0_SCB0_UART_TX},
    {3u, 0u, P3_0, P3_0_SCB3_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[12] = {
    {0u, 1u, P0_0, P0_0_TCPWM_LINE1},
    {0u, 0u, P0_1, P0_1_TCPWM_LINE0},
    {0u, 0u, P0_3, P0_3_TCPWM_LINE0},
    {0u, 1u, P0_4, P0_4_TCPWM_LINE1},
    {0u, 2u, P1_0, P1_0_TCPWM_LINE2},
    {0u, 3u, P1_1, P1_1_TCPWM_LINE3},
    {0u, 2u, P1_4, P1_4_TCPWM_LINE2},
    {0u, 3u, P1_5, P1_5_TCPWM_LINE3},
    {0u, 0u, P3_0, P3_0_TCPWM_LINE0},
    {0u, 1u, P3_1, P3_1_TCPWM_LINE1},
    {0u, 2u, P3_2, P3_2_TCPWM_LINE2},
    {0u, 3u, P3_3, P3_3_TCPWM_LINE3},
};

/* Connections for: tcpwm_tr_compare_match */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[8] = {
    {0u, 1u, P0_0, P0_0_TCPWM_TR_COMPARE_MATCH1},
    {0u, 0u, P0_1, P0_1_TCPWM_TR_COMPARE_MATCH0},
    {0u, 3u, P1_5, P1_5_TCPWM_TR_COMPARE_MATCH3},
    {0u, 2u, P1_6, P1_6_TCPWM_TR_COMPARE_MATCH2},
    {0u, 0u, P3_0, P3_0_TCPWM_TR_COMPARE_MATCH0},
    {0u, 1u, P3_1, P3_1_TCPWM_TR_COMPARE_MATCH1},
    {0u, 2u, P3_2, P3_2_TCPWM_TR_COMPARE_MATCH2},
    {0u, 3u, P3_3, P3_3_TCPWM_TR_COMPARE_MATCH3},
};

/* Connections for: tcpwm_tr_overflow */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_overflow[8] = {
    {0u, 1u, P0_0, P0_0_TCPWM_TR_OVERFLOW1},
    {0u, 0u, P0_1, P0_1_TCPWM_TR_OVERFLOW0},
    {0u, 3u, P1_5, P1_5_TCPWM_TR_OVERFLOW3},
    {0u, 2u, P1_6, P1_6_TCPWM_TR_OVERFLOW2},
    {0u, 0u, P3_0, P3_0_TCPWM_TR_OVERFLOW0},
    {0u, 1u, P3_1, P3_1_TCPWM_TR_OVERFLOW1},
    {0u, 2u, P3_2, P3_2_TCPWM_TR_OVERFLOW2},
    {0u, 3u, P3_3, P3_3_TCPWM_TR_OVERFLOW3},
};

/* Connections for: usbpd_adc_cmp_out_gpio */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[3] = {
    {0u, 0u, P0_2, P0_2_USBPD0_ADC_CMP_OUT_GPIO0},
    {0u, 1u, P0_3, P0_3_USBPD0_ADC_CMP_OUT_GPIO1},
    {1u, 0u, P0_4, P0_4_USBPD1_ADC_CMP_OUT_GPIO0},
};

/* Connections for: usbpd_afc_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[2] = {
    {1u, 0u, P0_2, P0_2_USBPD1_AFC_TX_DATA0},
    {0u, 0u, P2_1, P2_1_USBPD0_AFC_TX_DATA0},
};

/* Connections for: usbpd_afc_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[2] = {
    {1u, 0u, P0_1, P0_1_USBPD1_AFC_TX_DATA_EN},
    {0u, 0u, P2_0, P2_0_USBPD0_AFC_TX_DATA_EN},
};

/* Connections for: usbpd_ext_hs1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hs1[2] = {
    {0u, 0u, P1_0, P1_0_USBPD0_EXT_HS1},
    {1u, 0u, P3_0, P3_0_USBPD1_EXT_HS1},
};

/* Connections for: usbpd_ext_hs2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hs2[2] = {
    {0u, 0u, P1_2, P1_2_USBPD0_EXT_HS2},
    {1u, 0u, P3_2, P3_2_USBPD1_EXT_HS2},
};

/* Connections for: usbpd_ext_hsrcp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_hsrcp[2] = {
    {0u, 0u, P1_0, P1_0_USBPD0_EXT_HSRCP},
    {1u, 0u, P1_0, P1_0_USBPD1_EXT_HSRCP},
};

/* Connections for: usbpd_ext_ls1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_ls1[2] = {
    {0u, 0u, P1_1, P1_1_USBPD0_EXT_LS1},
    {1u, 0u, P3_1, P3_1_USBPD1_EXT_LS1},
};

/* Connections for: usbpd_ext_ls2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_ls2[2] = {
    {0u, 0u, P1_3, P1_3_USBPD0_EXT_LS2},
    {1u, 0u, P3_3, P3_3_USBPD1_EXT_LS2},
};

/* Connections for: usbpd_ext_lszcd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_lszcd[2] = {
    {0u, 0u, P1_4, P1_4_USBPD0_EXT_LSZCD},
    {1u, 0u, P1_4, P1_4_USBPD1_EXT_LSZCD},
};

/* Connections for: usbpd_ext_pwm_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_pwm_out[2] = {
    {0u, 0u, P1_1, P1_1_USBPD0_EXT_PWM_OUT},
    {1u, 0u, P1_1, P1_1_USBPD1_EXT_PWM_OUT},
};

/* Connections for: usbpd_ext_rst_sw1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_rst_sw1[2] = {
    {0u, 0u, P0_4, P0_4_USBPD0_EXT_RST_SW1},
    {1u, 0u, P0_4, P0_4_USBPD1_EXT_RST_SW1},
};

/* Connections for: usbpd_ext_scap_rst */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_scap_rst[2] = {
    {0u, 0u, P2_0, P2_0_USBPD0_EXT_SCAP_RST},
    {1u, 0u, P2_0, P2_0_USBPD1_EXT_SCAP_RST},
};

/* Connections for: usbpd_ext_scomp_out_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_scomp_out_en[2] = {
    {0u, 0u, P2_1, P2_1_USBPD0_EXT_SCOMP_OUT_EN},
    {1u, 0u, P2_1, P2_1_USBPD1_EXT_SCOMP_OUT_EN},
};

/* Connections for: usbpd_ext_set_boost */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_set_boost[2] = {
    {0u, 0u, P0_3, P0_3_USBPD0_EXT_SET_BOOST},
    {1u, 0u, P0_3, P0_3_USBPD1_EXT_SET_BOOST},
};

/* Connections for: usbpd_ext_set_buck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_ext_set_buck[2] = {
    {0u, 0u, P0_2, P0_2_USBPD0_EXT_SET_BUCK},
    {1u, 0u, P0_2, P0_2_USBPD1_EXT_SET_BUCK},
};

/* Connections for: usbpd_fault_gpio0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio0[2] = {
    {0u, 0u, P0_2, P0_2_USBPD0_FAULT_GPIO0},
    {1u, 0u, P1_4, P1_4_USBPD1_FAULT_GPIO0},
};

/* Connections for: usbpd_fault_gpio1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio1[2] = {
    {1u, 0u, P1_2, P1_2_USBPD1_FAULT_GPIO1},
    {0u, 0u, P1_3, P1_3_USBPD0_FAULT_GPIO1},
};

/* Connections for: usbpd_gpio_ddft0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[2] = {
    {0u, 0u, P0_1, P0_1_USBPD0_GPIO_DDFT0},
    {1u, 0u, P1_5, P1_5_USBPD1_GPIO_DDFT0},
};

/* Connections for: usbpd_gpio_ddft1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[2] = {
    {0u, 0u, P0_3, P0_3_USBPD0_GPIO_DDFT1},
    {1u, 0u, P0_4, P0_4_USBPD1_GPIO_DDFT1},
};

/* Connections for: usbpd_hpd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[4] = {
    {0u, 0u, P0_0, P0_0_USBPD0_HPD},
    {1u, 0u, P0_1, P0_1_USBPD1_HPD},
    {0u, 0u, P1_5, P1_5_USBPD0_HPD},
    {1u, 0u, P1_6, P1_6_USBPD1_HPD},
};

/* Connections for: usbpd_pad_bat2gnd_pulldn */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_bat2gnd_pulldn[2] = {
    {0u, 0u, P0_2, HSIOM_SEL_GPIO},
    {1u, 0u, P1_4, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_pad_lscsa_inp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_lscsa_inp[2] = {
    {0u, 0u, P0_1, HSIOM_SEL_GPIO},
    {1u, 0u, P1_5, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_pad_lscsa_vgnd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_pad_lscsa_vgnd[2] = {
    {0u, 0u, P0_0, HSIOM_SEL_GPIO},
    {1u, 0u, P1_6, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_swapt_in */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[2] = {
    {0u, 0u, P1_2, P1_2_USBPD0_SWAPT_IN},
    {1u, 0u, P1_3, P1_3_USBPD1_SWAPT_IN},
};

/* Connections for: usbpd_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[2] = {
    {1u, 0u, P2_1, P2_1_USBPD1_TX_DATA},
    {0u, 0u, P3_3, P3_3_USBPD0_TX_DATA},
};

/* Connections for: usbpd_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[2] = {
    {1u, 0u, P2_0, P2_0_USBPD1_TX_DATA_EN},
    {0u, 0u, P3_2, P3_2_USBPD0_TX_DATA_EN},
};

/* Connections for: usbpd_usbphy_dm_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dm_bch_det[2] = {
    {0u, 0u, P1_1, HSIOM_SEL_GPIO},
    {1u, 0u, P1_2, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_usbphy_dp_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dp_bch_det[2] = {
    {0u, 0u, P1_0, HSIOM_SEL_GPIO},
    {1u, 0u, P1_3, HSIOM_SEL_GPIO},
};

#endif
