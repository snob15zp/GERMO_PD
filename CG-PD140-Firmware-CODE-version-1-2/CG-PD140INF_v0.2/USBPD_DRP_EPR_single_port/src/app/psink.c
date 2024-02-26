/******************************************************************************
* File Name: psink.c
*
* Description: This source file implements functions associated with the power
*              consumer path control and fault detection which are part of the
*              PMG1 MCU USB-PD DRP Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#include "cybsp.h"
#include "config.h"
#include "psink.h"
#include "app.h"
#include "cy_sw_timer.h"
#include "cy_sw_timer_id.h"
#include "cy_usbpd_vbus_ctrl.h"

bool gl_psnk_enabled[NO_OF_TYPEC_PORTS] =
{
    false
};

bool app_psnk_vbus_ovp_cbk(void * cbkContext, bool comp_out);

extern cy_stc_pdstack_context_t *get_pdstack_context(uint8_t portIdx);

void sink_fet_off(cy_stc_pdstack_context_t * context)
{
    if (context->port == 0u)
    {
        Cy_GPIO_Clr (PFET_SNK_CTRL_P0_PORT, PFET_SNK_CTRL_P0_PIN);
    }
}

void sink_fet_on(cy_stc_pdstack_context_t * context)
{
    if (context->port == 0u)
    {
        Cy_GPIO_Set (PFET_SNK_CTRL_P0_PORT, PFET_SNK_CTRL_P0_PIN);
    }
}

#if VBUS_OVP_ENABLE
bool app_psnk_vbus_ovp_cbk(void * cbkContext, bool comp_out)
{
    /* Get the PD-Stack context from the USBPD context */
    cy_stc_usbpd_context_t * context = (cy_stc_usbpd_context_t *) cbkContext;
    cy_stc_pdstack_context_t * pdstack_ctx = get_pdstack_context(context->port);

    /* OVP fault */
    sink_fet_off(pdstack_ctx);

    /* Set alert message */
    cy_pd_pd_do_t alert;
    alert.val = 0;
    alert.ado_alert.ovp = true;
    pdstack_ctx->dpmStat.alert = alert;

    /* Notify the application layer about the fault. */
    app_event_handler(pdstack_ctx, APP_EVT_VBUS_OVP_FAULT, NULL);
    return 0;
}
#endif /* VBUS_OVP_ENABLE */

#if VBUS_UVP_ENABLE
bool app_psnk_vbus_uvp_cbk (void * context, bool comp_out)
{
    cy_stc_usbpd_context_t *ptrUsbPdContext = (cy_stc_usbpd_context_t *)context;
    /* Get the PD-Stack context from the USBPD context */
    cy_stc_pdstack_context_t * pdstack_ctx = get_pdstack_context(ptrUsbPdContext->port);

    /* UVP fault */
    sink_fet_off(pdstack_ctx);

    /* Notify the application layer about the fault. */
    app_event_handler(pdstack_ctx, APP_EVT_VBUS_UVP_FAULT, NULL);

    return 0;
}
#endif /* VBUS_UVP_ENABLE */

void psnk_set_voltage (cy_stc_pdstack_context_t * context, uint16_t volt_mV)
{
    app_status_t* app_stat = app_get_status(context->port);
    app_stat->psnk_volt = volt_mV;

    /* Disable VBus discharge when starting off as a SINK device. */
    Cy_USBPD_Vbus_DischargeOff(context->ptrUsbPdContext);

#if VBUS_OVP_ENABLE
    app_ovp_enable(context, volt_mV, false, app_psnk_vbus_ovp_cbk);

#endif /* VBUS_OVP_ENABLE */

#if VBUS_UVP_ENABLE
    app_uvp_enable(context, volt_mV, false, app_psnk_vbus_uvp_cbk);

#endif /* VBUS_UVP_ENABLE */
}

void psnk_set_current (cy_stc_pdstack_context_t * context, uint16_t cur_10mA)
{
    app_status_t* app_stat = app_get_status(context->port);

    /*
     * There is no implementation to update the current settings at present.
     * We are just storing the current value into a variable. This implementation
     * needs to be updated when the PMG1 solution has capability to control the
     * sink current capability.
     */
    app_stat->psnk_cur = cur_10mA;
    if (cur_10mA <= CY_PD_ISAFE_DEF)
    {
        /* Notify the application layer to reduce current consumption to Standby Current. */
        app_event_handler(context, APP_EVT_STANDBY_CURRENT, NULL);

#if SNK_STANDBY_FET_SHUTDOWN_ENABLE
        /* Turn off the Sink FET if not in dead battery condition. */
        if (context->dpmStat.deadBat == false)
        {
            sink_fet_off (context);
            gl_psnk_enabled[context->port] = false;
        }
#endif /* SNK_STANDBY_FET_SHUTDOWN_ENABLE */
    }
}

