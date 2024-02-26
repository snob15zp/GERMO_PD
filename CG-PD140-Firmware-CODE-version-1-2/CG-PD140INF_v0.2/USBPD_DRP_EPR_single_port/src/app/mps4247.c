/******************************************************************************
* File Name: mps42479.c
*
* Description: This is source code for the MPS EPR power regulator.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/


#include "cy_pdl.h"
#include "cybsp.h"
#include "ncp81239.h"

#if (MPS_28V_REG_ENABLE && (!SC8815_REG_ENABLE))
/* I2C master data rate in Hz */
#define I2CM_DATA_RATE_HZ           (100000U)
#define I2CM_TIMER_PERIOD           (10U)

#define MPS_DEFAULT_ADDR                (0x67u)
#define MPS_PORT_0_SLAVE_ADDR		    (0x67u)
#define MPS_MFR_CTRL4_BIT_7_5_DEFAULT	(0x20u)

#define MPS_VOLT_REG_ADDR			    (0x21u)
#define MPS_MFR_CTRL4_REG_ADDR          (0xD4u)

static cy_stc_scb_i2c_context_t  i2c_context;

/* I2C slave address assigned to NCP81239 controller for each PD port. */
static const uint8_t pd_ctrl_addr[NO_OF_TYPEC_PORTS] =
{
    MPS_PORT_0_SLAVE_ADDR
};

/* Configure the I2C interface. */
void i2cm_init(void)
{
    uint16_t dataRate = 0U;
    Cy_SCB_I2C_Init (SCB5, &I2CM_config, &i2c_context);

    /* Note. This function will have to be changed if the clock divider for the SCB is changed. */
    dataRate = Cy_SCB_I2C_SetDataRate(SCB5, I2CM_DATA_RATE_HZ, Cy_SysClk_PeriphGetFrequency(CY_SYSCLK_DIV_8_BIT, 4U));
    if ((dataRate > I2CM_DATA_RATE_HZ) || (dataRate == 0U))
    {
        return;
    }

    Cy_SCB_I2C_Enable(SCB5, &i2c_context);
}


bool I2C_Write (uint8_t addr, uint8_t *buffer, uint32_t count)
{
	return CY_SCB_I2C_SUCCESS;

	cy_en_scb_i2c_status_t status;
    uint32_t timeout = I2CM_TIMER_PERIOD;

    /* Send Start condition, address and receive ACK/NACK response from slave */
    status = Cy_SCB_I2C_MasterSendStart(SCB5, addr, CY_SCB_I2C_WRITE_XFER, timeout, &i2c_context);
    if (status == CY_SCB_I2C_SUCCESS)
    {
        uint32_t cnt = 0UL;
        /* Write data into the slave from the buffer */
        do
        {
            /* Write byte and receive ACK/NACK response */
            status = Cy_SCB_I2C_MasterWriteByte(SCB5, buffer[cnt], timeout, &i2c_context);
            ++cnt;
        }
        while((status == CY_SCB_I2C_SUCCESS) && (cnt < count));
    }
    /* Check status of transaction */
    if ((status == CY_SCB_I2C_SUCCESS)           ||
            (status == CY_SCB_I2C_MASTER_MANUAL_NAK) ||
            (status == CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK))
    {
        /* Send Stop condition on the bus */
        status = Cy_SCB_I2C_MasterSendStop(SCB5, timeout, &i2c_context);
    }

    return (status == CY_SCB_I2C_SUCCESS) ? true : false;
}

void pd_ctrl_init(void)
{
    /* Configure the I2C interface. */
    i2cm_init ();
}

/* Setting power voltage on MPS controller */
bool set_pd_ctrl_voltage(uint8_t port, uint16_t volt)
{
    uint8_t wr_buf[3];
    uint8_t status;

#if CY_PD_FRS_RX_ENABLE
    /* If fast role swap is enabled, we need to have a 5V supply read at all times. */
    if (volt < CY_PD_VSAFE_5V)
    {
        volt = CY_PD_VSAFE_5V;
    }
#endif /* CY_PD_FRS_RX_ENABLE */

    /* Configure the regulator output voltage. */
    wr_buf[0] = MPS_VOLT_REG_ADDR;
	wr_buf[1] = (volt * 1024) / 1500;
	wr_buf[2] = ((volt * 1024) / 1500) >> 8;

    status = I2C_Write(pd_ctrl_addr[port], wr_buf, 3);
    return (status);
}
#endif /* MPS_28V_REG_ENABLE */
