/******************************************************************************
* File Name: app.c
*
* Description: This is source code for the PMG1 MCU USB-PD DRP Code Example.
*              This file implements functions for handling of PDStack event
*              callbacks and power saving.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#include <cybsp.h>
#include <cy_pdstack_common.h>
#include "cy_pdstack_dpm.h"
#include <config.h>
#if (!CY_PD_SINK_ONLY)
#include <psource.h>
#endif /* CY_PD_SINK_ONLY */
#include <psink.h>
#include <swap.h>
#include <vdm.h>
#include <app.h>
#include <vdm_task_mngr.h>
#include <cy_sw_timer.h>
#include <cy_sw_timer_id.h>
#if (DFP_ALT_MODE_SUPP || UFP_ALT_MODE_SUPP)
#include <alt_mode_hw.h>
#include <alt_modes_mngr.h>
#endif /* (DFP_ALT_MODE_SUPP || DFP_ALT_MODE_SUPP) */
#include <cy_gpio.h>

#if BATTERY_CHARGING_ENABLE
#include <charger_detect.h>
#endif /* BATTERY_CHARGING_ENABLE */

extern uint16_t gl_LedBlinkRate;
extern cy_stc_pdstack_context_t *get_pdstack_context(uint8_t portIdx);

alt_mode_config_t alt_mode_info[NO_OF_TYPEC_PORTS] =
{
    {
        .altModeTrig = 0,
        .dpCfgSupported = 0,
        .dpMuxControl = 0,
        .dpOper = 0,
        .dpPrefMode = 0,
    }
};

app_status_t app_status[NO_OF_TYPEC_PORTS];

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
static bool app_is_vdm_task_ready(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    /* Assume cable discovery finished when device is UFP. */
    bool retval = true;

#if DFP_ALT_MODE_SUPP

    const cy_stc_pdstack_dpm_status_t *dpm_stat = dpm_get_status();

    /* This check only makes sense for DFP. */
    if (ptrPdStackContext.dpmConfig.curPortType != PRT_TYPE_UFP)
    {
#if (ROLE_PREFERENCE_ENABLE)
        /* Don't proceed with alternate mode if DR_SWAP is pending. */
        if ((app_status[port].app_pending_swaps & APP_DR_SWAP_PENDING) != 0)
        {
            return false;
        }
#endif /* (ROLE_PREFERENCE_ENABLE) */

#if (CY_PD_EPR_ENABLE)
        if(ptrPdStackContext->peStat.eprMultiMessageFlag)
        {
            return false;
        }
#endif

#if (!CCG_CBL_DISC_DISABLE)
        /*
         * Set the cable discovered flag if:
         * 1. Cable discovery is disabled.
         * 2. EMCA present flag in DPM is set.
         * 3. Cable discovery process not restarted.
         */
        if (
                (dpm_stat->cblDsc == false) ||
               ((dpm_stat->emcaPresent != false) &&
                (app_status[port].disc_cbl_pending == false))
            )
        {
            app_status[port].cbl_disc_id_finished = true;
        }

        /* Return the status of Cable discovered flag. */
        retval = app_status[port].cbl_disc_id_finished;
#endif /* (!CCG_CBL_DISC_DISABLE) */
    }

#endif /* DFP_ALT_MODE_SUPP */

    return retval;
}
#endif /* ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP)) */

cy_en_pdstack_status_t app_disable_pd_port(cy_stc_pdstack_context_t *ptrPdStackContext, cy_pdstack_dpm_typec_cmd_cbk_t cbk)
{
    cy_en_pdstack_status_t retval = CY_PDSTACK_STAT_SUCCESS;
    uint8_t port = ptrPdStackContext->port;

    if (cy_sw_timer_is_running (ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_FAULT_RECOVERY_TIMER)))
    {
        /* If the HPI Master is asking us to disable the port, make sure all fault protection state is cleared. */
        app_status[port].fault_status &= ~(
                APP_PORT_VBUS_DROP_WAIT_ACTIVE | APP_PORT_SINK_FAULT_ACTIVE | APP_PORT_DISABLE_IN_PROGRESS |
                APP_PORT_VCONN_FAULT_ACTIVE | APP_PORT_V5V_SUPPLY_LOST);

        cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_FAULT_RECOVERY_TIMER));

        Cy_USBPD_TypeC_DisableRd(ptrPdStackContext->ptrUsbPdContext, CY_PD_CC_CHANNEL_1);
        Cy_USBPD_TypeC_DisableRd(ptrPdStackContext->ptrUsbPdContext, CY_PD_CC_CHANNEL_2);
        cbk(ptrPdStackContext, CY_PDSTACK_DPM_RESP_SUCCESS);
    }
    else
    {
        /* Just pass the call on-to the stack. */
        if (ptrPdStackContext->dpmConfig.dpmEnabled)
        {
            retval = Cy_PdStack_Dpm_SendTypecCommand(ptrPdStackContext,  CY_PDSTACK_DPM_CMD_PORT_DISABLE,  cbk);
        }
        else
        {
            cbk(ptrPdStackContext, CY_PDSTACK_DPM_RESP_SUCCESS);
        }
    }

    return retval;
}

#if UNUSED_VARIABLE
static mux_select_t app_mux_state[NO_OF_TYPEC_PORTS];
#endif /* UNUSED_VARIABLE */

bool set_mux(cy_stc_pdstack_context_t* context, mux_select_t cfg, uint32_t custom_data)
{
    bool retval = true;
    uint8_t port = context->port;
    (void)custom_data;

    if (app_get_status(port)->skip_mux_config != false)
        return retval;

    if (cfg == MUX_CONFIG_DEINIT)
    {
#if UNUSED_VARIABLE
        app_mux_state[port] = cfg;
#endif /* UNUSED_VARIABLE */
        return retval;
    }

#if UNUSED_VARIABLE
    /* Store the current MUX configuration. */
    app_mux_state[port] = cfg;
#endif /* UNUSED_VARIABLE */

#if DPM_DEBUG_SUPPORT
    mux_push_to_buf(port, cfg);
#endif /* DPM_DEBUG_SUPPORT */

#if (MUX_TYPE == DP_MUX)
    if (cfg <= MUX_CONFIG_RIDGE_CUSTOM)
    {
        retval = mux_ctrl_set_cfg (port, cfg,  dpm_get_polarity (port));
    }
    else
    {
        retval = false;
    }

#elif (MUX_TYPE == RIDGE_MUX)
    /* In TBT use cases, this call is used to configure the SBU Mux.
     * This has to be configured before notifying the SoC. */
    if (cfg <= MUX_CONFIG_RIDGE_CUSTOM)
    {
        retval = mux_ctrl_set_cfg (port, cfg,  dpm_get_polarity (port));
    }

#endif /* MUX_TYPE */

    return retval;
}

#if (!CCG_CBL_DISC_DISABLE)
static void app_cbl_dsc_timer_cb (cy_timer_id_t id, void *callbackContext);
static void app_cbl_dsc_callback (cy_stc_pdstack_context_t *ptrPdStackContext, cy_en_pdstack_resp_status_t resp,
                                const cy_stc_pdstack_pd_packet_t *pkt_ptr)
{
    /* Keep repeating the DPM command until we succeed. */
    if (resp == CY_PDSTACK_SEQ_ABORTED)
    {
        cy_sw_timer_start (ptrPdStackContext->ptrTimerContext, ptrPdStackContext , CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_CBL_DISC_TRIGGER_TIMER), APP_CBL_DISC_TIMER_PERIOD, app_cbl_dsc_timer_cb);
    }
}


