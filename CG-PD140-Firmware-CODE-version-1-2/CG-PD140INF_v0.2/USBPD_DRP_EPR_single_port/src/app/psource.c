/******************************************************************************
* File Name: psource.c
*
* Description: This source file implements functions associated with the power
*              provider path control and fault detection which are part of the
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
#include "psource.h"
#include "app.h"
#include "cy_sw_timer.h"
#include "cy_sw_timer_id.h"
#include "cy_usbpd_vbus_ctrl.h"

#if (!CCG_SINK_ONLY)
/* Type-C current levels in 10mA units. */
#define CUR_LEVEL_3A    300
#define CUR_LEVEL_1_5A  150
#define CUR_LEVEL_DEF   90

/* VBUS absolute maximum voltage in mV units */
#define VBUS_MAX_VOLTAGE  (30000u)

#if CY_PD_EPR_AVS_ENABLE
/* Time (in ms) between VBus valid and triggering of PS_RDY. */
#define APP_PSOURCE_AVS_EN_HYS_TIMER_PERIOD         (5u)
#endif /* CY_PD_EPR_AVS_ENABLE */

extern cy_stc_pdstack_context_t *get_pdstack_context(uint8_t portIdx);

void psrc_en_ovp(cy_stc_pdstack_context_t * context);
void psrc_en_uvp(cy_stc_pdstack_context_t * context);
void psrc_en_rcp(cy_stc_pdstack_context_t * context);

static void psrc_dis_ovp(cy_stc_pdstack_context_t * context);
static void psrc_dis_uvp(cy_stc_pdstack_context_t * context);
static void psrc_dis_ocp(cy_stc_pdstack_context_t * context);
static void psrc_dis_scp(cy_stc_pdstack_context_t * context);
static void psrc_dis_rcp(cy_stc_pdstack_context_t * context);

static void psrc_shutdown(cy_stc_pdstack_context_t * context, bool discharge_dis);

#if VBUS_SOFT_START_ENABLE

bool gl_fet_soft_start_en[NO_OF_TYPEC_PORTS] = {false};
void ocp_handler_wrapper(cy_timer_id_t id,  void *cbkContext);

#endif /* VBUS_SOFT_START_ENABLE */

void app_psrc_tmr_cbk(cy_timer_id_t id,  void * callbackCtx);
bool app_psrc_vbus_ovp_cbk(void *context, bool compOut);
bool app_psrc_vbus_ocp_cbk(void * cbkContext, bool comp_out);
bool app_psrc_vbus_scp_cbk(void * cbkContext, bool comp_out);
bool app_psrc_vbus_rcp_cbk(void * cbkContext, bool comp_out);

void psrc_select_voltage(cy_stc_pdstack_context_t *context);

void vbus_fet_on_cbk (cy_timer_id_t id,  void * context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;
    /* Turn On the FET. */
    Cy_USBPD_Vbus_NgdoG1Ctrl (ptrPdStackContext->ptrUsbPdContext, true);
}

#if VBUS_SOFT_START_ENABLE
static void Vbus_NgdoSoftStartOn(cy_stc_pdstack_context_t *context)
{
    /* Disable the OCP fault detection module */
    Cy_USBPD_Fault_Vbus_OcpDisable(context->ptrUsbPdContext, true);

    /* Set the OCP threshold to 250 mA for soft start */
    Cy_USBPD_Fault_Vbus_OcpEnable(context->ptrUsbPdContext, 20, app_psrc_vbus_ocp_cbk);

    gl_fet_soft_start_en[context->port] = true;

    /* Set the drive strength of the NGDO to high (1.05uA). */
    Cy_USBPD_Vbus_NgdoSetDriveStrength(context->ptrUsbPdContext, (uint8_t)0x07);

    /* Start the timer which will change drive strength and OCP settings to default after a timeout. */
    cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_FET_SOFT_START_TIMER_ID), 50, ocp_handler_wrapper);
}
#endif /* VBUS_SOFT_START_ENABLE */

static void vbus_fet_on(cy_stc_pdstack_context_t *context)
{
    /* If fet is already On then no need to enable it again */    
    if(app_get_status(context->port)->is_vbus_on == false)
    {
        app_get_status(context->port)->is_vbus_on = true;
        /*
         * In case of REGULATOR_REQUIRE_STABLE_ON_TIME, the regulator is
         * already turned on. POWER_BANK implementation, uses a single
         * regulator and FET control for both source and sink operation.
         * Turning OFF sink FET here will cause the regulator to get wrongly
         * shut down. We should not disable sink here in this case.
         */
#if (!((REGULATOR_REQUIRE_STABLE_ON_TIME) && (POWER_BANK)))
        Cy_USBPD_Vbus_GdrvCfetOff(context->ptrUsbPdContext, false);
        Cy_SysLib_DelayUs(10);
#endif /* (!((REGULATOR_REQUIRE_STABLE_ON_TIME) && (POWER_BANK))) */

        cy_sw_timer_stop(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_VBUS_FET_OFF_TIMER));
#if VBUS_SOFT_START_ENABLE
        Vbus_NgdoSoftStartOn(context);
#endif /* VBUS_SOFT_START_ENABLE */

        Cy_USBPD_Vbus_GdrvPfetOn(context->ptrUsbPdContext, true);

        cy_sw_timer_start(context->ptrTimerContext, context, 
                CY_PDSTACK_GET_APP_TIMER_ID(context, APP_VBUS_FET_ON_TIMER),
                APP_VBUS_FET_ON_TIMER_PERIOD, vbus_fet_on_cbk);
    }
}

