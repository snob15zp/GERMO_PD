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
#include "cycfg_peripherals.h"

#if SC8815_REG_ENABLE

#define SC8815_EXTERNAL_FB			1
#define SC8815_EXTERNAL_REF_VAR		1
#define SC8815_FB_RUP_VALUE 		(100000U)
#define SC8815_FB_RDOWN_VALUE 		(7500U) //11000

/* I2C master data rate in Hz */
#define I2CM_DATA_RATE_HZ           (100000U)
#define I2CM_TIMER_PERIOD           (10U)

#define SC8815_DEFAULT_ADDR                (0x74)

#define SC_VBAT_SET                 (0x00)
#define SC_VBUSREF_I_SET            (0x01)
#define SC_VBUSREF_I_SET2           (0x02)
#define SC_VBUSREF_E_SET            (0x03)
#define SC_VBUSREF_E_SET2           (0x04)
#define SC_IBUS_LIM_SET             (0x05)
#define SC_IBAT_LIM_SET             (0x06)
#define SC_VINREG_SET               (0x07)
#define SC_RATIO                    (0x08)
#define SC_CTRL0_SET                (0x09)
#define SC_CTRL1_SET                (0x0A)
#define SC_CTRL2_SET                (0x0B)
#define SC_CTRL3_SET                (0x0C)
#define SC_VBUS_FB_VALUE            (0x0D)
#define SC_VBUS_FB_VALUE2           (0x0E)
#define SC_VBAT_FB_VALUE            (0x0F)
#define SC_VBAT_FB_VALUE2           (0x10)
#define SC_IBUS_VALUE               (0x11)
#define SC_IBUS_VALUE2              (0x12)
#define SC_IBAT_VALUE               (0x13)
#define SC_IBAT_VALUE2              (0x14)
#define SC_ADIN_VALUE               (0x15)
#define SC_ADIN_VALUE_2             (0x16)
#define SC_STATUS                   (0x17)
#define SC_RESERVED1                (0x18)
#define SC_MASK                     (0x19)
#define SC_RESERVED2                (0x1A)
#define SC_RESERVED3                (0x1B)


static cy_stc_scb_i2c_context_t  i2c_context;

/* I2C slave address assigned to NCP81239 controller for each PD port. */
static const uint8_t pd_ctrl_addr[NO_OF_TYPEC_PORTS] =
{
		SC8815_DEFAULT_ADDR
};

#if 0
void SC_SetOTGVoltage(uint16 VoltageValue)
{
	uint16 i;
    // VoltageValue = (SetValue + 1) * 2 * 12.5
    // make sure ration set to 12.5V (default)

#if SC8815_EXTERNAL_FB
    VoltageValue = VoltageValue + 100;  //more 100mV for cover cable compensation
    i = (VoltageValue / 20) - 1;

	SC_I2C_Write(SC_VBUSREF_E_SET,i>>2);
	SC_I2C_Write(SC_VBUSREF_E_SET2,(i&0x03) << 6);
#else
    VoltageValue = VoltageValue + 200;  //more 200mV for cover cable compensation
    i = (VoltageValue / 25) - 1;

	SC_I2C_Write(SC_VBUSREF_I_SET,i>>2);
	SC_I2C_Write(SC_VBUSREF_I_SET2,(i&0x03) << 6);
#endif
}


void SC_SetOTGCurrent(uint16 CurrentValue)
{
	uint16 i;
    // CurrentValue =  (IBUS_LIMI_SET + 1) /256 * IBUS_ratio * ( 10mohm/RS1)
    // make sure IBUS_ratio = 6 , RS1 = 10mohm  ,  if not need change in here
//--VSD    CurrentValue = CurrentValue + (CurrentValue >> 3);
//--VSD	i = (CurrentValue * 256 /3/*~~VSD*/ /1000) - 1;
i = CurrentValue / 22;
    if(i>0xff) i=0xff; //++VSD

	SC_I2C_Write(SC_IBUS_LIM_SET,i);

}
#endif
/* Configure the I2C interface. */
void i2cm_init(void)
{
    uint16_t dataRate = 0U;
    Cy_SCB_I2C_Init (I2CM_HW, &I2CM_config, &i2c_context);

    /* Note. This function will have to be changed if the clock divider for the SCB is changed. */
    dataRate = Cy_SCB_I2C_SetDataRate(I2CM_HW, I2CM_DATA_RATE_HZ, Cy_SysClk_PeriphGetFrequency(CY_SYSCLK_DIV_8_BIT, 4U));
    if ((dataRate > I2CM_DATA_RATE_HZ) || (dataRate == 0U))
    {
        return;
    }

    Cy_SCB_I2C_Enable(I2CM_HW, &i2c_context);
}