static void app_cbl_dsc_timer_cb (cy_timer_id_t id, void *callbackContext)
{
    cy_stc_pdstack_context_t *pdstack_context = callbackContext;

    if (Cy_PdStack_Dpm_SendPdCommand(pdstack_context, CY_PDSTACK_DPM_CMD_INITIATE_CBL_DISCOVERY, NULL, false, app_cbl_dsc_callback) != CY_PDSTACK_STAT_SUCCESS )
    {
        /* Start timer which will send initiate the DPM command after a delay. */
        app_cbl_dsc_callback(pdstack_context, CY_PDSTACK_SEQ_ABORTED, 0);
    }
}
#endif /* (!CCG_CBL_DISC_DISABLE) */

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))

static void app_exit_all_cbk (cy_timer_id_t id, void *callbackContext)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = callbackContext;
    /* Reset VDM layer */
    app_vdm_layer_reset(ptrPdStackContext);
}

static void app_exit_alt_modes_cbk(cy_stc_pdstack_context_t *ptrPdStackContext, uint32_t stat)
{
    /* Run timer to run VDM layer restart */
    cy_sw_timer_start (ptrPdStackContext->ptrTimerContext, ptrPdStackContext , CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_RESET_VDM_LAYER_TIMER), APP_RESET_VDM_TIMER_PERIOD, app_exit_all_cbk);  
        
}
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */

bool app_vdm_layer_reset(cy_stc_pdstack_context_t *ptrPdStackContext)
{
#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
     
    app_status_t *app = app_get_status(port);
    bool stat = true;

    if ((ptrPdStackContext->dpmConfig.contractExist) && (  ptrPdStackContext.dpmConfig== PRT_TYPE_DFP))
    {
        if (app->alt_mode_entered == false)
        {
            /*
             * Reset the alternate mode state machine. The cable discovery complete flag is also cleared so
             * that alternate mode state machine can be started at the end of cable discovery.
             */
            alt_mode_layer_reset(port);
        }
        else
        {
            /* Exit all alt modes at first by sending Exit VDM */
            alt_mode_mngr_exit_all(port, true, app_exit_alt_modes_cbk);
            return stat;
        }
#if (!CCG_CBL_DISC_DISABLE)
        app->cbl_disc_id_finished = false;
        app->disc_cbl_pending     = true;

        /* Ask PD stack to trigger cable discovery. */
        if (Cy_PdStack_Dpm_SendPdCommand(pdstack_context, CY_PDSTACK_DPM_CMD_INITIATE_CBL_DISCOVERY, NULL, false, app_cbl_dsc_callback) !=  CY_PDSTACK_STAT_SUCCESS)
        {
            cy_sw_timer_start (ptrPdStackContext->ptrTimerContext, ptrPdStackContext , CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, PP_CBL_DISC_TRIGGER_TIMER), APP_CBL_DISC_TIMER_PERIOD, app_cbl_dsc_timer_cb);
        }
#endif /* (!CCG_CBL_DISC_DISABLE) */
    }
    else
    {
#if VCONN_OCP_ENABLE
        /* If there is no PD contract in place and we are VConn source, enable VConn and move on. */
        if ((ptrPdStackContext->dpmConfig.attach) && (ptrPdStackContext->dpmConfig.vconnLogical))
        {
            Cy_USBPD_Vconn_Enable(ptrPdStackContext->ptrUsbPdContext, dpm_stat->revPol);
        }
#endif /* VCONN_OCP_ENABLE */

        stat = false;
    }
    return stat;
#else
    return false;
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */
}

uint8_t app_task(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    fault_handler_task (ptrPdStackContext);

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
    /* If VDM processing is allowed */
    if (app_status[port].vdm_task_en != false)
    {
        /* Wait for cable discovery completion before going on Alt. Modes. */
        if (app_is_vdm_task_ready (port))
        {
            vdm_task_mngr (port);
        }
    }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */

#if BATTERY_CHARGING_ENABLE
    chgdet_task (ptrPdStackContext);
#endif /* BATTERY_CHARGING_ENABLE */

    return true;
}

#if SYS_DEEPSLEEP_ENABLE

bool app_deepsleep_allowed(void)
{
    return true;
}

bool app_sleep(void)
{
    bool stat = true;
    uint8_t port;

    for (port = 0; port < NO_OF_TYPEC_PORTS; port++)
    {
        /* Don't go to sleep while CC/SBU fault handling is pending. */
        if ((app_get_status(port)->fault_status & APP_PORT_SINK_FAULT_ACTIVE) != 0)
        {
            stat = false;
            break;
        }

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
        if (!is_vdm_task_idle(port))
        {
            stat = false;
            break;
        }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */
   }

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
    if (stat)
    {
        for (port = 0; port < NO_OF_TYPEC_PORTS; port++)
        {
            /* Prepare for deep-sleep entry. */
            alt_mode_mngr_sleep(port);
        }
    }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */

    return stat;
}

void app_wakeup(void)
{
#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
    uint8_t port;

    for (port = 0; port < NO_OF_TYPEC_PORTS; port++)
    {
        alt_mode_mngr_wakeup (port);
    }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */
}
#endif /* SYS_DEEPSLEEP_ENABLE */

#if CY_PD_REV3_ENABLE

/* Temporary storage for ongoing AMS type while handling chunked extended messages. */
static cy_en_pdstack_ams_type_t gl_extd_amsType[NO_OF_TYPEC_PORTS]; 

/* Global variable used as dummy data buffer to send Chunk Request messages. */
static uint32_t gl_extd_dummy_data;

void extd_msg_cb(cy_stc_pdstack_context_t *ptrPdStackContext, cy_en_pdstack_resp_status_t resp,
                                                    const cy_stc_pdstack_pd_packet_t *pkt_ptr)
{
    (void)pkt_ptr;

    if(resp == CY_PDSTACK_RES_RCVD)
    {
        ptrPdStackContext->dpmStat.nonIntrResponse = gl_extd_amsType[ptrPdStackContext->port];
    }
    if(resp == CY_PDSTACK_CMD_SENT)
    {
        gl_extd_amsType[ptrPdStackContext->port] = ptrPdStackContext->dpmStat.nonIntrResponse;
    }
}

bool app_extd_msg_handler(cy_stc_pdstack_context_t *ptrPdStackContext, cy_stc_pd_packet_extd_t *pd_pkt_p)
{
    /* If this is a chunked message which is not complete, send another chunk request. */
    if ((pd_pkt_p->hdr.hdr.chunked == true) && (pd_pkt_p->hdr.hdr.dataSize >
               ((pd_pkt_p->hdr.hdr.chunkNum + 1) * CY_PD_MAX_EXTD_MSG_LEGACY_LEN)))
    {
        cy_stc_pdstack_dpm_pd_cmd_buf_t extd_dpm_buf;

        extd_dpm_buf.cmdSop = (cy_en_pd_sop_t)pd_pkt_p->sop;
        extd_dpm_buf.extdType = (cy_en_pdstack_extd_msg_t)pd_pkt_p->msg;
        extd_dpm_buf.extdHdr.val = 0;
        extd_dpm_buf.extdHdr.extd.chunked = true;
        extd_dpm_buf.extdHdr.extd.request = true;
        extd_dpm_buf.extdHdr.extd.chunkNum = pd_pkt_p->hdr.hdr.chunkNum + 1;
        extd_dpm_buf.datPtr = (uint8_t*)&gl_extd_dummy_data;
        extd_dpm_buf.timeout = CY_PD_SENDER_RESPONSE_TIMER_PERIOD;

        /* Send next chunk request */
        Cy_PdStack_Dpm_SendPdCommand(ptrPdStackContext,CY_PDSTACK_DPM_CMD_SEND_EXTENDED,
                                     &extd_dpm_buf, true, extd_msg_cb); 

     }
    else
    {
        /*
         * Don't send any response to response messages. Handling here instead of in the stack so that
         * these messages can be used for PD authentication implementation.
         */
        if ((pd_pkt_p->msg != CY_PDSTACK_EXTD_MSG_SECURITY_RESP) && (pd_pkt_p->msg != CY_PDSTACK_EXTD_MSG_FW_UPDATE_RESP))
        {
            /* Send Not supported message */
            Cy_PdStack_Dpm_SendPdCommand(ptrPdStackContext,
                                         CY_PDSTACK_DPM_CMD_SEND_NOT_SUPPORTED, NULL, true, NULL); 
        }
    }

    return true;
}
#endif /* CCG_PD_REV3_ENABLE */