void vbus_fet_off_cbk (cy_timer_id_t id,  void * context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;

    Cy_USBPD_Vbus_NgdoEqCtrl (ptrPdStackContext->ptrUsbPdContext, false);

    Cy_USBPD_Vbus_GdrvPfetOff(ptrPdStackContext->ptrUsbPdContext, true);
}

static void vbus_fet_off(cy_stc_pdstack_context_t *context)
{
    app_get_status(context->port)->is_vbus_on = false;

    /* Stop the VBUS_FET_ON_TIMER. */
    cy_sw_timer_stop(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_VBUS_FET_ON_TIMER));

    Cy_USBPD_Vbus_NgdoG1Ctrl (context->ptrUsbPdContext, false);
    Cy_USBPD_Vbus_NgdoEqCtrl (context->ptrUsbPdContext, true);

    cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_VBUS_FET_OFF_TIMER),
            APP_VBUS_FET_OFF_TIMER_PERIOD, vbus_fet_off_cbk);
}

#endif /* (!CCG_SINK_ONLY) */


#if (!CY_PD_SINK_ONLY)

static void call_psrc_ready_cbk(cy_stc_pdstack_context_t * context)
{
    app_status_t* app_stat = app_get_status(context->port);

    if (app_stat->pwr_ready_cbk != NULL)
    {
        app_stat->pwr_ready_cbk (context);
        app_stat->pwr_ready_cbk = NULL;
    }
}

/*Timer Callback*/
void app_psrc_tmr_cbk(cy_timer_id_t id,  void * callbackCtx)
{
    cy_stc_pdstack_context_t* context = callbackCtx;
    app_status_t* app_stat = app_get_status(context->port);
#if (CY_PD_EPR_AVS_ENABLE && EPR_AVS_HW_LIMITATION)
    bool isActive = false;
#endif /* CY_PD_EPR_AVS_ENABLE && EPR_AVS_HW_LIMITATION) */

    if (context->port != 0u)
    {
    	id = (cy_timer_id_t)((uint16_t)id - ((uint16_t)APP_PORT1_TIMER_START_ID - (uint16_t)APP_TIMERS_START_ID));
    }

    switch(id)
    {
        case APP_PSOURCE_EN_TIMER:
            /* Supply did not reach expected level. Turn off power and do error recovery. */
            cy_sw_timer_stop_range(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_MONITOR_TIMER), CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_HYS_TIMER));
#if (CY_PD_EPR_AVS_ENABLE && EPR_AVS_HW_LIMITATION)
            (void)Cy_PdStack_Dpm_IsEprAvsModeActive(context, &isActive);

            /* Workaround for AVS HW limitation */
            if (isActive == true)
            {
                call_psrc_ready_cbk(context);
            }
            else
#endif
            {
                app_stat->psrc_volt_old = CY_PD_VSAFE_0V;
                psrc_shutdown(context, true);
            }

#if (VBUS_UVP_ENABLE)
            /*
             *If the VBUS does not reach VSAFE5V, then we need to treat this as an
             * under voltage condition. Since the UVP hardware detection cannot be
             * enabled when turning on the VBUS, this has to be manually triggered
             * from here by invoking the callback directly. Do this only if UVP is
             * enabled from the configuration table.
             */
            if (context->ptrUsbPdContext->usbpdConfig->vbusOvpConfig->enable)
            {
                app_psrc_vbus_ovp_cbk(context, false);
            }
#endif /* (VBUS_UVP_ENABLE) */
            break;

        case APP_PSOURCE_EN_MONITOR_TIMER:
            if (((app_stat->psrc_rising == true) &&
                        (vbus_is_present(context, app_stat->psrc_volt, VBUS_TURN_ON_MARGIN) == true)) ||
                    ((app_stat->psrc_rising == false) &&
                     (vbus_is_present(context, app_stat->psrc_volt, VBUS_DISCHARGE_MARGIN) == false))
#if (CY_PD_EPR_AVS_ENABLE && EPR_AVS_HW_LIMITATION)
                    || (context->dpmExtStat.eprAvsMode == CY_PDSTACK_EPR_AVS_LARGE)
#endif
                    )
            {
#if CY_PD_EPR_AVS_ENABLE
                if(context->dpmExtStat.eprAvsMode == CY_PDSTACK_EPR_AVS_SMALL)
                {
                    /* Start Source enable AVS hysteresis Timer */
                    cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_HYS_TIMER),
                            APP_PSOURCE_AVS_EN_HYS_TIMER_PERIOD, app_psrc_tmr_cbk);
                }
                else
