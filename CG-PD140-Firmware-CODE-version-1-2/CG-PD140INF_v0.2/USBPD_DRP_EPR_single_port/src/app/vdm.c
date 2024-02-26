/******************************************************************************
* File Name: vdm.c
*
* Description: This source file implements handlers for Vendor Defined Messages (VDMs)
*              as part of the PMG1 MCU USB-PD DRP Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#include "config.h"
#include "cy_sw_timer.h"
#include "vdm.h"
#include "cy_pdstack_common.h"
#include "cy_pdstack_utils.h"
#include "app.h"
#include "vdm_task_mngr.h"
#if (DFP_ALT_MODE_SUPP || UFP_ALT_MODE_SUPP)
#include "alt_modes_mngr.h"
#endif /* (DFP_ALT_MODE_SUPP || UFP_ALT_MODE_SUPP) */
#if DP_GPIO_CONFIG_SELECT
#include "dp_sid.h"
#endif /* DP_GPIO_CONFIG_SELECT */


/* Stores Discover ID response VDO count */
static uint8_t  gl_vdm_id_vdo_cnt[NO_OF_TYPEC_PORTS];

/* Stores Discover SVID response VDO count */
static uint8_t  gl_vdm_svid_vdo_cnt[NO_OF_TYPEC_PORTS];

/* Stores Discover Modes response VDO count */
static uint16_t gl_vdm_mode_data_len[NO_OF_TYPEC_PORTS];

/* Stores the actual Discover ID response data */
static cy_pd_pd_do_t gl_vdm_id_vdo_resp[NO_OF_TYPEC_PORTS][CY_PD_MAX_NO_OF_DO];

/* Stores pointer to Discover ID response data */
static cy_pd_pd_do_t *gl_vdm_id_vdo_p[NO_OF_TYPEC_PORTS];

/* Stores pointer to Discover SVID response data */
static cy_pd_pd_do_t *gl_vdm_svid_vdo_p[NO_OF_TYPEC_PORTS];

/* Stores pointer to Discover Modes response data */
static uint8_t *gl_vdm_mode_data_p[NO_OF_TYPEC_PORTS];

const vdm_info_config_t vdm_info[NO_OF_TYPEC_PORTS] =
{
    {
        .discId = {0xFF00A041, 0x19C004B4, 0x00000000, 0xF5040000, 0x40000000},
        .dIdLength = 0x18,
        .sVidLength = 0,
        .disModeLength = 0,
    },
    {
        .discId = {0xFF00A041, 0x19C004B4, 0x00000000, 0xF5040000, 0x40000001},
        .dIdLength = 0x18,
        .sVidLength = 0,
        .disModeLength = 0,
    }
};


#if (FLASH_ENABLE_NB_MODE == 1) && (FLASHING_MODE_PD_ENABLE == 1)
vdm_resp_cbk_t gl_vdm_resp_cbk = NULL;
/*
 * In Non-Blocking Flash Write Scenario, this is the callback
 * invoked by Flash Module after Flash row write completes.
 * This should be used to send back the VDM response.
 *
 * @param NONE
 * @param NONE
 */
void uvdm_nb_flash_write_cb(flash_write_status_t write_status)
{
    /* Non-Blocking Flashing is supported only for CCG3. Hence the port index is
     * fixed to 0.*/
    app_status_t* app_stat = app_get_status(0);

    /* Response should be sent out only if Flash write was not aborted. */
    if (write_status == FLASH_WRITE_COMPLETE)
    {
        app_stat->vdmResp.respBuf[UVDM_HEADER_INDEX].val =
            ((get_pd_config()->flashing_vid << 16) |
            (CMD_TYPE_RESP_ACK << 11) | (uvdm_get_cur_nb_cmd ()));
        app_stat->vdmResp.respBuf[UVDM_RESPONSE_VDO_INDEX].val =
            (CCG_STAT_SUCCESS + CCG_STATUS_CODE_OFFSET);

        app_stat->vdmResp.doCount = 2;
        /* Ignore Unstructured VDM */
        app_stat->vdmResp.noResp = VDM_AMS_RESP_READY;
        gl_vdm_resp_cbk (0, &app_stat->vdmResp);
    }

    uvdm_reset_nb_cmd_state ();
}
#else
void *uvdm_nb_flash_write_cb = NULL;
#endif /* (FLASH_ENABLE_NB_MODE == 1) && (FLASHING_MODE_PD_ENABLE == 1) */

