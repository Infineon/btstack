/*
 * Copyright 2016-2024, Cypress Semiconductor Corporation or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 * Bluetooth Management (BTM) Application Programming Interface
 *
 * The BTM consists of several management entities:
 *      1. Device Control - controls the local device
 *      2. Device Discovery - manages inquiries, discover database
 *      3. ACL Channels - manages ACL connections (BR/EDR and LE)
 *      4. SCO Channels - manages SCO connections
 *      5. Security - manages all security functionality
 *      6. Power Management - manages park, sniff, hold, etc.
 *
 * AIROC Bluetooth Framework Functions
 */

#ifndef __WICED_BT_STACK_H__
#define __WICED_BT_STACK_H__

#include "wiced_bt_cfg.h"
#include "wiced_bt_dev.h"

/******************************************************
 *               Function Declarations
 ******************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/**
 *
 * @addtogroup  wiced_bt_init_functions       Bluetooth Stack Initialization & Configuration
 * This section describes API and Data structures required to initialize and configure the BTSTACK and various submodules.
 *
 * @{
 */
/****************************************************************************/

/**
 *
 * This API initializes the stack based on the configuration in \b p_bt_cfg_settings and allocates memory as per the configuration. It also initializes platform interfaces and the controller.
 * It registers the application callback for notification of Bluetooth events issues by the stack.
 * Upon successfully Initialization of Bluetooth controller and stack, application receives #BTM_ENABLED_EVT with the event data in  #wiced_bt_dev_enabled_t.
 *
 * @warning Controller FW (patch) download is the part of #wiced_bt_stack_init , if \ref wiced_bt_stack_platform_t.pf_patch_download fails, application may not receive #BTM_ENABLED_EVT.
 *
 * @param[in] p_bt_management_cback     : Callback for receiving Bluetooth management events(#wiced_bt_management_evt_e)
 * @param[in] p_bt_cfg_settings         : Bluetooth stack configuration #wiced_bt_cfg_settings_t
 *
 * @return   <b> WICED_BT_SUCCESS </b> : On success \n
 *           <b> WICED_ERROR  </b> : If an error occurred
 * @note This API must be implemented by platform porting layer. \n
 * This API must be called before using any Bluetooth functionality. \n
 * If \b p_bt_cfg_settings is null, stack uses default parameters defined in <b> wiced_bt_cfg.h </b> \n
 *     However, it is strongly recommended that applications define the configuration to appropriate values based on the application use case.
 */
wiced_result_t wiced_bt_stack_init(wiced_bt_management_cback_t *p_bt_management_cback,
                                    const wiced_bt_cfg_settings_t *p_bt_cfg_settings);

/**
 * This is a blocking call (returns after all de-initialization procedures are complete)
 * It is recommended that the application disconnect any outstanding connections prior to invoking this function.
 *
 * @return  <b>  WICED_BT_SUCCESS </b> : On success; \n
 *          <b>  WICED_BT_ERROR   </b> : If an error occurred
 */
wiced_result_t wiced_bt_stack_deinit( void );

/**
 * Initialize SMP(Security Manager).
 * This API enables the Security Manager module in the stack to accept incoming pairing requests
 *@note calling any SMP API in the application without calling #wiced_bt_smp_module_init will result in error or undefined behavior.
 *
 * @result #wiced_result_t \n
 *  <b> WICED_BT_SUCCESS </b>: If successful \n
 *  <b> WICED_BT_ERROR </b>: If an error occurred

 */

wiced_result_t wiced_bt_smp_module_init(void);

/**
* This API enables the Host based address resolution.
* If Host based resolution is enabled then advertisment packet with Resolvable private address is resolved by host.
* @note This should be invoked in the #BTM_ENABLED_EVT event.
*
* @result #wiced_result_t \n
*  <b> WICED_BT_SUCCESS </b>: If successful \n
*  <b> WICED_NO_MEMORY </b>: If no memory/buffers available to create the Resolving list
*/
wiced_result_t wiced_bt_init_resolution(void);

/**@} wiced_bt_init_functions */
/**@} wicedbt_Framework */


#ifdef __cplusplus
}
#endif

#endif //__WICED_BT_STACK_H__