#endif
                {
                    /* Start Source enable hysteresis Timer */
                    cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_HYS_TIMER),
                        APP_PSOURCE_EN_HYS_TIMER_PERIOD, app_psrc_tmr_cbk);
                }
                break;
            }

            /* Start Monitor Timer again */
            cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_MONITOR_TIMER),
                    APP_PSOURCE_EN_MONITOR_TIMER_PERIOD, app_psrc_tmr_cbk);
            break;

        case APP_PSOURCE_EN_HYS_TIMER:
#if REGULATOR_REQUIRE_STABLE_ON_TIME
            if (cy_sw_timer_is_running(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_MONITOR_TIMER)))
            {
                return;
            }
#endif /* REGULATOR_REQUIRE_STABLE_ON_TIME */           
            cy_sw_timer_stop(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_TIMER));
            app_stat->psrc_volt_old = app_stat->psrc_volt;
            vbus_discharge_off(context);

            if(app_stat->psrc_rising == false)
            {
                /* VBus voltage has stabilized at the new lower level. Update the OVP and RCP limits. */
                psrc_en_ovp (context);
                psrc_en_rcp (context);
            }
            else
            {
                psrc_en_uvp (context);
            }

            call_psrc_ready_cbk(context);
            break;

        case APP_PSOURCE_DIS_TIMER:
            /* Discharge operation timed out. */
            cy_sw_timer_stop(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_MONITOR_TIMER));
            psrc_shutdown(context, true);
            break;

        case APP_PSOURCE_DIS_MONITOR_TIMER:
            if (vbus_is_present(context, CY_PD_VSAFE_5V, VBUS_DISCHARGE_TO_5V_MARGIN) == false)
            {
                /* Voltage has dropped below 5 V. We can now turn off the FET and continue discharge. */
                psrc_shutdown(context, false);
            }

            if (vbus_is_present(context, CY_PD_VSAFE_0V, VBUS_TURN_ON_MARGIN) == false)
            {
                /* Start Extra discharge to allow proper discharge below Vsafe0V */
                cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_EXT_DIS_TIMER),
                        APP_PSOURCE_DIS_EXT_DIS_TIMER_PERIOD,
                        app_psrc_tmr_cbk);
            }
            else
            {
                /* Start Monitor Timer again */
                 cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_MONITOR_TIMER),
                        APP_PSOURCE_DIS_MONITOR_TIMER_PERIOD,
                        app_psrc_tmr_cbk);
            }
            break;

        case APP_PSOURCE_DIS_EXT_DIS_TIMER:
            cy_sw_timer_stop(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_TIMER));
            vbus_discharge_off(context);

            /* Notify the caller that psrc_disable is complete. */
            call_psrc_ready_cbk(context);
            break;

        default:
            break;
    }
}

#if VBUS_OCP_ENABLE
void app_psrc_vbus_ocp_tmr_cbk(cy_timer_id_t id,  void *context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;

    /* 
     * Stop all psource transition timers and notify stack about voltage
     * transition complete to process the SCP hard reset sequence. 
     * Also disable all other fault detection by calling psource shutdown.
     */
    cy_sw_timer_stop_range(ptrPdStackContext->ptrTimerContext,
            CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_PSOURCE_EN_TIMER),
            CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_PSOURCE_EN_HYS_TIMER));
    call_psrc_ready_cbk(ptrPdStackContext);

    /* OCP fault. */
    psrc_shutdown(ptrPdStackContext, true);
    
    /* Set alert message */
    cy_pd_pd_do_t alert;
    alert.val = 0;
    alert.ado_alert.ocp = true;
    ptrPdStackContext->dpmStat.alert = alert;

    /* Enqueue OCP fault event. */
    app_event_handler(ptrPdStackContext, APP_EVT_VBUS_OCP_FAULT, NULL);
}

#if VBUS_SOFT_START_ENABLE
void ocp_handler_wrapper(cy_timer_id_t id,  void *cbkContext)
{
    cy_stc_pdstack_context_t *context = (cy_stc_pdstack_context_t *)cbkContext;

    if (gl_fet_soft_start_en[context->port])
    {
        Cy_USBPD_Vbus_NgdoSetDriveStrength(context->ptrUsbPdContext, 0x0E);

        gl_fet_soft_start_en[context->port] = false;

        psrc_set_current(context, CUR_LEVEL_3A);
    }
}
#endif /* VBUS_SOFT_START_ENABLE */