bool I2C_Write (uint8_t addr, uint8_t *buffer, uint32_t count)
{
	cy_en_scb_i2c_status_t status;
    uint32_t timeout = I2CM_TIMER_PERIOD;

    /* Send Start condition, address and receive ACK/NACK response from slave */
    status = Cy_SCB_I2C_MasterSendStart(I2CM_HW, addr, CY_SCB_I2C_WRITE_XFER, timeout, &i2c_context);
    if (status == CY_SCB_I2C_SUCCESS)
    {
        uint32_t cnt = 0UL;
        /* Write data into the slave from the buffer */
        do
        {
            /* Write byte and receive ACK/NACK response */
            status = Cy_SCB_I2C_MasterWriteByte(I2CM_HW, buffer[cnt], timeout, &i2c_context);
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
        status = Cy_SCB_I2C_MasterSendStop(I2CM_HW, timeout, &i2c_context);
    }

    return (status == CY_SCB_I2C_SUCCESS) ? true : false;
}

void pd_ctrl_init(void)
{
    uint8_t wr_buf[3];
    /* Configure the I2C interface. */
    i2cm_init ();

//    SC_I2C_Write(SC_RATIO,0x38);  //fix: IBUS ratio set to 3
    wr_buf[0] = SC_RATIO;
	wr_buf[1] = 0x38;
	I2C_Write(pd_ctrl_addr[0], wr_buf, 2);


//    SC_I2C_Write(SC_CTRL2_SET,0x08);  //slew rate set the 1mV/us
    wr_buf[0] = SC_CTRL2_SET;
	wr_buf[1] = 0x08;
	I2C_Write(pd_ctrl_addr[0], wr_buf, 2);

//    SC_I2C_Write(SC_CTRL3_SET,0x22);  //Enable ADC
    wr_buf[0] = SC_CTRL3_SET;
	wr_buf[1] = 0x22;
//	wr_buf[1] = 0x23;		//PFM EN
	I2C_Write(pd_ctrl_addr[0], wr_buf, 2);

#if SC8815_EXTERNAL_FB
    wr_buf[0] = SC_CTRL1_SET;
	wr_buf[1] = 0x11; //use external FB
	I2C_Write(pd_ctrl_addr[0], wr_buf, 2);
#endif
}

/* Setting power voltage on MPS controller */
bool set_pd_ctrl_voltage(uint8_t port, uint16_t volt)
{
    uint8_t wr_buf[3];
    uint8_t status;
	uint16 i;

	if(port != 0) return 0;

#if CY_PD_FRS_RX_ENABLE
    /* If fast role swap is enabled, we need to have a 5V supply read at all times. */
    if (volt < CY_PD_VSAFE_5V)
    {
        volt = CY_PD_VSAFE_5V;
    }
#endif /* CY_PD_FRS_RX_ENABLE */

#if 0
    /* Configure the regulator output voltage. */
    wr_buf[0] = MPS_VOLT_REG_ADDR;
	wr_buf[1] = (volt * 1024) / 1500;
	wr_buf[2] = ((volt * 1024) / 1500) >> 8;
#endif

#if SC8815_EXTERNAL_FB
#if SC8815_EXTERNAL_REF_VAR

uint32 ref_hmux;
uint32 volt_hmv;
ref_hmux = ((SC8815_FB_RUP_VALUE * 100)/SC8815_FB_RDOWN_VALUE) + 100;

volt_hmv = (volt + 200) * 100;//more 200mV for cover cable compensation
i = (volt_hmv/ref_hmux)/2 - 1;

#if (((2820000 / (((SC8815_FB_RUP_VALUE * 100)/SC8815_FB_RDOWN_VALUE) + 100))/2) > 1024)
#error "resistor divider will not work for 28V"
#endif

    wr_buf[0] = SC_VBUSREF_E_SET;
	wr_buf[1] = i>>2;
	status = I2C_Write(pd_ctrl_addr[port], wr_buf, 2);

    wr_buf[0] = SC_VBUSREF_E_SET2;
	wr_buf[1] = (i&0x03) << 6;
	status = I2C_Write(pd_ctrl_addr[port], wr_buf, 2);
#endif
#else
	volt = volt + 200;  //more 200mV for cover cable compensation
    i = (volt / 25) - 1;

//	SC_I2C_Write(SC_VBUSREF_I_SET,i>>2);
//	SC_I2C_Write(SC_VBUSREF_I_SET2,(i&0x03) << 6);

    wr_buf[0] = SC_VBUSREF_I_SET;
	wr_buf[1] = i>>2;
	status = I2C_Write(pd_ctrl_addr[port], wr_buf, 2);

    wr_buf[0] = SC_VBUSREF_I_SET2;
	wr_buf[1] = (i&0x03) << 6;
	status = I2C_Write(pd_ctrl_addr[port], wr_buf, 2);
#endif

	return (status);
}

void SC_SetOTGMode(uint8 On_Off)
{
    uint8_t wr_buf[3];
	if(On_Off)
	{

//		SC_I2C_Write(SC_CTRL0_SET,0x80 | 0x04);  //OTG EN in 300kHz
//		SC_I2C_Write(SC_CTRL0_SET,0x80);        //OTG EN in 150kHz
	    wr_buf[0] = SC_CTRL0_SET;
//		wr_buf[1] = 0x80;			//OTG EN in 150kHz
//		wr_buf[1] = 0x80 | 0x04; 	//OTG EN in 300kHz
		wr_buf[1] = 0x80 | 0x0C; 	//OTG EN in 450kHz
		I2C_Write(pd_ctrl_addr[0], wr_buf, 2);
	}
	else
	{
//	    SC_I2C_Write(SC_CTRL0_SET,0x00 | 0x04);  //OTG DIS in 300kHz
//	    SC_I2C_Write(SC_CTRL0_SET,0x00);        //OTG DIS in 150kHz
	    wr_buf[0] = SC_CTRL0_SET;
//		wr_buf[1] = 0x00;				//OTG DIS in 150kHz
//		wr_buf[1] = 0x00 | 0x04;		//OTG DIS in 300kHz
		wr_buf[1] = 0x00 | 0x0C;		//OTG DIS in 450kHz
		I2C_Write(pd_ctrl_addr[0], wr_buf, 2);
	}

}

#endif /* MPS_28V_REG_ENABLE */