uint32_t get_bat_status[NO_OF_TYPEC_PORTS];

#if (ROLE_PREFERENCE_ENABLE)

/* Variable storing current preference for data role. */
volatile uint8_t app_pref_data_role[NO_OF_TYPEC_PORTS];

#if (POWER_ROLE_PREFERENCE_ENABLE)
/* Variable storing current preference for power role. */
volatile uint8_t app_pref_power_role[NO_OF_TYPEC_PORTS];
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

/* Forward declaration of function to trigger swap operations. */
static void app_initiate_swap (cy_timer_id_t id, void *context);

static void app_role_swap_resp_cb (cy_stc_pdstack_context_t *ptrPdStackContext, 
        cy_en_pdstack_resp_status_t resp,
        const cy_stc_pdstack_pd_packet_t *pkt_ptr)
{
    uint8_t port = ptrPdStackContext->port;
    app_status_t *app_stat = &app_status[port];

#if (POWER_ROLE_PREFERENCE_ENABLE)
    bool next_swap = false;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

    if (resp == CY_PDSTACK_RES_RCVD)
    {
        if (pkt_ptr->hdr.hdr.msgType == CY_PD_CTRL_MSG_WAIT)
        {
            app_stat->actv_swap_count++;
            if (app_stat->actv_swap_count < APP_MAX_SWAP_ATTEMPT_COUNT)
            {
                cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                        CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER), app_stat->actv_swap_delay, app_initiate_swap);
            }
            else
            {
#if (POWER_ROLE_PREFERENCE_ENABLE)
                /* Swap attempts timed out. Proceed with next swap. */
                next_swap = true;
#else
                app_stat->app_pending_swaps = 0;
                app_stat->actv_swap_type  = 0;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */
            }
        }
        else
        {
#if (POWER_ROLE_PREFERENCE_ENABLE)
            /* Swap succeeded or failed. Proceed with next swap. */
            next_swap = true;
#else
            app_stat->app_pending_swaps = 0;
            app_stat->actv_swap_type  = 0;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */
        }
    }
    else if ((resp == CY_PDSTACK_CMD_FAILED) || (resp == CY_PDSTACK_SEQ_ABORTED) || (resp == CY_PDSTACK_RES_TIMEOUT))
    {
        cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER), app_stat->actv_swap_delay, app_initiate_swap);
    }

#if (POWER_ROLE_PREFERENCE_ENABLE)
    if (next_swap)
    {
        /* Clear the LS bit in the app_pending_swaps flag as it has completed or failed. */
        app_stat->app_pending_swaps &= (app_stat->app_pending_swaps - 1);

        app_stat->actv_swap_type  = 0;
        app_stat->actv_swap_count = 0;
        cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER), APP_INITIATE_DR_SWAP_TIMER_PERIOD, app_initiate_swap);
    }
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */
}

static void app_initiate_swap (cy_timer_id_t id, void *context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;

    uint8_t port = ptrPdStackContext->port;
    app_status_t *app_stat_p = app_get_status(port);

    cy_stc_pdstack_dpm_pd_cmd_buf_t pd_cmd_buf;

    uint8_t actv_swap     = app_stat_p->actv_swap_type;
    uint8_t swaps_pending = app_stat_p->app_pending_swaps;

    /* Stop the timer that triggers swap operation. */
    cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER));

    /* Nothing to do if we are not in PD contract. */
    if (!ptrPdStackContext->dpmConfig.contractExist)
        return;

    if (actv_swap == 0)
    {
#if (POWER_ROLE_PREFERENCE_ENABLE)
        /* No ongoing swap operation. Pick the next pending swap from the list. */
        if ((swaps_pending & APP_VCONN_SWAP_PENDING) != 0)
        {
            actv_swap = CY_PDSTACK_DPM_CMD_SEND_VCONN_SWAP;
            app_stat_p->actv_swap_delay = APP_INITIATE_DR_SWAP_TIMER_PERIOD;
        }
        else
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */
        {
            if ((swaps_pending & APP_DR_SWAP_PENDING) != 0)
            {
                actv_swap = CY_PDSTACK_DPM_CMD_SEND_DR_SWAP;
                app_stat_p->actv_swap_delay = APP_INITIATE_DR_SWAP_TIMER_PERIOD;
            }
#if (POWER_ROLE_PREFERENCE_ENABLE)
            else
            {
                if (swaps_pending != 0)
                {
                    actv_swap = CY_PDSTACK_DPM_CMD_SEND_PR_SWAP;
                    app_stat_p->actv_swap_delay = APP_INITIATE_PR_SWAP_TIMER_PERIOD;
                }
            }
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */
        }

        app_stat_p->actv_swap_count = 0;
    }

    if (actv_swap != 0)
    {
        /* Check whether the selected swap is still valid. */
        switch (actv_swap)
        {
#if (POWER_ROLE_PREFERENCE_ENABLE)
            case CY_PDSTACK_DPM_CMD_SEND_VCONN_SWAP:
                if (ptrPdStackContext->dpmConfig.vconnLogical)
                {
                    app_stat_p->app_pending_swaps &= ~APP_VCONN_SWAP_PENDING;
                    actv_swap = 0;
                }
                break;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

            case CY_PDSTACK_DPM_CMD_SEND_DR_SWAP:
                /* Stop sending DR_SWAP if any alternate mode has been entered. */
                if (
                        (ptrPdStackContext->dpmConfig.curPortType == app_pref_data_role[port]) ||
                        (app_stat_p->alt_mode_entered != 0)
                   )
                {
                    app_stat_p->app_pending_swaps &= ~APP_DR_SWAP_PENDING;
                    actv_swap = 0;
                }
                break;

#if (POWER_ROLE_PREFERENCE_ENABLE)
            case CY_PDSTACK_DPM_CMD_SEND_PR_SWAP:
                if (ptrPdStackContext->dpmConfig.curPortRole == app_pref_power_role[port])
                {
                    app_stat_p->app_pending_swaps &= ~APP_PR_SWAP_PENDING;
                    actv_swap = 0;
                }
                break;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

            default:
                actv_swap = 0;
                break;
        }

        if (actv_swap == 0)
        {
            /*
             * Currently selected SWAP is no longer relevant. Re-run function to identify the next swap to be
             * performed.
             */
            if (app_stat_p->app_pending_swaps != 0)
            {
                app_stat_p->actv_swap_type = 0;
                cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                        CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER), APP_INITIATE_DR_SWAP_TIMER_PERIOD, app_initiate_swap);
            }
        }
        else
        {
            /* Store the swap command for use in the callback. */
            app_stat_p->actv_swap_type = actv_swap;

            /* Only packet type needs to be set when initiating swap operations. */
            pd_cmd_buf.cmdSop = CY_PD_SOP;

            /* Try to trigger the selected swap operation. */
            if (Cy_PdStack_Dpm_SendPdCommand(ptrPdStackContext, (cy_en_pdstack_dpm_pd_cmd_t)actv_swap, &pd_cmd_buf, 
                        false, app_role_swap_resp_cb) != CY_PDSTACK_STAT_SUCCESS)
            {
                /* Retries in case of AMS failure can always be done with a small delay. */
                cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                        CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER), APP_INITIATE_DR_SWAP_TIMER_PERIOD, app_initiate_swap);
            }
        }
    }
}