bool app_psrc_vbus_ocp_cbk(void *cbkContext, bool comp_out)
{
    cy_stc_usbpd_context_t * context = (cy_stc_usbpd_context_t *)cbkContext;
    cy_stc_pdstack_context_t * ptrPdStackContext = get_pdstack_context(context->port);
    bool retval = false;

    if (comp_out)
    {
#if VBUS_SOFT_START_ENABLE
        if(gl_fet_soft_start_en[context->port])
        {
             /* Disable the OCP fault detection module */
            Cy_USBPD_Fault_Vbus_OcpDisable(context, true);

            Cy_USBPD_Vbus_NgdoSetDriveStrength(context, 0x02); 
            
            /* Schedule a timer which will increase the drive strength after a delay. */
            cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext, 
                            CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_FET_SOFT_START_TIMER_ID), 5, ocp_handler_wrapper);
        }
        else
#endif /* VBUS_SOFT_START_ENABLE */
        {
            
            /* Start a OCP debounce timer */
            cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                    CY_PDSTACK_GET_PD_TIMER_ID(ptrPdStackContext, PD_OCP_DEBOUNCE_TIMER),
                    ptrPdStackContext->ptrUsbPdContext->usbpdConfig->vbusOcpConfig->debounce,
                    app_psrc_vbus_ocp_tmr_cbk);
        }
    }
    else
    {
        /* Negative edge. Check if the timer is still running. */
        retval = cy_sw_timer_is_running(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_PD_TIMER_ID(ptrPdStackContext, PD_OCP_DEBOUNCE_TIMER));
        if (retval)
        {
            cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_PD_TIMER_ID(ptrPdStackContext, PD_OCP_DEBOUNCE_TIMER));
        }
    }

    return retval;
}
#endif /* VBUS_OCP_ENABLE */


#if VBUS_SCP_ENABLE
bool app_psrc_vbus_scp_cbk(void * cbkContext, bool comp_out)
{
    /* Get the PD-Stack context from the USBPD context */
    cy_stc_usbpd_context_t * context = (cy_stc_usbpd_context_t *) cbkContext;
    cy_stc_pdstack_context_t * pdstack_ctx = get_pdstack_context(context->port);
    /* 
     * Stop all psource transition timers and notify stack about voltage
     * transition complete to process the SCP hard reset sequence. 
     * Also disable all other fault detection by calling psource shutdown.
     */ 
    cy_sw_timer_stop_range(pdstack_ctx->ptrTimerContext,
            CY_PDSTACK_GET_APP_TIMER_ID(pdstack_ctx, APP_PSOURCE_EN_TIMER),
            CY_PDSTACK_GET_APP_TIMER_ID(pdstack_ctx, APP_PSOURCE_EN_HYS_TIMER));
    call_psrc_ready_cbk(pdstack_ctx);

    /* SCP fault. */
    psrc_shutdown(pdstack_ctx, true);

    /* Set alert message */
    cy_pd_pd_do_t alert;
    alert.val = 0;
    alert.ado_alert.ocp = true;
    pdstack_ctx->dpmStat.alert = alert;

    /* Enqueue SCP fault event. */
    app_event_handler(pdstack_ctx, APP_EVT_VBUS_SCP_FAULT, NULL);

    return 0;
}
#endif /* VBUS_SCP_ENABLE */

#if VBUS_RCP_ENABLE
bool app_psrc_vbus_rcp_cbk(void * cbkContext, bool comp_out)
{
    /* Get the PD-Stack context from the USBPD context */
    cy_stc_usbpd_context_t * context = (cy_stc_usbpd_context_t *) cbkContext;
    cy_stc_pdstack_context_t * pdstack_ctx = get_pdstack_context(context->port);

    /* RCP fault. */
    psrc_shutdown(pdstack_ctx, true);

    cy_pd_pd_do_t alert;
    alert.val = 0;
    /* Treat RCP as equivalent to OVP and send an alert post fault recovery. */
    alert.ado_alert.ovp = true;
    pdstack_ctx->dpmStat.alert = alert;

    /* Notify the solution layer about the fault. */
    app_event_handler(pdstack_ctx, APP_EVT_VBUS_RCP_FAULT, NULL);

    return 0;
}
#endif /* VBUS_RCP_ENABLE */

#if ((VBUS_OVP_ENABLE) || (VBUS_UVP_ENABLE))

static void ovp_pwr_ready_cbk(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    /* Dummy callback to allow vbus discharge */
}

bool app_psrc_vbus_ovp_cbk(void *context, bool compOut)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;
    uint8_t port = ptrPdStackContext->port;
    app_status_t *app_stat = app_get_status(port);

    app_stat->psrc_volt = CY_PD_VSAFE_0V;
    psrc_select_voltage(ptrPdStackContext);

    /*OVP fault*/
    psrc_shutdown(ptrPdStackContext, true);

    if (compOut == true)
    {
        /* OVP fault condition. */

        /* Set alert message to be sent after fault recovery. */
        cy_pd_pd_do_t alert;
        alert.val = 0;
        alert.ado_alert.ovp = true;
        ptrPdStackContext->dpmStat.alert = alert;

        app_event_handler(ptrPdStackContext, APP_EVT_VBUS_OVP_FAULT, NULL);
        psrc_disable(ptrPdStackContext, ovp_pwr_ready_cbk);
    }
