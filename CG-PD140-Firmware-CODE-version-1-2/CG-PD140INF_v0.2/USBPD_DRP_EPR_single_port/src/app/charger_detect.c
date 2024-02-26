/******************************************************************************
* File Name: charger_detect.c
*
* Description: This source file implements the BC 1.2 (legacy) charger detect
*              functions which are part of the PMG1 MCU USBPD Sink Example for
*              ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2021-YEAR Cypress Semiconductor $
*******************************************************************************/

#include <cybsp.h>

#include <charger_detect.h>
#include <cy_pdstack_common.h>
#include <cy_pdstack_dpm.h>
#include <cy_pdstack_utils.h>
#include <cy_usbpd_bch.h>
#include <psink.h>
#include <psource.h>
#include <cy_sw_timer.h>
#include <cy_sw_timer_id.h>
#include <app.h>

#if (BATTERY_CHARGING_ENABLE)

chgdet_status_t gl_chgdet_status[NO_OF_TYPEC_PORTS];
bool vdm_src_applied[NO_OF_TYPEC_PORTS];
bool detach_detect_en[NO_OF_TYPEC_PORTS];

#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))

static void chgdet_timer_cb(cy_timer_id_t id, void *cbContext)
{
    if (id == APP_BC_GENERIC_TIMER1)
    {
        chgdet_fsm_set_evt((cy_stc_pdstack_context_t *)cbContext, BC_EVT_TIMEOUT1);
    }

    if (id == APP_BC_GENERIC_TIMER2)
    {
        chgdet_fsm_set_evt((cy_stc_pdstack_context_t *)cbContext, BC_EVT_TIMEOUT2);
    }
}

static void chgdet_fsm_off(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    /* Nothing to do in this state. */
    CY_UNUSED_PARAMETER(stack_ctx);
    CY_UNUSED_PARAMETER(evt);
}

static void chgdet_fsm_sink_start(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];

    if (evt == CHGDET_FSM_EVT_ENTRY)
    {
        /* Reset the charger detect hardware block by disabling and enabling it. */
        Cy_USBPD_Bch_Phy_Dis(stack_ctx->ptrUsbPdContext);
        Cy_USBPD_Bch_Phy_En(stack_ctx->ptrUsbPdContext);

        /* Move to the Primary Charger Detect state. */
        chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SINK_PRIMARY_CHARGER_DETECT;
        chgdet_fsm_set_evt (stack_ctx, BC_EVT_ENTRY);
    }
}

/* This state is for primary charger detect. Refer BC 1.2 spec for details. */
static void chgdet_fsm_sink_primary_charger_detect(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];

    switch (evt)
    {
        case CHGDET_FSM_EVT_ENTRY:
            /* Apply terminations on D+/- and start VDP_DM_SRC_ON timer to schedule the next step. */
            Cy_USBPD_Bch_Phy_ConfigSnkTerm (stack_ctx->ptrUsbPdContext, CHGB_SINK_TERM_PCD);
            cy_sw_timer_start(stack_ctx->ptrTimerContext, (void *)stack_ctx, APP_BC_GENERIC_TIMER1,
                    APP_BC_VDP_DM_SRC_ON_PERIOD, chgdet_timer_cb);
            break;

        case CHGDET_FSM_EVT_TIMEOUT1:
            /* Now measure D- and see if D- is pulled up to VDP_SRC. */
            if (Cy_USBPD_Bch_Phy_Config_Comp (stack_ctx->ptrUsbPdContext, 0U, CHGB_COMP_P_DM, CHGB_COMP_N_VREF,
                        CHGB_VREF_0_325V, CHGB_COMP_NO_INTR) == true)
            {
                /* Start timer for source to differentiate between primary and secondary detection */
                cy_sw_timer_start(stack_ctx->ptrTimerContext, (void *)stack_ctx, APP_BC_GENERIC_TIMER2,
                        APP_BC_VDMSRC_EN_DIS_PERIOD, chgdet_timer_cb);
            }
            else
            {
                /* TYPE-C only source is connected. */
                chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SINK_TYPE_C_ONLY_SOURCE_CONNECTED;
                chgdet_fsm_set_evt(stack_ctx, BC_EVT_ENTRY);
            }

            /* Remove applied terminations */
            Cy_USBPD_Bch_Phy_RemoveTerm(stack_ctx->ptrUsbPdContext);
            break;

        case CHGDET_FSM_EVT_TIMEOUT2:
            /* Proceed to secondary detection for CDP/DCP detection. */
            chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SINK_SECONDARY_CHARGER_DETECT;
            chgdet_fsm_set_evt(stack_ctx, BC_EVT_ENTRY);
            break;

        default:
            break;
    }
}