/* Store VDM information from the config table in the RAM variables. */
void vdm_data_init(cy_stc_pdstack_context_t * context)
{
    uint16_t size = 0;
    uint8_t port = context->port;

    /* Calculate the number of VDOs in the D_ID response. */
    size = vdm_info[port].dIdLength;
    /* Subtract 4 bytes for the header and reduce to number of VDOs. */
    if (size > 4)
        gl_vdm_id_vdo_cnt[port] = (uint8_t)((size - 4) >> 2);
    else
        gl_vdm_id_vdo_cnt[port] = 0;

    /* Copy the actual Discover Identity response. */
    memcpy ((uint8_t *)gl_vdm_id_vdo_resp[port], (const uint8_t *)vdm_info[port].discId,
            gl_vdm_id_vdo_cnt[port] * 4u);

    /* Update the vendor and product IDs from the configuration data. */
    gl_vdm_id_vdo_resp[port][1].std_id_hdr.usbVid = context->ptrPortCfg->mfgVid;
    gl_vdm_id_vdo_resp[port][3].std_prod_vdo.usbPid = context->ptrPortCfg->mfgPid;

    /* Update the D_ID response pointer. */
    gl_vdm_id_vdo_p[port] = (cy_pd_pd_do_t *)(gl_vdm_id_vdo_resp[port]);

    /* Calculate the number of VDOs in the D_SVID response. */
    size = vdm_info[port].sVidLength;
    /* Subtract 4 bytes for the header and reduce to number of VDOs. */
    if (size > 4)
    {
        gl_vdm_svid_vdo_cnt[port] = (uint8_t)((size - 4) >> 2);

        /* Update the D_SVID response pointer. */
        gl_vdm_svid_vdo_p[port] = (cy_pd_pd_do_t *)((uint8_t *)(vdm_info[port].sVid));


        /* Store the D_MODE response length from configuration table. */
        gl_vdm_mode_data_len[port] = vdm_info[port].disModeLength;

        /* Store pointer to the D_MODE responses. */
        gl_vdm_mode_data_p[port] = (uint8_t *)(vdm_info[port].discMode);
    }
    else
    {
        gl_vdm_svid_vdo_cnt[port] = 0;
        gl_vdm_mode_data_len[port] = 0;
    }
}

void vdm_update_svid_resp(cy_stc_pdstack_context_t * context, uint8_t svid_vdo_cnt, uint8_t *svid_vdo_p)
{
    gl_vdm_svid_vdo_cnt[context->port]  = svid_vdo_cnt;
    gl_vdm_svid_vdo_p[context->port]    = (cy_pd_pd_do_t *)svid_vdo_p;
}

void vdm_update_data(cy_stc_pdstack_context_t * context, uint8_t id_vdo_cnt, uint8_t *id_vdo_p,
        uint8_t svid_vdo_cnt, uint8_t *svid_vdo_p, uint16_t mode_resp_len, uint8_t *mode_resp_p)
{
    uint8_t port = context->port;

    if (port < NO_OF_TYPEC_PORTS)
    {
        gl_vdm_id_vdo_cnt[port]    = id_vdo_cnt;
        gl_vdm_id_vdo_p[port]      = (cy_pd_pd_do_t *)id_vdo_p;
        gl_vdm_svid_vdo_cnt[port]  = svid_vdo_cnt;
        gl_vdm_svid_vdo_p[port]    = (cy_pd_pd_do_t *)svid_vdo_p;
        gl_vdm_mode_data_len[port] = mode_resp_len;
        gl_vdm_mode_data_p[port]   = mode_resp_p;
    }
}

bool get_modes_vdo_info(cy_stc_pdstack_context_t * context, uint16_t svid, cy_pd_pd_do_t **temp_p, uint8_t *no_of_vdo)
{
    uint8_t d_mode_resp_size_total;
    uint8_t d_mode_resp_size;
    cy_pd_pd_do_t *header;
    uint8_t* resp_p = gl_vdm_mode_data_p[context->port];

    /* Parse all responses based on SVID */
    d_mode_resp_size_total = gl_vdm_mode_data_len[context->port];

    /* If size is less than or equal to 4, return NACK. */
    if (d_mode_resp_size_total <= 4)
    {
        return false;
    }

    while (d_mode_resp_size_total)
    {
        /* Get the size of packet. */
        d_mode_resp_size = *resp_p;

        /* Read the SVID from header. */
        header = (cy_pd_pd_do_t *)(resp_p + 4);
        if (header->std_vdm_hdr.svid == svid)
        {
            *no_of_vdo = ((d_mode_resp_size-4) >> 2);
            *temp_p = header;
            return true;
        }
        /* Move to next packet. */
        resp_p += d_mode_resp_size;
        d_mode_resp_size_total -= d_mode_resp_size;
    }
    return false;
}

