/***************************************************************************//**
* \file cy_pdstack_rom.h
* \version 3.0
*
* Provides User ROM Access.
*
********************************************************************************
* \copyright
* Copyright 2021-2022, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef _CY_PDSTACK_ROM_H_
#define _CY_PDSTACK_ROM_H_

/** \cond DOXYGEN_HIDE */
#if defined PMG1S3_SROM_CODE

/**
 * @brief Structure that encapsulates stack configuration constants so that they
 * can be updated while the stack is running from ROM.
 */
typedef struct {

    int8_t vsafe_5v_snk_turn_on_margin;
    int8_t vsafe_5v_src_turn_on_margin;
    uint16_t  max_vbus_off_delay;        /**< Time allowed for VBus turn OFF. */
    uint16_t  drp_try_timeout;           /**< tTryTimeout period in ms. */
    uint16_t  snk_detach_vbus_poll_cnt;  /**< Number of times VBus should be checked to detect a detach. */
    uint16_t  pd_phy_backoff_delay;      /**< Backoff delay in ms used in case of collision. */
    uint16_t  pd_hr_send_duration;       /**< Time for which protocol layer tries to send Hard Reset. */
    uint16_t  cc_debounce_period;        /**< CC debounce period in ms. */
    uint16_t  pd_debounce_period;        /**< PD debounce period for Rp change detection. */
    uint16_t  rd_debounce_period;        /**< Rd debounce period for detach detection. */
    uint16_t  attachwait_entry_delay;    /**< Delay between AttachWait entry and detach detection. */
    uint16_t  src_det_debounce_period;   /**< CC debounce period to detect Rd removal. */
    uint16_t  pd3_rp_debounce_period;    /**< Time used to detect Rp change while in PD 3.0 contract. */
    uint16_t  err_recov_delay;           /**< Error recovery time period. */
    uint16_t  drp_try_timer_period;      /**< Type-C Try DRP timer period in ms. */
    uint16_t  vbus_discharge_period;
    uint16_t  snk_try_timer_period;
    uint16_t  typec_activity_period;
    uint16_t  snk_vbus_discharge_period;
    uint16_t  vbus_turn_on_timer_period;
    uint16_t  src_disconnect_wait_period;
    uint16_t  good_crc_tx_timer_period;
    uint16_t  cable_delay_timer_period;
    uint16_t  soln_status_check_period;

} pd_stack_compile_const_t;