static void chgdet_fsm_sink_type_c_only_source_connected(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    if (evt == CHGDET_FSM_EVT_ENTRY)
    {
        /* Disable charger detect block operation. */
        Cy_USBPD_Bch_Phy_Dis(stack_ctx->ptrUsbPdContext);
    }
}

/* This state is used to perform secondary charger detect. Refer BC 1.2 spec for details. */
static void chgdet_fsm_sink_secondary_charger_detect(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];

    switch (evt)
    {
        case CHGDET_FSM_EVT_ENTRY:
            /* Apply terminations on D+/-. */
            Cy_USBPD_Bch_Phy_ConfigSnkTerm(stack_ctx->ptrUsbPdContext, CHGB_SINK_TERM_SCD);

            /* Start timer to apply VDM_SRC for TVDM_SRC_ON */
            cy_sw_timer_start(stack_ctx->ptrTimerContext, (void *)stack_ctx, APP_BC_GENERIC_TIMER1,
                    APP_BC_VDP_DM_SRC_ON_PERIOD, chgdet_timer_cb);
            break;

        case CHGDET_FSM_EVT_TIMEOUT1:
            /* Now measure D+ and see if D- is pulled up to VDM_SRC. */
            if (Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 0U, CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                        CHGB_VREF_0_325V, CHGB_COMP_NO_INTR) == true)
            {
                /* DCP connected. */
                chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SINK_DCP_CONNECTED;
            }
            else
            {
                /* CDP connected. */
                chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SINK_CDP_CONNECTED;
            }

            chgdet_fsm_set_evt(stack_ctx, BC_EVT_ENTRY);

            /* Remove applied terminations */
            Cy_USBPD_Bch_Phy_RemoveTerm(stack_ctx->ptrUsbPdContext);
            break;

        default:
            break;
    }
}

/* The Type-C source is a Downstream Charging Port (DCP). */
static void chgdet_fsm_sink_dcp_connected(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    if (evt == CHGDET_FSM_EVT_ENTRY)
    {
        Cy_USBPD_Bch_Phy_Dis(stack_ctx->ptrUsbPdContext);

        /* Set current limit to 1.5A (DCP) and enable Sink FET if not already turned ON. */
        psnk_set_current(stack_ctx, CY_PD_I_1P5A);
        psnk_enable(stack_ctx);
    }
}

/* The Type-C source is a Standard Downstream Port (SDP). */
static void chgdet_fsm_sink_sdp_connected(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    if (evt == CHGDET_FSM_EVT_ENTRY)
    {
        Cy_USBPD_Bch_Phy_Dis(stack_ctx->ptrUsbPdContext);

        /* Set current limit to 0.5A (SDP) and enable Sink FET if not already turned ON. */
        psnk_set_current(stack_ctx, CY_PD_ISAFE_DEF);
        psnk_enable(stack_ctx);
    }
}

/* The Type-C source is a Charging Downstream Port (CDP). */
static void chgdet_fsm_sink_cdp_connected(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    if (evt == CHGDET_FSM_EVT_ENTRY)
    {
        Cy_USBPD_Bch_Phy_Dis(stack_ctx->ptrUsbPdContext);

        /* Set current limit to 1.5A (CDP) and enable Sink FET if not already turned ON. */
        psnk_set_current(stack_ctx, CY_PD_I_1P5A);
        psnk_enable(stack_ctx);
    }
}

