/***************************************************************************//**
* \file cyhal_pmg1s2_40_qfn_pmg1_s2.c
*
* \brief
* PMG1S2 device GPIO HAL header for 40-QFN-PMG1-S2 package
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

#if defined(_GPIO_PMG1S2_40_QFN_PMG1_S2_H_)
#include "pin_packages/cyhal_pmg1s2_40_qfn_pmg1_s2.h"

/* Pin connections */
/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[4] = {
    {0u, 0u, P0_1, P0_1_SCB0_I2C_SCL},
    {3u, 0u, P1_2, P1_2_SCB3_I2C_SCL},
    {1u, 0u, P2_0, P2_0_SCB1_I2C_SCL},
    {2u, 0u, P3_5, P3_5_SCB2_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[4] = {
    {0u, 0u, P0_0, P0_0_SCB0_I2C_SDA},
    {3u, 0u, P1_3, P1_3_SCB3_I2C_SDA},
    {1u, 0u, P2_1, P2_1_SCB1_I2C_SDA},
    {2u, 0u, P3_4, P3_4_SCB2_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[4] = {
    {3u, 0u, P1_3, P1_3_SCB3_SPI_CLK},
    {1u, 0u, P2_0, P2_0_SCB1_SPI_CLK},
    {0u, 0u, P2_6, P2_6_SCB0_SPI_CLK},
    {2u, 0u, P3_5, P3_5_SCB2_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[6] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_MISO},
    {2u, 0u, P1_0, P1_0_SCB2_SPI_MISO},
    {3u, 0u, P1_4, P1_4_SCB3_SPI_MISO},
    {1u, 0u, P1_6, P1_6_SCB1_SPI_MISO},
    {1u, 0u, P2_4, P2_4_SCB1_SPI_MISO},
    {3u, 0u, P3_6, P3_6_SCB3_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[4] = {
    {3u, 0u, P1_2, P1_2_SCB3_SPI_MOSI},
    {1u, 0u, P2_1, P2_1_SCB1_SPI_MOSI},
    {0u, 0u, P2_5, P2_5_SCB0_SPI_MOSI},
    {2u, 0u, P3_4, P3_4_SCB2_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[6] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_SELECT0},
    {2u, 0u, P1_1, P1_1_SCB2_SPI_SELECT0},
    {3u, 0u, P1_5, P1_5_SCB3_SPI_SELECT0},
    {1u, 0u, P1_7, P1_7_SCB1_SPI_SELECT0},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_SELECT0},
    {3u, 0u, P3_3, P3_3_SCB3_SPI_SELECT0},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[4] = {
    {3u, 0u, P1_3, P1_3_SCB3_SPI_CLK},
    {1u, 0u, P2_0, P2_0_SCB1_SPI_CLK},
    {0u, 0u, P2_6, P2_6_SCB0_SPI_CLK},
    {2u, 0u, P3_5, P3_5_SCB2_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[6] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_MISO},
    {2u, 0u, P1_0, P1_0_SCB2_SPI_MISO},
    {3u, 0u, P1_4, P1_4_SCB3_SPI_MISO},
    {1u, 0u, P1_6, P1_6_SCB1_SPI_MISO},
    {1u, 0u, P2_4, P2_4_SCB1_SPI_MISO},
    {3u, 0u, P3_6, P3_6_SCB3_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[4] = {
    {3u, 0u, P1_2, P1_2_SCB3_SPI_MOSI},
    {1u, 0u, P2_1, P2_1_SCB1_SPI_MOSI},
    {0u, 0u, P2_5, P2_5_SCB0_SPI_MOSI},
    {2u, 0u, P3_4, P3_4_SCB2_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[6] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_SELECT0},
    {2u, 0u, P1_1, P1_1_SCB2_SPI_SELECT0},
    {3u, 0u, P1_5, P1_5_SCB3_SPI_SELECT0},
    {1u, 0u, P1_7, P1_7_SCB1_SPI_SELECT0},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_SELECT0},
    {3u, 0u, P3_3, P3_3_SCB3_SPI_SELECT0},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[4] = {
    {0u, 0u, P0_0, P0_0_SCB0_UART_CTS},
    {3u, 0u, P1_2, P1_2_SCB3_UART_CTS},
    {1u, 0u, P2_0, P2_0_SCB1_UART_CTS},
    {2u, 0u, P3_4, P3_4_SCB2_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[4] = {
    {0u, 0u, P0_1, P0_1_SCB0_UART_RTS},
    {3u, 0u, P1_3, P1_3_SCB3_UART_RTS},
    {1u, 0u, P2_1, P2_1_SCB1_UART_RTS},
    {2u, 0u, P3_5, P3_5_SCB2_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[5] = {
    {2u, 0u, P1_1, P1_1_SCB2_UART_RX},
    {0u, 0u, P1_2, P1_2_SCB0_UART_RX},
    {3u, 0u, P1_5, P1_5_SCB3_UART_RX},
    {1u, 0u, P1_7, P1_7_SCB1_UART_RX},
    {0u, 0u, P2_6, P2_6_SCB0_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[5] = {
    {2u, 0u, P1_0, P1_0_SCB2_UART_TX},
    {0u, 0u, P1_3, P1_3_SCB0_UART_TX},
    {3u, 0u, P1_4, P1_4_SCB3_UART_TX},
    {1u, 0u, P1_6, P1_6_SCB1_UART_TX},
    {0u, 0u, P2_5, P2_5_SCB0_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[6] = {
    {0u, 0u, P0_0, P0_0_TCPWM_LINE0},
    {0u, 1u, P0_1, P0_1_TCPWM_LINE1},
    {0u, 0u, P3_2, P3_2_TCPWM_LINE0},
    {0u, 1u, P3_3, P3_3_TCPWM_LINE1},
    {0u, 2u, P3_4, P3_4_TCPWM_LINE2},
    {0u, 3u, P3_5, P3_5_TCPWM_LINE3},
};

/* Connections for: tcpwm_tr_compare_match */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_compare_match[4] = {
    {0u, 0u, P3_2, P3_2_TCPWM_TR_COMPARE_MATCH0},
    {0u, 1u, P3_3, P3_3_TCPWM_TR_COMPARE_MATCH1},
    {0u, 2u, P3_4, P3_4_TCPWM_TR_COMPARE_MATCH2},
    {0u, 3u, P3_5, P3_5_TCPWM_TR_COMPARE_MATCH3},
};

/* Connections for: tcpwm_tr_overflow */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_overflow[4] = {
    {0u, 0u, P3_2, P3_2_TCPWM_TR_OVERFLOW0},
    {0u, 1u, P3_3, P3_3_TCPWM_TR_OVERFLOW1},
    {0u, 2u, P3_4, P3_4_TCPWM_TR_OVERFLOW2},
    {0u, 3u, P3_5, P3_5_TCPWM_TR_OVERFLOW3},
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
    {0u, 0u, VSSIO_4, HSIOM_SEL_GPIO},
};

/* Connections for: usb_vbus_valid */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_vbus_valid[1] = {
    {0u, 0u, P2_4, P2_4_USB_VBUS_VALID},
};

/* Connections for: usbpd_auxn_io */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_auxn_io[1] = {
    {0u, 0u, P1_7, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_auxp_io */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_auxp_io[1] = {
    {0u, 0u, P1_6, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_cmp_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_cmp_out[4] = {
    {0u, 0u, P0_0, P0_0_USBPD0_CMP_OUT0},
    {0u, 1u, P1_0, P1_0_USBPD0_CMP_OUT1},
    {0u, 0u, P2_6, P2_6_USBPD0_CMP_OUT0},
    {0u, 1u, P3_4, P3_4_USBPD0_CMP_OUT1},
};

/* Connections for: usbpd_gpio_ddft0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft0[1] = {
    {0u, 0u, P2_5, P2_5_USBPD0_GPIO_DDFT0},
};

/* Connections for: usbpd_gpio_ddft1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_gpio_ddft1[1] = {
    {0u, 0u, P2_4, P2_4_USBPD0_GPIO_DDFT1},
};

/* Connections for: usbpd_hpd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_hpd[2] = {
    {0u, 0u, P1_2, P1_2_USBPD0_HPD},
    {0u, 0u, P3_3, P3_3_USBPD0_HPD},
};

/* Connections for: usbpd_sbu1_io */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu1_io[1] = {
    {0u, 0u, P1_4, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_sbu2_io */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_sbu2_io[1] = {
    {0u, 0u, P1_5, HSIOM_SEL_GPIO},
};

/* Connections for: usbpd_swapt_in */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_in[1] = {
    {0u, 0u, P3_6, P3_6_USBPD0_SWAPT_IN},
};

/* Connections for: usbpd_swapt_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_swapt_out[2] = {
    {0u, 1u, P1_1, P1_1_USBPD0_SWAPT_OUT1},
    {0u, 0u, P1_3, P1_3_USBPD0_SWAPT_OUT0},
};

/* Connections for: usbpd_tx_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data[1] = {
    {0u, 0u, P3_2, P3_2_USBPD0_TX_DATA},
};

/* Connections for: usbpd_tx_data_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_usbpd_tx_data_en[1] = {
    {0u, 0u, P3_5, P3_5_USBPD0_TX_DATA_EN},
};

#endif
