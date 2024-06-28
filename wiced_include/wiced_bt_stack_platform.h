/*
 * Copyright 2019-2024, Cypress Semiconductor Corporation or
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
 * Runtime Bluetooth configuration parameters \n
 * This file contains platform interface structure, set of function pointers and APIs which provide OS/platform resources to AIROC Bluetooth Stack.
 *
 */

#ifndef __WICED_BT_STACK_PLATFORM_H__
#define __WICED_BT_STACK_PLATFORM_H__


#include <stdarg.h>
#include "wiced_bt_types.h"
#include "wiced_data_types.h"
#include "wiced_bt_cfg.h"
#include "wiced_bt_dev.h"

/** AIROC Bluetooth Stack Platform Structure. \n
* This structure contains a set of function pointers and platform settings for tracing, which are to be set by the platform poring layer. \n
* Interfaces like memory, timer and locking mechanism for multi-threaded apps are supplied by the porting layer.
*
*/
typedef struct
{
    /**
     * Exception callback
     */
    pf_wiced_exception pf_exception;

    /**
     * Platform function to allocate memory
     *
     * Called by stack code to allocate memory from the OS/Platform.
     * Implementing function is expected to return memory allocated from
     * the OS/Platform
     *
     * @param[in] size    : Size of memory to be allocated
     *
     * @return : Pointer to allocated memory
     */
    void * (*pf_os_malloc)(uint32_t size);

    /**
     * Platform memory free
     *
     * Called by stack code to free memory back to the OS/Platform.
     * Implementing function is expected to free the memory allocated
     * using pf_os_malloc (refer #pf_os_malloc ) call from the OS/Platform
     *
     * @param[in] p_mem    : Ptr to memory to be freed
     *
     * @return : None
     */
    void   (*pf_os_free)(void* p_mem);

    /**
     * Platform function to get tick count
     *
     * Called by stack timer code to get the free running 64 bit tick count
     *
     * @param[in] None
     *
     * @return : 64 bit current tick count
     */
    uint64_t (*pf_get_tick_count_64)(void);

    /**
     * Platform function to set the next timeout
     *
     * Called by stack timer code set the next timeout
     *
     * @param[in] abs_tick_count : 64 bit tick count instant at which the timeout has to occur
     *
     * @return : void
     */
    void   (*pf_set_next_timeout)(uint64_t  abs_tick_count);

    /** Stack lock */
    wiced_bt_lock_t stack_lock;

    /**
     * Platform function to get ACL buffer to send to lower
     *
     * Called by stack to get a buffer to fill in the data to be sent to 'transport' (LE or BR/EDR)
     * of 'size'
     *
     * @param[in] transport : Transport on which the buffer is to be sent
     * @param[in] size      : Size of the buffer
     *
     * @return : Pointer to buffer which will be filled with data
     */
    uint8_t       *(*pf_get_acl_to_lower_buffer)(wiced_bt_transport_t transport, uint32_t size);

    /**
     * Platform function to write ACL buffer to lower
     *
     * Called by stack to send the buffer allocated using pf_get_acl_to_lower_buffer
     * after filling it with the data to send.
     *
     * @param[in] transport : Transport on which the buffer is to be sent
     * @param[in] p_data    : Pointer received using pf_get_acl_to_lower_buffer
     * @param[in] len       : Length of data at p_data
     *
     * @return : wiced_result_t
     */
    wiced_result_t (*pf_write_acl_to_lower)(wiced_bt_transport_t transport, uint8_t* p_data, uint16_t len);

    /**
     * Platform function to write ISO buffer to lower
     *
     * Called by stack to send the buffer allocated using pf_get_acl_to_lower_buffer
     * after filling it with the data to send.
     *
     * @param[in] p_data    : Pointer received using pf_get_acl_to_lower_buffer
     * @param[in] len       : Length of data at p_data
     *
     * @return : wiced_result_t
     */
    wiced_result_t (*pf_write_iso_to_lower)(uint8_t* p_data, uint16_t len);

    /**
     * Platform function to write CMD buffer to lower
     *
     * Called by stack to send HCI CMD buffer to lower
     *
     * @param[in] p_cmd   : Pointer to HCI CMD data
     * @param[in] cmd_len : Length of data at p_cmd
     *
     * @return : wiced_result_t
     */
    wiced_result_t (*pf_write_cmd_to_lower)(uint8_t * p_cmd, uint16_t cmd_len);

     /**
     * Platform function to get SCO buffer to send to lower
     *
     * Called by stack to get a SCO buffer to fill in the data to be sent to HCI
     * of 'size'
     *
     * @param[in] size      : Size of the buffer
     *
     * @return : Pointer to buffer which will be filled with data
     */
    uint8_t       *(*pf_get_sco_to_lower_buffer)(uint32_t size);

    /**
     * Platform function to write SCO buffer to lower
     *
     * Called to send SCO CMD buffer to lower
     *
     * @param[in] p_sco_data   : Pointer to SCO data
     * @param[in] len      : Length of data at p_data
     *
     * @return : wiced_result_t
     */
    wiced_result_t (*pf_write_sco_to_lower)(uint8_t* p_sco_data, uint8_t len);

    /**
     * Callback function to trace HCI messages
     *
     * Called by stack to allow application to trace the HCI messages.
     * Application/Porting code is expected to treat received data as read only, and make a
     * copy of the data to reference it outside of the callback
     *
     * @param[in] type   : HCI event data type
     * @param[in] len    : Length of data at p_data
     * @param[in] p_data : Pointer to data
     *
     * @return : void
     */
    void (*pf_hci_trace_cback_t)(wiced_bt_hci_trace_type_t type, uint16_t len, uint8_t* p_data);

    /**
     * Callback function to dump out trace messages
     * This interface function can be NULL if no debug tracing is supported
     *
     * Called by stack to allow application to write debug trace messages
     *
     * @param[in] p_trace_buf   : Pointer to the trace buffer
     * @param[in] trace_buf_len : Length of the trace buffer
     * @param[in] trace_type    : Type of trace message
     *
     * @return : void
     */
    void (*pf_debug_trace)(char *p_trace_buf, int trace_buf_len, wiced_bt_trace_type_t trace_type);

    /** trace_buffer_len : Trace buffer len */
    int   trace_buffer_len;
    /**
     * trace_buffer     : Pointer to the trace buffer
     * Applications can set this to NULL to disable traces
     */
    char* trace_buffer;


    /**
     * Used for additional controller initialization by the porting layer to be performed
     * after the HCI reset. Can be set to NULL if no additional initialization required
     */
    void (*pf_patch_download)(void);

    /**
     *set is_legacy_bless_controller to 1 for only BLESS controllers.
     *This is used while sending BLESS vendor specific commands.
     */
    uint32_t is_legacy_bless_controller : 1;
} wiced_bt_stack_platform_t;