static void chgdet_pwr_ready_cbk(cy_stc_pdstack_context_t *stack_ctx)
{
   CY_UNUSED_PARAMETER(stack_ctx);

   /* Add application code here */
}

static void chgdet_fsm_src_look_for_connect(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];

    switch(evt)
    {
        case CHGDET_FSM_EVT_ENTRY:
            /*
             * The detection logic varies based on the protocols selected
             *
             * If Apple charging is selected, keep presenting the Apple terminations.
             * In case of Apple only charging mode, keep presenting the terminations.
             * There is no further action after this.
             *
             * If Apple charging along with BC 1.2 based detection is enabled,
             * then first start with Apple 2.4A termination. Also enable D+ comparator
             * to look for < 2.2V. If this is detected, then switch to BC termination
             * and proceed with BC 1.2 based connection detection logic.
             *
             * If Apple charging is not selected, then proceed directly to BC 1.2
             * terminations and subsequent detection logic.
             *
             * Detach detection for Apple and BC 1.2 DCP sink cannot be done as
             * sink terminations are not present after detection. Only re-attach
             * can be detected. So, In case of BC 1.2 DCP operation, this state
             * shall be re-entered to reapply Apple terminations as required.
             *
             * In case of QC and AFC mode of operation, detach can be detected.
             * When this happens, this state shall be re-entered. Detach handling
             * needs to be done for this.
             *
             * NOTE: There are two cases which are not currently dealt with:
             * 1. In case of Type-C port, when we enter legacy state machine for
             *    the first time, the VBUS may be already be present and the
             *    sink may already be attached and completed its detection logic.
             *    We may need to power cycle VBUS to restart sink's detection
             *    logic. This is not currently done as we start PD and Legacy
             *    together (LEGACY_PD_PARALLEL_OPER).
             *
             * 2. In case of Type-A port attached to a BC 1.2 sink or an Apple
             *    sink, there is no real detach detection. When Apple charging
             *    is enabled, there is also no re-attach detection.
             *
             *    The type-A port current consumption is monitored to switch to
             *    low power regulator when current drops below 300mA. This same
             *    logic moves back to high power regulator, but there is a polling
             *    delay as well as regulator turn on delay involved which can
             *    cause the 5V regulator (which also feeds the CCG3PA device) to
             *    shut-off due to over current.
             *
             *    There may be a work around; when we switch to low power regulator,
             *    also switch to BC 1.2 DCP attach wait state and stay there until
             *    there is an attach. In event of attach, switch to Apple mode of
             *    detection and proceed as usual.
             *
             *    Since the current systems are able to withstand the switch
             *    without disconnecting, no implementation is done currently.
             */
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
            cy_sw_timer_stop_range(stack_ctx->ptrTimerContext, APP_BC_GENERIC_TIMER1, APP_BC_DETACH_DETECT_TIMER);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_EVT_ALL_MASK);
            (void)Cy_USBPD_Bch_Phy_En(stack_ctx->ptrUsbPdContext);


           {
                /*
                 * If in DCP mode, do not change the setting, else this is
                 * a detach. Indicate the same.
                 */ 
                if (chgdet_stat->src_mode != BC_CHARGE_DCP)
                {
                    chgdet_stat->src_mode = BC_CHARGE_NONE;
                    chgdet_stat->attach = false;
                }

                /* Ensure CDP terminations are on by default. */
                (void)Cy_USBPD_Bch_Phy_ConfigSrcTerm(stack_ctx->ptrUsbPdContext, CHGB_SRC_TERM_CDP);

                /* Set Comp1 to look for > 0.4V on D+ */
                (void)Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 0U, CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                        CHGB_VREF_0_325V, CHGB_COMP_EDGE_RISING);
            }

            /* Ensure that VBUS is 5V. But do this only if PD is disabled. */
            if (
                    (stack_ctx->dpmStat.pdDisabled != false)
               )
            {
                psrc_set_voltage(stack_ctx, CY_PD_VSAFE_5V);
                psrc_enable(stack_ctx, chgdet_pwr_ready_cbk);
            }
            break;

        case CHGDET_FSM_EVT_CMP1_FIRE:
            {
                chgdet_stat->attach = true;
                chgdet_stat->src_mode = BC_CHARGE_NONE;
                chgdet_stat->cur_amp = BC_AMP_LIMIT;
                (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
        
                Cy_USBPD_Bch_Apply_VdmSrc(stack_ctx->ptrUsbPdContext);

                (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
                chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SRC_INITIAL_CONNECT;
                chgdet_fsm_set_evt(stack_ctx, BC_EVT_ENTRY);
            }
            break;
 
        default:
            /* No Statement */
            break;
    }
}