/* This function is called at the end of a PD contract to check whether any role swaps need to be triggered. */
void app_contract_handler (cy_stc_pdstack_context_t *ptrPdStackContext)
{
    app_status_t *app_stat = &app_status[ptrPdStackContext->port];
    //const cy_stc_pdstack_dpm_status_t* dpm = &ptrPdStackContext->dpmStat;

    uint16_t delay_reqd = APP_INITIATE_PR_SWAP_TIMER_PERIOD;

    uint8_t port = ptrPdStackContext->port;

#if (POWER_ROLE_PREFERENCE_ENABLE)
    /* Check if we need to go ahead with PR-SWAP. */
    if (
            (app_pref_power_role[port] == CY_PD_PRT_DUAL) ||
            (ptrPdStackContext->dpmConfig.curPortRole == app_pref_power_role[port])
       )
    {
        app_stat->app_pending_swaps &= ~APP_PR_SWAP_PENDING;
    }
    else
    {
        /* If we are about to swap to become source, ensure VConn Swap is done as required. */
        if ((app_pref_power_role[port] == CY_PD_PRT_ROLE_SOURCE) && (ptrPdStackContext->dpmConfig.vconnLogical == 0))
        {
            app_stat->app_pending_swaps |= APP_VCONN_SWAP_PENDING;

#if (DEFER_VCONN_SRC_ROLE_SWAP)
            /* Keep the VConn SWAP role until we have finished the required tasks. */
            app_stat->keep_vconn_src = true;
#endif /* (DEFER_VCONN_SRC_ROLE_SWAP) */
        }
    }
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

    /* Check if we need to go ahead with DR-SWAP. */
    if (
            (app_pref_data_role[port] == CY_PD_PRT_TYPE_DRP) ||
            (ptrPdStackContext->dpmConfig.curPortType == app_pref_data_role[port])
       )
    {
        app_stat->app_pending_swaps &= ~APP_DR_SWAP_PENDING;
    }
    else
    {
        /* DR-SWAPs need to be initiated as soon as possible. VConn swap will be triggered after DR_SWAP as needed. */
        delay_reqd = APP_INITIATE_DR_SWAP_TIMER_PERIOD;
    }

    /* Start a timer that will kick off the Swap state machine. */
    cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
            CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER), delay_reqd, app_initiate_swap);
}

void app_connect_change_handler (cy_stc_pdstack_context_t *ptrPdStackContext)
{
    /* Stop all timers used to trigger swap operations. */
    cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER));
    uint8_t port = ptrPdStackContext->port;

#if (POWER_ROLE_PREFERENCE_ENABLE)
    /* Assume that PR_SWAP and DR_SWAP are pending. The actual status will be updated on contract completion. */
    app_status[port].app_pending_swaps = APP_PR_SWAP_PENDING | APP_DR_SWAP_PENDING;
#else
    /* Assume that DR_SWAP is pending. The actual status will be updated on contract completion. */
    app_status[port].app_pending_swaps = APP_DR_SWAP_PENDING;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

    app_status[port].actv_swap_type    = 0;
    app_status[port].actv_swap_count   = 0;
}

#endif /* (ROLE_PREFERENCE_ENABLE) */

static uint8_t gl_app_previous_polarity[NO_OF_TYPEC_PORTS];

#if UNUSED_VARIABLE
static bool gl_app_hard_rst_sent_rcvd[NO_OF_TYPEC_PORTS] = {
    false
#if CCG_PD_DUALPORT_ENABLE
    ,
    false
#endif /* CCG_PD_DUALPORT_ENABLE */
};
#endif /* UNUSED_VARIABLE */

#if (CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY))
void epr_enter_mode_timer_cb (
        cy_timer_id_t id,
        void *ptrContext)
{
    (void)id;
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)ptrContext;

    if (Cy_PdStack_Dpm_SendPdCommand (ptrPdStackContext, CY_PDSTACK_DPM_CMD_SNK_EPR_MODE_ENTRY, NULL, false, NULL) != CY_PDSTACK_STAT_SUCCESS)
    {
        /* Retry the EPR Entry. */
        cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_EPR_SNK_TIMER), APP_EPR_SNK_ENTRY_TIMER_PERIOD, epr_enter_mode_timer_cb);
    }
}

#endif /* CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY) */


#if (!CY_PD_SINK_ONLY)
/* Dummy callback used to ensure VBus discharge happens after debug accessory sink is disconnected. */
static void debug_acc_src_disable_cbk(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    (void)ptrPdStackContext;
}

static void debug_acc_src_psrc_enable_cb(cy_timer_id_t id,  void *context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;
    ptrPdStackContext->ptrAppCbk->psrc_enable(ptrPdStackContext, NULL);
}
#endif /* CY_PD_SINK_ONLY */

#if (CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY))
bool gl_typec_reset_epr[NO_OF_TYPEC_PORTS];
#endif /* CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY) */

void app_event_handler(cy_stc_pdstack_context_t *ptrPdStackContext, 
               cy_en_pdstack_app_evt_t evt, const void* dat)
{
    const cy_en_pdstack_app_req_status_t* result;
    const cy_stc_pdstack_pd_contract_info_t* contract_status;
    bool  skip_soln_cb = false;
    bool  hardreset_cplt = false;
    bool  typec_only = false;
    uint8_t port = ptrPdStackContext->port;
#if CY_PD_REV3_ENABLE
#if HOST_ALERT_MSG_ENABLE
    pd_do_t alert_ado;
#endif /* HOST_ALERT_MSG_ENABLE */
#endif /* CCG_PD_REV3_ENABLE */

    switch(evt)
    {
        case APP_EVT_TYPEC_STARTED:
            mux_ctrl_init (port);

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
            app_status[port].vdm_prcs_failed = false;
#endif /* ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP)) */
            break;

        case APP_EVT_TYPEC_ATTACH:

            /* This will also enable the USB (DP/DM) MUX where required. */
            set_mux (ptrPdStackContext, MUX_CONFIG_SS_ONLY, 0);

            /* Clear all fault counters if we have seen a change in polarity from previous connection. */
            if (ptrPdStackContext->dpmConfig.polarity != gl_app_previous_polarity[port])
            {
                fault_handler_clear_counts (ptrPdStackContext->port);
            }
            gl_app_previous_polarity[port] = ptrPdStackContext->dpmConfig.polarity ;
#if (CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY))
            gl_typec_reset_epr[port] = false;
#endif /* CY_PD_EPR_ENABLE && (!CY_PD__SOURCE_ONLY) */
            break;

        case APP_EVT_CONNECT:
#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
            app_status[port].vdm_prcs_failed = false;
#endif /* ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP)) */
#if (!CCG_CBL_DISC_DISABLE)
            app_status[port].cbl_disc_id_finished = false;
            app_status[port].disc_cbl_pending = false;
#endif /* (!CCG_CBL_DISC_DISABLE) */
            /* Change the LED blink rate to 500 ms on TypeC Connect */
            gl_LedBlinkRate = 500;

            if (ptrPdStackContext->dpmConfig.attachedDev == CY_PD_DEV_DBG_ACC)
            {
                if(ptrPdStackContext->dpmConfig.curPortRole == CY_PD_PRT_ROLE_SOURCE)
                {
#if (!CY_PD_SINK_ONLY)
                    uint16_t mux_delay = ptrPdStackContext->ptrDpmParams->muxEnableDelayPeriod;
                    if(0U == mux_delay)
                    {
                        mux_delay = 1U;
                    }

                    cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_PSOURCE_EN_TIMER), mux_delay,
                                debug_acc_src_psrc_enable_cb);
#endif /* (!CY_PD_SINK_ONLY) */
                }

                app_status[port].debug_acc_attached = true;
            }

