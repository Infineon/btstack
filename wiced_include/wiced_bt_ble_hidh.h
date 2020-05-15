/*
 *  $ Copyright Cypress Semiconductor $
 */

/** @file
 *
 * WICED Bluetooth Low Energy (BLE) HID Host (HIDH) Functions
 *
 */

#pragma once

#include "wiced.h"
#include "wiced_bt_dev.h"
#include "wiced_bt_gatt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup  wiced_bt_ble_hidh_api_functions   HID Host Role (HIDH) over BLE
 * @ingroup     wiced_bt_hid
 *
 * The Human Interface Device Host Role (HIDH) BLE library of the WICED SDK provide a simple method
 * for an application to integrate HIDH functionality.
 * This library is typically used to connect to BLE HID Devices such as Bluetooth (classic) Mice,
 * Keyboards or Remote Control.
 *
 * @{
*/

/**
 * @brief BLE HIDH Maximum HID Devices.
 */
#define WICED_BT_BLE_HIDH_DEV_MAX                   3

/**
 * @brief BLE HIDH Maximum Characteristics for an HID Devices.
 */
#define WICED_BT_BLE_HIDH_DEV_CHAR_MAX              14

/**
 * @brief BLE HIDH Maximum Reports of an HID Devices.
 */
#define WICED_BT_BLE_HIDH_REPORT_DESC_MAX           10

/**
 * @brief BLE HIDH Handle Offset.
 *  We use an offset to convert ConnectionId to BLE-HIDH_Handle (to do distinguish BR-HID handles)
 */
#define WICED_BT_BLE_HIDH_HANDLE_OFFSET             20

/**
 * @brief BLE HIDH WakeUp Pattern Maximum Length.
 */
#define WICED_BT_BLE_HIDH_WAKEUP_PATTERN_LEN_MAX    10

/**
 * @brief BLE HIDH WakeUp Pattern Maximum Number.
 */
#define WICED_BT_BLE_HIDH_WAKEUP_PATTERN_NB_MAX     1

/**
 * @brief BLE HIDH Event Filter Maximum Number.
 */
#define WICED_BT_BLE_HIDH_EVENT_FILTER_NB_MAX       1

/**
 * @brief HIDH Events.
 *
 * BLE HID Host event received by the BLE HID Host callback (see wiced_bt_ble_hidh_cback_t)
 */
typedef enum
{
    WICED_BT_BLE_HIDH_OPEN_EVT,             /**< Connection Open. */
    WICED_BT_BLE_HIDH_CLOSE_EVT,            /**< Connection Closed. */
    WICED_BT_BLE_HIDH_DESCRIPTOR_EVT,       /**< HID Descriptor received. */
    WICED_BT_BLE_HIDH_GATT_CACHE_EVT,       /**< BLE HID GATT Cache. */
    WICED_BT_BLE_HIDH_REPORT_EVT,           /**< HID Report received from peer HID Device. */
    WICED_BT_BLE_HIDH_SET_REPORT_EVT,       /**< Set HID Report confirmation. */
    WICED_BT_BLE_HIDH_GET_REPORT_EVT,       /**< Get HID Report confirmation. */
    WICED_BT_BLE_HIDH_VIRTUAL_UNPLUG_EVT,   /**< Virtual Unplug. */
    WICED_BT_BLE_HIDH_SET_PROTOCOL_EVT,     /**< HID Set Protocol confirmation. */
} wiced_bt_ble_hidh_event_t;

/**
 * @brief BLE HID Error codes.
 *
 * This enumeration contains the list of HID Error codes.
 */

typedef enum
{
    WICED_BT_BLE_HIDH_STATUS_SUCCESS = 0,       /**< Operation success */
    WICED_BT_BLE_HIDH_STATUS_ERROR,             /**< Generic internal error */
    WICED_BT_BLE_HIDH_STATUS_GATT_ERROR,        /**< Generic GATT error */
    WICED_BT_BLE_HIDH_STATUS_INVALID_PARAM,     /**< Invalid Parameter */
    WICED_BT_BLE_HIDH_STATUS_MEM_FULL,          /**< Memory full */
    WICED_BT_BLE_HIDH_STATUS_CONNECTION_FAILED, /**< Not able to establish Baseband connection */
    WICED_BT_BLE_HIDH_STATUS_UNSUPPORTED,       /**< Feature unsupported by peer device */
    WICED_BT_BLE_HIDH_STATUS_NOT_YET_IMPLEMENTED,/**< Not Yet Implemented */
} wiced_bt_ble_hidh_status_t;


/**
 * @brief BLE HID Report Type.
 *
 * This enumeration contains the list of HID Report Types.
 */
typedef enum
{
    WICED_BT_BLE_HIDH_REPORT_TYPE_RESERVED = 0,   /* reserved         */
    WICED_BT_BLE_HIDH_REPORT_TYPE_INPUT,          /* input report     */
    WICED_BT_BLE_HIDH_REPORT_TYPE_OUTPUT,         /* output report    */
    WICED_BT_BLE_HIDH_REPORT_TYPE_FEATURE         /* feature report   */
} wiced_bt_ble_hidh_report_type_t;

/**
 * @brief HID Protocol definition (Regular Report or Boot Report mode).
 *
 */
typedef enum
{
    WICED_BT_BLE_HIDH_PROTOCOL_REPORT = 0,      /**< Protocol Mode Report. */
    WICED_BT_BLE_HIDH_PROTOCOL_BOOT,            /**< Protocol Mode Boot. */
} wiced_bt_ble_hidh_protocol_t;

/**
 * @brief HID Device WakeUp Commands
 *
 */
/*  */
typedef enum
{
    WICED_BT_BLE_HIDH_WAKEUP_PATTERN_CMD_ADD = 1,
    WICED_BT_BLE_HIDH_WAKEUP_PATTERN_CMD_DEL,
    WICED_BT_BLE_HIDH_WAKEUP_PATTERN_CMD_LIST,
} wiced_bt_ble_hidh_wakeup_pattern_cmd_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_OPEN_EVT.
 *
 * This event is received:
 *  - After the wiced_bt_ble_hidh_open function is called or
 *  - When a peer device reconnects (reconnection allowed with wiced_bt_ble_hidh_add)
 *
 */
typedef struct
{
    wiced_bt_device_address_t bdaddr;
    uint16_t handle;
    wiced_bt_ble_hidh_status_t status;
} wiced_bt_ble_hidh_connected_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_CLOSE_EVT.
 *
 * This event is received:
 *  - After the wiced_bt_ble_hidh_disconnect function is called or
 *  - When a peer device disconnects
 *
 */
typedef struct
{
    uint16_t handle;
    wiced_bt_gatt_disconn_reason_t reason;
} wiced_bt_ble_hidh_disconnected_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_DESCRIPTOR_EVT.
 *
 * This event is received after call to the wiced_bt_ble_hidh_get_descriptor function.
 */
typedef struct
{
    uint16_t                    handle;     /**< HIDH Connection Handle. */
    wiced_bt_ble_hidh_status_t  status;     /**< HIDH Operation Status. */
    uint8_t                     *p_descriptor;/**< HID Descriptor of the peer HID device. */
    uint16_t                    length;     /**< Length of the HID Descriptor */
} wiced_bt_ble_hidh_descriptor_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_REPORT_EVT.
 *
 * This event is received when the peer HID Device sends a report (e.g. Button pressed/released).
 */
typedef struct
{
    uint16_t                    handle;     /**< HIDH Connection Handle. */
    uint8_t                     report_id;  /**< HID Report Id. */
    uint8_t                     *p_data;    /**< HID Report data. */
    uint16_t                    length;     /**< HID Report length. */
} wiced_bt_ble_hidh_report_t;

/**
 * @brief BLE HID GATT Characteristic.
 *
 * This structure contains the informations of a BLE HID GATT Characteristic.
 */
typedef struct
{
    uint16_t uuid16;
    uint16_t handle;
    uint16_t val_handle;
    wiced_bt_gatt_char_properties_t properties;
} wiced_bt_ble_hidh_gatt_char_t;

/**
 * @brief BLE HID GATT Report.
 *
 * This structure contains the informations of a BLE HID Report.
 */
typedef struct
{
    uint16_t handle;
    uint16_t val_handle;
    uint8_t rpt_id;
    wiced_bt_ble_hidh_report_type_t rpt_type;
} wiced_bt_ble_hidh_gatt_report_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_GATT_CACHE_EVT.
 *
 * This event is received to save the BLE HID GATT Cache information in NVRAM.
 */
typedef struct
{
    wiced_bt_device_address_t bdaddr;       /**< BLE HID Device Address. */

    uint8_t characteristics_nb;             /**< Number of Characteristics in table. */
    wiced_bt_ble_hidh_gatt_char_t characteristics[WICED_BT_BLE_HIDH_DEV_CHAR_MAX];

    uint8_t report_descs_nb;                /**< Number of Report Descriptors in table. */
    wiced_bt_ble_hidh_gatt_report_t report_descs[WICED_BT_BLE_HIDH_REPORT_DESC_MAX];
} wiced_bt_ble_hidh_gatt_cache_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_SET_REPORT_EVT.
 *
 * This event is received after call to the wiced_bt_ble_hidh_set_report function.
 */
typedef struct
{
    uint16_t                    handle;     /**< HIDH Connection Handle. */
    wiced_bt_ble_hidh_status_t  status;     /**< HIDH Operation Status. */
} wiced_bt_ble_hidh_set_report_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_GET_REPORT_EVT.
 *
 * This event is received after call to the wiced_bt_ble_hidh_get_report function.
 */
typedef struct
{
    uint16_t                    handle;     /**< HIDH Connection Handle. */
    wiced_bt_ble_hidh_status_t  status;     /**< HIDH Operation Status. */
    uint8_t                     *p_data;    /**< HID Report data. */
    uint16_t                    length;     /**< HID Report length. */
} wiced_bt_ble_hidh_get_report_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_SET_PROTOCOL_EVT.
 *
 * This event is received after call to the wiced_bt_ble_hidh_set_protocol function.
 */
typedef struct
{
    uint16_t                    handle;     /**< HIDH Connection Handle. */
    wiced_bt_ble_hidh_status_t  status;     /**< HIDH Operation Status. */
} wiced_bt_ble_hidh_set_protocol_t;

/**
 * @brief Data associated with WICED_BT_BLE_HIDH_VIRTUAL_UNPLUG_EVT.
 *
 * This event is received when the peer HID Device sends a Virtual UnPlug event.
 * Upon reception of this event, the device will be disconnected and removed from the HID host
 * Database, but the application (embedded and/or MCU) must erase all Pairing information about
 * this device.
 */
typedef struct
{
    uint16_t                    handle;     /**< HIDH Connection Handle. */
} wiced_bt_ble_hidh_virtual_unplug_t;



typedef union
{
    wiced_bt_ble_hidh_connected_t    connected;     /**< WICED_BT_BLE_HIDH_OPEN_EVT */
    wiced_bt_ble_hidh_disconnected_t disconnected;  /**< WICED_BT_BLE_HIDH_CLOSE_EVT */
    wiced_bt_ble_hidh_descriptor_t   descriptor;    /**< WICED_BT_BLE_HIDH_DESCRIPTOR_EVT */
    wiced_bt_ble_hidh_set_report_t   set_report;    /**< WICED_BT_BLE_HIDH_SET_REPORT_EVT */
    wiced_bt_ble_hidh_get_report_t   get_report;    /**< WICED_BT_BLE_HIDH_GET_REPORT_EVT */
    wiced_bt_ble_hidh_report_t       report;        /**< WICED_BT_BLE_HIDH_REPORT_EVT */
    wiced_bt_ble_hidh_gatt_cache_t   gatt_cache;    /**< WICED_BT_BLE_HIDH_GATT_CACHE_EVT */
    wiced_bt_ble_hidh_set_protocol_t set_protocol;  /**< WICED_BT_BLE_HIDH_SET_PROTOCOL_EVT */
    wiced_bt_ble_hidh_virtual_unplug_t virtual_unplug;/**< WICED_BT_BLE_HIDH_VIRTUAL_UNPLUG_EVT */
} wiced_bt_ble_hidh_event_data_t;

/**
 * HIDH Callback function type wiced_bt_ble_hidh_cback_t
 *
 *                  WICED BLE HID Host Event callback (registered with wiced_bt_ble_hidh_init)
 *
 * @param[in]       event: BLE HIDH event received
 * @param[in]       p_data : Data (pointer on union of structure) associated with the event
 *
 * @return          None
 */
typedef void wiced_bt_ble_hidh_cback_t(wiced_bt_ble_hidh_event_t event,
        wiced_bt_ble_hidh_event_data_t *p_event_data);

/**
 * HIDH Callback function type wiced_bt_ble_hidh_filter_cback_t
 *
 *                  WICED BLE HID Host Event Filter callback (registered with
 *                  wiced_bt_ble_hidh_filter_register)
 *
 * @param[in]       event: BLE HIDH event received
 * @param[in]       p_data : Data (pointer on union of structure) associated with the event
 *
 * @return          WICED_TRUE if event filtered (will not be sent to Application).
 *                  WICED_FALSE if event not filtered (will be sent to Application).
 */
typedef wiced_bool_t wiced_bt_ble_hidh_filter_cback_t(wiced_bt_ble_hidh_event_t event,
        wiced_bt_ble_hidh_event_data_t *p_event_data);

/**
 *
 * Function         wiced_bt_hidh_init
 *
 * @param[in]       p_cback   : Callback for BLE HIDH event notification
 *
 *                  This function is called for BLE HID Host Initialization.
 *                  This function must be called, once, before any other BLE HIDH functions.
 *
 * @return          None
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_init(wiced_bt_ble_hidh_cback_t *p_callback);

/*
 * wiced_bt_ble_hidh_connect
 * Application calls this function to connect a BLE HID Device
 */
/**
 * Function         wiced_bt_ble_hidh_connect
 *
 *                  Open HID Host connection to an HID Device
 *                  The first HID connection to an HID Device must always be initiated by the BLE
 *                  HID Host device.
 *                  If this function returns a successfull status, the WICED_BT_BLE_HIDH_OPEN_EVT
 *                  event will be sent once the connection will be established.
 *
 * @param[in]       bdaddr      : BdAddr of the HID Device to connect
 * @param[in]       addr_type   : BdAddr Type (Random or Public)
 *
 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if opening in progress, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_connect(wiced_bt_device_address_t bdaddr,
        wiced_bt_ble_address_type_t addr_type);

/**
 * Function         wiced_bt_ble_hidh_disconnect
 *
 *                  Disconnect BLE HID Host connection to a BLE HID Device
 *                  If this function returns a successfull status, the WICED_BT_BLE_HIDH_CLOSE_EVT
 *                  event will be sent once the connection will be established.
 *
 * @param[in]       ble_hidh_conn_handle : BLE HID connection handle
 *
 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if opening in progress, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_disconnect(uint16_t ble_hidh_conn_handle);

/**
 * Function         wiced_bt_ble_hidh_add
 *
 *                  Add an BLE HID Device (to the known HID Device list).
 *                  This function is, typically, called during application startup to allow
 *                  a peer BLE HID Device to reconnect.
 *                  When a peer BLE HID Device will reconnect, the WICED_BT_BLE_HIDH_OPEN_EVT
 *                  event will be sent to the application.
 *                  Note, that a peer device is not automatically added during the initial HID
 *                  connection. The application must explicitly Add it with this API.
 *                  During the initial connection, the library will retrieve the GATT database
 *                  containing the Attributes and Report descriptions. The Application must
 *                  save it (in NVRAM) and pass it in this API.
 *
 * @param[in]       bdaddr          : BdAddr of the HID Device to add
 * @param[in]       addr_type       : BdAddr Type (Random or Public)
 * @param[in]       p_gatt_cache    : BLE HID GATT Database
 *
 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if opening in progress, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_add(wiced_bt_device_address_t bdaddr,
        wiced_bt_ble_address_type_t addr_type, wiced_bt_ble_hidh_gatt_cache_t *p_gatt_cache);

/*
 * wiced_bt_ble_hidh_remove
 * Application calls this function to remove a BLE HID Device (to do not allow it to reconnect)
 */
/**
 * Function         wiced_bt_ble_hidh_remove
 *
 *                  Remove a BLE HID Device (to do not allow it to reconnect).
 *
 * @param[in]       bdaddr          : BdAddr of the HID Device to remove
 *
 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if opening in progress, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_remove(wiced_bt_device_address_t bdaddr);

/**
 * Function         wiced_bt_hidh_set_report
 *
 *                  Set (send) a Report to a peer BLE HID Device.
 *                  This function is called to set (send) a BLE HID Report to an HID Device.
 *                  This function can be used, for example, to control the 'Caps Lock" led of
 *                  a Bluetooth Keyboard.
 *                  Upon completion, a WICED_BT_BLE_HIDH_SET_REPORT_EVT event will be sent to the
 *                  application.
 *
 * @param[in]       handle   : Handle of the HID Device (from WICED_BT_HIDH_OPEN_EVT)
 * @param[in]       type     : Report Type (Input/Output/Feature).
 * @param[in]       report_id: The ReportId to Set.
 * @param[in]       p_data   : The Report Data (NULL if no data).
 * @param[in]       length   : The Report Data length (if any).

 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if operation is progress, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_set_report(uint16_t handle,
        wiced_bt_ble_hidh_report_type_t report_type, uint8_t report_id, uint8_t *p_data,
        uint16_t length);

/**
 * Function         wiced_bt_ble_hidh_get_report
 *
 *                  This function is called to Get (receive) an BLE HID Report from a connected
 *                  BLE HID Device.
 *                  This function can be used, for example, to read the last HID Report received.

 * @param[in]       handle   : Handle of the HID Device (from WICED_BT_BLE_HIDH_OPEN_EVT)
 * @param[in]       type     : Report Type (Input/Output/Feature).
 * @param[in]       report_id: The ReportId to Get.
 *
 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if operation is progress, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_get_report(uint16_t handle,
        wiced_bt_ble_hidh_report_type_t type, uint8_t report_id, uint16_t length);

/**
 * Function         wiced_bt_ble_hidh_set_protocol
 *
 *                  Sends Set HID Protocol to a peer HID Device.
 *                  This function is called to Change the HID Protocol of a connected HID Device.
 *
 * @param[in]       handle   : Handle of the HID Device (from WICED_BT_BLE_HIDH_OPEN_EVT)
 * @param[in]       protocol : Protocol mode (Report/Boot).
 *
 * @return          Result code (see wiced_bt_ble_hidh_status_t)
 *                  WICED_BT_BLE_HIDH_STATUS_OK if successful, otherwise error.
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_set_protocol(uint16_t handle,
        wiced_bt_ble_hidh_protocol_t protocol);

/**
 * Function         wiced_bt_ble_hidh_up
 *
 *                  Application calls this function to when a BLE connection is established
 *
 * @param[in]       p_conn_status   : BLE GATT Connection Status
 *
 * @return          None.
 *
 */
void wiced_bt_ble_hidh_up(wiced_bt_gatt_connection_status_t *p_conn_status);

/**
 * Function         wiced_bt_ble_hidh_down
 *
 *                  Application calls this function to when a BLE connection is released
 *
 * @param[in]       p_conn_status   : BLE GATT Connection Status
 *
 * @return          None.
 *
 */
void wiced_bt_ble_hidh_down(wiced_bt_gatt_connection_status_t *p_conn_status);

/**
 * Function         wiced_bt_ble_hidh_encryption_changed
 *
 *                  Application calls this function to when a the BLE Encryption Status changes
 *
 * @param[in]       p_encryption_changed   : BLE Encryption Status
 *
 * @return          None.
 *
 */
void wiced_bt_ble_hidh_encryption_changed(wiced_bt_dev_encryption_status_t *p_encryption_changed);

/**
 * Function         wiced_bt_ble_hidh_gatt_discovery_result
 *
 *                  Application calls this function when GATT_DISCOVERY_RESULT_EVT event is received
 *
 * @param[in]       p_discovery_result   : BLE GATT Discovery Result
 *
 * @return          Result code (see wiced_bt_gatt_status_t)
 *
 */
wiced_bt_gatt_status_t wiced_bt_ble_hidh_gatt_discovery_result(
        wiced_bt_gatt_discovery_result_t *p_discovery_result);

/**
 * Function         wiced_bt_ble_hidh_gatt_discovery_complete
 *
 *                  Application calls this function when GATT_DISCOVERY_CPLT_EVT event is received
 *
 * @param[in]       p_discovery_complete   : BLE GATT Discovery Complete
 *
 * @return          Result code (see wiced_bt_gatt_status_t)
 *
 */
wiced_bt_gatt_status_t wiced_bt_ble_hidh_gatt_discovery_complete(
        wiced_bt_gatt_discovery_complete_t *p_discovery_complete);

/**
 * Function         wiced_bt_ble_hidh_gatt_discovery_complete
 *
 *                  Application calls this function when GATT_OPERATION_CPLT_EVT event is received
 *
 * @param[in]       p_operation_complete   : BLE GATT Operation Complete
 *
 * @return          Result code (see wiced_bt_gatt_status_t)
 *
 */
wiced_bt_gatt_status_t wiced_bt_ble_hidh_gatt_operation_complete(
        wiced_bt_gatt_operation_complete_t *p_operation_complete);

/**
 * Function         wiced_bt_ble_hidh_filter_register
 *
 *                  BLE HIDH libraries (e.g. BLE HIDH Audio) can use this function to register
 *                  a 'Filter Callback'
 *
 * @param[in]       p_callback      : BLE HIDH Filter callback
 *
 * @return          Result code (see wiced_bt_gatt_status_t)
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_filter_register(
        wiced_bt_ble_hidh_filter_cback_t *p_callback);

/**
 * Function         wiced_bt_ble_hidh_wakeup_pattern_set
 *
 *                  Application call this function to set the WakeUp pattern.
 *                  This function must be called after the wiced_bt_ble_hidh_add function
 *
 * @param[in]       bdaddr          : BdAddr of the HID Device
 * @param[in]       command         : WakeUp command
 * @param[in]       report_id       : WakeUp ReportId to filter
 * @param[in]       p_pattern       : WakeUp ReportId's pattern data to filter
 * @param[in]       p_pattern       : WakeUp ReportId's pattern data length to filter
 *
 * @return          Result code (see wiced_bt_gatt_status_t)
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_wakeup_pattern_set(wiced_bt_device_address_t bdaddr,
        wiced_bt_ble_hidh_wakeup_pattern_cmd_t command, uint16_t report_id,
        uint8_t *p_pattern, uint16_t pattern_len);

/**
 * Function         wiced_bt_ble_hidh_wakeup_pattern_control
 *
 *                  Application call this function to enable/disable the WakeUp.
 *                  This function is typically called after wiced_bt_ble_hidh_wakeup_pattern_set.
 *                  The p_data and data_len, could be used (later) to add additional GPIO Control
 *                  (duration, pattern, etc.).
 *
 * @param[in]       bdaddr          : BdAddr of the HID Device
 * @param[in]       command         : WakeUp command
 * @param[in]       report_id       : WakeUp ReportId to filter
 * @param[in]       p_pattern       : WakeUp ReportId's pattern data to filter
 * @param[in]       p_pattern       : WakeUp ReportId's pattern data length to filter
 *
 * @return          Result code (see wiced_bt_gatt_status_t)
 *
 */
wiced_bt_ble_hidh_status_t wiced_bt_ble_hidh_wakeup_pattern_control(wiced_bool_t enable,
        uint32_t gpio_num, uint8_t polarity, uint8_t *p_data, uint8_t data_len);

/** @} wiced_bt_ble_hidh_api_functions */

#ifdef __cplusplus
}
#endif