static void chgdet_fsm_src_initial_connect(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    
    switch(evt)
    {
        case CHGDET_FSM_EVT_ENTRY:
            chgdet_stat->comp_rising = false;
            /* Set Comp0 to look for < 0.4V on D+ for 1 second */
            (void)Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 0U, 
                                               CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                                               CHGB_VREF_0_325V, CHGB_COMP_EDGE_FALLING);

            /* Set Comp1 to ensure DP does not go above 0.85 V. */
            (void)Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 1U, 
                                                CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                                                CHGB_VREF_0_85V, CHGB_COMP_EDGE_RISING);
                            

            Cy_USBPD_Bch_Apply_VdmSrc(stack_ctx->ptrUsbPdContext);
            /* Start TGLITCH_BC_DONE timer to ascertain Apple or others */
            (void)cy_sw_timer_start(stack_ctx->ptrTimerContext, (void*)stack_ctx, (uint8_t)APP_BC_GENERIC_TIMER1,
                                               APP_BC_DCP_DETECT_TIMER_PERIOD, chgdet_timer_cb);
            break;

        case CHGDET_FSM_EVT_CMP1_FIRE:
            if(chgdet_stat->comp_rising == false)
            {
                /*
                 * If AFC or BC1.2 mode is enabled, then we will
                 * have to determine those devices.
                 */
                Cy_USBPD_Bch_Remove_VdmSrc(stack_ctx->ptrUsbPdContext);

                chgdet_fsm_clear_evt (stack_ctx, BC_EVT_TIMEOUT2);
                (void)cy_sw_timer_start(stack_ctx->ptrTimerContext, (void*)stack_ctx,
                        (uint8_t)APP_BC_GENERIC_TIMER2,
                        150u, chgdet_timer_cb);

                /* Set Comp0 to look for > 0.4V on D+. */
                (void)Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 0U, 
                                                   CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                                                   CHGB_VREF_0_325V, CHGB_COMP_EDGE_RISING);
                chgdet_stat->comp_rising = true;
            }
            else
            {
                /* The DP line has gone above 0.6V. Re-start detection. */
                cy_sw_timer_stop(stack_ctx->ptrTimerContext, (uint8_t)APP_BC_GENERIC_TIMER2);
                chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_TIMEOUT2);
                (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
                chgdet_fsm_set_evt(stack_ctx, CHGDET_FSM_EVT_ENTRY);
            }
            break;


        case CHGDET_FSM_EVT_CMP2_FIRE:
            /*
             * If TGLITCH_BC_DONE timer is running, that means DP went above 2V before
             * glitch filter timer expired. We will have to wait for DP to come back in 0.4 - 2V range
             * and then start device detection again. Till then we will stay in DCP only mode.
             */
            if (cy_sw_timer_is_running (stack_ctx->ptrTimerContext, (uint8_t)APP_BC_GENERIC_TIMER1))
            {
                /* DP went above 2V. We should stop DCP Detect timer. */
                cy_sw_timer_stop(stack_ctx->ptrTimerContext, (uint8_t)APP_BC_GENERIC_TIMER1);
                chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_TIMEOUT1);
                /* Stop Apple device detect timer as well. */
                cy_sw_timer_stop(stack_ctx->ptrTimerContext, (uint8_t)APP_BC_GENERIC_TIMER2);
                chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_TIMEOUT2);

                /* Stop Comp0. */
                (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
                chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_CMP1_FIRE);

                /*
                 * From this point on we should wait for DP to fall below 0.85V. When it falls below
                 * 0.85V, we can start device detetcion again.
                 */
                (void)Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 1U, CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                          CHGB_VREF_0_85V, CHGB_COMP_EDGE_FALLING);
            }
            else
            {
                /* DP is now below 2V. Start device detection again. */
                (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
                chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SRC_INITIAL_CONNECT;
                chgdet_fsm_set_evt(stack_ctx, CHGDET_FSM_EVT_ENTRY);
            }
            break;

#if (!QC_AFC_CHARGING_DISABLED)
        case BC_FSM_EVT_TIMEOUT1:
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_CMP1_FIRE);
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_CMP2_FIRE);
            cy_sw_timer_stop(stack_ctx->ptrTimerContext, (uint8_t)APP_BC_GENERIC_TIMER2);
            chgdet_fsm_clear_evt(stack->ctx, BC_EVT_TIMEOUT2);
            chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SRC_OTHERS_CONNECTED;
            chgdet_fsm_set_evt(stack_ctx, CHGDET_FSM_EVT_ENTRY);
            break;