#if VBUS_UVP_ENABLE
    else
    {
        /* UVP fault condition. */

        /* 
         * UVP is a hardware cutoff in micro seconds and OCP is a software
         * debounce and cutoff in milli seconds. When there is a sudden change
         * in Vbus current, Vbus voltage dips and causes UVP to react first
         * rather than OCP. Sink expects an alert message for OCP, that will be
         * missed if UVP is received. Hence, mimic OCP alert in case of UVP as
         * well. This will be taken care only for non-PPS contracts.
         */
        if(ptrPdStackContext->dpmStat.srcSelPdo.src_gen.supplyType != CY_PDSTACK_PDO_AUGMENTED)
        {
            /* Set alert message */
            cy_pd_pd_do_t alert;
            alert.val = 0;
            alert.ado_alert.ocp = true;
            ptrPdStackContext->dpmStat.alert = alert;
        }

        app_event_handler(ptrPdStackContext, APP_EVT_VBUS_UVP_FAULT, NULL);
    }
#endif /* VBUS_UVP_ENABLE */

    return 0;
}
#endif /* ((VBUS_OVP_ENABLE) || (VBUS_UVP_ENABLE)) */

void psrc_select_voltage(cy_stc_pdstack_context_t *context)
{
    uint8_t port = context->port;
#if (!HIGHER_VOLTAGES_SUPP_DISABLE)
    app_status_t *app_stat = app_get_status(port);

#if CCG_PROG_SOURCE_ENABLE
    uint32_t select_volt = app_stat->psrc_volt;

    /* Don't drop voltage below 5 V. */
    if (app_stat->psrc_volt == CY_PD_VSAFE_0V)
    {
        app_stat->psrc_volt = CY_PD_VSAFE_5V;
    }

    /* 
     * Cap the selected voltage to the absolute maximum voltage that can be
     * applied to the cable. 
     */ 
    if (select_volt > VBUS_MAX_VOLTAGE)
    {
        select_volt = VBUS_MAX_VOLTAGE;
    }

    if(port == TYPEC_PORT_0_IDX)
    {
        APP_VBUS_SET_VOLT_P1(select_volt);
    }

#else /* CCG_PROG_SOURCE_ENABLE */

    uint8_t intr_state = Cy_SysLib_EnterCriticalSection();

    if (port == TYPEC_PORT_0_IDX)
    {
        switch (app_stat->psrc_volt)
        {
            case CY_PD_VSAFE_9V:
                APP_VBUS_SET_9V_P1();
                break;
            case CY_PD_VSAFE_12V:
                APP_VBUS_SET_12V_P1();
                break;
            case CY_PD_VSAFE_13V:
                APP_VBUS_SET_13V_P1();
                break;
            case CY_PD_VSAFE_15V:
                APP_VBUS_SET_15V_P1();
                break;
            case CY_PD_VSAFE_19V:
                APP_VBUS_SET_19V_P1();
                break;
            case CY_PD_VSAFE_20V:
                APP_VBUS_SET_20V_P1();
                break;
            default:
                app_stat->psrc_volt = CY_PD_VSAFE_5V;
                APP_VBUS_SET_5V_P1();
                break;
        }
    }
#if CCG_PD_DUALPORT_ENABLE
    if(port == TYPEC_PORT_1_IDX)
    {
        switch (app_stat->psrc_volt)
        {
            case VSAFE_9V:
                APP_VBUS_SET_9V_P2();
                break;
            case VSAFE_12V:
                APP_VBUS_SET_12V_P2();
                break;
            case VSAFE_13V:
                APP_VBUS_SET_13V_P2();
                break;
            case VSAFE_15V:
                APP_VBUS_SET_15V_P2();
                break;
            case VSAFE_19V:
                APP_VBUS_SET_19V_P2();
                break;
            case VSAFE_20V:
                APP_VBUS_SET_20V_P2();
                break;
            default:
                app_stat->psrc_volt = VSAFE_5V;
                APP_VBUS_SET_5V_P2();
                break;
        }
    }
#endif /* CCG_PD_DUALPORT_ENABLE */
    Cy_SysLib_ExitCriticalSection(intr_state);
#endif  /* CCG_PROG_SOURCE_ENABLE */
#endif /* HIGHER_VOLTAGES_SUPP */
}