#if (ROLE_PREFERENCE_ENABLE)
            app_connect_change_handler (ptrPdStackContext);
#endif /* (ROLE_PREFERENCE_ENABLE) */
            break;

        case APP_EVT_HARD_RESET_COMPLETE:
            hardreset_cplt = true;
            /* Intentional fall-through. */

        case APP_EVT_HR_SENT_RCVD_DEFERRED:
        case APP_EVT_HARD_RESET_SENT:
        case APP_EVT_PE_DISABLED:
            typec_only = ((ptrPdStackContext->dpmStat.pdConnected == false) || (evt == APP_EVT_PE_DISABLED));
            /* Intentional fall-through. */

        case APP_EVT_HARD_RESET_RCVD:
        case APP_EVT_VBUS_PORT_DISABLE:
        case APP_EVT_DISCONNECT:
        case APP_EVT_TYPE_C_ERROR_RECOVERY:
#if (!CCG_CBL_DISC_DISABLE)
            app_status[port].cbl_disc_id_finished = false;
            app_status[port].disc_cbl_pending = false;
#endif /* (!CCG_CBL_DISC_DISABLE) */

            if (
                    (evt == APP_EVT_HARD_RESET_SENT) ||
                    (evt == APP_EVT_HARD_RESET_RCVD) ||
                    (evt == APP_EVT_HR_SENT_RCVD_DEFERRED)
               )
            {
#if UNUSED_VARIABLE
                gl_app_hard_rst_sent_rcvd[port] = true;
#endif /* UNUSED_VARIABLE */
            }

            if (evt == APP_EVT_DISCONNECT)
            {
#if (!CY_PD_SINK_ONLY)
                /* Mark debug accessory detached. */
                {
                    bool debug_acc_attached = app_status[port].debug_acc_attached;
                    app_status[port].debug_acc_attached = false;
                    if((false != debug_acc_attached)&&
                            (ptrPdStackContext->dpmConfig.curPortRole == CY_PD_PRT_ROLE_SOURCE))
                    {
                        ptrPdStackContext->ptrAppCbk->psrc_disable(ptrPdStackContext, debug_acc_src_disable_cbk);
                    }
                }
#endif /* (!CY_PD_SINK_ONLY) */
            }

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))

            if (evt == APP_EVT_DISCONNECT)
            {
#if DEBUG_ACCESSORY_SNK_ENABLE
                /* Mark debug accessory detached. */
                app_status[port].debug_acc_attached = false;
#endif /* DEBUG_ACCESSORY_SNK_ENABLE */
            }

#if (CCG_USB4_SUPPORT_ENABLE)
            app_status[port].usb4_active = false;
            app_status[port].usb4_data_rst_cnt = 0;
#endif /* CCG_USB4_SUPPORT_ENABLE */

            vdm_task_mngr_deinit (port);

#if ((defined(CCG5)) || (defined(CCG5C)) || (defined(CCG6)) || (defined(CCG6DF)) || (defined(CCG6SF)))
            timer_stop (port, APP_CBL_DISC_TRIGGER_TIMER);
#endif /* ((defined(CCG5)) || (defined(CCG5C)) || (defined(CCG6)) || (defined(CCG6DF)) || (defined(CCG6SF))) */

#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */

            if (hardreset_cplt)
            {
                set_mux (ptrPdStackContext, MUX_CONFIG_SS_ONLY, 0);
            }
            else
            {
                /*
                 * Isolate the data lines if this is a PD connection.
                 */
                if (!typec_only)
                {
                    set_mux (ptrPdStackContext, MUX_CONFIG_ISOLATE, 0);
                    cy_sw_timer_stop (ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_AME_TIMEOUT_TIMER));

                }
            }
#if (VBUS_OCP_ENABLE || VBUS_SCP_ENABLE || VBUS_OVP_ENABLE || VBUS_UVP_ENABLE)
            if(evt == APP_EVT_TYPE_C_ERROR_RECOVERY)
            {
                /* Clear port-in-fault flag if all fault counts are within limits. */
                if (!app_port_fault_count_exceeded(ptrPdStackContext))
                {
                    if ((app_get_status(port)->fault_status & APP_PORT_DISABLE_IN_PROGRESS) == 0)
                    {
                        ptrPdStackContext->dpmStat.faultActive = false;
                    }
                }
            }
#endif /* VBUS_OCP_ENABLE | VBUS_SCP_ENABLE | VBUS_OVP_ENABLE| VBUS_UVP_ENABLE */

            if ((evt == APP_EVT_DISCONNECT) || (evt == APP_EVT_VBUS_PORT_DISABLE))
            {
                /* Change the LED blink rate to 1000 ms on TypeC disonnect/Hard Reset/ Error Recovery */
                gl_LedBlinkRate = 1000;

#if REGULATOR_REQUIRE_STABLE_ON_TIME
                /* Disable the regulator on port disconnect */
                REGULATOR_DISABLE(port);
#endif /* REGULATOR_REQUIRE_STABLE_ON_TIME */

#if VCONN_OCP_ENABLE
                /* Clear the VConn fault status. */
                app_status[port].fault_status &= ~APP_PORT_VCONN_FAULT_ACTIVE;
#endif /* VCONN_OCP_ENABLE */
            }

#if ((!CY_PD_SINK_ONLY) || (ROLE_PREFERENCE_ENABLE))
            if (
                    (evt == APP_EVT_HARD_RESET_COMPLETE) ||
                    (evt == APP_EVT_TYPE_C_ERROR_RECOVERY) ||
                    (evt == APP_EVT_DISCONNECT)
               )
            {
#if UNUSED_VARIABLE
#if (!CY_PD_SINK_ONLY)
                gl_app_hard_rst_sent_rcvd[port] = false;
#endif /* (!CY_PD_SINK_ONLY) */
#endif /* UNUSED_VARIABLE */

#if (ROLE_PREFERENCE_ENABLE)
                /* Stop the DR-Swap and PR-Swap trigger timers.  Assume that
                 * PR_SWAP and DR_SWAP are pending. The actual status will be
                 * updated on contract completion.
                 */
                app_connect_change_handler (ptrPdStackContext);
#endif /* (ROLE_PREFERENCE_ENABLE) */
            }
#endif /* ((!CY_PD_SINK_ONLY) || (ROLE_PREFERENCE_ENABLE)) */

#if APP_FRS_RX_ENABLE
            gl_frs_in_prog[port] = false;
#endif /* APP_FRS_RX_ENABLE */
            break;

#if (!CCG_CBL_DISC_DISABLE)
        case APP_EVT_EMCA_NOT_DETECTED:
        case APP_EVT_EMCA_DETECTED:
            app_status[port].cbl_disc_id_finished = true;
            app_status[port].disc_cbl_pending = false;
            app_status[port].vdm_prcs_failed = false;

