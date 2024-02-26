/******************************************************************************
* @file pmg1_version.h
*
* @brief This file defines the base firmware stack version for PMG1.
*
*******************************************************************************
* $ Copyright 2022-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef _PMG1_VERSION_H_
#define _PMG1_VERSION_H_

/**
   @brief Major version of the firmware stack.
 */
#define FW_MAJOR_VERSION                                (1)

/**
   @brief Minor version of the firmware stack.
 */
#define FW_MINOR_VERSION                                (0)

/**
   @brief Patch version of the firmware stack.
 */
#define FW_PATCH_VERSION                                (0)

/**
   @brief Build number of the firmware stack. Base Build number: 0000
          When the value reaches 9999 this shall be reset to 0. 
          As we are reporting this value as part of DMC bcdDevice.
 */
#define FW_BUILD_NUMBER                                 (12)

/**
 *  @brief Composite firmware stack version value.
 *
 *  Composite firmware stack version value. This is a 4 byte value with the following format:
 *  Bytes 1-0: Build number
 *  Byte    2: Patch version
 *  Byte 3 (Bits 0:3): Minor Version
 *  Byte 3 (Bits 4:7): Major Version
 */
#define FW_BASE_VERSION                                         \
    ((FW_MAJOR_VERSION << 28) | (FW_MINOR_VERSION << 24) |      \
     (FW_PATCH_VERSION << 16) | (FW_BUILD_NUMBER))

#endif /* _PMG1_VERSION_H_ */

/* End of file */