#endif /* (!QC_AFC_CHARGING_DISABLED) */

        case CHGDET_FSM_EVT_TIMEOUT2:
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_CMP1_FIRE);
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_CMP2_FIRE);
            cy_sw_timer_stop(stack_ctx->ptrTimerContext, (uint8_t)APP_BC_GENERIC_TIMER1);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_FSM_EVT_TIMEOUT1);

            /* Treat this as a BC1.2 device. */
            /* Indicate BC1.2 device is connected so that current
             * monitoring can start. */
    
            chgdet_stat->connected = true;
            chgdet_stat->src_mode = BC_CHARGE_DCP;
            chgdet_stat->cur_amp = BC_AMP_LIMIT;
            /* Go back to init state and wait for DP attach event similar
             * to Apple mode. */
            chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SRC_LOOK_FOR_CONNECT;
            chgdet_fsm_set_evt(stack_ctx, CHGDET_FSM_EVT_ENTRY);
            break;

        default:
            /* No Statement */
            break;
    }
}

static void chgdet_fsm_src_apply_cdp(cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];

    switch(evt)
    {
        case CHGDET_FSM_EVT_ENTRY:

            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
            cy_sw_timer_stop_range(stack_ctx->ptrTimerContext, APP_BC_GENERIC_TIMER1, APP_CDP_DP_DM_POLL_TIMER);
            chgdet_fsm_clear_evt(stack_ctx, CHGDET_EVT_ALL_MASK);
            detach_detect_en[stack_ctx->port] = false;
            (void)Cy_USBPD_Bch_Phy_En(stack_ctx->ptrUsbPdContext);

            chgdet_stat->src_mode = BC_CHARGE_CDP;
            Cy_USBPD_Bch_Phy_ConfigSrcTerm(stack_ctx->ptrUsbPdContext, CHGB_SRC_TERM_CDP);

            /* Set comparator 1 to fire when D+ > 0.425V */
            Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 0U, CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                        CHGB_VREF_0_325V, CHGB_COMP_EDGE_RISING);
            /* Set comparator 2 to fire when D+ > 0.85V */
            Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 1U, CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                        CHGB_VREF_0_85V, CHGB_COMP_EDGE_RISING);
            
            vdm_src_applied[stack_ctx->port] = false;
            chgdet_stat->comp_rising = false;
            break;

        case CHGDET_FSM_EVT_CMP1_FIRE:
            if (!chgdet_stat->comp_rising)
            {
                /* Voltage in 0.4 to 0.8 range. Turn on VDM_SRC */
                if(!vdm_src_applied[stack_ctx->port])
                {
                    (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
                    vdm_src_applied[stack_ctx->port] = true;
                    chgdet_stat->comp_rising = true;

                    Cy_USBPD_Bch_Apply_VdmSrc(stack_ctx->ptrUsbPdContext);

                    /* Set comparator 1 to fire when D+ < 0.425V */
                    Cy_USBPD_Bch_Phy_Config_Comp(stack_ctx->ptrUsbPdContext, 0U, CHGB_COMP_P_DP, CHGB_COMP_N_VREF,
                        CHGB_VREF_0_325V, CHGB_COMP_EDGE_FALLING);
                }
            }
            else
            {
                /* Voltage below 0.4V , turn off VDM_SRC */
                chgdet_stat->comp_rising = false;
                if (vdm_src_applied[stack_ctx->port])
                {
                    Cy_USBPD_Bch_Remove_VdmSrc(stack_ctx->ptrUsbPdContext);
                    vdm_src_applied[stack_ctx->port] = false;
                }
               (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
               (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 1U);
               chgdet_fsm_set_evt(stack_ctx, CHGDET_FSM_EVT_ENTRY);
            }
            break;

        case CHGDET_FSM_EVT_CMP2_FIRE:
            /* Voltage gone above 0.8. Stop CDP detection */
            (void)Cy_USBPD_Bch_Phy_DisableComp(stack_ctx->ptrUsbPdContext, 0U);
            cy_sw_timer_stop_range(stack_ctx->ptrTimerContext, APP_BC_GENERIC_TIMER1, APP_BC_DP_DM_DEBOUNCE_TIMER);
            
            if(vdm_src_applied[stack_ctx->port])
            {
                Cy_USBPD_Bch_Remove_VdmSrc(stack_ctx->ptrUsbPdContext);
                vdm_src_applied[stack_ctx->port] = false;
            }
            break;

        default:
            break;
    }
}

