/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the PMG1 MCU: USB PD DRP EPR single port Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "config.h"

#include "cy_sw_timer.h"
#include "cy_usbpd_common.h"
#include "cy_pdstack_common.h"
#include "cy_usbpd_typec.h"
#include "cy_pdstack_dpm.h"
#include "cy_usbpd_vbus_ctrl.h"
#include "cy_usbpd_phy.h"
#include "instrumentation.h"
#include "app.h"
#include "pdo.h"
#include "psink.h"
#include "psource.h"
#include "swap.h"
#include "vdm.h"
#include "ncp81239.h"
#include "mtbcfg_ezpd.h"
#include "SC8815_HV.h"

/* LED blink rate in milliseconds */
uint16_t gl_LedBlinkRate = 1000;

cy_stc_sw_timer_t        gl_TimerCtx;
cy_stc_usbpd_context_t   gl_UsbPdPort0Ctx;

cy_stc_pdstack_context_t gl_PdStackPort0Ctx;

const cy_stc_pdstack_dpm_params_t pdstack_port0_dpm_params =
{
        .dpmSnkWaitCapPeriod = 400,
        .dpmRpAudioAcc = CY_PD_RP_TERM_RP_CUR_DEF,
        .dpmDefCableCap = 300,
        .muxEnableDelayPeriod = 0,
        .typeCSnkWaitCapPeriod = 0,
        .defCur = 90
};

cy_stc_pdstack_context_t * gl_PdStackContexts[NO_OF_TYPEC_PORTS] =
{
        &gl_PdStackPort0Ctx,
};

bool mux_ctrl_init(uint8_t port)
{
    /* No MUXes to be controlled on the PMG1 prototyping kits. */
    CY_UNUSED_PARAMETER(port);
    return true;
}

const cy_stc_sysint_t wdt_interrupt_config =
{
    .intrSrc = (IRQn_Type)srss_interrupt_wdt_IRQn,
    .intrPriority = 0U,
};

const cy_stc_sysint_t usbpd_port0_intr0_config =
{
    .intrSrc = (IRQn_Type)mtb_usbpd_port0_IRQ,
    .intrPriority = 0U,
};

const cy_stc_sysint_t usbpd_port0_intr1_config =
{
    .intrSrc = (IRQn_Type)mtb_usbpd_port0_DS_IRQ,
    .intrPriority = 0U,
};

#if DEBUG_LOG
const cyhal_uart_cfg_t uartConfig =
{
    .data_bits      = 8,
    .stop_bits      = 1,
    .parity         = CYHAL_UART_PARITY_NONE,
    .rx_buffer      = NULL,
    .rx_buffer_size = 0
};
#endif

cy_stc_pdstack_context_t *get_pdstack_context(uint8_t portIdx)
{
    return (gl_PdStackContexts[portIdx]);
}

/* Solution PD event handler */
void sln_pd_event_handler(cy_stc_pdstack_context_t* ctx, cy_en_pdstack_app_evt_t evt, const void *data)
{
    /* Nothing to do at present. */
    (void)ctx;
    (void)evt;
    (void)data;
}

void instrumentation_cb(uint8_t port, inst_evt_t evt)
{
    uint8_t evt_offset = APP_TOTAL_EVENTS;
    evt += evt_offset;
    sln_pd_event_handler(&gl_PdStackPort0Ctx, (cy_en_pdstack_app_evt_t)evt, NULL);
}

static void wdt_interrupt_handler(void)
{
    /* Clear WDT pending interrupt */
    Cy_WDT_ClearInterrupt();

#if (TIMER_TICKLESS_ENABLE == 0)
    /* Load the timer match register. */
    Cy_WDT_SetMatch((Cy_WDT_GetCount() + gl_TimerCtx.gl_multiplier))
#endif /* (TIMER_TICKLESS_ENABLE == 0) */

    /* Invoke the timer handler. */
    cy_sw_timer_interrupt_handler (&(gl_TimerCtx));
}

static void cy_usbpd0_intr0_handler(void)
{
    Cy_USBPD_Intr0Handler(&gl_UsbPdPort0Ctx);
}

static void cy_usbpd0_intr1_handler(void)
{
    Cy_USBPD_Intr1Handler(&gl_UsbPdPort0Ctx);
}