typedef struct
{
    cy_en_pdstack_status_t (*Cy_PdStack_Prot_Init)(cy_stc_pdstack_context_t *ptrPdStackContext, cy_pdstack_pd_cbk_t cbk);
    cy_en_pdstack_status_t (*Cy_PdStack_Prot_Start)(
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_Stop)(
            cy_stc_pdstack_context_t *ptrPdStackContext);

    bool (*Cy_PdStack_Prot_IsBusy)(
            cy_stc_pdstack_context_t *ptrPdStackContext);

    void (*Cy_PdStack_Prot_RefreshRoles) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_ResetAll) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_Reset) (
            cy_stc_pdstack_context_t *ptrPdStackContext,
            cy_en_pd_sop_t sop);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_ResetRx) (
            cy_stc_pdstack_context_t *ptrPdStackContext,
            cy_en_pd_sop_t sop);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_SendCtrlMsg)(
            cy_stc_pdstack_context_t *ptrPdStackContext,
            cy_en_pd_sop_t sop,
            cy_en_pd_ctrl_msg_t msgType);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_SendDataMsg) (
            cy_stc_pdstack_context_t *ptrPdStackContext,
            cy_en_pd_sop_t sop,
            cy_en_pdstack_data_msg_t msgType,
            uint8_t count,
            cy_pd_pd_do_t *ptrDObj);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_SendExtdMsg) (
            cy_stc_pdstack_context_t *ptrPdStackContext,
            cy_en_pd_sop_t sop,
            cy_en_pdstack_extd_msg_t msgType,
            cy_pdstack_extd_hdr_t extHdr,
            uint8_t* ptrDObj);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_SendHardReset) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_SendCableReset) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_EnBistCm2) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_DisBistCm2) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_EnBistTestData) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_DisBistTestData) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_SetAvoidRetry) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_FrsRxEnable) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_FrsRxDisable) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_FrsTxEnable) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    cy_en_pdstack_status_t (*Cy_PdStack_Prot_FrsTxDisable) (
            cy_stc_pdstack_context_t *ptrPdStackContext);


    /* PD Stack utilities */

    uint8_t (*mem_calculate_byte_checksum)(uint8_t *ptr, uint32_t  size);
    uint16_t (*mem_calculate_word_checksum)(uint16_t *ptr, uint32_t  size);
    uint32_t (*mem_calculate_dword_checksum)(uint32_t *ptr, uint32_t  size);
    uint16_t (*crc16)(uint16_t crc, uint8_t data);
    void (*mem_copy_word)(uint32_t* dest, const uint32_t* source, uint32_t size);
    void (*mem_copy) (uint8_t* dest, const uint8_t* source, uint32_t size);
    void (*mem_set) (uint8_t* dest, uint8_t c, uint32_t size);
    uint32_t (*div_round_up)(uint32_t x, uint32_t y);
    int32_t (*apply_threshold)(int32_t val, int8_t percentage);
    void (*event_group_set_event)(uint32_t *event_map, uint8_t event_sel);
    void (*event_group_set_events_by_val)(uint32_t *event_map, uint32_t event_sel);
    void (*event_group_clear_event)(uint32_t *event_map, uint8_t event_sel);
    void (*event_group_clear_events_by_val)(uint32_t *event_map, uint32_t event_sel);
    uint8_t (*event_group_get_event)(volatile uint32_t *event_map, bool clr_stat);

    /* Crypto functions */
#if defined PMG1S3_CRYPTO
    mbedtls_sha256_fptr mbedtls_sha256;
    mbedtls_sha256_init_fptr mbedtls_sha256_init;
    mbedtls_sha256_free_fptr mbedtls_sha256_free;
    mbedtls_sha256_starts_fptr mbedtls_sha256_starts;
    mbedtls_sha256_update_fptr mbedtls_sha256_update;
    mbedtls_sha256_finish_fptr mbedtls_sha256_finish;
    verify_signature_fptr verify_signature;
    crypto_init_globals_fptr crypto_init_globals;
#else
    uint32_t reserved[8];
#endif

    void (*Cy_PdStack_TypeC_GenEntryEvt)(cy_stc_pdstack_context_t *ptrPdStackContext, cy_en_pdstack_typec_fsm_state_t next_state);
    cy_en_pdstack_status_t (*Cy_PdStack_TypeC_Init)(cy_stc_pdstack_context_t *ptrPdStackContext);
    cy_en_pdstack_status_t (*Cy_PdStack_TypeC_Start) (cy_stc_pdstack_context_t *ptrPdStackContext);
    void (*Cy_PdStack_TypeC_DeassertRpRd)(cy_stc_pdstack_context_t *ptrPdStackContext, uint8_t cc_channel);
    cy_en_pdstack_status_t (*Cy_PdStack_TypeC_Stop) (cy_stc_pdstack_context_t *ptrPdStackContext);
    cy_en_pdstack_status_t (*Cy_PdStack_TypeC_IsBusy) (cy_stc_pdstack_context_t *ptrPdStackContext,
            bool *ptrIsBusy);

    cy_en_pdstack_status_t (*Cy_PdStack_TypeC_PrepareDeepSleep)(
            cy_stc_pdstack_context_t *ptrPdStackContext,
            bool *ptrDeepSleep);

    cy_en_pdstack_status_t (*Cy_PdStack_TypeC_Resume)(
            cy_stc_pdstack_context_t *ptrPdStackContext,
            bool *ptrResume);

    void (*Cy_PdStack_TypeC_ApplyRp)(cy_stc_pdstack_context_t *ptrPdStackContext, uint8_t cc_channel, cy_en_pd_rp_term_t rp_value);

    void (*Cy_PdStack_TypeC_AssertRp)(cy_stc_pdstack_context_t *ptrPdStackContext, uint8_t cc_channel);

    void (*Cy_PdStack_TypeC_AssertRd)(cy_stc_pdstack_context_t *ptrPdStackContext, uint8_t cc_channel);

    void (*Cy_PdStack_TypeC_FSM)(cy_stc_pdstack_context_t *ptrPdStackContext);

    void (*Cy_PdStack_TypeC_srom_vars_init) (void);

    bool (*Cy_PdStack_TypeC_IsConnectionDetected)(cy_stc_pdstack_context_t *ptrPdStackContext, cy_pd_cc_state_t state);

    /* PDO Evaluation & Handling */
    void (*eval_src_cap)(cy_stc_pdstack_context_t* context,
            const cy_stc_pdstack_pd_packet_t* src_cap,
            cy_pdstack_app_resp_cbk_t app_resp_handler);

    void (*eval_rdo)(cy_stc_pdstack_context_t* context, cy_pd_pd_do_t rdo, cy_pdstack_app_resp_cbk_t app_resp_handler);

} srom_in_cbk_t;