void (*const chgdet_fsm_table[CHGDET_FSM_MAX_EVTS]) (cy_stc_pdstack_context_t *stack_ctx, chgdet_fsm_evt_t evt) =
{
    chgdet_fsm_off,                                 /* 0: CHGDET_FSM_OFF */

#if !(CY_PD_SINK_ONLY)
    chgdet_fsm_src_look_for_connect,                /* 1: CHGDET_FSM_SRC_LOOK_FOR_CONNECT */
    chgdet_fsm_src_initial_connect,                 /* 2: CHGDET_FSM_SRC_INITIAL_CONNECT */

#else
    chgdet_fsm_off,                                 /* 0: CHGDET_FSM_OFF */
    chgdet_fsm_off,                                 /* 0: CHGDET_FSM_OFF */
#endif /* SRC */

#if (defined(CY_DEVICE_CCG6) || defined(CY_DEVICE_PMG1S3))
    chgdet_fsm_src_apply_cdp,                       /* 3: CHGDET_FSM_SRC_CDP_CONNECTED */
#else
    chgdet_fsm_off,
#endif /* (defined(CY_DEVICE_CCG6) || defined(CY_DEVICE_PMG1S3)) */

    chgdet_fsm_sink_start,                          /* 4: CHGDET_FSM_SINK_START */
    chgdet_fsm_sink_primary_charger_detect,         /* 5: CHGDET_FSM_SINK_PRIMARY_CHARGER_DETECT */
    chgdet_fsm_sink_type_c_only_source_connected,   /* 6: CHGDET_FSM_SINK_TYPE_C_ONLY_SOURCE_CONNECTED */
    chgdet_fsm_sink_secondary_charger_detect,       /* 7: CHGDET_FSM_SINK_SECONDARY_CHARGER_DETECT */
    chgdet_fsm_sink_dcp_connected,                  /* 8: CHGDET_FSM_SINK_DCP_CONNECTED */
    chgdet_fsm_sink_sdp_connected,                  /* 9: CHGDET_FSM_SINK_SDP_CONNECTED */
    chgdet_fsm_sink_cdp_connected                   /* 10: CHGDET_FSM_SINK_CDP_CONNECTED */
};