#if APP_FW_LED_ENABLE
void led_timer_cb (
        cy_timer_id_t id,           /**< Timer ID for which callback is being generated. */
        void *callbackContext)       /**< Timer module Context. */
{
    /* Toggle the User LED and re-start timer to schedule the next toggle event. */
    cyhal_gpio_toggle(CYBSP_USER_LED);

    cy_sw_timer_start (&gl_TimerCtx, callbackContext, id, gl_LedBlinkRate, led_timer_cb);
}
#endif /* APP_FW_LED_ENABLE */

cy_stc_pd_dpm_config_t* get_dpm_connect_stat(void)
{
    return &(gl_PdStackPort0Ctx.dpmConfig);
}

/*
 * Application callback functions for the DPM. Since this application
 * uses the functions provided by the stack, loading the stack defaults.
 */
const cy_stc_pdstack_app_cbk_t app_callback =
{
    app_event_handler,
#if (!CY_PD_SINK_ONLY)
    psrc_set_voltage,
    psrc_set_current,
    psrc_enable,
    psrc_disable,
#endif  /* (!CY_PD_SINK_ONLY) */
    vconn_enable,
    vconn_disable,
    vconn_is_present,
    vbus_is_present,
    vbus_discharge_on,
    vbus_discharge_off,
    psnk_set_voltage,
    psnk_set_current,
    psnk_enable,
    psnk_disable,
    eval_src_cap,
#if (!CY_PD_SINK_ONLY)
    eval_rdo,
#endif  /* (!CY_PD_SINK_ONLY) */
    eval_dr_swap,
    eval_pr_swap,
    eval_vconn_swap,
    eval_vdm,
#if CY_PD_REV3_ENABLE
#if (!CY_PD_SINK_ONLY)
    eval_fr_swap,
#endif   /* (!CY_PD_SINK_ONLY) */
#endif /* CY_PD_REV3_ENABLE */
    vbus_get_value,
#if (!CY_PD_SINK_ONLY)
    psrc_get_voltage,
#endif  /* (!CY_PD_SINK_ONLY) */
#if CY_PD_USB4_SUPPORT_ENABLE
   NULL,
#endif
#if ((CY_PD_EPR_ENABLE) && (!CY_PD_SINK_ONLY))
    eval_epr_mode,
    send_epr_cap
#endif /* (CY_PD_EPR_ENABLE) && (!CY_PD_SINK_ONLY) */
};

cy_stc_pdstack_app_cbk_t* app_get_callback_ptr(cy_stc_pdstack_context_t * context)
{
    (void)context;
    /* Solution callback pointer is same for all ports */
    return ((cy_stc_pdstack_app_cbk_t *)(&app_callback));
}