cy_pd_pd_do_t* get_gl_vdm_id(cy_stc_pdstack_context_t * context)
{
    return gl_vdm_id_vdo_p[context->port];
}

void eval_vdm(cy_stc_pdstack_context_t * context, const cy_stc_pdstack_pd_packet_t *vdm, cy_pdstack_vdm_resp_cbk_t vdm_resp_handler)
{
    app_status_t* app_stat = app_get_status(context->port);
    uint8_t port = context->port;

    cy_pd_pd_do_t* dobj = NULL;
    uint8_t i, count = 0u;
    bool pd3_live = false;

#if (!CCG_BACKUP_FIRMWARE)
    bool eval_rslt;
#endif /* (!CCG_BACKUP_FIRMWARE) */

#if (FLASHING_MODE_PD_ENABLE == 1)
#if (FLASH_ENABLE_NB_MODE == 1)
    gl_vdm_resp_cbk = vdm_resp_handler;
#endif /* FLASH_ENABLE_NB_MODE */
    uvdm_response_state_t response_state = UVDM_NOT_HANDLED;
#endif /* FLASHING_MODE_PD_ENABLE */

#if CY_PD_REV3_ENABLE
    if (context->dpmConfig.specRevSopLive >= CY_PD_REV3)
        pd3_live = true;
#endif

    /* By Default assume we will respond */
    app_stat->vdmResp.noResp = CY_PDSTACK_VDM_AMS_RESP_READY;

    if (
            (vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.vdmType == CY_PDSTACK_VDM_TYPE_STRUCTURED) &&
            (vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmdType == CY_PDSTACK_CMD_TYPE_INITIATOR)
       )
    {
        /* Copy received VDM Header data to VDM response Header*/
        app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].val = vdm->dat[CY_PD_VDM_HEADER_IDX].val;

#if CY_PD_REV3_ENABLE
        /* Use the minimum VDM version from among the partner's revision and the live revision. */
        app_stat->vdm_version = GET_MIN (app_stat->vdm_version, vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.stVer);
#endif /* CCG_PD_REV3_ENABLE */

        /* Set a NAK response by default. */
        app_stat->vdmResp.doCount = 1 ;
        app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmdType = CY_PDSTACK_CMD_TYPE_RESP_NAK;

#if MUX_DELAY_EN
        /* Save pointer to VDM response handler and set appropriate flag */
        app_stat->is_vdm_pending = true;
        app_stat->vdm_resp_cbk = vdm_resp_handler;
#endif /* MUX_DELAY_EN */


        if ((context->dpmConfig.curPortType == CY_PD_PRT_TYPE_UFP) || (pd3_live))
        {
            /* VDM Commands (D_ID -- EXIT_MODE) should be NAKd if VDO Count in VDM
             * command is more than one. */
            if (vdm->len == 1)
            {
                switch(vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmd)
                {
                    case CY_PDSTACK_VDM_CMD_DSC_IDENTITY:
                        count = gl_vdm_id_vdo_cnt[port];
                        if((vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.svid ==  STD_SVID) && (count != 0))
                        {
                            app_stat->vdmResp.doCount = count;
                            dobj = gl_vdm_id_vdo_p[port];
                            for(i = 0 ; i < count; i++)
                            {
                                app_stat->vdmResp.respBuf[i] = dobj[i];
                            }

#if CY_PD_REV3_ENABLE
                            /* Mask Product Type (DFP) and Connector Type fields when VDM version is 1.0. */
                            if (app_stat->vdm_version == 0)
                            {
                                cy_pd_pd_do_t id_hdr = app_stat->vdmResp.respBuf[VDO_START_IDX];
                                uint8_t max_do_cnt = 4;

                                /* Make sure to clear fields that are reserved under PD 2.0. */
                                id_hdr.val &= 0xFC1FFFFF;

                                /* Make sure to not use invalid product types. */
                                if (id_hdr.std_id_hdr.prodType == CY_PDSTACK_PROD_TYPE_PSD)
                                {
                                    id_hdr.std_id_hdr.prodType = CY_PDSTACK_PROD_TYPE_UNDEF;
                                }

                                /* AMAs may be providing one extra VDO. */
                                if (id_hdr.std_id_hdr.prodType == CY_PDSTACK_PROD_TYPE_AMA)
                                {
                                    max_do_cnt++;
                                }

                                /* Ensure that the size of the response is limited to what is valid based
                                 * on the ID header. */
                                if (app_stat->vdmResp.doCount > max_do_cnt)
                                    app_stat->vdmResp.doCount = max_do_cnt;
                                app_stat->vdmResp.respBuf[VDO_START_IDX] = id_hdr;
                            }
#else /* !CCG_PD_REV3_ENABLE */
                            app_stat->vdmResp.respBuf[VDO_START_IDX].std_id_hdr.rsvd1 = 0;
#endif /* CCG_PD_REV3_ENABLE */

                            /* Set VDM Response ACKed */
                            app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmdType = CY_PDSTACK_CMD_TYPE_RESP_ACK;
                        }
                        break;

#if (!CCG_BACKUP_FIRMWARE)
                    case CY_PDSTACK_VDM_CMD_DSC_SVIDS:
                        count = gl_vdm_svid_vdo_cnt[port];
                        if((vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.svid == STD_SVID) && (count != 0))
                        {
                            app_stat->vdmResp.doCount = count;
                            dobj = gl_vdm_svid_vdo_p[port];
                            for(i = 0 ; i < count; i++)
                            {
                                app_stat->vdmResp.respBuf[i] = dobj[i];
                            }
                            /* Set VDM Response ACKed */
                            app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmdType = CY_PDSTACK_CMD_TYPE_RESP_ACK;
                        }
                        break;

                    case CY_PDSTACK_VDM_CMD_DSC_MODES:
                        eval_rslt = get_modes_vdo_info (context, vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.svid,
                            &dobj, &count);
                        if (eval_rslt == true)
                        {
                            app_stat->vdmResp.doCount = count;
                            for (i = 0; i < count; i++)
                            {
                                app_stat->vdmResp.respBuf[i] = dobj[i];
                            }
#if DP_GPIO_CONFIG_SELECT
                            /*
                             * For GPIO based DP Pin configuration selection, update the
                             * response based on GPIO status.
                             */
                            if (vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.svid == DP_SVID)
                            {
                                app_stat->vdmResp.respBuf[1].std_dp_vdo.dfpDPin = dp_sink_get_pin_config ();
                            }
#endif /* DP_GPIO_CONFIG_SELECT */

#if ((TBT_UFP_SUPP) && (VPRO_DOCK_SUPPORT_ENABLE))
                            if (
                                    (PD_GET_PTR_TBTHOST_CFG_TBL(port)->vpro_capable)
                               )
                            {
                                /* Set the VPro available bit in the Mode VDO if enabled in config table. */
                                if (vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.svid == INTEL_VID)
                                {
                                    /* Set the VPro enable bit in the Mode VDO. */
                                    app_stat->vdmResp.respBuf[1].val |= TBT_MODE_VPRO_AVAIL;
                                }
                            }
#endif /* ((TBT_UFP_SUPP) && (VPRO_DOCK_SUPPORT_ENABLE)) */

                            /* Set VDM Response ACKed */
                            app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmdType = CY_PDSTACK_CMD_TYPE_RESP_ACK;
                        }
                        break;

                    case CY_PDSTACK_VDM_CMD_ENTER_MODE:
                        break;

                    case CY_PDSTACK_VDM_CMD_EXIT_MODE:
                        break;
#endif /* (!CCG_BACKUP_FIRMWARE) */

                    case CY_PDSTACK_VDM_CMD_ATTENTION:
                        /* Ignore Attention VDM */
                        app_stat->vdmResp.noResp = CY_PDSTACK_VDM_AMS_RESP_NOT_REQ;
                        break;

                    default:
                        break;
                }
            }

            /* Under PD2, handle VDMs based on VDM manager functionality. */
            if (!pd3_live)
            {
                if (
                        (vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.svid != STD_SVID) &&
                        (vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmd != CY_PDSTACK_VDM_CMD_ATTENTION)
                   )
                {
#if UFP_ALT_MODE_SUPP
                    /* If DFP cmd processed success */
                    if (eval_rec_vdm(port, vdm))
                    {
                        /* Set VDM Response ACKed */
                        app_stat->vdmResp.respBuf[VDM_HEADER_IDX].std_vdm_hdr.cmdType = CMD_TYPE_RESP_ACK;
                    }
                    else
#endif /* UFP_ALT_MODE_SUPP */
                    {
                    }
                }
            }
#if CY_PD_REV3_ENABLE
            else
            {
#if ((DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP))
                if (gl_dpm_port_type[port] != PRT_TYPE_UFP)
                {
                    if ((vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.cmd == VDM_CMD_ENTER_MODE) ||
                            (vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.cmd == VDM_CMD_EXIT_MODE))
                    {
                        app_stat->vdmResp.noResp = VDM_AMS_RESP_NOT_REQ;
                    }
                    else
                    {
                        if (vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.cmd == VDM_CMD_ATTENTION)
                        {
                            app_stat->vdmResp.noResp = VDM_AMS_RESP_NOT_REQ;
                        }
                        eval_rec_vdm(port, vdm);
                    }
                }
                else
                {
                    /* If received cmd processed success */
                    if (eval_rec_vdm(port, vdm) == true)
                    {
                        /* Set VDM Response ACKed */
                        app_stat->vdmResp.respBuf[VDM_HEADER_IDX].std_vdm_hdr.cmdType = CMD_TYPE_RESP_ACK;
                    }
                }
#endif /* (DFP_ALT_MODE_SUPP) || (UFP_ALT_MODE_SUPP) */
            }
#endif /* CCG_PD_REV3_ENABLE */
        }
        else
        {
#if DFP_ALT_MODE_SUPP
            if ((vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.cmd == VDM_CMD_ATTENTION) && (app_stat->vdm_task_en == true))
            {
                /* evaluate attention VDM */
                eval_rec_vdm(port, vdm);
            }
#endif /* DFP_ALT_MODE_SUPP */

            if (vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmd == CY_PDSTACK_VDM_CMD_ATTENTION)
            {
                /* Ignore Attention VDM */
                app_stat->vdmResp.noResp = CY_PDSTACK_VDM_AMS_RESP_NOT_REQ;
            }
            else
            {
                if (vdm->dat[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.svid == STD_SVID)
                {
                    /* Respond with a NAK to Standard VDMs received on PD 2.0 connection while in DFP role. */
                    app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.cmdType = CY_PDSTACK_CMD_TYPE_RESP_NAK;
                }
            }
        }

        /* Set the VDM version for the response. */
        app_stat->vdmResp.respBuf[CY_PD_VDM_HEADER_IDX].std_vdm_hdr.stVer = app_stat->vdm_version;
    }
    else
    {
#if (FLASHING_MODE_PD_ENABLE == 1)
        /* Pass the VDM to U_VDM handler */
        response_state = uvdm_handle_cmd ((uint32_t *)(&vdm->hdr), &dobj, &count,
            uvdm_nb_flash_write_cb);
        /* Response is ready. Notify PD. */
        if (response_state == UVDM_HANDLED_RESPONSE_READY)
        {
            app_stat->vdmResp.doCount = count;
            for (i = 0; i < count; i++)
            {
                app_stat->vdmResp.respBuf[i] = dobj[i];
            }
        }
        /* No response to UVDM. */
        else if (response_state == UVDM_HANDLED_NO_RESPONSE)
        {
           /* Ignore Unstructured VDM response. */
            app_stat->vdmResp.noResp = VDM_AMS_RESP_FROM_EC;
        }
        /* UVDM not recognized by default UVDM handler. */
        else if (response_state == UVDM_NOT_HANDLED)
        {
            /*
             * This is the default implementation to handle UVDM commands which are
             * not recognized by CY UVDM handler. User can update this with custom
             * handlers.
             */

            /* If SVID is Flashing VID, respond with NAK. */
            if (vdm->dat[VDM_HEADER_IDX].std_vdm_hdr.svid ==
                get_pd_config()->flashing_vid)
            {
                app_stat->vdmResp.respBuf[VDM_HEADER_IDX].val =
                    vdm->dat[VDM_HEADER_IDX].val;
                app_stat->vdmResp.respBuf[VDM_HEADER_IDX].ustd_vdm_hdr.cmdType
                    = CMD_TYPE_RESP_NAK;
                app_stat->vdmResp.doCount = 1;
            }
            else
            {
                /* Invoke non-CY UVDM handlers here. */
#if QC_4_0_ENABLE
                /* QC 4.0 UVDM handling. */
                response_state = uvdm_qc_4_0_handler(port, (uint32_t *)(&vdm->hdr),
                    &dobj, &count);
                if (response_state == UVDM_HANDLED_RESPONSE_READY)
                {
                    app_stat->vdmResp.doCount = count;
                    for (i = 0; i < count; i++)
                    {
                        app_stat->vdmResp.respBuf[i] = dobj[i];
                    }
                }
                /* No response to UVDM. */
                else if (response_state == UVDM_HANDLED_NO_RESPONSE)
                {
                   /* Ignore Unstructured VDM response. */
                    app_stat->vdmResp.noResp = VDM_AMS_RESP_FROM_EC;
                }
#endif /* QC_4_0_ENABLE */

                if (response_state == UVDM_NOT_HANDLED)
                {

                    /*
                     * SVID is not Recognized. Ignore if PD contract is PD 2.0.
                     * Send Not_Supported if Contract is PD 3.0.
                     */

                    /* No VDM response required. */
                    app_stat->vdmResp.noResp = VDM_AMS_RESP_NOT_REQ;
#if CCG_PD_REV3_ENABLE
                    if (pd3_live)
                    {
                        /* PD 3.0 Contract: Respond with Not_Supported. */
                        app_stat->vdmResp.noResp = VDM_AMS_RESP_NOT_SUPP;
                    }
#endif /* CCG_PD_REV3_ENABLE */
                }
            }
        }
        /* UVDM handled but response will be sent later. */
        else
        {
            /* Ignore. */
            return;
        }
#else /* (FLASHING_MODE_PD_ENABLE != 1) */

#if UVDM_SUPP
        if (eval_rec_vdm(port, vdm) == false)
        {
            /* If UVDM not successed then ignore this UVDM */
            app_stat->vdmResp.noResp = VDM_AMS_RESP_FROM_EC;
        }
#else /* !UVDM_SUPP */
        if (
                (!pd3_live)
           )
        {
            /* If UVDM not successed then ignore this UVDM */
            app_stat->vdmResp.noResp = CY_PDSTACK_VDM_AMS_RESP_FROM_EC;
        }
        else
        {
            /* PD 3.0 Contract: Respond with Not_Supported. */
            app_stat->vdmResp.noResp = CY_PDSTACK_VDM_AMS_RESP_NOT_SUPP;
        }
#endif /* UVDM_SUPP */
#endif /* FLASHING_MODE_PD_ENABLE */
    }

#if MUX_DELAY_EN
    /* Send VDM response only when MUX is idle or alt mode response is NACK */
    if (
            (app_stat->vdmResp.respBuf[VDM_HEADER_IDX].std_vdm_hdr.cmdType != CMD_TYPE_RESP_ACK) ||
            (app_stat->is_mux_busy == false)
       )
    {
        vdm_resp_handler(port, &app_stat->vdmResp);
        app_stat->is_vdm_pending = false;
    }
#else
    vdm_resp_handler(context, &app_stat->vdmResp);
#endif /* MUX_DELAY_EN */
}