void psrc_set_voltage(cy_stc_pdstack_context_t * context, uint16_t volt_mV)
{
    uint8_t port = context->port;
    app_status_t *app_stat = app_get_status(port);
    const cy_stc_pd_dpm_config_t *dpm_stat = &context->dpmConfig;
    app_stat->psrc_volt = volt_mV;

#if VBUS_OCP_ENABLE
    /* Leave OCP detection disabled while doing the voltage transition. */
    psrc_dis_ocp (context);
#endif /* VBUS_OCP_ENABLE */

    if ((app_stat->psrc_volt >= app_stat->psrc_volt_old) && (volt_mV != CY_PD_VSAFE_0V))
    {
        /* If voltage is being increased, make sure that OVP and RCP limits are moved up. */
        psrc_en_ovp (context);
        psrc_en_rcp (context);
    }
    else if ((app_stat->psrc_volt < app_stat->psrc_volt_old) && (volt_mV != CY_PD_VSAFE_0V))
    {
        /*
         * Enable UVP only if port partner is attached. We need to ensure that
         * UVP does not get enabled if VBUS is not applied, like in case of
         * HARD_RESET.
         */
        if ((dpm_stat->attach == true) && (app_stat->is_vbus_on == true))
        {
            psrc_en_uvp (context);
        }
    }

    psrc_select_voltage(context);
}

uint32_t psrc_get_voltage (cy_stc_pdstack_context_t *context)
{
    return app_get_status(context->port)->psrc_volt;
}

#if (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE)
static const uint32_t cc_rp_to_cur_map[] = {
    CUR_LEVEL_DEF,
    CUR_LEVEL_1_5A,
    CUR_LEVEL_3A
};
#endif /* (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE) */

void psrc_set_current (cy_stc_pdstack_context_t *context, uint16_t cur_10mA)
{
#if (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE)
    /* Update the OCP/SCP thresholds when required. */
    const cy_stc_pdstack_dpm_status_t *dpm_stat = &context->dpmStat;
    cy_stc_pd_dpm_config_t *dpm_config = &context->dpmConfig;
    uint32_t ocp_cur;

    if (dpm_config->contractExist)
    {
    	switch(dpm_stat->srcSelPdo.src_gen.supplyType)
    	{
            case CY_PDSTACK_PDO_FIXED_SUPPLY:
            case CY_PDSTACK_PDO_VARIABLE_SUPPLY:
                ocp_cur = dpm_stat->srcSelPdo.src_gen.maxCurPower;
                break;
            case CY_PDSTACK_PDO_AUGMENTED:
                if(dpm_stat->srcSelPdo.pps_src.apdoType == CY_PDSTACK_APDO_AVS)
                {
                    /* PDP value is in 1W units and the max volt is in 100mV units. Convert pdp in 100mW units
                     * and divide by voltage gives the current in Amps then multiplied by 100 to convert in 10mA units */  
                    ocp_cur = ((dpm_stat->srcSelPdo.epr_avs_src.pdp * 10) / dpm_stat->srcSelPdo.epr_avs_src.maxVolt) * 100;
                }
                else
                {
                    /* Max current in PPS PDO is in 50mA units, multiplied by 5 to convert in 10mA units */
                    ocp_cur = dpm_stat->srcSelPdo.pps_src.maxCur * 5;
                }
                break;
            default:
                ocp_cur = dpm_stat->srcSelPdo.src_gen.maxCurPower;
                break;
    	}
    }
    else
    {
        ocp_cur = cc_rp_to_cur_map[dpm_stat->srcCurLevel];

#if BATTERY_CHARGING_ENABLE && 0
        /* Update current limit as per battery charging module */
        if (
                (bc_get_status(port)->cur_mode != BC_CHARGE_NONE) &&
                (bc_get_status(port)->cur_mode != BC_CHARGE_CDP)
           )
        {
            ocp_cur = GET_MAX(ocp_cur, bc_get_status(port)->cur_amp);
        }
#endif /* BATTERY_CHARGING_ENABLE */
    }

#if VBUS_OCP_ENABLE
    if (context->ptrUsbPdContext->usbpdConfig->vbusOcpConfig->enable)
    {
        Cy_USBPD_Fault_Vbus_OcpEnable (context->ptrUsbPdContext, ocp_cur, app_psrc_vbus_ocp_cbk);
    }
#endif /* VBUS_OCP_ENABLE */

#if VBUS_SCP_ENABLE
    /* Enable SCP. */
    if (context->ptrUsbPdContext->usbpdConfig->vbusScpConfig->enable)
    {
        Cy_USBPD_Fault_Vbus_ScpEnable (context->ptrUsbPdContext, 1000, app_psrc_vbus_scp_cbk);
    }
#endif /* VBUS_SCP_ENABLE */

#endif /* (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE) */
}

void psrc_enable (cy_stc_pdstack_context_t * context,
        cy_pdstack_pwr_ready_cbk_t pwr_ready_handler)
{
    app_status_t* app_stat = app_get_status(context->port);
    const cy_stc_pdstack_dpm_status_t *dpm_stat = &(context->dpmStat);
    const cy_stc_pdstack_dpm_ext_status_t *dpm_ext_stat = &(context->dpmExtStat);
    uint8_t intr_state;
#if CY_PD_EPR_ENABLE
    uint32_t pwr_en_tmr_period;
#endif /* CY_PD_EPR_ENABLE */

    intr_state = Cy_SysLib_EnterCriticalSection();

    cy_sw_timer_stop_range(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_TIMER), 
            CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_EXT_DIS_TIMER));

    /* Turn on FETs only if dpm is enabled and there is no active fault condition. */
    if ((context->dpmConfig.dpmEnabled) && (dpm_stat->faultActive == false))
    {
#if (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE)
        /* Make sure OCP/SCP is enabled where required. The current parameter is not used. */
        psrc_set_current (context, CUR_LEVEL_3A);
#endif /* (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE) */

#if REGULATOR_REQUIRE_STABLE_ON_TIME  
        if(REGULATOR_STATUS(port) == false)
        {
            /* Enable the regulator before turning on the FET */
            REGULATOR_ENABLE(port);
            cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_MONITOR_TIMER), REGULATOR_TURN_ON_DELAY, app_psrc_tmr_cbk);
        }