int main(void)
{
    cy_rslt_t result;

    /* Enable this to delay the firmware execution under SWD connect. */
#ifdef BREAK_AT_MAIN
    uint8_t volatile x= 0;
    while(x==0);
#endif /* BREAK_AT_MAIN */

#if DEBUG_LOG
    cyhal_uart_t uartObj;

    const char string[] = "Hello world\r\n";
    size_t stringSize = strlen(string);
#endif

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    sln_pd_event_handler(&gl_PdStackPort0Ctx, APP_EVT_POWER_CYCLE, NULL);
    /*
     * Register the interrupt handler for the watchdog timer. This timer is used to
     * implement the soft timers required by the USB-PD Stack.
     */
    Cy_SysInt_Init(&wdt_interrupt_config, &wdt_interrupt_handler);
    NVIC_EnableIRQ(wdt_interrupt_config.intrSrc);

    /* Initialize the soft timer module. */
    cy_sw_timer_init(&gl_TimerCtx, Cy_SysClk_ClkSysGetFrequency());

#if DEBUG_LOG
    /* Configure and enable the UART peripheral. */
    Cy_SCB_UART_Init(CYBSP_UART_HW, &CYBSP_UART_config, &CYBSP_UART_context);
    Cy_SCB_UART_Enable(CYBSP_UART_HW);
#endif

    /* Enable global interrupts */
    __enable_irq();

#if DEBUG_LOG
    /* Send a string over serial terminal */
    Cy_SCB_UART_PutString(CYBSP_UART_HW, string);
#endif
    /* Enable NCP81239 controller */
    pd_ctrl_init ();

    /* Initialize the instrumentation related data structures. */
    instrumentation_init();

    /* Register callback function to be executed when instrumentation fault occurs. */
    instrumentation_register_cb((instrumentation_cb_t)instrumentation_cb);

    /* Configure and enable the USBPD interrupts */
    Cy_SysInt_Init(&usbpd_port0_intr0_config, &cy_usbpd0_intr0_handler);
    NVIC_EnableIRQ(usbpd_port0_intr0_config.intrSrc);

    Cy_SysInt_Init(&usbpd_port0_intr1_config, &cy_usbpd0_intr1_handler);
    NVIC_EnableIRQ(usbpd_port0_intr1_config.intrSrc);

    /* Initialize the USBPD driver */
    Cy_USBPD_Init(&gl_UsbPdPort0Ctx, 0, mtb_usbpd_port0_HW, mtb_usbpd_port0_HW_TRIM,
            (cy_stc_usbpd_config_t *)&mtb_usbpd_port0_config, get_dpm_connect_stat);

    /* Make sure SCP and RCP blocks have been disabled. */
    Cy_USBPD_Fault_Vbus_ScpDisable(&gl_UsbPdPort0Ctx);
    Cy_USBPD_Fault_Vbus_RcpDisable(&gl_UsbPdPort0Ctx);

    /* Workaround for pd_ctrl_init () bug. Set to 5 V. */
    APP_VBUS_SET_VOLT_P1(5000);
    APP_VBUS_SET_VOLT_P2(5000);
    SC_SetOTGMode(1);

    Cy_GPIO_Clr (SC8815_EN_PORT, SC8815_EN_PIN);

    /* Initialize the Device Policy Manager. */
    Cy_PdStack_Dpm_Init(&gl_PdStackPort0Ctx,
                       &gl_UsbPdPort0Ctx,
                       &mtb_usbpd_port0_pdstack_config,
                       app_get_callback_ptr(&gl_PdStackPort0Ctx),
                       &pdstack_port0_dpm_params,
                       &gl_TimerCtx);

    /* Send NOT_SUPPORTED for DATA RESET message. */
    Cy_PdStack_Dpm_SetDataReset (&gl_PdStackPort0Ctx, false);

    /* Perform application level initialization. */
    app_init(&gl_PdStackPort0Ctx);

    /* Initialize the fault configuration values */
    fault_handler_init_vars(&gl_PdStackPort0Ctx);

    /* Start any timers or tasks associated with application instrumentation. */
    instrumentation_start();

    /* Start the device policy manager operation. This will initialize the USB-PD block and enable connect detection. */
    Cy_PdStack_Dpm_Start(&gl_PdStackPort0Ctx);

#if APP_FW_LED_ENABLE
    /* Configure LED pin as a strong drive output */
    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);

    /* Start a timer that will blink the FW ACTIVE LED. */
    cy_sw_timer_start (&gl_TimerCtx, (void *)&gl_PdStackPort0Ctx, (cy_timer_id_t)LED_TIMER_ID,
            gl_LedBlinkRate, led_timer_cb);
#endif /* APP_FW_LED_ENABLE */

    /*
     * After the initialization is complete, keep processing the USB-PD device policy manager task in a loop.
     * Since this application does not have any other function, the PMG1 device can be placed in "deep sleep"
     * mode for power saving whenever the PD stack and drivers are idle.
     */
#if !CY_PD_SINK_ONLY
    gl_PdStackPort0Ctx.dpmStat.srcCapStartDelay = DELAY_SRC_CAP_START_MS;
#endif /* !CY_PD_SINK_ONLY */

    for (;;)
    {
        /* Handle the device policy tasks for each PD port. */
        Cy_PdStack_Dpm_Task(&gl_PdStackPort0Ctx);

        /* Perform any application level tasks. */
        app_task(&gl_PdStackPort0Ctx);

        /* Perform tasks associated with instrumentation. */
        instrumentation_task();

#if SYS_DEEPSLEEP_ENABLE
        /* If possible, enter deep sleep mode for power saving. */
        system_sleep(&gl_PdStackPort0Ctx, NULL);
#endif /* SYS_DEEPSLEEP_ENABLE */
    }
}

/* [] END OF FILE */
