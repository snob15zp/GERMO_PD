/***************************************************************************//**
* \file cyhal_psoc4100s_35_wlcsp_2.c
*
* \brief
* PSoC4100S device GPIO HAL header for 35-WLCSP-2 package
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

#if defined(_GPIO_PSOC4100S_35_WLCSP_2_H_)
#include "pin_packages/cyhal_psoc4100s_35_wlcsp_2.h"

/* Pin connections */
/* Connections for: lpcomp_dsi_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_dsi_comp[3] = {
    {0u, 0u, P2_7, P2_7_LPCOMP_COMP0},
    {0u, 0u, P4_2, P4_2_LPCOMP_COMP0},
    {0u, 1u, P4_3, P4_3_LPCOMP_COMP1},
};

/* Connections for: lpcomp_inn_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inn_comp[2] = {
    {0u, 0u, P0_1, HSIOM_SEL_GPIO},
    {0u, 1u, P0_3, HSIOM_SEL_GPIO},
};

/* Connections for: lpcomp_inp_comp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inp_comp[2] = {
    {0u, 0u, P0_0, HSIOM_SEL_GPIO},
    {0u, 1u, P0_2, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_dsi_ctb_cmp */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_dsi_ctb_cmp[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_out_10x */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_out_10x[2] = {
    {0u, 0u, P1_2, HSIOM_SEL_GPIO},
    {0u, 1u, P1_3, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_vin_m */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_m[2] = {
    {0u, 0u, P1_1, HSIOM_SEL_GPIO},
    {0u, 1u, P1_4, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_vin_p0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p0[2] = {
    {0u, 0u, P1_0, HSIOM_SEL_GPIO},
    {0u, 1u, P1_5, HSIOM_SEL_GPIO},
};

/* Connections for: opamp_vin_p1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_opamp_vin_p1[2] = {
    {0u, 0u, P1_6, HSIOM_SEL_GPIO},
    {0u, 1u, P1_7, HSIOM_SEL_GPIO},
};

/* Connections for: pass_dsi_sar_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data[12] = {
    {0u, 2u, P0_3, P0_3_PASS0_DSI_SAR_DATA2},
    {0u, 0u, P0_4, P0_4_PASS0_DSI_SAR_DATA0},
    {0u, 1u, P0_5, P0_5_PASS0_DSI_SAR_DATA1},
    {0u, 3u, P1_2, P1_2_PASS0_DSI_SAR_DATA3},
    {0u, 4u, P1_3, P1_3_PASS0_DSI_SAR_DATA4},
    {0u, 5u, P2_6, P2_6_PASS0_DSI_SAR_DATA5},
    {0u, 6u, P2_7, P2_7_PASS0_DSI_SAR_DATA6},
    {0u, 7u, P3_0, P3_0_PASS0_DSI_SAR_DATA7},
    {0u, 8u, P3_1, P3_1_PASS0_DSI_SAR_DATA8},
    {0u, 9u, P4_0, P4_0_PASS0_DSI_SAR_DATA9},
    {0u, 10u, P4_2, P4_2_PASS0_DSI_SAR_DATA10},
    {0u, 11u, P4_3, P4_3_PASS0_DSI_SAR_DATA11},
};

/* Connections for: pass_dsi_sar_data_valid */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_data_valid[1] = {
    {0u, 0u, P0_0, P0_0_PASS0_DSI_SAR_DATA_VALID},
};

/* Connections for: pass_dsi_sar_sample_done */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_dsi_sar_sample_done[1] = {
    {0u, 0u, P0_2, P0_2_PASS0_DSI_SAR_SAMPLE_DONE},
};

/* Connections for: pass_sar_ext_vref0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref0[1] = {
    {0u, 0u, P1_7, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sar_ext_vref1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_vref1[1] = {
    {0u, 0u, P1_7, HSIOM_SEL_GPIO},
};

/* Connections for: pass_sarmux_pads */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[6] = {
    {0u, 2u, P2_2, HSIOM_SEL_GPIO},
    {0u, 3u, P2_3, HSIOM_SEL_GPIO},
    {0u, 4u, P2_4, HSIOM_SEL_GPIO},
    {0u, 5u, P2_5, HSIOM_SEL_GPIO},
    {0u, 6u, P2_6, HSIOM_SEL_GPIO},
    {0u, 7u, P2_7, HSIOM_SEL_GPIO},
};

/* Connections for: pass_tr_sar_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_tr_sar_out[1] = {
    {0u, 0u, P0_1, P0_1_PASS0_TR_SAR_OUT},
};

/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[6] = {
    {2u, 0u, P0_0, P0_0_SCB2_I2C_SCL},
    {1u, 0u, P0_4, P0_4_SCB1_I2C_SCL},
    {0u, 0u, P1_0, P1_0_SCB0_I2C_SCL},
    {2u, 0u, P1_2, P1_2_SCB2_I2C_SCL},
    {1u, 0u, P3_0, P3_0_SCB1_I2C_SCL},
    {0u, 0u, P4_0, P4_0_SCB0_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[6] = {
    {2u, 0u, P0_1, P0_1_SCB2_I2C_SDA},
    {1u, 0u, P0_5, P0_5_SCB1_I2C_SDA},
    {0u, 0u, P1_1, P1_1_SCB0_I2C_SDA},
    {2u, 0u, P1_3, P1_3_SCB2_I2C_SDA},
    {1u, 0u, P3_1, P3_1_SCB1_I2C_SDA},
    {0u, 0u, P4_1, P4_1_SCB0_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[6] = {
    {1u, 0u, P0_6, P0_6_SCB1_SPI_CLK},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_CLK},
    {2u, 0u, P1_7, P1_7_SCB2_SPI_CLK},
    {1u, 0u, P2_2, P2_2_SCB1_SPI_CLK},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_CLK},
    {0u, 0u, P4_2, P4_2_SCB0_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[4] = {
    {1u, 0u, P0_5, P0_5_SCB1_SPI_MISO},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_MISO},
    {1u, 0u, P3_1, P3_1_SCB1_SPI_MISO},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[5] = {
    {1u, 0u, P0_4, P0_4_SCB1_SPI_MOSI},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MOSI},
    {2u, 0u, P2_7, P2_7_SCB2_SPI_MOSI},
    {1u, 0u, P3_0, P3_0_SCB1_SPI_MOSI},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[6] = {
    {2u, 0u, P0_3, P0_3_SCB2_SPI_SELECT0},
    {1u, 0u, P0_7, P0_7_SCB1_SPI_SELECT0},
    {0u, 0u, P1_3, P1_3_SCB0_SPI_SELECT0},
    {1u, 0u, P2_3, P2_3_SCB1_SPI_SELECT0},
    {1u, 0u, P3_3, P3_3_SCB1_SPI_SELECT0},
    {0u, 0u, P4_3, P4_3_SCB0_SPI_SELECT0},
};

/* Connections for: scb_spi_m_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[4] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_SELECT1},
    {0u, 0u, P1_4, P1_4_SCB0_SPI_SELECT1},
    {1u, 0u, P2_4, P2_4_SCB1_SPI_SELECT1},
    {1u, 0u, P3_4, P3_4_SCB1_SPI_SELECT1},
};

/* Connections for: scb_spi_m_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[3] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_SELECT2},
    {0u, 0u, P1_5, P1_5_SCB0_SPI_SELECT2},
    {1u, 0u, P2_5, P2_5_SCB1_SPI_SELECT2},
};

/* Connections for: scb_spi_m_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[3] = {
    {0u, 0u, P0_2, P0_2_SCB0_SPI_SELECT3},
    {0u, 0u, P1_6, P1_6_SCB0_SPI_SELECT3},
    {1u, 0u, P2_6, P2_6_SCB1_SPI_SELECT3},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[6] = {
    {1u, 0u, P0_6, P0_6_SCB1_SPI_CLK},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_CLK},
    {2u, 0u, P1_7, P1_7_SCB2_SPI_CLK},
    {1u, 0u, P2_2, P2_2_SCB1_SPI_CLK},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_CLK},
    {0u, 0u, P4_2, P4_2_SCB0_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[4] = {
    {1u, 0u, P0_5, P0_5_SCB1_SPI_MISO},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_MISO},
    {1u, 0u, P3_1, P3_1_SCB1_SPI_MISO},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[5] = {
    {1u, 0u, P0_4, P0_4_SCB1_SPI_MOSI},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MOSI},
    {2u, 0u, P2_7, P2_7_SCB2_SPI_MOSI},
    {1u, 0u, P3_0, P3_0_SCB1_SPI_MOSI},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[6] = {
    {2u, 0u, P0_3, P0_3_SCB2_SPI_SELECT0},
    {1u, 0u, P0_7, P0_7_SCB1_SPI_SELECT0},
    {0u, 0u, P1_3, P1_3_SCB0_SPI_SELECT0},
    {1u, 0u, P2_3, P2_3_SCB1_SPI_SELECT0},
    {1u, 0u, P3_3, P3_3_SCB1_SPI_SELECT0},
    {0u, 0u, P4_3, P4_3_SCB0_SPI_SELECT0},
};

/* Connections for: scb_spi_s_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[4] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_SELECT1},
    {0u, 0u, P1_4, P1_4_SCB0_SPI_SELECT1},
    {1u, 0u, P2_4, P2_4_SCB1_SPI_SELECT1},
    {1u, 0u, P3_4, P3_4_SCB1_SPI_SELECT1},
};

/* Connections for: scb_spi_s_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[3] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_SELECT2},
    {0u, 0u, P1_5, P1_5_SCB0_SPI_SELECT2},
    {1u, 0u, P2_5, P2_5_SCB1_SPI_SELECT2},
};

/* Connections for: scb_spi_s_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[3] = {
    {0u, 0u, P0_2, P0_2_SCB0_SPI_SELECT3},
    {0u, 0u, P1_6, P1_6_SCB0_SPI_SELECT3},
    {1u, 0u, P2_6, P2_6_SCB1_SPI_SELECT3},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[5] = {
    {2u, 0u, P0_0, P0_0_SCB2_UART_CTS},
    {1u, 0u, P0_6, P0_6_SCB1_UART_CTS},
    {0u, 0u, P1_2, P1_2_SCB0_UART_CTS},
    {1u, 0u, P3_2, P3_2_SCB1_UART_CTS},
    {0u, 0u, P4_2, P4_2_SCB0_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[5] = {
    {2u, 0u, P0_1, P0_1_SCB2_UART_RTS},
    {1u, 0u, P0_7, P0_7_SCB1_UART_RTS},
    {0u, 0u, P1_3, P1_3_SCB0_UART_RTS},
    {1u, 0u, P3_3, P3_3_SCB1_UART_RTS},
    {0u, 0u, P4_3, P4_3_SCB0_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[5] = {
    {1u, 0u, P0_4, P0_4_SCB1_UART_RX},
    {2u, 0u, P0_4, P0_4_SCB2_UART_RX},
    {0u, 0u, P1_0, P1_0_SCB0_UART_RX},
    {1u, 0u, P3_0, P3_0_SCB1_UART_RX},
    {0u, 0u, P4_0, P4_0_SCB0_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[6] = {
    {1u, 0u, P0_5, P0_5_SCB1_UART_TX},
    {2u, 0u, P0_5, P0_5_SCB2_UART_TX},
    {2u, 0u, P0_6, P0_6_SCB2_UART_TX},
    {0u, 0u, P1_1, P1_1_SCB0_UART_TX},
    {1u, 0u, P3_1, P3_1_SCB1_UART_TX},
    {0u, 0u, P4_1, P4_1_SCB0_UART_TX},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[8] = {
    {0u, 0u, P0_7, P0_7_TCPWM_LINE0},
    {0u, 2u, P1_0, P1_0_TCPWM_LINE2},
    {0u, 3u, P1_2, P1_2_TCPWM_LINE3},
    {0u, 0u, P2_4, P2_4_TCPWM_LINE0},
    {0u, 1u, P2_6, P2_6_TCPWM_LINE1},
    {0u, 0u, P3_0, P3_0_TCPWM_LINE0},
    {0u, 1u, P3_2, P3_2_TCPWM_LINE1},
    {0u, 2u, P3_4, P3_4_TCPWM_LINE2},
};

/* Connections for: tcpwm_line_compl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[6] = {
    {0u, 2u, P1_1, P1_1_TCPWM_LINE_COMPL2},
    {0u, 3u, P1_3, P1_3_TCPWM_LINE_COMPL3},
    {0u, 0u, P2_5, P2_5_TCPWM_LINE_COMPL0},
    {0u, 1u, P2_7, P2_7_TCPWM_LINE_COMPL1},
    {0u, 0u, P3_1, P3_1_TCPWM_LINE_COMPL0},
    {0u, 1u, P3_3, P3_3_TCPWM_LINE_COMPL1},
};

/* Connections for: tcpwm_tr_in */
/* Since the GPIO pin is not tied to a particular TCPWM resource the channel_num has no value to
   how the connection works. However, the HAL driver needs to know the index of the tcpwm input
   line. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_in[5] = {
    {0u, 0u, P0_0, P0_0_TCPWM_TR_IN0},
    {0u, 1u, P0_1, P0_1_TCPWM_TR_IN1},
    {0u, 2u, P1_2, P1_2_TCPWM_TR_IN2},
    {0u, 3u, P1_3, P1_3_TCPWM_TR_IN3},
    {0u, 6u, P3_4, P3_4_TCPWM_TR_IN6},
};

#endif