void psnk_enable (cy_stc_pdstack_context_t * context)
{
    uint8_t intr_state;

    intr_state = Cy_SysLib_EnterCriticalSection();

    /* Make sure discharge path is disabled at this stage. */
    Cy_USBPD_Vbus_DischargeOff(context->ptrUsbPdContext);

    /* Turn on FETs only if dpm is enabled and there is no active fault condition. */
    if ((context->dpmConfig.dpmEnabled) && (context->dpmStat.faultActive == false))
    {
#if (SNK_STANDBY_FET_SHUTDOWN_ENABLE)
        /* Enable the sink path only if we are allowed to draw more than 0.5 A of current. */
        if (app_get_status(context->port)->psnk_cur > CY_PD_ISAFE_DEF)
#endif /* (SNK_STANDBY_FET_SHUTDOWN_ENABLE) */
        {
            if (!gl_psnk_enabled[context->port])
            {
                gl_psnk_enabled[context->port] = true;
                sink_fet_on(context);
            }
        }
    }

    Cy_SysLib_ExitCriticalSection(intr_state);
}

/* Timer Callback */
static void app_psnk_tmr_cbk(cy_timer_id_t id,  void * callbackCtx)
{
    cy_stc_pdstack_context_t * context = callbackCtx;
    uint8_t port = context->port;
    app_status_t* app_stat = app_get_status(port);

    if (context->port != 0u)
    {
        id = (cy_timer_id_t)((uint16_t)id - ((uint16_t)APP_PORT1_TIMER_START_ID - (uint16_t)APP_TIMERS_START_ID));
    }

    switch((cy_sw_timer_id_t)id)
    {
        case APP_PSINK_DIS_TIMER:
            cy_sw_timer_stop(context->ptrTimerContext,
                    CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_MONITOR_TIMER));
            Cy_USBPD_Vbus_DischargeOff(context->ptrUsbPdContext);
            break;

        case APP_PSINK_DIS_MONITOR_TIMER:
            if(vbus_is_present(context, CY_PD_VSAFE_5V, 0) == false)
            {
                cy_sw_timer_stop(context->ptrTimerContext,
                        CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_TIMER));
                Cy_USBPD_Vbus_DischargeOff(context->ptrUsbPdContext);
                app_stat->snk_dis_cbk(context);
            }
            else
            {
                /*Start Monitor Timer again*/
                cy_sw_timer_start(context->ptrTimerContext, context,
                        CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_MONITOR_TIMER),
                        APP_PSINK_DIS_MONITOR_TIMER_PERIOD, app_psnk_tmr_cbk);
            }
            break;

        default:
            break;
    }
}

void psnk_disable (cy_stc_pdstack_context_t * context, cy_pdstack_sink_discharge_off_cbk_t snk_discharge_off_handler)
{
    uint8_t intr_state;
    uint8_t port = context->port;
    app_status_t* app_stat = app_get_status(port);

    intr_state = Cy_SysLib_EnterCriticalSection();

#if VBUS_OVP_ENABLE
    app_ovp_disable (context, false);
#endif /* VBUS_OVP_ENABLE */

#if VBUS_UVP_ENABLE
    app_uvp_disable (context, false);
#endif /* VBUS_UVP_ENABLE */

    sink_fet_off(context);
    gl_psnk_enabled[port] = false;

    Cy_USBPD_Vbus_DischargeOff(context->ptrUsbPdContext);
    cy_sw_timer_stop_range(context->ptrTimerContext,
            CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_TIMER),
            CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_MONITOR_TIMER));

    if ((snk_discharge_off_handler != NULL) && (context->dpmConfig.dpmEnabled))
    {
        Cy_USBPD_Vbus_DischargeOn(context->ptrUsbPdContext);

        app_stat->snk_dis_cbk = snk_discharge_off_handler;

        /* Start Power source enable and monitor timers. */
        cy_sw_timer_start(context->ptrTimerContext, context,
                CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_TIMER),
                APP_PSINK_DIS_TIMER_PERIOD, app_psnk_tmr_cbk);
        cy_sw_timer_start(context->ptrTimerContext, context,
                CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSINK_DIS_MONITOR_TIMER),
                APP_PSINK_DIS_MONITOR_TIMER_PERIOD, app_psnk_tmr_cbk);
    }

    /* Update the psnk_volt data structure so that we do not have stale value till the next sink attach */
    app_stat->psnk_volt = CY_PD_VSAFE_5V;

    Cy_SysLib_ExitCriticalSection(intr_state);
}

/* End of File */