typedef struct
{
    cy_en_usbpd_status_t (*Cy_USBPD_TypeC_Init)(cy_stc_usbpd_context_t *context);
    cy_en_usbpd_status_t (*Cy_USBPD_SetTypeCEvtCb)(cy_stc_usbpd_context_t *context,
            void *callerContext,cy_usbpd_typec_evt_cbk_t cb);
    cy_en_usbpd_status_t (*Cy_USBPD_TypeC_Start)(cy_stc_usbpd_context_t *context);

    cy_en_usbpd_status_t (*Cy_USBPD_Phy_Init)(cy_stc_usbpd_context_t *context, cy_cb_usbpd_phy_handle_events_t phyCbk);
    bool (*Cy_USBPD_Phy_IsBusy)(cy_stc_usbpd_context_t *context);
    void (*Cy_USBPD_Phy_RefreshRoles)(cy_stc_usbpd_context_t *context);
    cy_en_usbpd_status_t (*Cy_USBPD_Phy_AbortTxMsg)(cy_stc_usbpd_context_t *context);
    bool (*Cy_USBPD_Phy_LoadMsg)(cy_stc_usbpd_context_t *context, cy_en_pd_sop_t sop, uint8_t retries,
            uint8_t dobjCount, uint32_t header, bool unchunked, uint32_t* buf);
    bool (*Cy_USBPD_Phy_SendMsg)(cy_stc_usbpd_context_t *context);
    cy_en_usbpd_status_t (*Cy_USBPD_Phy_SendReset)(cy_stc_usbpd_context_t *context, cy_en_pd_sop_t sop);
    cy_en_usbpd_status_t (*Cy_USBPD_Phy_SendBIST_Cm2)(cy_stc_usbpd_context_t *context);
    cy_en_usbpd_status_t (*Cy_USBPD_Phy_AbortBIST_Cm2)(cy_stc_usbpd_context_t *context);
    void (*Cy_USBPD_Phy_DisUnchunkedTx) (cy_stc_usbpd_context_t *context);
    cy_stc_pd_packet_extd_t *(*Cy_USBPD_Phy_GetRxPacket)(cy_stc_usbpd_context_t *context);

    bool (*Cy_USBPD_Vbus_FrsRxEnable)(cy_stc_usbpd_context_t *context);
    bool (*Cy_USBPD_Vbus_FrsRxDisable)(cy_stc_usbpd_context_t *context);
    bool (*Cy_USBPD_Vbus_FrsTxEnable)(cy_stc_usbpd_context_t *context);
    bool (*Cy_USBPD_Vbus_FrsTxDisable)(cy_stc_usbpd_context_t *context);

    bool (*cy_sw_timer_start)(cy_stc_sw_timer_t *context, void *callbackContext,
            cy_timer_id_t id, uint16_t period, cy_cb_timer_t cb);
    void (*cy_sw_timer_stop_range)(cy_stc_sw_timer_t *context,
            cy_timer_id_t start, cy_timer_id_t end);
    void (*cy_sw_timer_stop)(cy_stc_sw_timer_t *context, cy_timer_id_t id);
    bool (*cy_sw_timer_is_running) (cy_stc_sw_timer_t *context, cy_timer_id_t id);
    bool (*cy_sw_timer_range_enabled)(cy_stc_sw_timer_t *context, cy_timer_id_t low, cy_timer_id_t high);
    bool (*cy_sw_timer_start_wocb)(cy_stc_sw_timer_t *context, cy_timer_id_t id, uint16_t period);

    bool (*pd_is_msg)(const void * pkt,cy_en_pd_sop_t sop_type,
            cy_en_pdstack_pd_msg_class_t msg_class, uint32_t msg_mask,
            uint16_t length);

    uint32_t (*Cy_SysLib_EnterCriticalSection)(void);
    void (*Cy_SysLib_ExitCriticalSection)(uint32_t savedIntrStatus);

    void *(*memset)(void *str, int c, size_t n);

    void (*Cy_PdStack_Dpm_ClearTypecEvt) (
            cy_stc_pdstack_context_t *ptrPdStackContext,
            uint32_t evtMask);

    void (*Cy_PdStack_Dpm_SetTypecEvt) (
            cy_stc_pdstack_context_t *ptrPdStackContext,
            uint32_t evtMask);

    void (*Cy_PdStack_Pe_Stop)(cy_stc_pdstack_context_t *ptrPdStackContext);
    void (*Cy_PdStack_Pe_Start)(cy_stc_pdstack_context_t *ptrPdStackContext);

    void (*Cy_USBPD_TypeC_AbortAutoToggle)(cy_stc_usbpd_context_t *context);
    void (*Cy_USBPD_TypeC_DisDpSlpRp)(cy_stc_usbpd_context_t *context);
    cy_en_usbpd_status_t (*Cy_USBPD_TypeC_Stop)(cy_stc_usbpd_context_t *context);
    bool (*Cy_USBPD_TypeC_IsAutoToggleActive)(cy_stc_usbpd_context_t *context);
    uint16_t (*Cy_PdStack_Dpm_GetSinkDetachVoltage) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    int8_t (*Cy_PdStack_Dpm_GetSinkDetachMargin) (
            cy_stc_pdstack_context_t *ptrPdStackContext);

    bool (*Cy_USBPD_PrepareDeepSleep)(cy_stc_usbpd_context_t *context,
            uint16_t voltage,
            int8_t percentage);

    bool (*Cy_USBPD_Resume)(
            cy_stc_usbpd_context_t *context);

    void (*Cy_USBPD_TypeC_EnableRp)(
            cy_stc_usbpd_context_t *context,
            uint8_t channel,
            cy_en_pd_rp_term_t rpVal);

    void (*Cy_USBPD_TypeC_DisableRd)(
            cy_stc_usbpd_context_t *context,
            uint8_t channel);

    void (*Cy_USBPD_TypeC_EnableRd)(
            cy_stc_usbpd_context_t *context,
            uint8_t channel);

    void (*Cy_USBPD_TypeC_DisableRp)(
            cy_stc_usbpd_context_t *context,
            uint8_t channel);

    void (*Cy_USBPD_TypeC_ChangeRp) (
            cy_stc_usbpd_context_t *context,
            cy_en_pd_rp_term_t rp);

    void (*Cy_SysLib_DelayUs)(uint16_t microseconds);

    void (*Cy_USBPD_TypeC_CfgAutoToggle)(
            cy_stc_usbpd_context_t *context,
            bool enable);

    cy_pd_cc_state_t (*Cy_USBPD_TypeC_GetCCStatus)(
            cy_stc_usbpd_context_t *context);

    void (*Cy_USBPD_TypeC_SMRestart)(
            cy_stc_usbpd_context_t *context);

    void (*dpm_notify_app)(cy_stc_pdstack_context_t *ptrPdStackContext, cy_en_pdstack_app_evt_t evt);

    void (*Cy_USBPD_TypeC_SnkUpdateTrim)(cy_stc_usbpd_context_t *context);

    void (*Cy_USBPD_TypeC_SetPolarity)(cy_stc_usbpd_context_t *context, bool polarity);

    void (*Cy_USBPD_Phy_DisRxTx)(cy_stc_usbpd_context_t *context);

    /* Memory Allocation APIs */
    void *(*calloc) (size_t count, size_t eltsize);
    void (*free) (void *ptr);

#if defined APP_LAYER
    app_resp_t* (*app_get_resp_buf)(uint8_t port);
#else
    uint32_t reserved;
#endif /* APP_LAYER */

} srom_out_cbk_t;