#endif /* REGULATOR_REQUIRE_STABLE_ON_TIME */    

        /* Turn off VBus Discharge by default. */
        vbus_discharge_off(context);

        /* Turn on PSource FET */
        vbus_fet_on(context);

        if (pwr_ready_handler != NULL)
        {
            app_stat->psrc_rising = true;

            /* If the VBus voltage is dropping, turn the discharge path on. */
            if(app_stat->psrc_volt_old > app_stat->psrc_volt)
            {
                app_stat->psrc_rising = false;
                vbus_discharge_on(context);
            }
            app_stat->pwr_ready_cbk = pwr_ready_handler;

            /* Start Power source enable and monitor timers */
#if CY_PD_EPR_ENABLE

            bool isActive = false;
            (void)Cy_PdStack_Dpm_IsEprModeActive(context, &isActive);

            if (isActive == false)
            {
                pwr_en_tmr_period = APP_PSOURCE_EN_TIMER_PERIOD;
            }
            else
            {
#if CY_PD_EPR_AVS_ENABLE
                (void)Cy_PdStack_Dpm_IsEprAvsModeActive(context, &isActive);

                if (isActive == true)
                {
                    /* After sending the Accept Message, the Adjustable Voltage Supply starts to
                    decrease its output voltage. The Adjustable Voltage Supply new voltage set-point
                    (corresponding to vAvsNew) Shall be reached by tAvsSrcTransLarge for steps larger than
                    vAvsSmallStep or else by tAvsSrcTransSmall. The power supply informs
                    the Device Policy Manager that it is has reached the new level.
                    The power supply status is passed to the Policy Engine.
                    */
                    if(dpm_ext_stat->eprAvsMode == CY_PDSTACK_EPR_AVS_SMALL)
                    {
                        pwr_en_tmr_period = CY_PD_PSOURCE_AVS_TRANS_SMALL_PERIOD;
                    }
                    else if(dpm_ext_stat->eprAvsMode == CY_PDSTACK_EPR_AVS_LARGE)
                    {
                        pwr_en_tmr_period = CY_PD_PSOURCE_AVS_TRANS_LARGE_PERIOD;
                    }
                    else
                    {
                        pwr_en_tmr_period = APP_PSOURCE_EN_TIMER_PERIOD;
                    }
                }
                else
#endif /* CY_PD_EPR_AVS_ENABLE */
                {
                    pwr_en_tmr_period = APP_PSOURCE_EPR_EN_TIMER_PERIOD;
                }
            }
            cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_TIMER),
                    pwr_en_tmr_period, app_psrc_tmr_cbk);
#else
            cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_TIMER),
                                APP_PSOURCE_EN_TIMER_PERIOD, app_psrc_tmr_cbk);
#endif /* CCG_EPR_ENABLE */

            /* For CCG3PA/CCG3PA2/PAG1S APP_PSOURCE_EN_MONITOR_TIMER is not required */
            cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_MONITOR_TIMER),
                    APP_PSOURCE_EN_MONITOR_TIMER_PERIOD, app_psrc_tmr_cbk);
        }
    }
    Cy_SysLib_ExitCriticalSection(intr_state);
}

void psrc_disable(cy_stc_pdstack_context_t * context, cy_pdstack_pwr_ready_cbk_t pwr_ready_handler)
{
    uint8_t port = context->port;
    app_status_t* app_stat = app_get_status(port);
    uint8_t intr_state;

    intr_state = Cy_SysLib_EnterCriticalSection();

    cy_sw_timer_stop_range(context->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_EN_TIMER), 
            CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_EXT_DIS_TIMER));

#if VBUS_UVP_ENABLE
    psrc_dis_uvp(context);
#endif /* VBUS_UVP_ENABLE */

    if(app_stat->psrc_volt_old <= CY_PD_VSAFE_5V)
    {
        psrc_shutdown(context, false);
        Cy_SysLib_DelayUs(20);
    }
    else
    {
        psrc_set_voltage(context, CY_PD_VSAFE_5V);
    }

    app_stat->psrc_volt_old = CY_PD_VSAFE_0V;

    if ((pwr_ready_handler != NULL) && (context->dpmConfig.dpmEnabled))
    {
        /* Turn on discharge to get the voltage to drop faster. */
        vbus_discharge_on(context);
        app_stat->pwr_ready_cbk = pwr_ready_handler;
#if(CY_PD_EPR_ENABLE)
        bool isActive = true;
        Cy_PdStack_Dpm_IsEprModeActive(context, &isActive);
        cy_sw_timer_start(context->ptrTimerContext, context,
            CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_TIMER),
            isActive ?  APP_PSOURCE_EPR_DIS_TIMER_PERIOD : APP_PSOURCE_DIS_TIMER_PERIOD,
            app_psrc_tmr_cbk);
