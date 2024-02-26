/******************************************************************************
* File Name: vdm.h
*
* Description: This header file defines data structures and function prototypes
*              for the Vendor Defined Message (VDM) handler as part of the PMG1
*              MCU USB-PD DRP Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef _VDM_H_
#define _VDM_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/

#include <cy_pdstack_common.h>

#define VDO_START_IDX                   (1u)

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/

/**
 * @brief Store the VDM data from the configuration table.
 *
 * This function retrieves the VDM data (for CCG as UFP) that is stored in
 * the configuration table and stores it in the run-time data structures.
 *
 * @param port USB-PD port for which the data is to be stored.
 *
 * @return None.
 */
void vdm_data_init (cy_stc_pdstack_context_t * context);

/**
 * @brief This function allows the VDM data for CCG to be changed.
 *
 * This function allows the user to change the VDM responses that CCG sends
 * for D_ID, D_SVID and D_MODE requests. The default responses are taken
 * from the configuration table. This function allows the user to change
 * the response data. The caller is responsible to ensure that the responses
 * are not changed while CCG is already in contract as a UFP.
 *
 * @param port PD port for which responses are to be changed.
 * @param id_vdo_cnt Number of VDOs in the D_ID response.
 * @param id_vdo_p Pointer to the actual D_ID response in memory.
 * @param svid_vdo_cnt Number of VDOs in the D_SVID response.
 *        Should be less than 8.
 * @param svid_vdo_p Pointer to the actual D_SVID response in memory.
 * @param mode_resp_len Total length of mode response. This includes
 *        the D_MODE responses for each supported SVID, along with the
 *        corresponding header fields.
 * @param mode_resp_p Pointer to all of the mode responses in memory.
 *
 * @return None
 */
void vdm_update_data(cy_stc_pdstack_context_t * context, uint8_t id_vdo_cnt, uint8_t *id_vdo_p,
        uint8_t svid_vdo_cnt, uint8_t *svid_vdo_p, uint16_t mode_resp_len,
        uint8_t *mode_resp_p);

/**
 * @brief This function is responsible for analysing and processing received VDM.
 * This function also makes a decision about necessity of response to the received
 * VDM.
 *
 * @param port Port index the function is performed for.
 * @param vdm Pointer to pd packet which contains received VDM.
 * @param vdm_resp_handler VDM handler callback function.
 *
 * @return None
 */
void eval_vdm(cy_stc_pdstack_context_t * context, const cy_stc_pdstack_pd_packet_t *vdm,
        cy_pdstack_vdm_resp_cbk_t vdm_resp_handler);

/**
 * @brief Function to evaluate an Enter_USB request and report whether it should be
 * accepted or rejected.
 *
 * @param port Port index the function is performed for.
 * @param eudo Pointer to the Enter_USB packet.
 * @param app_resp_handler Response callback through which the response is passed to the PD stack.
 * @return None
 */
void eval_enter_usb(cy_stc_pdstack_context_t * context, const cy_stc_pdstack_pd_packet_t *eudo, cy_pdstack_app_resp_cbk_t app_resp_handler);

/** @cond DOXYGEN_HIDE */

/**
 * @brief This function is responsible for getting Discover Mode info from config table.
 *
 * @param port Port index the function is performed for.
 * @param svid SVID which the infofmation is searching for.
 * @param temp_p Temporary pointer to the pointer of PD data object.
 * @param no_of_vdo Pointer to the variable which contains number of VDOs 
 *        in Disc MODE response.
 *
 * @return Returns true if config table contains Disc MODE info for input SVID.
 *         Else returns false.
 */
bool get_modes_vdo_info(cy_stc_pdstack_context_t * context, uint16_t svid, cy_pd_pd_do_t **temp_p,
        uint8_t *no_of_vdo);

/**
 * @brief Update the Discover SVID response sent by the device. This method is provided so that the list
 * of supported SVIDs can be changed dynamically without having to change all of the VDO configuration.
 *
 * @param port PD port to be updated.
 * @param svid_vdo_cnt Number of VDOs in the D_SVID response.
 *        Should be less than 8.
 * @param svid_vdo_p Pointer to the actual D_SVID response in memory.
 * @return None
 */
void vdm_update_svid_resp(cy_stc_pdstack_context_t * context, uint8_t svid_vdo_cnt, uint8_t *svid_vdo_p);

/**
 * @brief Returns Discover ID response of CCG.
 *
 * @param port PD port index.
 *
 * @return Pointer to Discover ID buffer
 */
cy_pd_pd_do_t* get_gl_vdm_id(cy_stc_pdstack_context_t * context);
/** @endcond */

#endif /* _VDM_H_ */

/* End of File */