#if (DEFER_VCONN_SRC_ROLE_SWAP)
#if DFP_ALT_MODE_SUPP
            /* If alt. mode state machine is inactive or idle, we can allow VConn swaps to proceed. */
            if (is_vdm_task_idle(port))
            {
                app_status[port].keep_vconn_src = false;
            }
#endif /* DFP_ALT_MODE_SUPP */
#endif /* (DEFER_VCONN_SRC_ROLE_SWAP) */
            break;
#endif /* (!CCG_CBL_DISC_DISABLE) */

        case APP_EVT_DR_SWAP_COMPLETE:
            result = (const cy_en_pdstack_app_req_status_t*)dat;
            if(*result == CY_PDSTACK_REQ_ACCEPT)
            {
#if (ROLE_PREFERENCE_ENABLE)
                app_status[port].app_pending_swaps &= ~APP_DR_SWAP_PENDING;
                if (app_status[port].actv_swap_type == CY_PDSTACK_DPM_CMD_SEND_DR_SWAP)
                {
                    cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER));
                    app_contract_handler (ptrPdStackContext);
                }
#endif /* (ROLE_PREFERENCE_ENABLE) */

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
#if CCG_USB4_SUPPORT_ENABLE
                if (app_status[port].usb4_active != false)
                {
                    /* Run VDM manager */
                    app_status[port].vdm_task_en = false;
                    enable_vdm_task_mngr(port);
                }
                else
#endif /* CCG_USB4_SUPPORT_ENABLE */
                {
                    /* Device data role changed. Reset alternate mode layer. */
                    alt_mode_layer_reset(port);
                }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */
            }
            break;

#if (!CCG_BACKUP_FIRMWARE)
        case APP_EVT_VENDOR_RESPONSE_TIMEOUT:
            /* If the APP layer is going to retry the VDM, do not send the event. */
            if (app_status[port].vdm_retry_pending)
                skip_soln_cb = true;
            break;
#endif /* (!CCG_BACKUP_FIRMWARE) */
        case APP_EVT_BAD_SINK_APDO_SEL:
            break;

        case APP_EVT_PD_CONTRACT_NEGOTIATION_COMPLETE:
            /* Change the LED blink rate to 100 ms on successfull contract negotiation */
            gl_LedBlinkRate = 100;
            contract_status = (cy_stc_pdstack_pd_contract_info_t*)dat;

            /* Set VDM version based on active PD revision. */
#if CY_PD_REV3_ENABLE
            if (ptrPdStackContext->dpmConfig.specRevSopLive >= CY_PD_REV3)
            {
                app_status[port].vdm_version = CY_PD_STD_VDM_VERSION_REV3;
            }
            else
#endif /* CCG_PD_REV3_ENABLE */
            {
                app_status[port].vdm_version = CY_PD_STD_VDM_VERSION_REV2;
            }

            if ((contract_status->status ==CY_PDSTACK_CONTRACT_NEGOTIATION_SUCCESSFUL) ||
                    (contract_status->status == CY_PDSTACK_CONTRACT_CAP_MISMATCH_DETECTED))
            {

#if (ROLE_PREFERENCE_ENABLE)
                app_contract_handler (ptrPdStackContext);
#endif /* (ROLE_PREFERENCE_ENABLE) */

#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
                /*
                 * Contract established.  Enable VDM task manager for Alt. Mode support.
                 * This function will have no effect if the Alt. Modes are already running.
                 */
                if (
                        (gl_dpm_port_type[port] == PRT_TYPE_UFP) ||
                        (app_status[port].vdm_prcs_failed == false)
                   )
                {
                    enable_vdm_task_mngr(port);
                }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */
            }

#if (DEFER_VCONN_SRC_ROLE_SWAP)
            /* If we are not DFP, we can now allow the port partner to become VConn Source. */
            if (
                    (gl_dpm_port_type[port] == PRT_TYPE_UFP)
#if ROLE_PREFERENCE_ENABLE
                    &&
                    (app_pref_data_role[port] != PRT_TYPE_DFP)
#endif /* ROLE_PREFERENCE_ENABLE */
               )
            {
                app_status[port].keep_vconn_src = false;
            }
#endif /* (DEFER_VCONN_SRC_ROLE_SWAP) */

#if (CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY))
            if(!gl_typec_reset_epr[port])
            {
                /* Start a timer to attempt EPR entry if the current role is Sink. */
                if ( (ptrPdStackContext->dpmConfig.curPortRole == CY_PD_PRT_ROLE_SINK) &&
                        (ptrPdStackContext->dpmStat.srcCapP->dat[0].fixed_src.eprModeCapable == true) && 
                            (ptrPdStackContext->dpmExtStat.epr.snkEnable == true))
                {
                    cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                            CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_EPR_SNK_TIMER), APP_EPR_SNK_ENTRY_TIMER_PERIOD, epr_enter_mode_timer_cb);

                    gl_typec_reset_epr[port] = true;
                }
            }

#endif /* CY_PD_EPR_ENABLE && (!CY_PD_SOURCE_ONLY) */
            break;

#if CY_PD_REV3_ENABLE
        case APP_EVT_HANDLE_EXTENDED_MSG:
            {
                if(!(app_extd_msg_handler(ptrPdStackContext, (cy_stc_pd_packet_extd_t *)dat)))
                {
                    skip_soln_cb  = false;
                }
                else
                {
                    skip_soln_cb  = true;
                }
            }
            break;
#endif /* CCG_PD_REV3_ENABLE */

        case APP_EVT_TYPEC_ATTACH_WAIT:
#if REGULATOR_REQUIRE_STABLE_ON_TIME
            REGULATOR_ENABLE(port);
#endif /* REGULATOR_REQUIRE_STABLE_ON_TIME */

            break;

        case APP_EVT_TYPEC_ATTACH_WAIT_TO_UNATTACHED:
#if REGULATOR_REQUIRE_STABLE_ON_TIME
            REGULATOR_DISABLE(port);
#endif /* REGULATOR_REQUIRE_STABLE_ON_TIME */
            break;

#if (POWER_ROLE_PREFERENCE_ENABLE)
        case APP_EVT_PR_SWAP_COMPLETE:
            app_status[port].app_pending_swaps &= ~APP_PR_SWAP_PENDING;
            if (app_status[port].actv_swap_type == CY_PDSTACK_DPM_CMD_SEND_PR_SWAP)
            {
                cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER));
                app_contract_handler (ptrPdStackContext);
            }
            break;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */

#if (!CY_PD_SINK_ONLY)
#if (DEFER_VCONN_SRC_ROLE_SWAP)
        case APP_EVT_ALT_MODE:
#if DFP_ALT_MODE_SUPP
            /* We can clear the keep VConn source flag once the alternate mode state machine has become idle. */
            if (is_vdm_task_idle (port))
            {
                app_status[port].keep_vconn_src = false;
            }
#endif /* DFP_ALT_MODE_SUPP */
            break;
#endif /* (DEFER_VCONN_SRC_ROLE_SWAP) */
#endif /* (!CY_PD_SINK_ONLY) */

        case APP_EVT_DATA_RESET_ACCEPTED:
#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
        /* Need to reset alternate modes as part of Data_Reset. No status update is to be provided. */
            alt_mode_layer_reset (port);
#endif /* ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP)) */

#if (!CCG_CBL_DISC_DISABLE)
            app_status[port].cbl_disc_id_finished = false;
#endif /* (!CCG_CBL_DISC_DISABLE) */

#if (CCG_USB4_SUPPORT_ENABLE)
            /* Mark USB4 not active as Data Reset has been accepted. */
            app_get_status(port)->usb4_active = false;
