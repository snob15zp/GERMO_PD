/******************************************************************************
* File Name: pdo.h
*
* Description: This header file defines data structures and function prototypes
*              for PDO evaluation and handling.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef _PDO_H_
#define _PDO_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/

#include "cy_pdstack_common.h"

/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/

#define APP_PPS_SNK_CONTRACT_PERIOD             (9000u)
/**< Period after which a PPS Sink repeats PD contract attempts. This should be faster than once in 10 seconds. */

#define APP_PPS_SNK_CONTRACT_RETRY_PERIOD       (5u)
/**< Period after which a failed PPS sink re-contract attempt will be retried. */

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/

/**
 * @brief This function is called by the PD stack to allow the application
 * logic to evaluate the Source Capabilities received from the port partner
 * and generate the desired request. The request object is expected to be
 * passed back to the stack through the app_resp_handler() callback.
 *
 * The default implementation of this function matches each of the received
 * source PDOs against the active sink capabilities; and then selects the
 * source PDO that can deliver the maximum power to the system as a sink.
 *
 * @warning On the CCG6 device, the eval_src_cap function is executed from
 * ROM and hence changes in this function will not affect the policy engine
 * behavior. The app_update_rdo() function should be used to update the request
 * object in this case.
 *
 * @param port Port index the function is performed for.
 * @param srcCap Pointer to PD packet which contains source capabilities.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_src_cap(cy_stc_pdstack_context_t* context, const cy_stc_pdstack_pd_packet_t* srcCap, cy_pdstack_app_resp_cbk_t app_resp_handler) ;

/**
 * @brief This function is called by the PD stack to allow the application
 * to evaluate a power request data object received from the port partner and
 * decide whether it should be satisfied. The response to the request should
 * be passed back to the stack through the app_resp_handler() callback.
 *
 * @warning On the CCG6 device, the eval_rdo function is executed from ROM
 * and hence changes in this function will not affect the policy engine
 * behavior. The application is expected to update the source capabilities
 * registered with the PD stack based on the current system status.
 *
 * @param port Port index the function is performed for.
 * @param rdo The request data object received.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_rdo(cy_stc_pdstack_context_t* context, cy_pd_pd_do_t rdo, cy_pdstack_app_resp_cbk_t app_resp_handler) ;

/**
 * @brief This function is only applicable in the case of the CCG6 device,
 * and can be used by the application logic to modify the RDO generated by
 * the ROM-ed version of the eval_src_cap function.
 *
 * @param port Port index the function is performed for.
 * @param srcCap Pointer to PD packet which contains source capabilities.
 * @param appResp Response containing the updated RDO.
 *
 * @return None
 */
void app_update_rdo (cy_stc_pdstack_context_t* context, const cy_stc_pdstack_pd_packet_t* srcCap, cy_pdstack_app_resp_cbk_t *appResp);


#endif /* _PDO_H_ */

/* End of File */