#if CCG_USB4_SUPPORT_ENABLE
/*
 * Follow "Valid Responses to Enter_USB Request" table for PD spec addendum.
 * This function assumes that the UFP VDO1 is always present as the first product type VDO in the
 * Discover_Identity response, for feature matching purposes.
 */
void eval_enter_usb(uint8_t port, const pd_packet_t *eudo_p, app_resp_cbk_t app_resp_handler)
{
    /* Basic validity checks including message length would have been done by the PD stack. */
    pd_do_t eudo    = eudo_p->dat[0];
    pd_do_t ufp_vdo = gl_vdm_id_vdo_p[port][PRODUCT_TYPE_VDO_1_IDX];

    /* Default response: REJECT. */
    app_get_resp_buf(port)->reqStatus = REQ_REJECT;

    /* Match the configuration from the Enter USB DO against the UFP VDO1. */
    if (gl_vdm_id_vdo_cnt[port] > PRODUCT_TYPE_VDO_1_IDX)
    {
        if ((eudo.enterusb_vdo.usbMode == CCG_USB_MODE_USB4) && (ufp_vdo.ufp_vdo_1.devCap & DEV_CAP_USB_4_0))
        {
            app_get_resp_buf(port)->reqStatus = REQ_ACCEPT;
            usb4_update_data_status (port, eudo, 0x00);
        }
    }

    app_resp_handler(port, app_get_resp_buf(port));
}
#endif /* CCG_USB4_SUPPORT_ENABLE */

/* End of File */