typedef struct
{
    /* Type-C Manager Variables */
    void (*typec_fsm_table [CY_PDSTACK_TYPEC_FSM_MAX_STATES]) (cy_stc_pdstack_context_t *ptrPdStackContext, typec_fsm_evt_t evt);

    /* PDO variables */
    uint32_t gl_max_min_cur_pwr[NO_OF_TYPEC_PORTS];
    uint32_t gl_contract_power[NO_OF_TYPEC_PORTS];
    uint32_t gl_contract_voltage[NO_OF_TYPEC_PORTS];
    uint32_t gl_op_cur_power[NO_OF_TYPEC_PORTS];

    cy_en_pd_rp_term_t typec_dpmcmd_rp_map[3];

    uint8_t pdo_sel_algorithm;
    pd_stack_compile_const_t *config_params;

} srom_vars_t;

extern srom_out_cbk_t *glp_srom_out_cbk __attribute__((weak));
extern srom_in_cbk_t *glp_srom_in_cbk __attribute__((weak));
extern srom_vars_t *glp_srom_vars __attribute__((weak));

#define TYPEC_ATTRIBUTES __attribute__ ((section (".sromCode"))) __attribute__((used))  __attribute__((noinline))
#define PDPROT_ATTRIBUTES __attribute__ ((section (".sromCode"))) __attribute__((used))  __attribute__((noinline))
#define UTILS_ATTRIBUTES __attribute__ ((section (".sromCode"))) __attribute__((used))  __attribute__((noinline))