#else
        /*Start Power source enable and monitor timer*/
        cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_TIMER),
                APP_PSOURCE_DIS_TIMER_PERIOD, app_psrc_tmr_cbk);
#endif /* CY_PD_EPR_ENABLE */
        cy_sw_timer_start(context->ptrTimerContext, context, CY_PDSTACK_GET_APP_TIMER_ID(context, APP_PSOURCE_DIS_MONITOR_TIMER),
                APP_PSOURCE_DIS_MONITOR_TIMER_PERIOD, app_psrc_tmr_cbk);
    }
    else
    {
        psrc_shutdown(context, true);
    }

    Cy_SysLib_ExitCriticalSection(intr_state);
}

static void psrc_dis_ovp(cy_stc_pdstack_context_t * context)
{
#if VBUS_OVP_ENABLE
    app_ovp_disable (context, CCG_SRC_FET);
#endif /* VBUS_OVP_ENABLE */
}

static void psrc_dis_ocp(cy_stc_pdstack_context_t * context)
{
#if VBUS_OCP_ENABLE
    if (context->ptrUsbPdContext->usbpdConfig->vbusOcpConfig->enable)
    {
        /* Make sure the OCP debounce timer has been stopped. */
        cy_sw_timer_stop(context->ptrTimerContext, CY_PDSTACK_GET_PD_TIMER_ID(context, PD_OCP_DEBOUNCE_TIMER));
        Cy_USBPD_Fault_Vbus_OcpDisable (context->ptrUsbPdContext, false);
    }
#endif /* VBUS_OCP_ENABLE */
}

static void psrc_dis_scp(cy_stc_pdstack_context_t * context)
{
#if VBUS_SCP_ENABLE
    if (context->ptrUsbPdContext->usbpdConfig->vbusScpConfig->enable)
    {
        Cy_USBPD_Fault_Vbus_ScpDisable (context->ptrUsbPdContext);
    }
#endif /* VBUS_SCP_ENABLE */
}

static void psrc_dis_uvp(cy_stc_pdstack_context_t * context)
{
#if VBUS_UVP_ENABLE
    app_uvp_disable (context, CCG_SRC_FET);
#endif /* VBUS_UVP_ENABLE */
}

static void psrc_dis_rcp(cy_stc_pdstack_context_t * context)
{
#if VBUS_RCP_ENABLE
    if (context->ptrUsbPdContext->usbpdConfig->vbusRcpConfig->enable)
    {
        Cy_USBPD_Fault_Vbus_RcpDisable (context->ptrUsbPdContext);
    }
#endif /* VBUS_RCP_ENABLE */
}

static void psrc_shutdown(cy_stc_pdstack_context_t * context, bool discharge_dis)
{
    uint8_t port = context->port;

    /* Turn Off Source FET */
    vbus_fet_off(context);

    if(discharge_dis == true)
    {
        vbus_discharge_off(context);
    }

    /* Disable OVP/OCP/UVP */
    psrc_dis_ovp(context);
    psrc_dis_uvp(context);
    psrc_dis_ocp(context);
    psrc_dis_scp(context);
    psrc_dis_rcp(context);

    (void) port;
}

void psrc_en_ovp(cy_stc_pdstack_context_t * context)
{
#if (VBUS_OVP_ENABLE)
    app_ovp_enable(context, app_get_status(context->port)->psrc_volt,
            CCG_SRC_FET, app_psrc_vbus_ovp_cbk);
#endif /* (VBUS_OVP_ENABLE) */
}

void psrc_en_rcp(cy_stc_pdstack_context_t * context)
{
#if VBUS_RCP_ENABLE
    if (context->ptrUsbPdContext->usbpdConfig->vbusRcpConfig->enable)
    {
        Cy_USBPD_Fault_Vbus_RcpEnable(context->ptrUsbPdContext, app_get_status(context->port)->psrc_volt, app_psrc_vbus_rcp_cbk);
    }
#endif /* VBUS_RCP_ENABLE */
}

void psrc_en_uvp(cy_stc_pdstack_context_t * context)
{
#if VBUS_UVP_ENABLE
    /* Using the same callback as OVP as behavior is same. */
    app_uvp_enable(context, app_get_status(context->port)->psrc_volt, CCG_SRC_FET, app_psrc_vbus_ovp_cbk);
#endif /* VBUS_UVP_ENABLE */
}

#endif /* (!CCG_SINK_ONLY) */

/* End of File */