#endif /* CCG_USB4_SUPPORT_ENABLE */            
            /* Switch to USB only configuration once data reset has been accepted. */
            if (ptrPdStackContext->dpmConfig.curPortType == CY_PD_PRT_TYPE_UFP)
            {
                set_mux (ptrPdStackContext, MUX_CONFIG_SS_ONLY, 0);
            }
            else
            {
                set_mux (ptrPdStackContext, MUX_CONFIG_ISOLATE, 0);
            }
            break;

        case APP_EVT_DATA_RESET_CPLT:
            /* DFP needs to re-enable USBx connections at completion of Data_Reset. */
            if (ptrPdStackContext->dpmConfig.curPortType == CY_PD_PRT_TYPE_DFP)
            {
                set_mux (ptrPdStackContext, MUX_CONFIG_SS_ONLY, 0);
            }
            break;

#if (CCG_USB4_SUPPORT_ENABLE)
        case APP_EVT_USB_ENTRY_CPLT:
            app_get_status(port)->usb4_data_rst_cnt = 0;
            app_get_status(port)->usb4_active = true;
            break;
#endif /* CCG_USB4_SUPPORT_ENABLE */

        case APP_EVT_PD_SINK_DEVICE_CONNECTED:
            break;

        case APP_EVT_PKT_RCVD:
            break;

        case APP_EVT_CBL_RESET_SENT:
            app_get_status(port)->cbl_rst_done = true;
            break;

#if (!CY_PD_SINK_ONLY)
        case APP_EVT_HR_PSRC_ENABLE:
            set_mux (ptrPdStackContext, MUX_CONFIG_SS_ONLY, 0);
            break;
#endif /* (!CY_PD_SINK_ONLY) */

#if CY_PD_EPR_ENABLE
        case APP_EVT_EPR_MODE_ENTER_FAILED:
            break;
        case APP_EVT_EPR_MODE_ENTER_RECEIVED:
#if ROLE_PREFERENCE_ENABLE
            cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_INITIATE_SWAP_TIMER));
#endif /* ROLE_PREFERENCE_ENABLE */
            break;
        case APP_EVT_EPR_MODE_ENTER_SUCCESS:
            break;
#endif /* CY_PD_EPR_ENABLE */

        default:
            /* Nothing to do. */
            break;
    }

    /* Pass the event notification to the fault handler module. */
    if (fault_event_handler (ptrPdStackContext, evt, dat))
    {
        skip_soln_cb = true;
    }

#if BATTERY_CHARGING_ENABLE
    chgdet_pd_event_handler (ptrPdStackContext, evt, dat);
#endif /* BATTERY_CHARGING_ENABLE */

    if (!skip_soln_cb)
    {
        /* Send notifications to the solution */
       sln_pd_event_handler(ptrPdStackContext, evt, dat) ;
    }
}

app_resp_t* app_get_resp_buf(uint8_t port)
{
    return &app_status[port].appResp;
}

app_status_t* app_get_status(uint8_t port)
{
    return &app_status[port];
}

void app_init(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    uint8_t port = ptrPdStackContext->port;

    /* For now, only the VDM handlers require an init call. */

    /* Initialize the VDM responses from the configuration table. */
    vdm_data_init(ptrPdStackContext);

    /* Set alt mode trigger based on config. */
    app_get_status(port)->alt_mode_trig_mask = alt_mode_info->altModeTrig;

#if BATTERY_CHARGING_ENABLE
    chgdet_init(ptrPdStackContext);
#endif /* BATTERY_CHARGING_ENABLE */

#if (ROLE_PREFERENCE_ENABLE)
    uint8_t port = ptrPdStackContext->port;
#if (POWER_ROLE_PREFERENCE_ENABLE)
    app_pref_power_role[port] = CY_PD_PRT_ROLE_SOURCE;
#endif /* (POWER_ROLE_PREFERENCE_ENABLE) */
    app_pref_data_role[port] = CY_PD_PRT_TYPE_DFP;
#endif /* (ROLE_PREFERENCE_ENABLE) */

    /* Update custom host config settings to the stack. */
    ptrPdStackContext->dpmStat.typecAccessorySuppDisabled = !(ptrPdStackContext->ptrPortCfg->accessoryEn);
    ptrPdStackContext->dpmStat.typecRpDetachDisabled = !(ptrPdStackContext->ptrPortCfg->rpDetachEn);
}

#if SYS_DEEPSLEEP_ENABLE
/* Implements PMG1 deep sleep functionality for power saving. */
bool system_sleep(cy_stc_pdstack_context_t *ptrPdStackContext, cy_stc_pdstack_context_t *ptrPdStack1Context)
{
    uint32_t intr_state;
    bool dpm_slept = false;
    bool retval = false;
    bool bc_slept = true;
//#if PMG1_PD_DUALPORT_ENABLE
//    bool dpm_port1_slept = false;
//#endif /* PMG1_PD_DUALPORT_ENABLE */

    /* Do one DPM sleep capability check before locking interrupts out. */
    if (
            (Cy_PdStack_Dpm_IsIdle (ptrPdStackContext, &dpm_slept) != CY_PDSTACK_STAT_SUCCESS) ||
            (!dpm_slept)
       )
    {
        return retval;
    }

    intr_state = Cy_SysLib_EnterCriticalSection();

#if BATTERY_CHARGING_ENABLE
    bc_slept = chgdet_prepare_deepsleep(ptrPdStackContext);
#endif /* BATTERY_CHARGING_ENABLE */

    if (bc_slept)
    {
        if (
                ((Cy_PdStack_Dpm_PrepareDeepSleep(ptrPdStackContext, &dpm_slept) == CY_PDSTACK_STAT_SUCCESS) &&
                (dpm_slept))
			)
        {
            cy_sw_timer_enter_sleep(ptrPdStackContext->ptrTimerContext);

            Cy_USBPD_SetReference(ptrPdStackContext->ptrUsbPdContext, true);

            /* Device sleep entry. */
            Cy_SysPm_CpuEnterDeepSleep();

            Cy_USBPD_SetReference(ptrPdStackContext->ptrUsbPdContext, false);

            retval = true;
        }
    }

    Cy_SysLib_ExitCriticalSection(intr_state);

    /* Call dpm_wakeup() if dpm_sleep() had returned true. */
    if (dpm_slept)
    {
        Cy_PdStack_Dpm_Resume(ptrPdStackContext, &dpm_slept);
    }

#if BATTERY_CHARGING_ENABLE
    if (bc_slept)
    {
        chgdet_resume (ptrPdStackContext);
    }
#endif /* BATTERY_CHARGING_ENABLE */

    (void)ptrPdStack1Context;
    return retval;
}
#endif /* SYS_DEEPSLEEP_ENABLE */

#if VCONN_OCP_ENABLE
void app_vconn_ocp_tmr_cbk(cy_timer_id_t id,  void *context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;

    /* Disable VConn since we hit a fault. */
    vconn_disable(ptrPdStackContext, ptrPdStackContext->dpmConfig.revPol);

    /* Notify application layer about fault. */
    app_event_handler(ptrPdStackContext, APP_EVT_VCONN_OCP_FAULT, NULL);
}

