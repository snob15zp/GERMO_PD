# CAT2 (PMG/PSoC™ 4) Hardware Abstraction Layer (HAL) Release Notes
The CAT2 Hardware Abstraction Layer (HAL) provides an implementation of the Hardware Abstraction Layer for the PMG & PSoC™ 4 chip families. This API provides convenience methods for initializing and manipulating different hardware peripherals. Depending on the specific chip being used, not all features may be supported.

### What's Included?
This release of the CAT2 HAL includes support for the following drivers:
* ADC
* Clock
* Comparator
* CRC
* DMA
* EZ-I2C
* Flash
* GPIO
* Hardware Manager
* I2C
* I2S
* LowPower Timer (LPTimer)
* OpAmp
* Power Management (SysPM)
* PWM
* Quadrature Decoder (QuadDec)
* SPI
* System
* TDM
* Timer
* True Random Number Generator (TRNG)
* UART
* WDT

The following HAL drivers are not supported on CAT2 as none of the devices in ModusToolbox™ have the necessary hardware support:
* DAC
* PDM/PCM
* QSPI
* RTC
* SDHC
* SDIO
* USB Device

### What Changed?
#### v2.0.0
This major version update includes changes that break API compatibility with prior releases. Each major or breaking change is described below:
* Clock:
  1. Renamed cyhal_resource_inst_t CYHAL_CLOCK_&lt;name&gt; constants with CYHAL_CLOCK_RSC_&lt;name&gt;. Created new CYHAL_CLOCK_&lt;name&gt; constants of type cyhal_clock_t.
  2. Replaced cyhal_clock_init with cyhal_clock_reserve.
* DMA:
  1. cyhal_dma_enable must be called after configuring the DMA, but before a trigger will initiate a transfer
* Flash:
  1. The data buffer passed to functions must be from SRAM, the driver no longer contains a scratch buffer to copy into.
* GPIO:
  1. cyhal_gpio_enable_output updated to require a new argument to specify whether the signal is level or edge based.
  2. cyhal_gpio_connect_digital no longer takes the signal type parameter.
  3. cyhal_gpio_register_callback now takes a structure containing details about the callback.
  4. Removed deprecated functions cyhal_gpio_register_irq & cyhal_gpio_irq_enable
* I2C:
  1. Removed deprecated functions cyhal_i2c_register_irq & cyhal_i2c_irq_enable
* PWM:
  1. cyhal_pwm_connect_digital no longer takes the signal type parameter.
  2. cyhal_pwm_init will always produce a non-inverted waveform on the specified pin, even if that pin natively produces an inverted
     output (for example, the `line_compl` pins on PSoC™ devices). This improves consistency with the behavior of cyhal_pwm_init_adv.
* Timer:
  1. cyhal_timer_connect_digital no longer takes the signal type parameter.
* I2C:
  1. The following deprecated functions have been removed: cyhal_i2c_slave_config_write_buff, cyhal_i2c_slave_config_read_buff.
* Added support for new drivers: Comparator, CRC, I2S, OpAmp, TDM, TRNG
NOTE: This version requires core-lib 1.3.0 or later
NOTE: This version requires mtb-pdl-cat2 v1.3.0 or later
#### v1.1.0
* Added support for additional devices
* Extended System driver to support registering for other interrupts
* Fixed issues with level trigger signals to the DMA driver
* Fixed a few bugs in various drivers
#### v1.0.1
* Added support for additional devices
#### v1.0.0
* Initial production release (ADC, Clock, DMA, EZ-I2C, Flash, GPIO, Hardware Manager, I2C, LPTimer, PWM, QuadDec, SPI, System, SysPM, Timer, UART, WDT)
#### v0.5.0
* Initial pre-production release (Clock, EZ-I2C, GPIO, Hardware Manager, I2C, PWM, SPI, System, Timer, UART, WDT)

### Supported Software and Tools
This version of the CAT2 Hardware Abstraction Layer was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ Software Environment        | 2.4.0   |
| GCC Compiler                              | 10.3.1  |
| IAR Compiler                              | 8.4     |
| ARM Compiler                              | 6.11    |

Minimum required ModusToolbox™ Software Environment: v2.2

### More information
Use the following links for more information, as needed:
* [API Reference Guide](https://infineon.github.io/mtb-hal-cat2/html/modules.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2021.