#define TYPEC_CALL_MAP(func_name) (glp_srom_in_cbk->func_name)
#define PDPROT_CALL_MAP(func_name) (glp_srom_in_cbk->func_name)
#define UTILS_CALL_MAP(func_name) (glp_srom_in_cbk->func_name)

#define VAR_MAP(var_name) (glp_srom_vars->var_name)
#define PDSTACK_CALL_MAP(func_name) (glp_srom_out_cbk->func_name)
#define TIMER_CALL_MAP(func_name) (glp_srom_out_cbk->func_name)
#define DRIVER_CALL_MAP(func_name) (glp_srom_out_cbk->func_name)
#define SYS_CALL_MAP(func_name) (glp_srom_out_cbk->func_name)

#else
#define TYPEC_ATTRIBUTES
#define PDPROT_ATTRIBUTES
#define UTILS_ATTRIBUTES

#define TYPEC_CALL_MAP(func_name) func_name
#define PDPROT_CALL_MAP(func_name) func_name
#define UTILS_CALL_MAP(func_name) func_name

#define VAR_MAP(var_name) (var_name)

#define PDSTACK_CALL_MAP(func_name) func_name
#define TIMER_CALL_MAP(func_name) func_name
#define DRIVER_CALL_MAP(func_name) func_name
#define SYS_CALL_MAP(func_name) func_name
#endif /* PMG1S3_SROM_CODE */
/** \endcond */

#endif /* _CY_PDSTACK_ROM_H_ */

/* [] END OF FILE */