/* Callback from the PDL driver. */
static void chgdet_phy_cbk_handler(void *drv_ctx, uint32_t event)
{
    cy_stc_usbpd_context_t *context = (cy_stc_usbpd_context_t *)drv_ctx;
    cy_stc_pdstack_context_t *stack_ctx = (cy_stc_pdstack_context_t *)(context->pdStackContext);
    chgdet_fsm_set_evt(stack_ctx, event);
}

#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */

cy_en_usbpd_status_t chgdet_init(cy_stc_pdstack_context_t *stack_ctx)
{
    cy_en_usbpd_status_t stat = CY_USBPD_STAT_BAD_PARAM;

#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    if ((stack_ctx != NULL) && (stack_ctx->port < NO_OF_TYPEC_PORTS))
    {
        if (Cy_USBPD_Bch_Phy_Init (stack_ctx->ptrUsbPdContext, chgdet_phy_cbk_handler) == CY_USBPD_STAT_SUCCESS)
        {
            stat = CY_USBPD_STAT_SUCCESS;
            gl_chgdet_status[stack_ctx->port].chgdet_fsm_state = CHGDET_FSM_OFF;
            gl_chgdet_status[stack_ctx->port].chgdet_evt       = 0;
        }
    }
#else
    CY_UNUSED_PARAMETER(stack_ctx);
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */

    return stat;
}

cy_en_usbpd_status_t chgdet_start(cy_stc_pdstack_context_t *stack_ctx)
{
#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];

    if (stack_ctx->dpmConfig.curPortRole == CY_PD_PRT_ROLE_SINK)
    {
        /* Move to start state for sink mode operation. */
        chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SINK_START;
    }
    else
    {
        /* Move to start state for source mode operation. */
        chgdet_stat->chgdet_fsm_state = CHGDET_FSM_SRC_CDP_CONNECTED;
        //Cy_USBPD_Bch_Phy_ConfigSrcTerm(stack_ctx->ptrUsbPdContext, CHGB_SRC_TERM_CDP);
    }
    chgdet_stat->chgdet_evt       = 1 << CHGDET_FSM_EVT_ENTRY;
    chgdet_stat->connected        = false;
#else
    CY_UNUSED_PARAMETER(stack_ctx);
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */

    return CY_USBPD_STAT_SUCCESS;
}

cy_en_usbpd_status_t chgdet_stop(cy_stc_pdstack_context_t *stack_ctx)
{
#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    cy_stc_usbpd_context_t *drv_ctx = (cy_stc_usbpd_context_t *)(stack_ctx->ptrUsbPdContext);

    Cy_USBPD_Bch_Phy_DisableComp(drv_ctx, 0u);
    cy_sw_timer_stop_range(stack_ctx->ptrTimerContext, APP_BC_GENERIC_TIMER1, APP_CDP_DP_DM_POLL_TIMER);
    Cy_USBPD_Bch_Phy_Dis(drv_ctx);

    chgdet_stat->chgdet_fsm_state = CHGDET_FSM_OFF;
    chgdet_stat->chgdet_evt       = 0;
    chgdet_stat->connected        = false;
    chgdet_stat->attach           = false;
    chgdet_stat->cur_volt         = CY_PD_VSAFE_0V;

    /* If there is no PD contract, ensure current limit is set to minimum. */
    if (stack_ctx->dpmConfig.contractExist == 0u)
    {
        psnk_set_current (stack_ctx, CY_PD_ISAFE_0A);
    }

#else
    CY_UNUSED_PARAMETER(stack_ctx);
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */

    return CY_USBPD_STAT_SUCCESS;
}

bool chgdet_is_active(cy_stc_pdstack_context_t *stack_ctx)
{
#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    bool ret = false;

    if (chgdet_stat->chgdet_fsm_state != CHGDET_FSM_OFF)
    {
        ret = true;
    }

    return ret;
#else
    CY_UNUSED_PARAMETER(stack_ctx);
    return false;
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */
}

