/***************************************************************************//**
* \file cyhal_psoc4000s_25_wlcsp.c
*
* \brief
* PSoC4000S device GPIO HAL header for 25-WLCSP package
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

#if defined(_GPIO_PSOC4000S_25_WLCSP_H_)
#include "pin_packages/cyhal_psoc4000s_25_wlcsp.h"

/* Pin connections */
/* Connections for: lpcomp_dsi_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_dsi_comp[3] = {
    {0u, 0u, P2_7, P2_7_LPCOMP_COMP0},
    {0u, 0u, P4_2, P4_2_LPCOMP_COMP0},
    {0u, 1u, P4_3, P4_3_LPCOMP_COMP1},
};

/* Connections for: lpcomp_inn_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inn_comp[1] = {
    {0u, 0u, P0_1, HSIOM_SEL_GPIO},
};

/* Connections for: lpcomp_inp_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inp_comp[1] = {
    {0u, 0u, P0_0, HSIOM_SEL_GPIO},
};

/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[4] = {
    {1u, 0u, P0_4, P0_4_SCB1_I2C_SCL},
    {1u, 0u, P2_0, P2_0_SCB1_I2C_SCL},
    {1u, 0u, P3_0, P3_0_SCB1_I2C_SCL},
    {0u, 0u, P4_0, P4_0_SCB0_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[4] = {
    {1u, 0u, P0_5, P0_5_SCB1_I2C_SDA},
    {1u, 0u, P2_1, P2_1_SCB1_I2C_SDA},
    {1u, 0u, P3_1, P3_1_SCB1_I2C_SDA},
    {0u, 0u, P4_1, P4_1_SCB0_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[4] = {
    {1u, 0u, P0_6, P0_6_SCB1_SPI_CLK},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_CLK},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_CLK},
    {0u, 0u, P4_2, P4_2_SCB0_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[4] = {
    {1u, 0u, P0_5, P0_5_SCB1_SPI_MISO},
    {1u, 0u, P2_1, P2_1_SCB1_SPI_MISO},
    {1u, 0u, P3_1, P3_1_SCB1_SPI_MISO},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[4] = {
    {1u, 0u, P0_4, P0_4_SCB1_SPI_MOSI},
    {1u, 0u, P2_0, P2_0_SCB1_SPI_MOSI},
    {1u, 0u, P3_0, P3_0_SCB1_SPI_MOSI},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[4] = {
    {1u, 0u, P0_7, P0_7_SCB1_SPI_SELECT0},
    {0u, 0u, P1_3, P1_3_SCB0_SPI_SELECT0},
    {1u, 0u, P3_3, P3_3_SCB1_SPI_SELECT0},
    {0u, 0u, P4_3, P4_3_SCB0_SPI_SELECT0},
};

/* Connections for: scb_spi_m_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[1] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_SELECT1},
};

/* Connections for: scb_spi_m_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[1] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_SELECT2},
};

/* Connections for: scb_spi_m_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[1] = {
    {1u, 0u, P2_6, P2_6_SCB1_SPI_SELECT3},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[4] = {
    {1u, 0u, P0_6, P0_6_SCB1_SPI_CLK},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_CLK},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_CLK},
    {0u, 0u, P4_2, P4_2_SCB0_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[4] = {
    {1u, 0u, P0_5, P0_5_SCB1_SPI_MISO},
    {1u, 0u, P2_1, P2_1_SCB1_SPI_MISO},
    {1u, 0u, P3_1, P3_1_SCB1_SPI_MISO},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[4] = {
    {1u, 0u, P0_4, P0_4_SCB1_SPI_MOSI},
    {1u, 0u, P2_0, P2_0_SCB1_SPI_MOSI},
    {1u, 0u, P3_0, P3_0_SCB1_SPI_MOSI},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[4] = {
    {1u, 0u, P0_7, P0_7_SCB1_SPI_SELECT0},
    {0u, 0u, P1_3, P1_3_SCB0_SPI_SELECT0},
    {1u, 0u, P3_3, P3_3_SCB1_SPI_SELECT0},
    {0u, 0u, P4_3, P4_3_SCB0_SPI_SELECT0},
};

/* Connections for: scb_spi_s_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[1] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_SELECT1},
};

/* Connections for: scb_spi_s_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[1] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_SELECT2},
};

/* Connections for: scb_spi_s_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[1] = {
    {1u, 0u, P2_6, P2_6_SCB1_SPI_SELECT3},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[4] = {
    {1u, 0u, P0_6, P0_6_SCB1_UART_CTS},
    {0u, 0u, P1_2, P1_2_SCB0_UART_CTS},
    {1u, 0u, P3_2, P3_2_SCB1_UART_CTS},
    {0u, 0u, P4_2, P4_2_SCB0_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[4] = {
    {1u, 0u, P0_7, P0_7_SCB1_UART_RTS},
    {0u, 0u, P1_3, P1_3_SCB0_UART_RTS},
    {1u, 0u, P3_3, P3_3_SCB1_UART_RTS},
    {0u, 0u, P4_3, P4_3_SCB0_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[3] = {
    {1u, 0u, P0_4, P0_4_SCB1_UART_RX},
    {1u, 0u, P3_0, P3_0_SCB1_UART_RX},
    {0u, 0u, P4_0, P4_0_SCB0_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[3] = {
    {1u, 0u, P0_5, P0_5_SCB1_UART_TX},
    {1u, 0u, P3_1, P3_1_SCB1_UART_TX},
    {0u, 0u, P4_1, P4_1_SCB0_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[5] = {
    {0u, 3u, P1_2, P1_2_TCPWM_LINE3},
    {0u, 4u, P2_0, P2_0_TCPWM_LINE4},
    {0u, 1u, P2_6, P2_6_TCPWM_LINE1},
    {0u, 0u, P3_0, P3_0_TCPWM_LINE0},
    {0u, 1u, P3_2, P3_2_TCPWM_LINE1},
};

/* Connections for: tcpwm_line_compl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[5] = {
    {0u, 3u, P1_3, P1_3_TCPWM_LINE_COMPL3},
    {0u, 4u, P2_1, P2_1_TCPWM_LINE_COMPL4},
    {0u, 1u, P2_7, P2_7_TCPWM_LINE_COMPL1},
    {0u, 0u, P3_1, P3_1_TCPWM_LINE_COMPL0},
    {0u, 1u, P3_3, P3_3_TCPWM_LINE_COMPL1},
};

/* Connections for: tcpwm_tr_in */
/* Since the GPIO pin is not tied to a particular TCPWM resource the channel_num has no value to
   how the connection works. However, the HAL driver needs to know the index of the tcpwm input
   line. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[8] = {
    {0u, 0u, P0_0, P0_0_TCPWM_TR_IN0},
    {0u, 1u, P0_1, P0_1_TCPWM_TR_IN1},
    {0u, 2u, P1_2, P1_2_TCPWM_TR_IN2},
    {0u, 3u, P1_3, P1_3_TCPWM_TR_IN3},
    {0u, 4u, P2_0, P2_0_TCPWM_TR_IN4},
    {0u, 5u, P2_1, P2_1_TCPWM_TR_IN5},
    {0u, 10u, P4_0, P4_0_TCPWM_TR_IN10},
    {0u, 11u, P4_1, P4_1_TCPWM_TR_IN11},
};

#endif
