/***************************************************************************//**
* \file cyhal_pmg1s0_24_qfn_pmg1_s0.c
*
* \brief
* PMG1S0 device GPIO HAL header for 24-QFN-PMG1-S0 package
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

#if defined(_GPIO_PMG1S0_24_QFN_PMG1_S0_H_)
#include "pin_packages/cyhal_pmg1s0_24_qfn_pmg1_s0.h"

/* Pin connections */
/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[3] = {
    {0u, 0u, P0_1, P0_1_SCB0_I2C_SCL},
    {1u, 0u, P1_1, P1_1_SCB1_I2C_SCL},
    {1u, 0u, P2_3, P2_3_SCB1_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[3] = {
    {0u, 0u, P0_0, P0_0_SCB0_I2C_SDA},
    {1u, 0u, P1_0, P1_0_SCB1_I2C_SDA},
    {1u, 0u, P2_2, P2_2_SCB1_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[2] = {
    {0u, 0u, P1_3, P1_3_SCB0_SPI_CLK},
    {1u, 0u, P2_1, P2_1_SCB1_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[2] = {
    {1u, 0u, P0_1, P0_1_SCB1_SPI_MISO},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[2] = {
    {1u, 0u, P0_0, P0_0_SCB1_SPI_MOSI},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[2] = {
    {0u, 0u, P1_0, P1_0_SCB0_SPI_SELECT0},
    {1u, 0u, P2_0, P2_0_SCB1_SPI_SELECT0},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[2] = {
    {0u, 0u, P1_3, P1_3_SCB0_SPI_CLK},
    {1u, 0u, P2_1, P2_1_SCB1_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[2] = {
    {1u, 0u, P0_1, P0_1_SCB1_SPI_MISO},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[2] = {
    {1u, 0u, P0_0, P0_0_SCB1_SPI_MOSI},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[2] = {
    {0u, 0u, P1_0, P1_0_SCB0_SPI_SELECT0},
    {1u, 0u, P2_0, P2_0_SCB1_SPI_SELECT0},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[2] = {
    {0u, 0u, P0_0, P0_0_SCB0_UART_CTS},
    {1u, 0u, P1_0, P1_0_SCB1_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[2] = {
    {0u, 0u, P0_1, P0_1_SCB0_UART_RTS},
    {1u, 0u, P1_1, P1_1_SCB1_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[4] = {
    {1u, 0u, P1_3, P1_3_SCB1_UART_RX},
    {0u, 0u, P2_1, P2_1_SCB0_UART_RX},
    {0u, 0u, P2_3, P2_3_SCB0_UART_RX},
    {1u, 0u, P3_1, P3_1_SCB1_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[4] = {
    {1u, 0u, P1_2, P1_2_SCB1_UART_TX},
    {0u, 0u, P2_0, P2_0_SCB0_UART_TX},
    {0u, 0u, P2_2, P2_2_SCB0_UART_TX},
    {1u, 0u, P3_0, P3_0_SCB1_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[8] = {
    {0u, 0u, P0_0, P0_0_TCPWM_LINE0},
    {0u, 1u, P0_1, P0_1_TCPWM_LINE1},
    {0u, 2u, P1_0, P1_0_TCPWM_LINE2},
    {0u, 3u, P1_1, P1_1_TCPWM_LINE3},
    {0u, 2u, P2_0, P2_0_TCPWM_LINE2},
    {0u, 3u, P2_1, P2_1_TCPWM_LINE3},
    {0u, 0u, P2_2, P2_2_TCPWM_LINE0},
    {0u, 1u, P2_3, P2_3_TCPWM_LINE1},
};

/* Connections for: tcpwm_tr_compare_match */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[4] = {
    {0u, 0u, P0_0, P0_0_TCPWM_TR_COMPARE_MATCH0},
    {0u, 1u, P0_1, P0_1_TCPWM_TR_COMPARE_MATCH1},
    {0u, 2u, P2_0, P2_0_TCPWM_TR_COMPARE_MATCH2},
    {0u, 3u, P2_1, P2_1_TCPWM_TR_COMPARE_MATCH3},
};

/* Connections for: tcpwm_tr_in */
/* Since the GPIO pin is not tied to a particular TCPWM resource the channel_num has no value to
   how the connection works. However, the HAL driver needs to know the index of the tcpwm input
   line. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[7] = {
    {0u, 1u, P0_0, P0_0_TCPWM_TR_IN1},
    {0u, 2u, P0_1, P0_1_TCPWM_TR_IN2},
    {0u, 0u, P1_1, P1_1_TCPWM_TR_IN0},
    {0u, 3u, P2_0, P2_0_TCPWM_TR_IN3},
    {0u, 4u, P2_1, P2_1_TCPWM_TR_IN4},
    {0u, 5u, P2_2, P2_2_TCPWM_TR_IN5},
    {0u, 6u, P2_3, P2_3_TCPWM_TR_IN6},
};

/* Connections for: tcpwm_tr_overflow */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_overflow[4] = {
    {0u, 0u, P1_0, P1_0_TCPWM_TR_OVERFLOW0},
    {0u, 1u, P1_1, P1_1_TCPWM_TR_OVERFLOW1},
    {0u, 2u, P1_2, P1_2_TCPWM_TR_OVERFLOW2},
    {0u, 3u, P1_3, P1_3_TCPWM_TR_OVERFLOW3},
};

/* Connections for: usbpd_adc_cmp_out_gpio */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_adc_cmp_out_gpio[2] = {
    {0u, 1u, P1_0, P1_0_USBPD0_ADC_CMP_OUT_GPIO1},
    {0u, 0u, P1_2, P1_2_USBPD0_ADC_CMP_OUT_GPIO0},
};

/* Connections for: usbpd_afc_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data[2] = {
    {0u, 0u, P2_2, P2_2_USBPD0_AFC_TX_DATA0},
    {0u, 1u, P2_3, P2_3_USBPD0_AFC_TX_DATA1},
};

/* Connections for: usbpd_afc_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_afc_tx_data_en[1] = {
    {0u, 0u, P3_1, P3_1_USBPD0_AFC_TX_DATA_EN},
};

/* Connections for: usbpd_fault_gpio0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio0[1] = {
    {0u, 0u, P1_0, P1_0_USBPD0_FAULT_GPIO0},
};

/* Connections for: usbpd_fault_gpio1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_fault_gpio1[1] = {
    {0u, 0u, P1_1, P1_1_USBPD0_FAULT_GPIO1},
};

/* Connections for: usbpd_gpio_ddft0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[1] = {
    {0u, 0u, P2_3, P2_3_USBPD0_GPIO_DDFT0},
};

/* Connections for: usbpd_gpio_ddft1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[1] = {
    {0u, 0u, P2_2, P2_2_USBPD0_GPIO_DDFT1},
};

/* Connections for: usbpd_gpio_rx_frs */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_rx_frs[1] = {
    {0u, 0u, P1_3, P1_3_USBPD0_GPIO_RX_FRS},
};

/* Connections for: usbpd_hpd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[1] = {
    {0u, 0u, P1_2, P1_2_USBPD0_HPD},
};

/* Connections for: usbpd_sbu_io */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu_io[2] = {
    {0u, 0u, P2_2, HSIOM_SEL_GPIO},
    {0u, 1u, P2_3, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_swapt_in */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[1] = {
    {0u, 0u, P1_3, P1_3_USBPD0_SWAPT_IN},
};

/* Connections for: usbpd_swapt_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_out[2] = {
    {0u, 0u, P2_0, P2_0_USBPD0_SWAPT_OUT0},
    {0u, 1u, P2_1, P2_1_USBPD0_SWAPT_OUT1},
};

/* Connections for: usbpd_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[1] = {
    {0u, 0u, P3_0, P3_0_USBPD0_TX_DATA},
};

/* Connections for: usbpd_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[1] = {
    {0u, 0u, P1_1, P1_1_USBPD0_TX_DATA_EN},
};

/* Connections for: usbpd_usbphy_dm_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dm_bch_det[2] = {
    {0u, 1u, P1_3, HSIOM_SEL_GPIO},
    {0u, 0u, P3_1, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_usbphy_dp_bch_det */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_usbphy_dp_bch_det[2] = {
    {0u, 1u, P1_2, HSIOM_SEL_GPIO},
    {0u, 0u, P3_0, HSIOM_SEL_GPIO},
};

#endif