/**
* Function prototype for the post Stack Init Callback.
*/
typedef void (*wiced_bt_internal_post_stack_init_cb)(void);

/**
* Function prototype for the HCI event monitor function that the application may suppply.
* The application MUST return TRUE if the it handled the event and does not want the stack to
* process the event. \n
* If the application returns FALSE, the stack will process the event.
*/
typedef wiced_bool_t (*wiced_bt_internal_stack_evt_handler_cb)(uint8_t* p_event);


 /**
 * @addtogroup  wiced_bt_platform_group Bluetooth Stack Platform Interface
 *
 * Interface between Stack and platform.
 * It contains APIs which are used for configuring and initializing the AIROC Bluetooth stack. \n
 * The APIs should be called in the order mentioned below. \n
 * 1. #wiced_bt_stack_platform_initialize() \n
 * 2. #wiced_bt_set_stack_config() \n
 * 3. #wiced_bt_stack_init_internal() \n
 * 4. #wiced_bt_continue_reset() \n
 * Please check API documentation for more details. Depending on the HCI platform interface, the calls may be made asynchronously. \n
 * This section also lists the APIs which are used for processing data and events received from Controller.
 *
 * @{
 */
/**
 * API to initialize the platform interfaces, by providing porting functions specific to
 * the underlying platform.
 * This API is called from #wiced_bt_stack_init()
 *
 * @param[in] platform_interfaces  : Pointer to platform interface structure #wiced_bt_stack_platform_t \n
 *                                   Implementation of callback functions, which are members of #wiced_bt_stack_platform_t, may differ from platform to platform
 *
 * @return   #wiced_result_t \n
 *           <b> WICED_BT_SUCCESS </b> : on success \n
 *           <b> WICED_BT_ERROR  </b>  : if an error occurred
 */