bool app_vconn_ocp_cbk(void *context, bool comp_out)
{
    cy_stc_usbpd_context_t * ptrUsbPdContext = (cy_stc_usbpd_context_t *)context;
    cy_stc_pdstack_context_t * ptrPdStackContext = get_pdstack_context(ptrUsbPdContext->port);
    bool retval = false;

    if (comp_out)
    {
        /* Start a VConn OCP debounce timer */
        cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
                CY_PDSTACK_GET_PD_TIMER_ID(ptrPdStackContext, PD_VCONN_OCP_DEBOUNCE_TIMER),
                ptrPdStackContext->ptrUsbPdContext->usbpdConfig->vconnOcpConfig->debounce,
                app_vconn_ocp_tmr_cbk);
    }
    else
    {
        /* Negative edge. Check if the timer is still running. */
        retval = cy_sw_timer_is_running(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_PD_TIMER_ID(ptrPdStackContext, PD_VCONN_OCP_DEBOUNCE_TIMER));
        if (retval)
        {
            cy_sw_timer_stop(ptrPdStackContext->ptrTimerContext, CY_PDSTACK_GET_PD_TIMER_ID(ptrPdStackContext, PD_VCONN_OCP_DEBOUNCE_TIMER));
        }
    }

    return retval;
}

#endif /* VCONN_OCP_ENABLE */

void app_vconn_tmr_cbk(cy_timer_id_t id,  void *context)
{
    cy_stc_pdstack_context_t *ptrPdStackContext = (cy_stc_pdstack_context_t *)context;
    Cy_USBPD_Vconn_GatePullUp_Enable(ptrPdStackContext->ptrUsbPdContext);
}

bool vconn_enable(cy_stc_pdstack_context_t *ptrPdStackContext, uint8_t channel)
{
#if VCONN_OCP_ENABLE

    /* Do not attempt to enable VConn if fault was detected in present connection. */
    if ((app_get_status(ptrPdStackContext->port)->fault_status & APP_PORT_VCONN_FAULT_ACTIVE) != 0)
    {
        return false;
    }

    Cy_USBPD_Fault_Vconn_OcpEnable (ptrPdStackContext->ptrUsbPdContext, app_vconn_ocp_cbk);
#endif /* VCONN_OCP_ENABLE */

    /* Reset RX Protocol for cable */
    Cy_PdStack_Dpm_ProtResetRx(ptrPdStackContext, CY_PD_SOP_PRIME);
    Cy_PdStack_Dpm_ProtResetRx(ptrPdStackContext, CY_PD_SOP_DPRIME);

    if (Cy_USBPD_Vconn_Enable(ptrPdStackContext->ptrUsbPdContext, channel) != CY_USBPD_STAT_SUCCESS)
    {
#if ((defined(CY_DEVICE_CCG6)) || (defined(CY_DEVICE_PMG1S3)))
        app_status[ptrPdStackContext->port].fault_status |= APP_PORT_V5V_SUPPLY_LOST;
#endif /* PMG1 */
        return false;
    }
    /* Start a VConn OCP debounce timer */
    cy_sw_timer_start(ptrPdStackContext->ptrTimerContext, ptrPdStackContext,
            CY_PDSTACK_GET_APP_TIMER_ID(ptrPdStackContext, APP_VCONN_TURN_ON_DELAY_TIMER),
            APP_VCONN_TURN_ON_DELAY_PERIOD,
            app_vconn_tmr_cbk);
    return true;
}

void vconn_disable(cy_stc_pdstack_context_t *ptrPdStackContext, uint8_t channel)
{
    Cy_USBPD_Vconn_Disable(ptrPdStackContext->ptrUsbPdContext, channel);
#if VCONN_OCP_ENABLE
    Cy_USBPD_Fault_Vconn_OcpDisable(ptrPdStackContext->ptrUsbPdContext);
#endif /* VCONN_OCP_ENABLE */
}

bool vconn_is_present(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    return Cy_USBPD_Vconn_IsPresent(ptrPdStackContext->ptrUsbPdContext, ptrPdStackContext->dpmConfig.revPol);
}

#if PSVP_FPGA_ENABLE
#include "cy_usbpd_pmg1s3_regs.h"
#endif /* PSVP_FPGA_ENABLE */

bool vbus_is_present(cy_stc_pdstack_context_t *ptrPdStackContext, uint16_t volt, int8 per)
{
#if PSVP_FPGA_ENABLE
    PPDSS_REGS_T pd = ptrPdStackContext->ptrUsbPdContext->base;
    bool ret = false;

    /* Since the PSVP implementation does not support any analog components, we need to use a hack to identify whether
     * the Vbus voltage is under 1 V or higher than 4 V.
     */
    if ((volt + ((per * volt) / 100)) <= 5500)
    {
        pd->adc_ctrl = ((pd->adc_ctrl & 0x7F00) | 0x02);
        Cy_SysLib_DelayUs (100);
        if ((pd->adc_ctrl & (1 << 15)) != 0)
            ret = true;
    }
    else
    {
        if (volt <= 800u)
        {
            pd->adc_ctrl = ((pd->adc_ctrl & 0x7F00) | 0x01);
            Cy_SysLib_DelayUs (100);
            if ((pd->adc_ctrl & (1 << 15)) != 0)
                ret = true;
        }
    }

    return ret;
#else
    uint8_t level;
    uint8_t retVal;

    /*
     * Re-run calibration every time to ensure that VDDD or the measurement
     * does not break.
     */
    Cy_USBPD_Adc_Calibrate(ptrPdStackContext->ptrUsbPdContext, APP_VBUS_POLL_ADC_ID);
    level =  Cy_USBPD_Adc_GetVbusLevel(ptrPdStackContext->ptrUsbPdContext,
                           APP_VBUS_POLL_ADC_ID,
                           volt, per);

    retVal = Cy_USBPD_Adc_CompSample(ptrPdStackContext->ptrUsbPdContext,
                     APP_VBUS_POLL_ADC_ID,
                     APP_VBUS_POLL_ADC_INPUT, level);

    return retVal;
#endif /* PSVP_FPGA_ENABLE */
}

void vbus_discharge_on(cy_stc_pdstack_context_t* context)
{
    Cy_USBPD_Vbus_DischargeOn(context->ptrUsbPdContext);
}

void vbus_discharge_off(cy_stc_pdstack_context_t* context)
{
    Cy_USBPD_Vbus_DischargeOff(context->ptrUsbPdContext);
}

uint16_t vbus_get_value(cy_stc_pdstack_context_t *ptrPdStackContext)
{
    uint16_t retVal;

    /* Measure the actual VBUS voltage. */
    retVal = Cy_USBPD_Adc_MeasureVbus(ptrPdStackContext->ptrUsbPdContext,
                          APP_VBUS_POLL_ADC_ID,
                          APP_VBUS_POLL_ADC_INPUT);

    return retVal;
}

#if ((CY_PD_EPR_ENABLE) && (!CY_PD_SINK_ONLY))
bool eval_epr_mode(cy_stc_pdstack_context_t *ptrPdStackContext, cy_en_pdstack_eprmdo_action_t eprModeState, cy_pdstack_app_resp_cbk_t app_resp_handler)
{
    (void) ptrPdStackContext;
    (void) eprModeState;
    (void) app_resp_handler;

    /* Place holder for customer specific EPR Source preparation
     * It is possible to provide additional checking before sends EPR Mode Enter Acknowledged  */

    return true;
}

bool send_epr_cap(cy_stc_pdstack_context_t *ptrPdStackContext, cy_pdstack_app_resp_cbk_t app_resp_handler)
{
    (void) ptrPdStackContext;
    (void) app_resp_handler;

    /* Place holder for customer specific EPR Source preparation
     * It is possible to provide additional checking before sends EPR SRC CAP  */

    app_resp_handler(ptrPdStackContext, NULL);

    return true;
}
#endif /* ((CY_PD_EPR_ENABLE) && (!CY_PD_SINK_ONLY)) */

/* End of File */