cy_en_usbpd_status_t chgdet_task(cy_stc_pdstack_context_t *stack_ctx)
{
#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    chgdet_status_t* chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    uint8_t evt;

    if (stack_ctx->dpmConfig.connect == 0u)
    {
        chgdet_stop(stack_ctx);
        return CY_USBPD_STAT_SUCCESS;
    }

    /* Get the next event to be processed. */
    evt = event_group_get_event((uint32_t *)&(chgdet_stat->chgdet_evt), true);
    if (evt < CHGDET_FSM_MAX_EVTS)
    {
        /* Call the FSM handler function if we have a valid event. */
        chgdet_fsm_table[chgdet_stat->chgdet_fsm_state](stack_ctx, (chgdet_fsm_evt_t)evt);
    }
#else
    CY_UNUSED_PARAMETER(stack_ctx);
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */

    return CY_USBPD_STAT_SUCCESS;
}

bool chgdet_prepare_deepsleep(cy_stc_pdstack_context_t *stack_ctx)
{
#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    bool ret = false;

    if (
            (chgdet_stat->chgdet_evt == 0u) &&
            (!cy_sw_timer_range_enabled (stack_ctx->ptrTimerContext, APP_BC_GENERIC_TIMER1, APP_BC_DP_DM_DEBOUNCE_TIMER))
       )
    {
        Cy_USBPD_Bch_Phy_Config_DeepSleep ((cy_stc_usbpd_context_t *)(stack_ctx->ptrUsbPdContext));
        ret = true;
    }

    return ret;
#else
    CY_UNUSED_PARAMETER(stack_ctx);
    return true;
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */
}

void chgdet_resume(cy_stc_pdstack_context_t *stack_ctx)
{
#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    Cy_USBPD_Bch_Phy_Config_Wakeup((cy_stc_usbpd_context_t *)(stack_ctx->ptrUsbPdContext));
#else
    CY_UNUSED_PARAMETER(stack_ctx);
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */
}

const chgdet_status_t* chgdet_get_status(cy_stc_pdstack_context_t *stack_ctx)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    return ((const chgdet_status_t *)chgdet_stat);
}

void chgdet_pd_event_handler(cy_stc_pdstack_context_t *stack_ctx, cy_en_pdstack_app_evt_t evt, const void* dat)
{
    CY_UNUSED_PARAMETER(dat);

    if (stack_ctx->port != 0)
        return;

#if (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD))
    switch (evt)
    {
        case APP_EVT_DISCONNECT:
        case APP_EVT_VBUS_PORT_DISABLE:
        case APP_EVT_TYPE_C_ERROR_RECOVERY:
            chgdet_stop(stack_ctx);
            break;

        case APP_EVT_TYPEC_ATTACH:
        case APP_EVT_PE_DISABLED:

            if (stack_ctx->dpmConfig.curPortRole == CY_PD_PRT_ROLE_SINK)
            {
                /* Start charger detect state machine once in the connected state if Rp detected is default Rp. */
                if (stack_ctx->dpmConfig.snkCurLevel == CY_PD_RD_USB)
                {
                    chgdet_start(stack_ctx);
                }
            }
            else
            {
                chgdet_start(stack_ctx);
            }
            break;

       case APP_EVT_PD_CONTRACT_NEGOTIATION_COMPLETE:
            /* Stop charger detect state machine once PD contract has been established. */
            chgdet_stop(stack_ctx);
            break;

        default:
            break;
    }
#else
    CY_UNUSED_PARAMETER(stack_ctx);
    CY_UNUSED_PARAMETER(evt);
#endif /* (defined(CY_IP_MXUSBPD) || defined(CY_IP_M0S8USBPD)) */
}

void chgdet_fsm_set_evt(cy_stc_pdstack_context_t *stack_ctx, uint32_t evt_mask)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    chgdet_stat->chgdet_evt |= evt_mask;
}

void chgdet_fsm_clear_evt(cy_stc_pdstack_context_t *stack_ctx, uint32_t evt_mask)
{
    chgdet_status_t *chgdet_stat = &gl_chgdet_status[stack_ctx->port];
    chgdet_stat->chgdet_evt &= ~evt_mask;
}


#endif /* (BATTERY_CHARGING_ENABLE) */

/* End of File */