extern wiced_result_t wiced_bt_stack_platform_initialize(wiced_bt_stack_platform_t * platform_interfaces);

/**
* API to set AIROC Bluetooth stack configuration. This API is invoked by porting layer to configure AIROC Bluetooth Stack.
* This API is called from #wiced_bt_stack_init()
*
* @param[in] p_bt_new_cfg_settings : Pointer to stack configuration settings
*
* @return   0 if there is any error in the configuration, otherwise the dynamic
*           memory size requirement of the stack for the given \p p_bt_new_cfg_settings configuration.
*
*/
extern uint32_t wiced_bt_set_stack_config(const wiced_bt_cfg_settings_t *p_bt_new_cfg_settings);

/**
* API for doing internal stack initialization.
* Once HCI platform interface to Controller is initialized, porting layer calls this API to start with AIROC Bluetooth Stack initialization.
*
* @param[in] mgmt_cback : Application Bluetooth Management callback
* @param[in] post_stack_cb : Internal post stack init callback
* @param[in] evt_handler_cb : Internal stack event handler
*
* @return    void
*
*/
void wiced_bt_stack_init_internal(wiced_bt_management_cback_t mgmt_cback,
                                  wiced_bt_internal_post_stack_init_cb post_stack_cb,
                                  wiced_bt_internal_stack_evt_handler_cb evt_handler_cb);

/**
 * This API is called by porting layer to complete/continue the reset process.
 * It is called after downloading firmware patches to the Controller.
 *
 * @return    void
 */
extern void wiced_bt_continue_reset(void);

/**
 * API to process ACL data.
 * This API is called by porting layer to process incoming ACL data received from the
 * remote bluetooth device
 *
 * @param[in] pData  : Pointer to the ACL data to be processed
 * @param[in] length : Length of the ACL data buffer
 *
 * @return    void
 */
extern void wiced_bt_process_acl_data(uint8_t* pData, uint32_t length);

/**
 * API to process HCI events.
 * This API is called by porting layer to process incoming HCI events from the local
 * bluetooth controller
 *
 * @param[in] pData  : Pointer to the HCI Events to be processed
 * @param[in] length : Length of the event buffer
 *
 * @return    void
 */
extern void wiced_bt_process_hci_events(uint8_t* pData, uint32_t length);

/**
 * API to process SCO data.
 * This API is called by porting layer to process incoming SCO data received from the
 * remote bluetooth device
 *
 * @param[in] pData  : Pointer to the SCO data to be processed
 * @param[in] length : Length of the SCO data buffer
 *
 * @return    void
 */

extern void wiced_bt_process_sco_data(uint8_t *pData, uint32_t length);

/**
 * API to process ISOC data.
 * This API is called by porting layer to process incoming ISOC data received from the
 * remote bluetooth device
 *
 * @param[in] pData  : Pointer to the ISOC data to be processed
 * @param[in] length : Length of the ISOC data buffer
 *
 * @return    void
 */
extern void wiced_bt_process_isoc_data(uint8_t *pData, uint32_t length);

 /**
 * This API is called by porting layer on expiry of the timer to process pending timers
 *
 * @return    void
 */
extern void wiced_bt_process_timer(void);

/**
 * This API is called by porting layer to restart sending ACL data to the Controller through lower layer transport driver.
 * @note This API is expected to be invoked by porting layer, to restart
 *     transfers from stack to Controller. \n
 *     The lower transport layer is expected to have space for atleast one complete ACL buffer. \n
 *     Typically used in cases where the lower transport has lesser number of buffers than allowed by the Controller.
 */
extern void wiced_bt_stack_indicate_lower_tx_complete(void);

/**
 * This function blocks until all de-initialisation procedures are complete.
 * It is recommended that the application disconnect any outstanding connections prior to invoking this function.
 *
 * @return    void
 */
void wiced_bt_stack_shutdown(void);

/**@} wiced_bt_platform_group */

#endif //__WICED_BT_STACK_PLATFORM_H__
