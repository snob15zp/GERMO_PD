/**
 * @file app_version.h
 *
 * @brief @{Version definition for the PMG1 firmware application. This version
 * information follows a Cypress defined format that identifies the type
 * of application along with the version information.@}
 *
 */

#ifndef _APP_VERSION_H_
#define _APP_VERSION_H_
    

/******************************************************************************
 * Constant definitions.
 *****************************************************************************/

#define APP_TYPE_NOTEBOOK               (0x6d63)        /* "mc" */

#define APP_TYPE_STRING                 (APP_TYPE_NOTEBOOK)
#define APP_EXT_CIR_NUM                 (0x00u)
#define APP_MAJOR_VERSION               (0x00u)
#define APP_MINOR_VERSION               (0x00u)

/*
   The version format is as follows:
   Bytes 1:0 identify the type of CCG application. 0x6e62 specifies that this is a notebook port controller.
   Byte    2 identifies the hardware design version.
   Byte    3 identifies the major and minor version of the firmware.
 */
#define APP_VERSION                                             \
    (((uint32_t)APP_TYPE_STRING) | ((uint32_t)APP_EXT_CIR_NUM << 16) |              \
     ((uint32_t)APP_MINOR_VERSION << 24) | ((uint32_t)APP_MAJOR_VERSION << 28))

#endif /* _APP_VERSION_H_ */

/* [] END OF FILE */

