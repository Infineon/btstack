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
 * AIROC Bluetooth Low Energy (LE) Functions
 *
 */
#ifndef __WICED_BT_BLE_H__
#define __WICED_BT_BLE_H__



#include "wiced_bt_cfg.h"
#include "wiced_bt_dev.h"
#include "wiced_bt_isoc.h"

#define BTM_BLE_LEGACY_AD_DATA_LEN 31                       /**< Max legacy advertisement data len*/
#define BTM_AFH_CHNL_MAP_SIZE    HCI_AFH_CHANNEL_MAP_LEN    /**< AFH channel map size */
#define BLE_CHANNEL_MAP_LEN      5                          /**< AFH Channel Map len */
/** LE Channel Map */
typedef uint8_t wiced_bt_ble_chnl_map_t[BLE_CHANNEL_MAP_LEN];


/** Scanner filter policy */
enum wiced_bt_ble_scanner_filter_policy_e {
    BTM_BLE_SCAN_POLICY_ACCEPT_ADV_RSP,              /**< accept adv packet from all, directed adv pkt not directed to local device is ignored */
    BTM_BLE_SCAN_POLICY_FILTER_ADV_RSP,        /**< accept adv packet from device in filter Accept List, directed adv packet not directed to local device is ignored */
    BTM_BLE_SCAN_POLICY_ACCEPT_RPA_DIR_ADV_RSP,      /**< accept adv packet from all, directed adv pkt not directed to local device is ignored except direct adv with RPA */
    BTM_BLE_SCAN_POLICY_FILTER_RPA_DIR_ADV_RSP,/**< accept adv packet from device in filter Accept List, directed adv pkt not directed to me is ignored except direct adv with RPA */
    BTM_BLE_SCAN_POLICY_MAX                       /**< Max Scan filter policy value */
};
/** LE Scanner filter policy */
typedef uint8_t   wiced_bt_ble_scanner_filter_policy_t;  /**< Scanner filter policy (see #wiced_bt_ble_scanner_filter_policy_e) */


/** default advertising channel map */
#ifndef BTM_BLE_DEFAULT_ADVERT_CHNL_MAP
#define BTM_BLE_DEFAULT_ADVERT_CHNL_MAP   (BTM_BLE_ADVERT_CHNL_37| BTM_BLE_ADVERT_CHNL_38| BTM_BLE_ADVERT_CHNL_39)
#endif

/** Advertising filter policy */
enum wiced_bt_ble_advert_filter_policy_e {
    BTM_BLE_ADV_POLICY_ACCEPT_CONN_AND_SCAN     = 0x00,    /**< Process scan and connection requests from all devices (i.e., the Filter Accept List is not in use) (default) */
    BTM_BLE_ADV_POLICY_ACCEPT_CONN_FILTER_SCAN  = 0x01,    /**< Process connection requests from all devices and only scan requests from devices that are in the Filter Accept List. */
    BTM_BLE_ADV_POLICY_FILTER_CONN_ACCEPT_SCAN  = 0x02,    /**< Process scan requests from all devices and only connection requests from devices that are in the Filter Accept List */
    BTM_BLE_ADV_POLICY_FILTER_CONN_FILTER_SCAN  = 0x03,    /**< Process scan and connection requests only from devices in the Filter Accept List. */
    BTM_BLE_ADV_POLICY_MAX                                 /**< Max Adv filter value */
};
typedef uint8_t   wiced_bt_ble_advert_filter_policy_t;  /**< Advertising filter policy (see #wiced_bt_ble_advert_filter_policy_e) */

/** default advertising filter policy */
#define BTM_BLE_ADVERT_FILTER_DEFAULT   BTM_BLE_ADV_POLICY_ACCEPT_CONN_AND_SCAN

#define BTM_BLE_ADVERT_INTERVAL_MIN     0x0020  /**< adv parameter Min value */
#define BTM_BLE_ADVERT_INTERVAL_MAX     0x4000  /**< adv parameter Max value */

#define BTM_BLE_SCAN_INTERVAL_MIN       0x0004  /**< Scan interval minimum value */
#define BTM_BLE_SCAN_INTERVAL_MAX       0x4000  /**< Scan interval miximum value */
#define BTM_BLE_SCAN_WINDOW_MIN         0x0004  /**< Scan window minimum value */
#define BTM_BLE_SCAN_WINDOW_MAX         0x4000  /**< Scan window maximum value */
#define BTM_BLE_CONN_INTERVAL_MIN       0x0006  /**< Connection interval minimum value */
#define BTM_BLE_CONN_INTERVAL_MAX       0x0C80  /**< Connection interval maximum value */
#define BTM_BLE_CONN_LATENCY_MAX        500     /**< Maximum Connection Latency */
#define BTM_BLE_CONN_SUP_TOUT_MIN       0x000A  /**< Minimum Supervision Timeout */
#define BTM_BLE_CONN_SUP_TOUT_MAX       0x0C80  /**< Maximum Supervision Timeout */
#define BTM_BLE_CONN_PARAM_UNDEF        0xffff  /**< use this value when a specific value not to be overwritten */
#define BTM_BLE_CONN_SUP_TOUT_DEF       700     /**< Default Supervision Timeout */

/* default connection parameters if not configured, use GAP recommend value for auto connection */
/** default scan interval
 *  30 ~ 60 ms (use 60)  = 96 *0.625
 */
#define BTM_BLE_SCAN_FAST_INTERVAL      96

/** default scan window (in .625ms slots) for background auto connections
 * 30 ms = 48 *0.625
 */
#define BTM_BLE_SCAN_FAST_WINDOW        48

/** default scan interval used in reduced power cycle (background scanning)
 *  1.28 s   = 2048 *0.625
 */
#define BTM_BLE_SCAN_SLOW_INTERVAL_1    2048

/** default scan window used in reduced power cycle (background scanning)
 *   11.25 ms = 18 *0.625
 */
#define BTM_BLE_SCAN_SLOW_WINDOW_1      18

/** default scan interval used in reduced power cycle (background scanning)
 *  2.56 s   = 4096 *0.625
 */
#define BTM_BLE_SCAN_SLOW_INTERVAL_2    4096

/** default scan window used in reduced power cycle (background scanning)
 *  22.5 ms = 36 *0.625
 */
#define BTM_BLE_SCAN_SLOW_WINDOW_2      36

/** default connection interval min
 *  recommended min: 30ms  = 24 * 1.25
 */
#define BTM_BLE_CONN_INTERVAL_MIN_DEF   24

/** default connection interval max
 * recommended max: 50 ms = 56 * 1.25
 */
#define BTM_BLE_CONN_INTERVAL_MAX_DEF   40

/** default Peripheral latency */
#define BTM_BLE_CONN_PERIPHERAL_LATENCY_DEF  0

/** default supervision timeout */
#define BTM_BLE_CONN_TIMEOUT_DEF                    2000

/** LE Signature
 *  LE data signature length 8 Bytes + 4 bytes counter
 */
#define BTM_BLE_AUTH_SIGNATURE_SIZE                 12
typedef uint8_t wiced_dev_ble_signature_t[BTM_BLE_AUTH_SIGNATURE_SIZE];     /**< Device address (see #BTM_BLE_AUTH_SIGNATURE_SIZE) */

#define BTM_BLE_POLICY_REJECT_ALL                   0x00    /**< relevant to both */
#define BTM_BLE_POLICY_ALLOW_SCAN                   0x01    /**< relevant to advertiser */
#define BTM_BLE_POLICY_ALLOW_CONN                   0x02    /**< relevant to advertiser */
#define BTM_BLE_POLICY_ALLOW_ALL                    0x03    /**< relevant to both */

/* ADV data flag bit definition used for BTM_BLE_ADVERT_TYPE_FLAG */
#define BTM_BLE_LIMITED_DISCOVERABLE_FLAG           (0x01 << 0)     /**< Limited Discoverable */
#define BTM_BLE_GENERAL_DISCOVERABLE_FLAG           (0x01 << 1)     /**< General Discoverable */
#define BTM_BLE_BREDR_NOT_SUPPORTED                 (0x01 << 2)     /**< BR/EDR Not Supported */
/* 4.1 spec adv flag for simultaneous BR/EDR+LE connection support (see) */
#define BTM_BLE_SIMULTANEOUS_DUAL_MODE_TO_SAME_DEVICE_CONTROLLER_SUPPORTED      (0x01 << 3)   /**< Simultaneous LE and BR/EDR to Same Device Capable (Controller). */
#define BTM_BLE_SIMULTANEOUS_DUAL_MODE_TO_SAME_DEVICE_HOST_SUPPORTED            (0x01 << 4)   /**< Simultaneous LE and BR/EDR to Same Device Capable (Host). */
#define BTM_BLE_NON_LIMITED_DISCOVERABLE_FLAG       (0x00 )         /**< Non Discoverable */
#define BTM_BLE_ADVERT_FLAG_MASK                    (BTM_BLE_LIMITED_DISCOVERABLE_FLAG | BTM_BLE_BREDR_NOT_SUPPORTED | BTM_BLE_GENERAL_DISCOVERABLE_FLAG) /**< LE adverisement mask */
#define BTM_BLE_LIMITED_DISCOVERABLE_MASK           (BTM_BLE_LIMITED_DISCOVERABLE_FLAG )    /**< LE Limited discovery mask*/

#define MULTI_ADV_MAX_NUM_INSTANCES  16 /**< Maximum number of Instance for Multi Advertisement  */

/** Advertisement data types */
enum wiced_bt_ble_advert_type_e {
    BTM_BLE_ADVERT_TYPE_FLAG                        = 0x01,                 /**< Advertisement flags */
    BTM_BLE_ADVERT_TYPE_16SRV_PARTIAL               = 0x02,                 /**< List of supported services - 16 bit UUIDs (partial) */
    BTM_BLE_ADVERT_TYPE_16SRV_COMPLETE              = 0x03,                 /**< List of supported services - 16 bit UUIDs (complete) */
    BTM_BLE_ADVERT_TYPE_32SRV_PARTIAL               = 0x04,                 /**< List of supported services - 32 bit UUIDs (partial) */
    BTM_BLE_ADVERT_TYPE_32SRV_COMPLETE              = 0x05,                 /**< List of supported services - 32 bit UUIDs (complete) */
    BTM_BLE_ADVERT_TYPE_128SRV_PARTIAL              = 0x06,                 /**< List of supported services - 128 bit UUIDs (partial) */
    BTM_BLE_ADVERT_TYPE_128SRV_COMPLETE             = 0x07,                 /**< List of supported services - 128 bit UUIDs (complete) */
    BTM_BLE_ADVERT_TYPE_NAME_SHORT                  = 0x08,                 /**< Short name */
    BTM_BLE_ADVERT_TYPE_NAME_COMPLETE               = 0x09,                 /**< Complete name */
    BTM_BLE_ADVERT_TYPE_TX_POWER                    = 0x0A,                 /**< TX Power level  */
    BTM_BLE_ADVERT_TYPE_DEV_CLASS                   = 0x0D,                 /**< Device Class */
    BTM_BLE_ADVERT_TYPE_SIMPLE_PAIRING_HASH_C       = 0x0E,                 /**< Simple Pairing Hash C */
    BTM_BLE_ADVERT_TYPE_SIMPLE_PAIRING_RAND_C       = 0x0F,                 /**< Simple Pairing Randomizer R */
    BTM_BLE_ADVERT_TYPE_SM_TK                       = 0x10,                 /**< Security manager TK value */
    BTM_BLE_ADVERT_TYPE_SM_OOB_FLAG                 = 0x11,                 /**< Security manager Out-of-Band data */
    BTM_BLE_ADVERT_TYPE_INTERVAL_RANGE              = 0x12,                 /**< Peripheral connection interval range */
    BTM_BLE_ADVERT_TYPE_SOLICITATION_SRV_UUID       = 0x14,                 /**< List of solicitated services - 16 bit UUIDs */
    BTM_BLE_ADVERT_TYPE_128SOLICITATION_SRV_UUID    = 0x15,                 /**< List of solicitated services - 128 bit UUIDs */
    BTM_BLE_ADVERT_TYPE_SERVICE_DATA                = 0x16,                 /**< Service data - 16 bit UUID */
    BTM_BLE_ADVERT_TYPE_PUBLIC_TARGET               = 0x17,                 /**< Public target address */
    BTM_BLE_ADVERT_TYPE_RANDOM_TARGET               = 0x18,                 /**< Random target address */
    BTM_BLE_ADVERT_TYPE_APPEARANCE                  = 0x19,                 /**< Appearance */
    BTM_BLE_ADVERT_TYPE_ADVERT_INTERVAL             = 0x1a,                 /**< Advertising interval */
    BTM_BLE_ADVERT_TYPE_LE_BD_ADDR                  = 0x1b,                 /**< LE device bluetooth address */
    BTM_BLE_ADVERT_TYPE_LE_ROLE                     = 0x1c,                 /**< LE role */
    BTM_BLE_ADVERT_TYPE_256SIMPLE_PAIRING_HASH      = 0x1d,                 /**< Simple Pairing Hash C-256 */
    BTM_BLE_ADVERT_TYPE_256SIMPLE_PAIRING_RAND      = 0x1e,                 /**< Simple Pairing Randomizer R-256 */
    BTM_BLE_ADVERT_TYPE_32SOLICITATION_SRV_UUID     = 0x1f,                 /**< List of solicitated services - 32 bit UUIDs */
    BTM_BLE_ADVERT_TYPE_32SERVICE_DATA              = 0x20,                 /**< Service data - 32 bit UUID */
    BTM_BLE_ADVERT_TYPE_128SERVICE_DATA             = 0x21,                 /**< Service data - 128 bit UUID */
    BTM_BLE_ADVERT_TYPE_CONN_CONFIRM_VAL            = 0x22,                 /**< LE Secure Connections Confirmation Value */
    BTM_BLE_ADVERT_TYPE_CONN_RAND_VAL               = 0x23,                 /**< LE Secure Connections Random Value */
    BTM_BLE_ADVERT_TYPE_URI                         = 0x24,                 /**< URI */
    BTM_BLE_ADVERT_TYPE_INDOOR_POS                  = 0x25,                 /**< Indoor Positioning */
    BTM_BLE_ADVERT_TYPE_TRANS_DISCOVER_DATA         = 0x26,                 /**< Transport Discovery Data */
    BTM_BLE_ADVERT_TYPE_SUPPORTED_FEATURES          = 0x27,                 /**< LE Supported Features */
    BTM_BLE_ADVERT_TYPE_UPDATE_CH_MAP_IND           = 0x28,                 /**< Channel Map Update Indication */
    BTM_BLE_ADVERT_TYPE_PB_ADV                      = 0x29,                 /**< PB-ADV */
    BTM_BLE_ADVERT_TYPE_MESH_MSG                    = 0x2A,                 /**< Mesh Message */
    BTM_BLE_ADVERT_TYPE_MESH_BEACON                 = 0x2B,                 /**< Mesh Beacon */
    BTM_BLE_ADVERT_TYPE_PSRI                        = 0x2E,                 /**< Generic Audio Provate Set Random Identifier */
    BTM_BLE_ADVERT_TYPE_EAD                         = 0x31,                 /**< Encrypted Advertising Data */
    BTM_BLE_ADVERT_TYPE_3D_INFO_DATA                = 0x3D,                 /**< 3D Information Data */
    BTM_BLE_ADVERT_TYPE_MANUFACTURER                = 0xFF                  /**< Manufacturer data */
};
typedef uint8_t   wiced_bt_ble_advert_type_t;    /**< LE advertisement data type (see #wiced_bt_ble_advert_type_e) */

/** security settings used with L2CAP LE COC */
enum wiced_bt_ble_sec_flags_e
{
    BTM_SEC_LE_LINK_ENCRYPTED                       = 0x01,                 /**< Link encrypted */
    BTM_SEC_LE_LINK_PAIRED_WITHOUT_MITM             = 0x02,                 /**< Paired without man-in-the-middle protection */
    BTM_SEC_LE_LINK_PAIRED_WITH_MITM                = 0x04                  /**< Link with man-in-the-middle protection */
};

/** Advertisement element */
typedef struct
{
    uint8_t                     *p_data;        /**< Advertisement data */
    uint16_t                    len;            /**< Advertisement length */
    wiced_bt_ble_advert_type_t  advert_type;    /**< Advertisement data type */
}wiced_bt_ble_advert_elem_t;

/** Scan result event type */
enum wiced_bt_dev_ble_evt_type_e {
    BTM_BLE_EVT_CONNECTABLE_ADVERTISEMENT           = 0x00,                 /**< Connectable advertisement */
    BTM_BLE_EVT_CONNECTABLE_DIRECTED_ADVERTISEMENT  = 0x01,                 /**< Connectable Directed advertisement */
    BTM_BLE_EVT_SCANNABLE_ADVERTISEMENT             = 0x02,                 /**< Scannable advertisement */
    BTM_BLE_EVT_NON_CONNECTABLE_ADVERTISEMENT       = 0x03,                 /**< Non connectable advertisement */
    BTM_BLE_EVT_SCAN_RSP                            = 0x04                  /**< Scan response */
};
typedef uint8_t wiced_bt_dev_ble_evt_type_t;    /**< Scan result event value (see #wiced_bt_dev_ble_evt_type_e) */

/** Background connection type */
enum wiced_bt_ble_conn_type_e
{
    BTM_BLE_CONN_NONE,                          /**< No background connection */
    BTM_BLE_CONN_AUTO,                          /**< Auto connection based on filter list */
    BTM_BLE_CONN_SELECTIVE = BTM_BLE_CONN_AUTO  /**< Selective not used */
};
typedef uint8_t wiced_bt_ble_conn_type_t;       /**< Connection type (see #wiced_bt_ble_conn_type_e) */

/** LE inquiry result type */
typedef struct
{
    wiced_bool_t                    is_extended;                            /**< True if an extended ADV */
    wiced_bt_device_address_t       remote_bd_addr;                         /**< Device address */
    uint8_t                         ble_addr_type;                          /**< LE Address type */
    wiced_bt_dev_ble_evt_type_t     ble_evt_type;                           /**< Scan result event type */
    int8_t                          rssi;                                   /**< Set to #BTM_INQ_RES_IGNORE_RSSI, if not valid */
    uint8_t                         flag;                                   /**< Adverisement Flag value */
    uint8_t                         primary_phy;                            /**< Primary PHY */
    uint8_t                         secondary_phy;                          /**< Secondary PHY */
    uint8_t                         adv_sid;                                /**< advertisement security ID */
    uint8_t                         tx_power;                               /**< Tx power */
    uint16_t                        periodic_adv_interval;                  /**< Periodic advertisement interval */
    uint8_t                         direct_addr_type;                       /**< Directed address type */
    wiced_bt_device_address_t       direct_bda;                             /**< Directed address */
} wiced_bt_ble_scan_results_t;

/** LE encryption method **/
enum wiced_bt_ble_sec_action_type_e
{
    BTM_BLE_SEC_NONE,               /**< No encryption */
    BTM_BLE_SEC_ENCRYPT,            /**< Encrypt the link using current key */
    BTM_BLE_SEC_ENCRYPT_NO_MITM,    /**< Encryption without MITM (man in the middle) */
    BTM_BLE_SEC_ENCRYPT_MITM        /**< Encryption with MITM (man in the middle) */
};
typedef uint8_t wiced_bt_ble_sec_action_type_t;  /**< LE security type. refer #wiced_bt_ble_sec_action_type_e */

#define BTM_BLE_PREFER_1M_PHY              0x01    /**< LE 1M PHY preference */
#define BTM_BLE_PREFER_2M_PHY              0x02    /**< LE 2M PHY preference */
#define BTM_BLE_PREFER_LELR_PHY            0x04    /**< LE LELR PHY preference */

/**  Host preferences on PHY.
 *  Bit field that indicates the PHY that the Host prefers the Controller to use. \n
 *  <pre>
 *  Bit number 0   : The Host prefers to use the LE 1M PHY (possibly among others)
 *  Bit number 1   : The Host prefers to use the LE 2M PHY (possibly among others)
 *  Bit number 2   : The Host prefers to use the LE Coded PHY (possibly among others)
 *  Bit number 3-7 : Reserved for future
 *  </pre>
 *  @note The valid values for PHY preference are #BTM_BLE_PREFER_1M_PHY , #BTM_BLE_PREFER_2M_PHY and #BTM_BLE_PREFER_LELR_PHY.
 */
typedef uint8_t   wiced_bt_ble_host_phy_preferences_t;

#define BTM_BLE_PREFER_NO_LELR    0x0000 /**< No preferred coding */
#define BTM_BLE_PREFER_LELR_S2    0x0001 /**< Preferred coding is S=2, 500 kb/s */
#define BTM_BLE_PREFER_LELR_S8    0x0002 /**< Preferred coding is S=8, 125 kb/s */

/**
 * @note BTM_BLE_PREFER_LELR_512K and BTM_BLE_PREFER_LELR_125K are going to be deprecated.
 * Use #BTM_BLE_PREFER_LELR_S2 and #BTM_BLE_PREFER_LELR_S8 instead.
 */
#define BTM_BLE_PREFER_LELR_512K    BTM_BLE_PREFER_LELR_S2 /**< @note To be deprecated use \ref BTM_BLE_PREFER_LELR_S2 */
#define BTM_BLE_PREFER_LELR_125K    BTM_BLE_PREFER_LELR_S8 /**< @note To be deprecated use \ref BTM_BLE_PREFER_LELR_S8 */

/**  The PHY_options parameter is a bit field that allows the Host to specify options for LE long range PHY.
 *    <pre>
 *    Bit 0-1  : 0 = Host has no preferred coding when using LE Coded PHY
 *               1 = Host prefers that S=2 coding be used when using LE Coded PHY
 *               2 = Host prefers that S=8 coding be used when using LE Coded PHY
 *               3 = Reserved for future use
 *    Bit 2-15 : Reserved for future use
 *    </pre>
 *    The default value for a new connection is "no preference for coding" when using LE coded PHY. The Controller may override any
 *    preferred coding (S=2 coded PHY for 500 kb/s and S=8 coded PHY for 125 kb/s ) for
 *    transmitting on the LE Coded PHY. \n
 *    The Host may specify a preferred coding even if it prefers not to use the LE
 *    Coded transmitter PHY since the Controller may override the PHY preference. \n
 *
 *  @note  These preferences are applicable only when #BTM_BLE_PREFER_LELR_PHY flag is set. \n
 * The valid values for PHY_options are #BTM_BLE_PREFER_NO_LELR , #BTM_BLE_PREFER_LELR_S2 and #BTM_BLE_PREFER_LELR_S8.
 */
typedef uint16_t  wiced_bt_ble_lelr_phy_preferences_t;

/** Host PHY preferences */
typedef struct
{
    wiced_bt_device_address_t               remote_bd_addr;     /**< Peer Device address */
    wiced_bt_ble_host_phy_preferences_t     tx_phys;            /**< Host preference among the transmitter PHYs. \n The valid values for transmitter PHY preference
                                                                are #BTM_BLE_PREFER_1M_PHY , #BTM_BLE_PREFER_2M_PHY and #BTM_BLE_PREFER_LELR_PHY \n
                                                                Refer #wiced_bt_ble_host_phy_preferences_t for more details. */
    wiced_bt_ble_host_phy_preferences_t     rx_phys;            /**< Host preference among the receiver PHYs. \n The valid values for receiver PHY preference are
                                                                #BTM_BLE_PREFER_1M_PHY , #BTM_BLE_PREFER_2M_PHY and #BTM_BLE_PREFER_LELR_PHY \n
                                                                Refer #wiced_bt_ble_host_phy_preferences_t for more details.*/
    wiced_bt_ble_lelr_phy_preferences_t     phy_opts;           /**< Host preference on LE coded PHY. \n The valid values for PHY_options are
                                                                #BTM_BLE_PREFER_NO_LELR , #BTM_BLE_PREFER_LELR_S2 and #BTM_BLE_PREFER_LELR_S8. \n
                                                                Refer #wiced_bt_ble_lelr_phy_preferences_t for more details.*/
}wiced_bt_ble_phy_preferences_t;

/** LE connection parameteres */
typedef struct
{
    wiced_bt_dev_role_t role;           /**< Connection role 0: Central  1: Peripheral */
    uint16_t            conn_interval;          /**< Connection interval in slots */
    uint16_t            conn_latency;           /**< Connection latency */
    uint16_t            supervision_timeout;    /**< Supervision timeout */
}wiced_bt_ble_conn_params_t;

/** LE preferred connection parameters */
typedef struct
{
    uint16_t  conn_interval_min;  /**< minimum connection interval */
    uint16_t  conn_interval_max;  /**< maximum connection interval */
    uint16_t  conn_latency;  /**< connection latency */
    uint16_t  conn_supervision_timeout;  /**< connection supervision timeout */
}wiced_bt_ble_pref_conn_params_t;


/* The power table for multi ADV Tx Power levels
    Min   : -12 dBm     #define BTM_BLE_ADV_TX_POWER_MIN        0
    Low   :  -8 dBm     #define BTM_BLE_ADV_TX_POWER_LOW        1
    Mid   :  -4 dBm     #define BTM_BLE_ADV_TX_POWER_MID        2
    Upper :   0 dBm     #define BTM_BLE_ADV_TX_POWER_UPPER      3
    Max   :   4 dBm     #define BTM_BLE_ADV_TX_POWER_MAX        4
*/
#define MULTI_ADV_TX_POWER_MIN_INDEX                0   /**< Multi adv tx min power index */
#define MULTI_ADV_TX_POWER_MAX_INDEX                4   /**< Multi adv tx max power index */

/** Transmit Power in dBm ( #MULTI_ADV_TX_POWER_MIN_INDEX to #MULTI_ADV_TX_POWER_MAX_INDEX ) */
typedef int8_t wiced_bt_ble_adv_tx_power_t;

/** Multi-advertisement start/stop */
enum wiced_bt_ble_multi_advert_start_e
{
    MULTI_ADVERT_STOP                               = 0x00,                 /**< Stop Multi-adverstisment */
    MULTI_ADVERT_START                              = 0x01                  /**< Start Multi-adverstisment */
};

/** Multi-advertisement type */
enum wiced_bt_ble_multi_advert_type_e
{
    MULTI_ADVERT_CONNECTABLE_UNDIRECT_EVENT         = 0x00,     /**< Multi adv Connectable undirected event */
    MULTI_ADVERT_CONNECTABLE_DIRECT_EVENT           = 0x01,     /**< Multi adv Connectable directed event */
    MULTI_ADVERT_DISCOVERABLE_EVENT                 = 0x02,     /**< Multi adv Discoverable event */
    MULTI_ADVERT_NONCONNECTABLE_EVENT               = 0x03,     /**< Multi adv NonConnectable event */
    MULTI_ADVERT_LOW_DUTY_CYCLE_DIRECT_EVENT        = 0x04      /**< Multi adv Low Cycle directed event */
};
typedef uint8_t wiced_bt_ble_multi_advert_type_t;    /**< LE advertisement type (see #wiced_bt_ble_multi_advert_type_e) */


/** LE Multi advertising parameter */
typedef struct
{
    /**< BTM_BLE_ADVERT_INTERVAL_MIN to BTM_BLE_ADVERT_INTERVAL_MAX ( As per spec ) */
    uint16_t                             adv_int_min;            /**< Minimum adv interval */
    /**< BTM_BLE_ADVERT_INTERVAL_MIN to BTM_BLE_ADVERT_INTERVAL_MAX ( As per spec ) */
    uint16_t                             adv_int_max;            /**< Maximum adv interval */
    wiced_bt_ble_multi_advert_type_t     adv_type;               /**< Adv event type */
    wiced_bt_ble_advert_chnl_map_t       channel_map;            /**< Adv channel map */
    wiced_bt_ble_advert_filter_policy_t  adv_filter_policy;      /**< Advertising filter policy */
    wiced_bt_ble_adv_tx_power_t          adv_tx_power;           /**< Adv tx power */
    wiced_bt_device_address_t            peer_bd_addr;           /**< Peer Device address */
    wiced_bt_ble_address_type_t          peer_addr_type;         /**< Peer LE Address type */
    wiced_bt_device_address_t            own_bd_addr;            /**< Own LE address */
    wiced_bt_ble_address_type_t          own_addr_type;          /**< Own LE Address type */
}wiced_bt_ble_multi_adv_params_t;

/** Privacy mode
 * refer Spec version 5.0 Vol 3 Part C Section 10.7 privacy feature
 */
enum wiced_bt_ble_privacy_e
{
    BTM_BLE_PRIVACY_MODE_NETWORK,                           /**< network privacy mode*/
    BTM_BLE_PRIVACY_MODE_DEVICE                             /**< device privacy mode*/
};
/** LE Privacy mode. Refer #wiced_bt_ble_privacy_e */
typedef uint8_t wiced_bt_ble_privacy_mode_t;

/** Multi-advertisement Filtering policy  */
enum wiced_bt_ble_multi_advert_filtering_policy_e
{
    MULTI_ADVERT_FILTER_POLICY_NOT_USED                         = 0x00,   /**< Multi adv filter filter Accept List not used */
    MULTI_ADVERT_FILTER_POLICY_ADV_ALLOW_UNKNOWN_CONNECTION     = 0x01,   /**< Multi adv filter filter Accept List for scan request */
    MULTI_ADVERT_FILTER_POLICY_ADV_ALLOW_UNKNOWN_SCANNING       = 0x02,   /**< Multi adv filter filter Accept List for connection request */
    MULTI_ADVERT_FILTER_POLICY_USE_FOR_ALL                      = 0x03    /**< Multi adv filter filter Accept List for all */
};
typedef uint8_t wiced_bt_ble_multi_advert_filtering_policy_t;    /**< LE advertisement filtering policy (see #wiced_bt_ble_multi_advert_filtering_policy_e) */

/**
 * Callback wiced_bt_ble_scan_result_cback_t
 *
 * Scan result callback (from calling #wiced_bt_ble_scan)
 *
 * @param p_scan_result             : scan result data (NULL indicates end of scanning)
 * @param p_adv_data                : Advertisement data (parse using #wiced_bt_ble_check_advertising_data)
 *
 * @return Nothing
 */
typedef void (wiced_bt_ble_scan_result_cback_t) (wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data);

/**
 * Callback wiced_bt_ble_read_phy_complete_callback_t
 *
 * read phy complete callback (from calling #wiced_bt_ble_read_phy)
 *
 * @param p_phy_result             : read phys result
 *
 * @return Nothing
 */
typedef void (wiced_bt_ble_read_phy_complete_callback_t) (wiced_bt_ble_phy_update_t *p_phy_result);

/** ADV extension structures */
#define WICED_BT_BLE_MAX_EXT_ADV_DATA_LEN    251

/** LE PHY */
enum
{
    WICED_BT_BLE_EXT_ADV_PHY_1M          = 0x1, /**< advetiser advertisement PHY is LE 1M */
    WICED_BT_BLE_EXT_ADV_PHY_2M          = 0x2, /**< advetiser advertisement PHY is LE 2M */
    WICED_BT_BLE_EXT_ADV_PHY_LE_CODED    = 0x3, /**< advetiser advertisement PHY is LE Coded (for long range) */
    WICED_BT_BLE_EXT_ADV_NUM_PHYS        = 0x3  /**< 3 PHYs are defined */
};
typedef uint8_t wiced_bt_ble_ext_adv_phy_t;     /**< LE phy to be used for extended advertisement */

/** LE PHY bit mask */
enum
{
    WICED_BT_BLE_EXT_ADV_PHY_1M_BIT         = (1 << 0), /**< Bit mask to specify for LE1M PHY */
    WICED_BT_BLE_EXT_ADV_PHY_2M_BIT         = (1 << 1), /**< Bit mask to specify for LE2M PHY */
    WICED_BT_BLE_EXT_ADV_PHY_LE_CODED_BIT   = (1 << 2), /**< Bit mask to specify for LE coded PHY */
};
typedef uint8_t wiced_bt_ble_ext_adv_phy_mask_t;  /**< LE phy mask to be used for extended advertisement */

/** Advertising event properties: Describes the type of advertising event that is being configured and its basic properties */
enum
{
    WICED_BT_BLE_EXT_ADV_EVENT_CONNECTABLE_ADV                       = (1 << 0),   /**< Connectable ADV */
    WICED_BT_BLE_EXT_ADV_EVENT_SCANNABLE_ADV                         = (1 << 1),   /**< Scannable ADV */
    WICED_BT_BLE_EXT_ADV_EVENT_DIRECTED_ADV                          = (1 << 2),   /**< Low duty cycle directed advertisement */
    WICED_BT_BLE_EXT_ADV_EVENT_HIGH_DUTY_DIRECTED_CONNECTABLE_ADV    = (1 << 3),   /**< 3.75 ms Advertising Interval, only valid in legacy ADV */
    WICED_BT_BLE_EXT_ADV_EVENT_LEGACY_ADV                            = (1 << 4),   /**< Legacy Advertisement. Adv data cannot be more than 31 bytes.*/
    WICED_BT_BLE_EXT_ADV_EVENT_ANONYMOUS_ADV                         = (1 << 5),   /**< Omits advertisers address from all PDUs */
    WICED_BT_BLE_EXT_ADV_EVENT_INCLUDE_TX_POWER                      = (1 << 6),   /**< Include Tx power in ext ADV pdus */

    /** Other bits RFU */
};
typedef uint16_t wiced_bt_ble_ext_adv_event_property_t;  /**< LE extended advertisement event property */

/** Advertisement set handle to identify adv set b/n host and controller */
enum
{
    WICED_BT_BLE_EXT_ADV_HANDLE_MIN = 0x00,     /**< min advertisement set handle value */
    WICED_BT_BLE_EXT_ADV_HANDLE_MAX = 0xef,     /**< max advertisement set handle value */
};

typedef uint8_t wiced_bt_ble_ext_adv_handle_t; /**< advertisement set handle value */

/** The Advertising set identifier(SID) is used to uniquely identify adv sets from advertiser.
    SID the value to be transmitted in the advertising SID subfield of the ADI field of the Extended ADV PDUs */
enum
{
    WICED_BT_BLE_EXT_ADV_SID_MIN = 0x00,        /**< min SID value */
    WICED_BT_BLE_EXT_ADV_SID_MAX = 0x0f,        /**< max SID value */
};
typedef uint8_t wiced_bt_ble_ext_adv_sid_t; /**< SID value */

/** Value to configure to receive scan request recived notification */
enum wiced_bt_ble_ext_adv_scan_req_notification_setting_e
{
    WICED_BT_BLE_EXT_ADV_SCAN_REQ_NOTIFY_DISABLE = 0x00,    /**< Do not send Notification on scan request */
    WICED_BT_BLE_EXT_ADV_SCAN_REQ_NOTIFY_ENABLE  = 0x01,    /**< Send Notification on scan request */
};
/** Enable or disable notification value (see #wiced_bt_ble_ext_adv_scan_req_notification_setting_e) */
typedef uint8_t wiced_bt_ble_ext_adv_scan_req_notification_setting_t;

/** Advertisement duration configuration for specified adv handle */
typedef struct
{
    wiced_bt_ble_ext_adv_handle_t   adv_handle;     /**< advertisement set handle */

    uint16_t adv_duration; /**< 0 = No advertising duration. Advertising to continue until the Host disables it.
                                                    0xXXXX = Range: 0x0001 - 0xFFFF (10 ms to 655,350 ms) */

    uint8_t max_ext_adv_events; /**< 0xXX: Maximum number of extended advertising events the Controller shall
                                            attempt to send prior to disabling the extended advertising set even if
                                            the adv_duration parameter has not expired.
                                            0x00: No maximum number of advertising events */

} wiced_bt_ble_ext_adv_duration_config_t;

/** Encryption Data Key Material structure */
typedef struct
{
    wiced_bt_link_key_t session_key; /**< Session key */
    wiced_bt_iv_t iv;                /**< Initialization Vector */
} wiced_bt_ble_key_material_t;


/** Periodic adv property */
enum wiced_bt_ble_periodic_adv_prop_e
{
    WICED_BT_BLE_PERIODIC_ADV_PROPERTY_INCLUDE_TX_POWER      = (1 << 6) /**< Speicify Tx power in periodic adv events */
};
typedef uint16_t wiced_bt_ble_periodic_adv_prop_t;/**< Periodic adv property (see #wiced_bt_ble_periodic_adv_prop_e) */

/** Extended scan duplicate filter policy */
enum wiced_bt_ble_ext_scan_filter_duplicate_e
{
    WICED_BT_BLE_EXT_SCAN_FILTER_DUPLICATE_DISABLE,                     /**< send all advertisements received from advertisers*/
    WICED_BT_BLE_EXT_SCAN_FILTER_DUPLICATE_ENABLE,                      /**< duplicate advertisements should not be sent until scan disabled */
    WICED_BT_BLE_EXT_SCAN_FILTER_DUPLICATE_ENABLE_RESET_ON_SCAN_PERIOD, /**< filter duplicate adv during single scan Duration
                                                                        (see wiced_bt_ble_ext_scan_enable_t).Period should be non zero on using this option */
};

typedef uint8_t wiced_bt_ble_ext_scan_filter_duplicate_t; /**< Extended scan duplicate filter policy (see #wiced_bt_ble_ext_scan_filter_duplicate_e) */

/** Filter policy used in extended create connection command */
enum wiced_bt_ble_ext_filter_policy_e
{
    /* Initiator filter policy enums */
    WICED_BT_BLE_IGNORE_FILTER_ACCEPT_LIST_FOR_CONNS               = 0,           /**< Filter Accept List is not used to determine which advertiser to connect to.
                                                                Peer_Address_Type and Peer_Address shall be used */
    WICED_BT_BLE_USE_FILTER_ACCEPT_LIST_FOR_CONNS   = 1,           /**< Filter Accept List is used to determine which advertiser to connect to.
                                                                Peer_Address_Type and Peer_Address shall be ignored. */
};
typedef uint8_t wiced_bt_ble_ext_filter_policy_t;/**< Filter policy used. (see #wiced_bt_ble_ext_filter_policy_e) */

/** Options used in create periodic sync to periodic adv command */
enum wiced_bt_ble_adv_sync_options_e
{
    WICED_BT_BLE_IGNORE_SYNC_TO_PERIODIC_ADV_LIST =
        0, /**< Use the Advertising_SID, Advertising_Address_Type, and Advertising
                                                                Address parameters specified in create sync command to determine
                                                                which advertiser to listen to */

    WICED_BT_BLE_SYNC_TO_PERIODIC_ADV_LIST = 1, /**< Use the Periodic Advertiser List to determine which
                                                                advertiser to listen to.*/
};
/** Options used in create periodic sync to periodic adv command (see #wiced_bt_ble_adv_sync_options_e)*/
typedef uint8_t wiced_bt_ble_adv_sync_options_t;

/** Mode used in Periodic Advertising Sync Transfer Parameters */
enum wiced_bt_ble_periodic_adv_sync_transfer_mode_e
{
    WICED_BT_BLE_IGNORE_PA_SYNC_TRANSFER_EVT, /**< No attempt is made to synchronize to the periodic advertising and no
                                                                     HCI_LE_Periodic_Advertising_Sync_Transfer_Received event is sent to the Host (default). */
    WICED_BT_BLE_ENABLE_PA_SYNC_TRANSFER_DISABLE_PA_REPORT_EVT, /**< An HCI_LE_Periodic_Advertising_Sync_Transfer_Received event is
                                                                      sent to the Host. HCI_LE_Periodic_Advertising_Report events will be disabled. */
    WICED_BT_BLE_ENABLE_PA_SYNC_TRANSFER_ENABLE_PA_REPORT_EVT, /**< An HCI_LE_Periodic_Advertising_Sync_Transfer_Received event is
                                                                     sent to the Host. HCI_LE_Periodic_Advertising_Report events will be enabled. */
};
/** Mode used in create periodic sync to periodic adv command (see #wiced_bt_ble_periodic_adv_sync_transfer_mode_e)*/
typedef uint8_t wiced_bt_ble_periodic_adv_sync_transfer_mode_t;

enum
{
    /** The Host has no preferred or required coding when transmitting on the LE Coded PHY  */
    WICED_BT_BLE_PHY_ADV_OPTIONS_NO_PREFERENCE = 0,
    /** The Host prefers that S=2 coding be used when transmitting on the LE Coded PHY */
    WICED_BT_BLE_PHY_ADV_OPTIONS_PREFER_S2 = 1,
    /** The Host prefers that S=8 coding be used when transmitting on the LE Coded PHY */
    WICED_BT_BLE_PHY_ADV_OPTIONS_PREFER_S8 = 2,
    /** The Host requires that S=2 coding be used when transmitting on the LE Coded PHY */
    WICED_BT_BLE_PHY_ADV_OPTIONS_REQUIRE_S2 = 3,
    /** The Host requires that S=8 coding be used when transmitting on the LE Coded PHY */
    WICED_BT_BLE_PHY_ADV_OPTIONS_REQUIRE_S8 = 4,
};
/** Phy adv options to be set in \ref wiced_bt_ble_set_ext_adv_parameters_v2 */
typedef uint8_t wiced_bt_ble_phy_adv_options_t;

/** Parameters for extended adv */
typedef struct
{
    /** event_properties Bit mask to specify connectable, scannable, low duty, high duty, directed, legacy adv */
    wiced_bt_ble_ext_adv_event_property_t event_properties;
    /** primary_adv_int_min Range : 0x000020 to 0xFFFFFF(20 ms to 10, 485.759375 s) */
    uint32_t primary_adv_int_min;

    /** primary_adv_int_max Range : 0x000020 to 0xFFFFFF(20 ms to 10, 485.759375 s) */
    uint32_t primary_adv_int_max;

    /** primary_adv_channel_map LE advertisement channel map(see #wiced_bt_ble_advert_chnl_map_e) */
    wiced_bt_ble_advert_chnl_map_t primary_adv_channel_map;

    /** own_addr_type Ignored in case of anonymous adv.See event_properties */
    wiced_bt_ble_address_type_t own_addr_type;

    /** peer_addr_type Peer address type */
    wiced_bt_ble_address_type_t peer_addr_type;

    /** peer_addr peer address */
    wiced_bt_device_address_t peer_addr;

    /** adv_filter_policy Adv filter policy */
    wiced_bt_ble_advert_filter_policy_t adv_filter_policy;

    /** adv_tx_power - 127 to + 126. 127 means host has no preference */
    int8_t adv_tx_power;

    /** primary_adv_phy Phy used to transmit ADV packets on Primary ADV channels */
    wiced_bt_ble_ext_adv_phy_t primary_adv_phy;

    /** secondary_adv_max_skip Valid only in case of extended ADV.Range 0 to FF.Maximum advertising events controller
        can skip before sending auxiliary adv packets on the secondary adv channel */
    uint8_t secondary_adv_max_skip;

    /** secondary_adv_phy Phy used to transmit ADV packets on secondary ADV channels .Valid only in case of extended ADV */
    wiced_bt_ble_ext_adv_phy_t secondary_adv_phy;

    /** adv_sid Advertisement set identifier is the value to be transmitted in extended ADV PDUs */
    wiced_bt_ble_ext_adv_sid_t adv_sid;

    /** scan_request_not scan request received notification enable/ disable */
    wiced_bt_ble_ext_adv_scan_req_notification_setting_t scan_request_not;

    /** primary phy adv options */
    wiced_bt_ble_phy_adv_options_t primary_phy_opts;

    /** secondary phy adv options */
    wiced_bt_ble_phy_adv_options_t secondary_phy_opts;
} wiced_bt_ble_ext_adv_params_t;


/** Extended ADV connection configuration structure */
typedef struct
{
    uint8_t adv_handle;  /**< advertising handle, Range: 0x00 to 0xEF or 0xFF. @note adv_handle shall be set to 0xff in case adv_handle parameter is not to be used */
    uint8_t sub_event;  /**< subevent,Range: 0x00 to 0x7F or 0xFF. @note sub_event shall be set to 0xff in case sub_event parameter is not to be used */

    wiced_bt_ble_ext_adv_phy_mask_t   initiating_phys;      /**< Bit 0 = 1: Scan connectable advertisements on the LE 1M PHY.
	                                                                     Connection parameters for the LE 1M PHY are provided.
                                                                 Bit 1 = 1: Connection parameters for the LE 2M PHY are provided.
                                                                 Bit 2 = 1: Scan connectable advertisements on the LE Coded PHY. Connection
                                                                            parameters for the LE Coded PHY are provided.
	                                                          The PHY(s) bit mask on which the advertising packets should be received on the primary
			                                          advertising channel and the PHYs for which connection parameters have been specified.*/

    uint16_t      scan_int[WICED_BT_BLE_EXT_ADV_NUM_PHYS];       /**< Range N: 0x0004 to 0xFFFF.Time = N * 0.625 ms. Time Range: 2.5 ms to 40.959375 s */
    uint16_t      scan_window[WICED_BT_BLE_EXT_ADV_NUM_PHYS];    /**< Range N: 0x0004 to 0xFFFF.Time = N * 0.625 ms. Time Range: 2.5 ms to 40.959375 s */
    uint16_t      min_conn_int[WICED_BT_BLE_EXT_ADV_NUM_PHYS];   /**< Range N: 0x0006 to 0x0C80 Time = N * 1.25 ms Time Range: 7.5 ms to 4 s */
    uint16_t      max_conn_int[WICED_BT_BLE_EXT_ADV_NUM_PHYS];   /**< Range N: 0x0006 to 0x0C80 Time = N * 1.25 ms Time Range: 7.5 ms to 4 s */
    uint16_t      conn_latency[WICED_BT_BLE_EXT_ADV_NUM_PHYS];   /**< Range N: 0x0000 to 0x01F3 */
    uint16_t      supervision_to[WICED_BT_BLE_EXT_ADV_NUM_PHYS]; /**< Range N: 0x000A to 0x0C80 Time = N * 10 ms Time Range: 100 ms to 32 s */
    uint16_t      min_ce_len[WICED_BT_BLE_EXT_ADV_NUM_PHYS];     /**< Range N: 0x0000 � 0xFFFF. Time = N * 0.625 ms */
    uint16_t      max_ce_len[WICED_BT_BLE_EXT_ADV_NUM_PHYS];     /**< Range N: 0x0000 � 0xFFFF. Time = N * 0.625 ms */

} wiced_bt_ble_ext_conn_cfg_t;

/** When controller receives succesfully periodic adv event based on create sync to periodic advertiser command,
    sync handle get generated by controller and reported in periodic sync established event
    scanner uniquely identifies periodic adv data from adv reports using this handle and advertismenet set id(SID) */
enum
{
    PERIODIC_SYNC_HANDLE_MIN = 0,
    PERIODIC_SYNC_HANDLE_MAX = 0x0EFF,
};

/** Sync_Handle to be used to identify the periodic advertiser. Range: 0x0000-0x0EFF */
typedef uint16_t wiced_bt_ble_periodic_adv_sync_handle_t;

#define IS_CONNECTABLE_ADV_REPORT(x) (x & (1 << 0))            /**< adv is connectable */
#define IS_SCANNABLE_ADV_REPORT(x) (x & (1 << 1))              /**< adv is scannable */
#define IS_DIRECTED_ADV_REPORT(x) (x & (1 << 2))               /**< directed adv */
#define IS_SCAN_RSP_ADV_REPORT(x) (x & (1 << 3))               /**< scan response */
#define IS_LEGACY_ADV_REPORT(x) (x & (1 << 4))                 /**< legacy adv */
#define IS_ADV_REPORT_DATA_STATUS_INCOMPLETE(x) (x & (1 << 5)) /**< adv data incomplete, more data to come */
#define IS_ADV_REPORT_DATA_STATUS_TRUNCATED(x) (x & (2 << 5))  /**< Incomplete, data truncated, no more to come */
/** Bit mask to identify the type of the adv received in extended adv report. (see #wiced_bt_ble_ext_adv_report_t) event_type filed */
typedef uint16_t wiced_bt_ble_adv_report_event_mask_t;

/**
Extended advertisement report data format

@note When multiple advertising packets are used to complete a single advertising
report(i.e. if adv set data received as multipl adv reports), the RSSI and TxPower event parameters
shall be set based on the last packet received.*/
typedef struct
{
    wiced_bt_ble_adv_report_event_mask_t
        event_type;                            /**< Type of the adv. (See #wiced_bt_ble_adv_report_event_mask_t) */
    wiced_bt_ble_address_type_t addr_type;     /**< advertiser address type */
    wiced_bt_device_address_t bd_addr;         /**< advertiser address */
    wiced_bt_ble_ext_adv_phy_t prim_phy;       /**< PHY on which extended ADV PDUs received */
    wiced_bt_ble_ext_adv_phy_t sec_phy;        /**< PHY on which auxilary ADV PDUs received */
    wiced_bt_ble_ext_adv_sid_t adv_sid;        /**< advertising set identifier */
    int8_t tx_pwr;                             /**< advertisement transmit power */
    int8_t rssi;                               /**< advertisement RSSI */
    uint16_t periodic_adv_int;                 /**< Interval of the periodic advertisements if periodic adv enabled
                                                                on the same set. Range: N = 0x0006 to 0xFFFF, Time = N * 1.25 ms */
    wiced_bt_ble_address_type_t dir_addr_type; /**< Target device address type in case of directed adv report */
    wiced_bt_device_address_t dir_bdaddr;      /**< Target device address in case of directed adv report */
    uint8_t data_len;                          /**< adv data length */

    /* Place holder for adv data */
    uint8_t ad_data[]; /**< adv data  */
} wiced_bt_ble_ext_adv_report_t;

/** Min and Max possible number of reports in LE extended adv report event */
enum wiced_bt_ble_ext_adv_report_count_e
{
    ADV_REP_EVT_COUNT_MIN = 1,  /**< min number of reports in LE extended adv report event */
    ADV_REP_EVT_COUNT_MAX = 10, /**< max number of reports in LE extended adv report event */
};
typedef uint8_t
    wiced_bt_ble_ext_adv_report_count_t; /**< Min and Max reports (see #wiced_bt_ble_ext_adv_report_count_e)*/

/** Advertiser clock accuracy */
enum wiced_bt_ble_advertiser_clock_accuracy_e
{
    ADVERTISER_CLK_ACCURACY_500PPM,
    ADVERTISER_CLK_ACCURACY_250PPM,
    ADVERTISER_CLK_ACCURACY_150PPM,
    ADVERTISER_CLK_ACCURACY_100PPM,
    ADVERTISER_CLK_ACCURACY_75PPM,
    ADVERTISER_CLK_ACCURACY_50PPM,
    ADVERTISER_CLK_ACCURACY_30PPM,
    ADVERTISER_CLK_ACCURACY_20PPM,
};
typedef uint8_t
    wiced_bt_ble_advertiser_clock_accuracy_t; /**< Advertiser clock accuracy (see #wiced_bt_ble_advertiser_clock_accuracy_e) */

/** Sync extablished to periodic advertiser event data format.
    (The LE Periodic Advertising Sync Established event indicates that the
    Controller has received the first periodic advertising packet from an advertiser
    after the LE_Periodic_Advertising_Create_Sync Command has been sent to
    the Controller.)
*/
typedef struct
{
    uint8_t status;                                                     /**< HCI status */
    wiced_bt_ble_periodic_adv_sync_handle_t sync_handle;                /**< sync handle */
    wiced_bt_ble_ext_adv_sid_t adv_sid;                                 /**< advertisement set identifier */
    wiced_bt_ble_address_type_t adv_addr_type;                          /**< advertiser address type */
    wiced_bt_device_address_t adv_addr;                                 /**< advertiser address */
    wiced_bt_ble_ext_adv_phy_t adv_phy;                                 /**< advertiser phy */
    uint16_t periodic_adv_int;                                          /**< Periodic adv interval */
    wiced_bt_ble_advertiser_clock_accuracy_t advertiser_clock_accuracy; /**< advertiser clock accuracy */
} wiced_bt_ble_periodic_adv_sync_established_event_data_t;

/** Periodic advertising report data format */
typedef struct
{
    wiced_bt_ble_periodic_adv_sync_handle_t sync_handle; /**< sync handle */
    int8_t adv_tx_power; /**< advertisement transmit power Range: -127 to +126 dbm. 127 means tx power is not available */
    int8_t adv_rssi;  /**< RSSI. range: -127 to +126. 127 means RSSI is not available */
    uint8_t cte_type; /**< CTE Type */
    uint8_t data_status; /**< 0 = complete data, 1 = data incomplete more data to come, 2 = data truncated.other RFU */
    uint8_t data_len;    /**< Range: 0 -248. Other values RFU */
    uint8_t adv_data[WICED_BT_BLE_MAX_EXT_ADV_DATA_LEN]; /**< periodic adv data */
} wiced_bt_ble_periodic_adv_report_event_data_t;

/** sync handle and connection handle are same range */
typedef wiced_bt_ble_periodic_adv_sync_handle_t wiced_bt_ble_connection_handle_t;

/** extended adv set terminated event data format. This event generated asynchronously by the
    controller when adv set get terminated either adv duration expires or connection being created */
typedef struct
{
    uint8_t status;                                                     /**< HCI status */
    wiced_bt_ble_ext_adv_handle_t adv_handle;                           /**< advertisement set handle */
    wiced_bt_ble_connection_handle_t conn_handle;                       /**< connection handle. The conn_handle
                                                        parameter is only valid when advertising ends because a connection was created */
    uint8_t                             num_completed_ext_adv_events;   /**< number of completed extended advertising events the Controller had
                                                                        transmitted when either the duration elapsed or the maximum number of
                                                                        extended advertising events was reached; otherwise it shall be set to zero. */
} wiced_bt_ble_ext_adv_set_terminated_event_data_t;

/** scan request received event data format */
typedef struct
{
    wiced_bt_ble_ext_adv_handle_t   adv_handle;         /**< advertisement set handle */
    wiced_bt_ble_address_type_t     scanner_addr_type;  /**< Scanner address type */
    wiced_bt_device_address_t       scanner_address;    /**< Scanner address */
} wiced_bt_ble_scan_req_received_event_data_t;

/** LE channel selection algorithms */
enum wiced_bt_ble_channel_sel_algo_e
{
    LE_CHANNEL_SEL_ALGO_1_USED,         /**< LE channel selection algorithm#1 used */
    LE_CHANNEL_SEL_ALGO_2_USED,         /**< LE channel selection algorithm#2 used */
};
typedef uint8_t wiced_bt_ble_channel_sel_algo_t;/**< LE channel algorithm selection (see #wiced_bt_ble_channel_sel_algo_e) */

/** Channel selection algorithm event data format */
typedef struct
{
    wiced_bt_ble_connection_handle_t      connection_handle;    /**< HCI connection handle */
    wiced_bt_ble_channel_sel_algo_t       channel_sel_algo;     /**< LE channel selection algorithm used for this connection */

    /* remaining RFU */
} wiced_bt_ble_channel_sel_algo_event_data_t;

/** BIGInfo report */
typedef struct
{
    uint16_t sync_handle; /**< Sync_Handle identifying the periodic advertising train (Range: 0x0000 to 0x0EFF) */
    uint8_t num_bis;      /**< Value of the Num_BIS subfield of the BIGInfo field */
    uint8_t number_of_subevents;        /**< Value of the NSE subfield of the BIGInfo field */
    uint16_t iso_interval;              /**< Value of the ISO_Interval subfield of the BIGInfo field */
    uint8_t burst_number;               /**< Value of the BN subfield of the BIGInfo field */
    uint8_t pretransmission_offset;     /**< Value of the PTO subfield of the BIGInfo field */
    uint8_t immediate_repetition_count; /**< Value of the IRC subfield of the BIGInfo field */
    uint16_t max_pdu;                /**< Value of the Max_PDU subfield of the BIGInfo field in the Advertising PDU */
    uint32_t sdu_interval;           /**< Value of the SDU_Interval subfield of the BIGInfo field */
    uint16_t max_sdu;                /**< Value of the Max_SDU subfield of the BIGInfo field in the Advertising PDU */
    wiced_bt_isoc_phy_t phy;         /**< The transmitter PHY of packets */
    wiced_bt_isoc_framing_t framing; /**< Framing parameter */
    wiced_bt_isoc_encryption_t encryption; /**< BIG carries encrypted or unencrypted data */
} wiced_bt_ble_biginfo_adv_report_t;

/** Periodic Adv Sync Transfer Received Event Data */
typedef struct
{
    wiced_bt_ble_periodic_adv_sync_established_event_data_t sync_data; /**< Periodic Adv Sync Data */
    wiced_bt_ble_connection_handle_t conn_handle;                      /**< connection handle */
    uint16_t service_data; /**< Service Data value provided by the peer device */
} wiced_bt_ble_periodic_adv_sync_transfer_event_data_t;

/* @cond PAWR_API
   APIs for Periodic Advertising with Response*/

/** Maximum PAWR Subevent data len */
#define WICED_BT_MAX_PAWR_SUBEVENT_DATA_LEN  251

/** Periodic Advertising with Response (PAWR) Sync Established Event Data */
typedef struct
{
    uint8_t                                 status;                     /**< HCI status */
    wiced_bt_ble_periodic_adv_sync_handle_t sync_handle;                /**< sync handle */
    wiced_bt_ble_ext_adv_sid_t              adv_sid;                    /**< advertisement set identifier */
    wiced_bt_ble_address_type_t             adv_addr_type;              /**< advertiser address type */
    wiced_bt_device_address_t               adv_addr;                   /**< advertiser address */
    wiced_bt_ble_ext_adv_phy_t              adv_phy;                    /**< advertiser phy */
    uint16_t                                periodic_adv_int;           /**< Periodic adv interval */
    wiced_bt_ble_advertiser_clock_accuracy_t advertiser_clock_accuracy; /**< advertiser clock accuracy */
    uint8_t                                 num_subevents;              /**< number of subevents */
    uint8_t                                 subevent_interval;          /**< subevent interval */
    uint8_t                                 response_slot_delay;        /**< response slot delay */
    uint8_t                                 response_slot_spacing;      /**< response slot spacing */
} wiced_bt_ble_pawr_sync_established_event_data_t;

/** Periodic Advertising with Response (PAWR) Subevent Data Request Event Data */
typedef struct
{
    wiced_bt_ble_ext_adv_handle_t   adv_handle;                 /**< advertisement set handle */
    uint8_t                         subevent_start;             /**< first subevent */
    uint8_t                         subevent_start_count;       /**< number of subevents */
} wiced_bt_ble_pawr_subevent_data_req_event_data_t;

/** Periodic Advertising with Response (PAWR) Response Report Event Data */
typedef struct
{
    uint8_t adv_handle;      /**< advertisement set handle */
    uint8_t subevent;        /**< subevent number */
    uint8_t tx_status;       /**< if 1, AUX_SYNC_SUBEVENT_IND pkt was transmitted, else no */
    uint8_t tx_power;        /**< tx power */
    uint8_t rssi;            /**< rssi */
    uint8_t cte_type;        /**< constant tone extension */
    uint8_t response_slot;   /**< response slot */
    uint8_t data_status;     /**< data status */
    uint8_t data_len;        /**< data length */
    uint8_t data[WICED_BT_MAX_PAWR_SUBEVENT_DATA_LEN];    /**< data in the event */
} wiced_bt_ble_pawr_rsp_report_event_data_t;

/** Periodic Advertising with Response (PAWR) Indication Report Event Data */
typedef struct
{
    wiced_bt_ble_periodic_adv_sync_handle_t sync_handle;    /**< sync handle */
    uint8_t     tx_power;       /**< tx power */
    uint8_t     rssi;           /**< rssi */
    uint8_t     cte_type;       /**< constant tone extension */
    uint16_t    periodic_evt_counter;    /**< Periodic Event counter */
    uint8_t     sub_event;           /**< Subevent number*/
    uint8_t     data_status;         /**< data status */
    uint8_t     data_length;                                /**< Length of the subevent indication data  */
    uint8_t     data[WICED_BT_MAX_PAWR_SUBEVENT_DATA_LEN];  /**< Subevent data  */
} wiced_bt_ble_pawr_ind_report_event_data_t;
/* @endcond */

/** ADV extension events to the application */
typedef enum
{
    WICED_BT_BLE_PERIODIC_ADV_SYNC_ESTABLISHED_EVENT,   /**< Sync established to periodic advertiser's periodic advertisement. Event Data : wiced_bt_ble_periodic_adv_sync_established_event_data_t */
    WICED_BT_BLE_PERIODIC_ADV_REPORT_EVENT,             /**< Periodic adv report. Event Data: wiced_bt_ble_periodic_adv_report_event_data_t */
    WICED_BT_BLE_PERIODIC_ADV_SYNC_LOST_EVENT,          /**< Periodic sync lost event. Event Data: wiced_bt_ble_periodic_adv_sync_handle_t */
    WICED_BT_BLE_ADV_SET_TERMINATED_EVENT,              /**< Advertising set terminated becaue either connection being created or adv timeout. Event data: wiced_bt_ble_ext_adv_set_terminated_event_data_t */
    WICED_BT_BLE_SCAN_REQUEST_RECEIVED_EVENT,           /**< scan request received event. Event data: wiced_bt_ble_scan_req_received_event_data_t */
    WICED_BT_BLE_CHANNEL_SEL_ALGO_EVENT,                /**< LE Channel selected algorithm event. Event Data: wiced_bt_ble_channel_sel_algo_event_data_t */
    WICED_BT_BLE_BIGINFO_ADV_REPORT_EVENT,              /**< BIGInfo adv report event. Event Data: wiced_bt_ble_biginfo_adv_report_t */
    WICED_BT_BLE_PERIODIC_ADV_SYNC_TRANSFER_EVENT,      /**< Periodic Adv Sync Transfer Event. Event Data: wiced_bt_ble_periodic_adv_sync_transfer_event_data_t */
	/* @cond PAWR_API
	APIs for Periodic Advertising with Response*/
    WICED_BT_BLE_PAWR_SYNC_ESTABLISHED_EVENT,           /**< Periodic Adv Sync Transfer Event. Event Data: wiced_bt_ble_pawr_sync_established_event_data_t */
    WICED_BT_BLE_PAWR_SUBEVENT_DATA_REQ_EVENT,          /**< Periodic Adv Sync Transfer Event. Event Data: wiced_bt_ble_pawr_subevent_data_req_event_data_t */
    WICED_BT_BLE_PAWR_IND_REPORT_EVENT,                 /**< Periodic Adv Sync Transfer Event. Event Data: wiced_bt_ble_pawr_ind_report_event_data_t */
    WICED_BT_BLE_PAWR_RSP_REPORT_EVENT                  /**< Periodic Adv Sync Transfer Event. Event Data: wiced_bt_ble_pawr_rsp_report_event_data_t */
	/* @endcond */
} wiced_bt_ble_adv_ext_event_t;

/** union of events data */
typedef union
{
    wiced_bt_ble_periodic_adv_sync_established_event_data_t sync_establish;     /**< Data for WICED_BT_BLE_PERIODIC_ADV_SYNC_ESTABLISHED_EVENT*/
    wiced_bt_ble_periodic_adv_report_event_data_t           periodic_adv_report;/**< Data for WICED_BT_BLE_PERIODIC_ADV_REPORT_EVENT*/
    wiced_bt_ble_periodic_adv_sync_handle_t                 sync_handle;        /**< Data for WICED_BT_BLE_PERIODIC_ADV_SYNC_LOST_EVENT*/
    wiced_bt_ble_ext_adv_set_terminated_event_data_t        adv_set_terminated; /**< Data for WICED_BT_BLE_ADV_SET_TERMINATED_EVENT*/
    wiced_bt_ble_scan_req_received_event_data_t             scan_req_received;  /**< Data for WICED_BT_BLE_SCAN_REQUEST_RECEIVED_EVENT*/
    wiced_bt_ble_channel_sel_algo_event_data_t              channel_sel_algo;   /**< Data for WICED_BT_BLE_CHANNEL_SEL_ALGO_EVENT*/
    wiced_bt_ble_biginfo_adv_report_t                       biginfo_adv_report; /**< Data for WICED_BT_BLE_BIGINFO_ADV_REPORT_EVENT*/
    wiced_bt_ble_periodic_adv_sync_transfer_event_data_t    sync_transfer;      /**< Data for WICED_BT_BLE_PERIODIC_ADV_SYNC_TRANSFER_EVENT */
	/* @cond PAWR_API
	APIs for Periodic Advertising with Response*/
    wiced_bt_ble_pawr_sync_established_event_data_t         pawr_sync;          /**< Data for WICED_BT_BLE_PAWR_SYNC_ESTABLISHED_EVENT*/
    wiced_bt_ble_pawr_subevent_data_req_event_data_t        pawr_data_req;      /**< Data for WICED_BT_BLE_PAWR_SUBEVENT_DATA_REQ_EVENT*/
    wiced_bt_ble_pawr_ind_report_event_data_t               pawr_ind_report;    /**< Data for WICED_BT_BLE_PAWR_IND_REPORT_EVENT*/
    wiced_bt_ble_pawr_rsp_report_event_data_t               pawr_rsp_report;    /**< Data for WICED_BT_BLE_PAWR_RSP_REPORT_EVENT*/
	/* @endcond */
} wiced_bt_ble_adv_ext_event_data_t;

/** Configuration for extended scanning */
typedef struct
{
    wiced_bt_ble_ext_adv_phy_mask_t  scanning_phys;      /**< The Scanning_PHYs parameter indicates the PHY(s) on which the advertising
                                                                packets should be received on the primary advertising channel.*/

    uint8_t     enc_phy_scan_type;          /**< encoded phy scan type. (active or passive) */
    uint16_t    enc_phy_scan_int;           /**< encoded phy scan interval */
    uint16_t    enc_phy_scan_win;           /**< encoded phy scan window */

    /** When the Duration and Period parameters are non-zero, the Controller shall
    scan for the duration of the Duration parameter within a scan period specified
    by the Period parameter. After the scan period has expired, a new scan period
    shall begin and scanning shall begin again for the duration specified. The scan
    periods continue until the Host disables scanning. Duration parameter cannot be greater than or equal to the Period parameter
    If the Duration parameter is zero or both the Duration parameter and Period parameter are non-zero controller continue
    scanning until host disable scanning with enable set to false */
    uint16_t    duration;                   /**< Scan duration */
    uint16_t    period;                     /**< Scan period */
} wiced_bt_ble_ext_scan_config_t;

/**
 * Callback wiced_bt_ble_adv_ext_event_cb_fp_t
 *
 * Adv extension command status, command complete event and LE adv extension meta event callback
 *
 * @param event             : Event type (see #wiced_bt_ble_adv_ext_event_t)
 * @param p_data            : Event data (see #wiced_bt_ble_adv_ext_event_data_t)
 *
 * @return Nothing
 */
typedef void (*wiced_bt_ble_adv_ext_event_cb_fp_t) (wiced_bt_ble_adv_ext_event_t event, wiced_bt_ble_adv_ext_event_data_t *p_data);

/* @cond PAWR_API
   APIs for Periodic Advertising with Response*/
/** Configuration for Periodic Advertising with Response (PAWR) subevent indication data
**  which is sent by the central device at the start of each subevent
*/
typedef struct
{
    uint8_t     subevent_num;               /**< The subevent number */
    uint8_t     rsp_slot_start;             /**< Response slot start */
    uint8_t     rsp_slot_count;             /**< Response slot count */
    uint8_t     ind_data_length;            /**< Length of the subevent indication data  */
    uint8_t     ind_data[WICED_BT_MAX_PAWR_SUBEVENT_DATA_LEN]; /**< Subevent data  */
} wiced_bt_ble_pawr_subevent_ind_data_t;


/** Configuration for Periodic Advertising with Response (PAWR) response data*/
typedef struct
{
    uint16_t req_event;         /**< Request Event */
    uint8_t req_subevent;       /**< Request Subevent */
    int8_t rsp_subevent;        /**< Response Subevent */
    uint8_t rsp_slot;           /**< Response Slot */
    uint8_t rsp_data_len;       /**< Response data length */
    uint8_t *p_data;            /**< Response data  */
} wiced_bt_ble_pawr_subevent_rsp_data_t;


/** LE Set Periodic Advertising Parameter V2 command parameter */
typedef struct
{
    uint16_t    adv_int_min; /**< Minimum Periodic Advertising Interval  */
    uint16_t    adv_int_max; /**< Maximum Periodic Advertising Interval  */
    wiced_bt_ble_periodic_adv_prop_t adv_properties; /**< Advertising properties */
    uint8_t     subevent_num;               /**< Number of subevents*/
    uint8_t     subevent_interval;             /**< Interval between subevents */
    uint8_t     rsp_slot_delay;             /**< Response slot delay */
    uint8_t     rsp_slot_spacing;             /**< Response slot spacing */
    uint8_t     rsp_slot_num;            /**< Number of subevent response slots */
} wiced_bt_ble_periodic_adv_params_t;

/** @endcond */



/******************************************************
 *               Function Declarations
 *
 ******************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @if DUAL_MODE
 * @addtogroup  btm_ble_api_functions        LE (Bluetooth Low Energy)
 * @ingroup  wicedbt_DeviceManagement
 * This section describes the API's to use LE functionality such as advertisement, scanning
 * LE Connection, Data transfer, LE Security etc.
 * @else
 * @addtogroup  wicedbt_DeviceManagement   Device Management
 * This section consists of several management entities:
 *      1. Device Control - controls the local device
 *      2. Device Discovery - manages inquiries, discover database
 *      3. ACL Channels - manages LE ACL connections
 *      4. Security - manages all security functionality
 * @endif
 *
 *
 * @{
 */

/**
 * @addtogroup  btm_ble_adv_scan_functions        Advertisement & Scan
 * @ingroup     btm_ble_api_functions
 *
 * This section provides functions for LE advertisement and LE scan operations.
 *
 * @{
 */

/**
 * Start advertising.
 *
 * Use #wiced_bt_ble_set_raw_advertisement_data to configure advertising data
 * prior to starting advertisements. The advertisements are stopped upon successful LE connection establishment.
 *
 * @note <b>1</b>.Follow below steps for undirected ADVs viz., \ref BTM_BLE_ADVERT_UNDIRECTED_HIGH, \ref BTM_BLE_ADVERT_UNDIRECTED_LOW,
 * and non connectable ADVs viz., \ref BTM_BLE_ADVERT_NONCONN_HIGH, \ref BTM_BLE_ADVERT_NONCONN_LOW <br>
 <pre>
 *   a) Set the Advertisement data
 *   b) Set Scan Response data if advertisement type is scannable
 </pre>
 * @note <b>2</b>.If adv type is set to Directed then the stack resets any advertisement data which was set for an earlier advertisement.
 * To attempt an UNDIRECTED_ADV after a DIRECTED_ADV, refer to instructions in note 1.
 *
 * The <b>advert_mode</b> parameter determines what advertising parameters and durations
 * to use (as specified by the application configuration).
 *
 * @param[in]       advert_mode                         : Advertisement mode
 * @param[in]       directed_advertisement_bdaddr_type  : If using directed advertisements, \ref BLE_ADDR_PUBLIC or \ref BLE_ADDR_RANDOM, otherwise ignored
 * @param[in]       directed_advertisement_bdaddr_ptr   : Directed advertisement address (NULL if not using directed advertisement)
 *
 * @return      #wiced_result_t status
 *
 */
wiced_result_t wiced_bt_start_advertisements(wiced_bt_ble_advert_mode_t advert_mode, wiced_bt_ble_address_type_t directed_advertisement_bdaddr_type, wiced_bt_device_address_ptr_t directed_advertisement_bdaddr_ptr);

/**
 *
 * Get current advertising mode
 *
 * @return          Current advertising mode (refer #wiced_bt_ble_advert_mode_e)
 *
 */
wiced_bt_ble_advert_mode_t wiced_bt_ble_get_current_advert_mode(void);

/**
 * Set advertisement raw data to the controller. Application can invoke #wiced_bt_start_advertisements
 * after setting the advertising data. Max length of the advertising data to be set is 31 bytes.
 * API returns an error if the length of data being set exceeds 31 bytes
 *
 * @param[in] num_elem :   Number of ADV data element
 * @param[in] p_data :     Advertisement raw data
 *
 * @return         \ref wiced_result_t
 *
 */
wiced_result_t wiced_bt_ble_set_raw_advertisement_data(uint8_t num_elem, wiced_bt_ble_advert_elem_t *p_data);

/**
 * Create advertisement raw data in application buffer for setting the advertising data using API #wiced_bt_ble_set_raw_advertisement_data.
 *
 * @note This API does not write data to the controller
 *
 * @param[in] p_adv : Buffer pointer at which the raw data in \p p_type_data is to be written
 * @param[in] adv_len : Length of the buffer pointer pointed to by \p p_adv, should be atleast (2 + \p type_len)
 *                     for a successful write operation
 * @param[in] adv_type : Adveritsement type
 * @param[in] p_type_data : Advertisement data of \p adv_type
 * @param[in] type_len : Length of advertisement data at \p p_type_data of \p adv_type
 *
 * @return  Length of the \p p_adv buffer written.
 *
 */
int wiced_bt_ble_build_raw_advertisement_data(uint8_t *p_adv,
                                              int adv_len,
                                              wiced_bt_ble_advert_type_t adv_type,
                                              uint8_t *p_type_data,
                                              uint16_t type_len);

/**
 * Parse advertising data (returned from scan results callback #wiced_bt_ble_scan_result_cback_t).
 * @note Specified advertisement data type \p type can be searched using this API.
 *
 * @param[in]       p_adv       : Pointer to received advertisement data
 * @param[in]       type        : Advertisement data type to look for
 * @param[out]      p_length    : Length of advertisement data (if found)
 *
 * @return          Pointer to start of requested advertisement data (if found). NULL if requested data type is not found.
 *
 */
uint8_t *wiced_bt_ble_check_advertising_data( uint8_t *p_adv, wiced_bt_ble_advert_type_t type, uint8_t *p_length);

/**
 * When multiple entry for same adv type is available in the advertising data this API will help to get next entry of specified advertisement data type
 * when there is a single instance use #wiced_bt_ble_check_advertising_data
 *
 * @param[in]       p_adv       : Pointer to advertisement data
 * @param[in]       p_offset    : Offset from the start of the adv data recevied, also returns next offset to start searching from
 * @param[in]       type        : Advertisement data type to look for
 * @param[out]      p_length    : Length of advertisement data (if found)
 *
 * @return          Pointer to next requested advertisement data (if found). NULL if requested data type not found.
 *
 */
uint8_t *wiced_bt_ble_get_next_adv_entry(uint8_t *p_adv,
                                         int *p_offset,
                                         wiced_bt_ble_advert_type_t type,
                                         uint8_t *p_length);
 /**
 *
 * Update the filter policy of advertiser.
 *
 *  @param[in]      advertising_policy : Advertising Filter Policy
 *
 *  @return         <b>WICED_TRUE</b> : if command is successfully sent to the controller \n
 *                   <b> WICED_FALSE </b>  Otherwise.
 */
wiced_bool_t wiced_btm_ble_update_advertisement_filter_policy(wiced_bt_ble_advert_filter_policy_t advertising_policy);

/**
 *
 * Set the scan response raw data
 *
 * @param[in] num_elem :   Number of scan response data elements
 * @param[in] p_data :     Scan response raw data
 *
 * @return          #wiced_bt_dev_status_t status of the operation.
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_raw_scan_response_data(uint8_t num_elem,
                                                        wiced_bt_ble_advert_elem_t *p_data);

/**
 *
 * This function makes the device start or stop operating in the observer role.The observer role device receives advertising events from a broadcast device.
 *
 * @note This API uses following parameters from the configuration settings \ref wiced_bt_cfg_ble_t.p_ble_scan_cfg, \n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.low_duty_scan_interval,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.low_duty_scan_window, \n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.scan_mode, \n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.scan_mode
 *
 *
 *
 * @param[in] start :               TRUE to start the scanning
 * @param[in] duration :            The time duration in seconds for scanning
 * @param[in] p_scan_result_cback : Scan result callback
 *
 * @return          #wiced_bt_dev_status_t Status of the operation
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_observe (wiced_bool_t start, uint8_t duration, wiced_bt_ble_scan_result_cback_t *p_scan_result_cback);

/**
 * Start LE scanning
 *
 * The <b>scan_type</b> parameter determines what scanning parameters and durations
 *                  to use (as specified by the application configuration).
 *
 *                  Scan results are notified using \p p_scan_result_cback
 *
 * @note This API uses following parameters from the configuration settings of \ref wiced_bt_cfg_ble_t.p_ble_scan_cfg,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.high_duty_scan_interval,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.high_duty_scan_window,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.high_duty_scan_duration,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.low_duty_scan_interval,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.low_duty_scan_window,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.low_duty_scan_duration,\n
 *       \ref wiced_bt_cfg_ble_scan_settings_t.scan_mode \n
 *
 *
 * @param[in]       scan_type : select one of the \p scan_type #wiced_bt_ble_scan_type_e to configure the scan parameters.
 * @param[in]       duplicate_filter_enable : TRUE or FALSE to enable or disable duplicate filtering
 *
 * @param[in]       p_scan_result_cback : Scan result callback
 *
 * @return          #wiced_result_t \n
 *
 * <b> WICED_BT_PENDING </b>        : if successfully initiated \n
 * <b> WICED_BT_BUSY </b>           : if already in progress \n
 * <b> WICED_BT_ILLEGAL_VALUE </b>  : if parameter(s) are out of range \n
 * <b> WICED_BT_NO_RESOURCES </b>   : if could not allocate resources to start the command \n
 * <b> WICED_BT_WRONG_MODE </b>     : if the device is not up.
 */
wiced_result_t  wiced_bt_ble_scan (wiced_bt_ble_scan_type_t scan_type, wiced_bool_t duplicate_filter_enable, wiced_bt_ble_scan_result_cback_t *p_scan_result_cback);

/**
 *
 * Get current scanning state
 *
 * @return          #wiced_bt_ble_scan_type_t \n
 *
 * <b> BTM_BLE_SCAN_TYPE_NONE </b>        : Not scanning \n
 * <b> BTM_BLE_SCAN_TYPE_HIGH_DUTY </b>   : High duty cycle scan \n
 * <b> BTM_BLE_SCAN_TYPE_LOW_DUTY </b>    : Low duty cycle scan
 */
wiced_bt_ble_scan_type_t wiced_bt_ble_get_current_scan_state(void);

/**
 *
 * Update the Scanning Filter Policy of the scanner. This API updates the Scanning Filter Policy in scan parameter command.
 *
 *  @param[in]      scanner_policy : Scanning Filter Policy
 *
 *  @return         void
 */
void wiced_bt_ble_update_scanner_filter_policy(wiced_bt_ble_scanner_filter_policy_t scanner_policy);

/**@} btm_ble_adv_scan_functions */

/**
 *
 * @addtogroup  tx_power_settings
 *
 * @{
 */
/**
*  Command to set LE Advertisement Transmit power.
* This API helps to set Tx power of <b> Legacy advertisement </b>. \n
* This API should not be used for setting Tx power during Extended advertisement. Instead #wiced_bt_ble_set_ext_adv_parameters_v2() should be used.
*
* @param[in]       power          :  power value in db
* @param[in]       p_cb           :  Result callback (pointer to #wiced_bt_set_adv_tx_power_result_t will be passed as \ref wiced_bt_dev_vendor_specific_command_complete_params_t.p_param_buf)
*
* @return          #wiced_result_t \n
*                  <b> WICED_BT_PENDING </b> : if \p p_cb is not NULL \n
*                  <b> WICED_BT_SUCCESS </b> : if \p p_cb is NULL \n
*
*
**/
wiced_result_t wiced_bt_ble_set_adv_tx_power(int8_t power, wiced_bt_dev_vendor_specific_command_complete_cback_t *p_cb);

/**
* Read LE Advertisement transmit power.
* This API sends HCI_LE_Read_Advertising_Channel_Tx_Power command to controller.
* @note This API can be used to get Tx power for Legacy advertisements. \n
*        It will return an error if the application is using Extended Advertisements. \n
*        See Bluetool Core spec 5.2, Vol 4, Part E, section 3.1.1 Legacy and Extended advertising
*
* @param[in]       p_cback         : Result callback (pointer to #wiced_bt_tx_power_result_t will be passed to \p p_cback)
*
* @return          #wiced_result_t \n
*                  <b> WICED_BT_PENDING </b> : if command issued to controller. \n
*                  <b> WICED_BT_NO_RESOURCES </b> : if couldn't allocate memory to issue command \n
*                  <b> WICED_BT_BUSY </b> : if command is already in progress \n
*                  <b> WICED_BT_ILLEGAL_VALUE </b> : if \p p_cback is NULL \n
*/
wiced_result_t wiced_bt_ble_read_adv_tx_power(wiced_bt_dev_cmpl_cback_t *p_cback);
/**@} tx_power_settings */

/**
 * @addtogroup  btm_ble_conn_filter_accept_list_functions        Connection and Filter Accept List
 * @ingroup     btm_ble_api_functions
 *
 * This section provides functions related to LE connection and Filter Accept List operations.
 *
 * @{
 */

/**
 *
 * Set LE background connection procedure type.
 *
 * @param[in]       conn_type     : #BTM_BLE_CONN_NONE or #BTM_BLE_CONN_AUTO
 * @param[in]       p_select_cback: UNUSED
 *
 * @return           <b> WICED_TRUE </b>   If background connection set \n
 *                   <b> WICED_FALSE </b>  Otherwise.
 *
 */
wiced_bool_t wiced_bt_ble_set_background_connection_type (wiced_bt_ble_conn_type_t conn_type, void *p_select_cback);

/**
 *
 * This function is called to add or remove a device into/from the
 * filter list. The background connection procedure is decided by
 * the background connection type, it can be auto connection, or none.
 *
 * @param[in]       add_remove    : TRUE to add; FALSE to remove.
 * @param[in]       remote_bda    : Bluetooth address of the device to be added/removed.
 * @param[in]       ble_addr_type : Address type (see @ref WICED_BT_ADDR_TYPE "Bluetooth Address Types")

 * @return          <b> WICED_TRUE </b> if successful \n
 *                  <b> WICED_FALSE </b> Otherwise
 *
 */
wiced_bool_t wiced_bt_ble_update_background_connection_device(wiced_bool_t add_remove, wiced_bt_device_address_t remote_bda, wiced_bt_ble_address_type_t ble_addr_type);

/**
 * API to read connection parameters using bluetooth address of the remote device.The \p remote_bda is received via #GATT_CONNECTION_STATUS_EVT \n
 * in the call back function registered using API #wiced_bt_gatt_register.
 *
 *@note The ACL connection corresponding to provided \p remote_bda should be active in order for this API to succeed.
 *
 * @param[in]       remote_bda          : Bluetooth address of the remote device
 * @param[out]      p_conn_parameters   : Pointer to Connection Parameters
 *
 * @return          #wiced_result_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : if p_conn_parameters is NULL. \n
 * <b> WICED_BT_UNKNOWN_ADDR </b>  : if device address is bad. \n
 * <b> WICED_BT_SUCCESS </b> otherwise.
 *
 */
wiced_result_t wiced_bt_ble_get_connection_parameters(wiced_bt_device_address_t remote_bda, wiced_bt_ble_conn_params_t *p_conn_parameters);

/**
 *
 * API to add or remove a device from Advertising Filter Accept List. This API is used by the application to allow scan or connect request only from the devices those are added in the Advertising Filter Accept List
 *@note This API sends <b> HCI_LE_Add_Device_To_Filter_Accept_List </b> or <b> HCI_LE_Remove_Device_From_Filter_Accept_List </b> to controller.
 *
 * @param[in]       add         : TRUE to add; FALSE to remove
 * @param[in]       addr_type   : The Remote device address type (see @ref WICED_BT_ADDR_TYPE "Bluetooth Address Types")
 * @param[in]       remote_bda  : Bluetooth address of remote device
 *
 * @return          <b> WICED_TRUE </b> if successful \n
 *                  <b> WICED_FALSE </b> Otherwise.
 *
 */
wiced_bool_t wiced_bt_ble_update_advertising_filter_accept_list(wiced_bool_t add, wiced_bt_ble_address_type_t addr_type, wiced_bt_device_address_t remote_bda);

/**
 *
 * API to add or remove a device from Scanner Filter Accept List.This API is used by the application to allow scan result and scan response only from the devices those are added in the Scanning Filter Accept List
 *@note This API sends  <b> HCI_LE_Add_Device_To_Filter_Accept_List </b> or <b> HCI_LE_Remove_Device_From_Filter_Accept_List </b> to controller.
 *
 * @param[in]       add        : TRUE to add; FALSE to remove
 * @param[in]       remote_bda : Bluetooth address of remote device
 * @param[in]       addr_type  : The Remote device address type (see @ref WICED_BT_ADDR_TYPE "Bluetooth Address Types")
 *
 * @return          <b> WICED_TRUE </b> if successful \n
 *                  <b> WICED_FALSE </b> Otherwise.
 *
 */
wiced_bool_t wiced_bt_ble_update_scanner_filter_list(wiced_bool_t add, wiced_bt_device_address_t remote_bda,  wiced_bt_ble_address_type_t addr_type);

/**
 *
 * API to clear the Filter Accept List stored in controller
 *
 * @note This API sends  <b> HCI_LE_Clear_Filter_Accept_List </b> to controller.
 *
 * @return          <b> WICED_TRUE </b> if request of clear is sent to controller \n
 *                  <b> WICED_FALSE </b> Otherwise.
 *
 */
wiced_bool_t wiced_bt_ble_clear_filter_accept_list(void);

/**
 *
 * API to get the number of Filter Accept List entries in the controller
 *
 *
 * @return          number of entries in Filter Accept List in controller
 *
 */
uint8_t wiced_bt_ble_get_filter_accept_list_size(void);

/**
 * This API allows to suggest maximum transmission payload size (typically called GATT MTU) and maximum packet transmission time
 * to be used for LL DATA PDUs on a given connection. Controller may use smaller or larger values.
 *
 * @param[in]       bd_addr  : Bluetooth address for which the LL Data PDU needs to be set
 * @param[in]       tx_pdu_length : Preferred maximum number of payload octets (typically called GATT MTU) to be used in a single packet on this connection. \n
 *                                  AIROC Bluetooth Host Stack adds 4 bytes of L2CAP header to \p tx_pdu_length. Valid range of LL Data PDU is 27 (0x001B) to 251 (0x00FB). \n
 *                                  Hence valid range of \p tx_pdu_length is 23 to 247.
 * @param[in]       tx_time :  Preferred maximum number of microseconds that the controller should take to transmit a single packet on this connection (valid range is 0x0148 to 0x4290)
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_SUCCESS </b>       : If  command sent successfully. \n
 * <b> WICED_BT_ERROR </b>         : If there is no connection exists. \n
 * <b> WICED_BT_WRONG_MODE </b>    : If command not supported. \n
 *
 *  @note This API sends <b> HCI_LE_Set_Data_Length </b> command to controller. \n
 *  If \p tx_time = 0, then a default maximum value is assigned to \p tx_time based on controller HCI version.
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_data_packet_length(wiced_bt_device_address_t bd_addr, uint16_t tx_pdu_length, uint16_t tx_time);


/**@} btm_ble_conn_filter_accept_list_functions */

/**
 * @addtogroup  btm_ble_phy_functions        PHY
 * @ingroup     btm_ble_api_functions
 *
 * This section provides functionality to read and update PHY. \n
 * PHY refers to the physical layer radio specifications that govern the operation of the Bluetooth LE Radio.
 *
 * @{
 */

/**
 * Host to read the current transmitter PHY and receiver PHY on the connection identified by the \p remote bd_addr.
 * PHY results are notified using #wiced_bt_ble_read_phy_complete_callback_t callback. \n
 * This API sends <b> HCI_LE_Read_PHY </b> command to controller.
 *
 * @param[in]       remote_bd_addr                   - Bluetooth address of remote device
 * @param[in]       p_read_phy_complete_callback     - Read phy complete callback
 *
 * @return          #wiced_result_t \n
 *
 * <b> WICED_BT_SUCCESS </b>        : if the request was successfully sent to HCI. \n
 * <b> WICED_BT_UNKNOWN_ADDR </b>   : if \p remote_bd_addr does not correspond to a connected remote device \n
 * <b> WICED_BT_ILLEGAL_VALUE </b>  : if \p p_read_phy_complete_callback is NULL \n
 * <b> WICED_BT_NO_RESOURCES </b>   : if could not allocate resources to start the command
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_read_phy (wiced_bt_device_address_t remote_bd_addr,
                        wiced_bt_ble_read_phy_complete_callback_t *p_read_phy_complete_callback);

/**
 * Host to configure default transmitter PHY and receiver PHY to
 * be used for all subsequent connections over the LE transport.
 * This API sends <b> HCI_LE_Set_Default_PHY </b> command to Controller.
 *
 * @param[in]       phy_preferences      - Phy preferences #wiced_bt_ble_phy_preferences_t
 *
 * Note : \ref wiced_bt_ble_phy_preferences_t.remote_bd_addr field of the \p phy_preferences is ignored.
 *
 * @return          #wiced_result_t \n
 *
 * <b> WICED_BT_SUCCESS </b>        : if the request was successfully sent to HCI. \n
 * <b> WICED_BT_ILLEGAL_VALUE </b>  : if \p phy_preferences is NULL \n
 * <b> WICED_BT_NO_RESOURCES </b>   : if could not allocate resources to start the command
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_default_phy (wiced_bt_ble_phy_preferences_t *phy_preferences);

/**
 * Host to configure the LE link either to 1M or 2M or to LE coded PHY.
 * This API sends <b> HCI_LE_Set_PHY </b> command to set the PHY preference for the connection identified by
 * \ref wiced_bt_ble_phy_preferences_t.remote_bd_addr field of \p phy_preferences. \n
 * The PHY preferences provided by this API, override those provided via  #wiced_bt_ble_set_default_phy() or any preferences previously set using this
 * API itself on the same connection. \n
 *
 * @param[in]       phy_preferences      - Phy preferences #wiced_bt_ble_phy_preferences_t
 *
 * @return          #wiced_result_t \n
 *
 * <b> WICED_BT_SUCCESS </b>        : if the request was successfully sent to HCI. \n
 * <b> WICED_BT_ILLEGAL_VALUE </b>  : if \p phy_preferences is NULL \n
 * <b> WICED_BT_UNKNOWN_ADDR </b>   : if device address does not correspond to a connected remote device \n
 * <b> WICED_BT_NO_RESOURCES </b>   : if could not allocate resources to start the command
 *
 */
wiced_result_t wiced_bt_ble_set_phy (wiced_bt_ble_phy_preferences_t *phy_preferences);

/**
 * Set Host channel classification for the available 37 channels.
 * This API sends <b> HCI_LE_Set_Host_Channel_Classification </b> command to specify a channel classification
 * for the data, secondary advertising, periodic, isochronous physical channels based on its "local
 * information". \n
 *
 * Only 37 bits (0 to 36) of \p ble_channel_map are meaningful. The nth such field (in the range of 0 to 36)
 * contains the value for the Link Layer channel index n. \n
 *
 * Channel n is bad = 0. \n
 * Channel n is unknown = 1. \n
 *
 * At least one channel shall be marked as unknown.
 *
 * @param[in]       ble_channel_map
 *
 * @return          #wiced_result_t \n
 *
 * <b> WICED_BT_SUCCESS </b>      :  If successfully initiated \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If could not allocate resources to start the command
 */
wiced_result_t wiced_bt_ble_set_channel_classification(const wiced_bt_ble_chnl_map_t ble_channel_map);
/**@} btm_ble_phy_functions */

/**
 * @addtogroup  btm_ble_multi_adv_functions        MultiAdv
 * @ingroup     btm_ble_api_functions
 *
 * This section describes Multiple Advertisement API, using this interface application can enable more than one advertisement train.
 * @note Controller should have support for this feature.
 *
 * @{
 */

/**
 * Start or Stop Multi advertisements.
 * wiced_start_multi_advertisements gives option to start multiple adverstisment instances
 * Each of the instances can set different #wiced_set_multi_advertisement_params and #wiced_set_multi_advertisement_data.
 * Hence this feature allows the device to advertise to multiple Centrals at the same time like a multiple peripheral device,
 * with different advertising data, Random private addresses, tx_power etc.
 *
 * @param[in]       advertising_enable :
 * <pre>#MULTI_ADVERT_START  - Advertising is enabled
 * #MULTI_ADVERT_STOP   - Advertising is disabled </pre>
 *
 * @param[in]       adv_instance       : 1 to #MULTI_ADV_MAX_NUM_INSTANCES
 *
 * @return          #wiced_bt_dev_status_t \n
 *                  <b> WICED_BT_SUCCESS </b> : If command succeeded \n
 *                  <b> WICED_BT_PENDING </b>   : If command queued to send down \n
 *                  <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 */
 wiced_bt_dev_status_t wiced_start_multi_advertisements( uint8_t advertising_enable, uint8_t adv_instance );

/**
 * Set multi advertisement data for each adv_instance
 *
 *
 * @param[in]       p_data        : Advertising Data ( Max length 31 bytess)
 * @param[in]       data_len      : Advertising Data len ( Max 31 bytes )
 * @param[in]       adv_instance  : 1 to #MULTI_ADV_MAX_NUM_INSTANCES
 *
 * @return          #wiced_bt_dev_status_t \n
 *                  <b> WICED_BT_ILLEGAL_VALUE </b>  : If parameter is invalid \n
 *                  <b> WICED_BT_NO_RESOURCES </b>    : If no memory to issue the command \n
 *                  <b> WICED_BT_SUCCESS </b>     : If command started \n
 *                  <b> WICED_BT_PENDING </b>     :  If command queued to send down \n
 */
wiced_bt_dev_status_t wiced_set_multi_advertisement_data( uint8_t * p_data, uint8_t data_len, uint8_t adv_instance );

/**
 * Set multi advertisement params for each adv_instance
 *
 *
 * @param[in]       adv_instance  : 1 to #MULTI_ADV_MAX_NUM_INSTANCES
 * @param[in]       params        : Advertising params refer #wiced_bt_ble_multi_adv_params_t
 *
 * @return          #wiced_bt_dev_status_t \n
 *                  <b> WICED_BT_ILLEGAL_VALUE </b>  : If parameter is invalid \n
 *                  <b> WICED_BT_NO_RESOURCES </b>    : If no memory to issue the command \n
 *                  <b> WICED_BT_SUCCESS </b>     : If command started \n
 *                  <b> WICED_BT_PENDING </b>     :  If command queued to send down \n
 *
 */

wiced_bt_dev_status_t wiced_set_multi_advertisement_params(uint8_t adv_instance, wiced_bt_ble_multi_adv_params_t *params);


/**
 * Set multi advertisement data for scan response
 *
 * @param[in]       p_data        : Advertising Data ( Max length 31 bytess)
 * @param[in]       data_len      : Advertising Data Len ( Max 31 bytes )
 * @param[in]       adv_instance  : 1 to #MULTI_ADV_MAX_NUM_INSTANCES
 *
 * @return          #wiced_bt_dev_status_t \n
 *                  <b> WICED_BT_ILLEGAL_VALUE </b>  : If parameter is invalid \n
 *                  <b> WICED_BT_NO_RESOURCES </b>    : If no memory to issue the command \n
 *                  <b> WICED_BT_SUCCESS </b>     : If command started \n
 *                  <b> WICED_BT_PENDING </b>     :  If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_set_multi_advertisement_scan_response_data( uint8_t * p_data, uint8_t data_len, uint8_t adv_instance );

/**
 * Set multi advertisement random address for an instance
 *
 *
 * @param[in]       randomAddr    : own random address
 * @param[in]       adv_instance  : 1 to #MULTI_ADV_MAX_NUM_INSTANCES
 *
 * @return          wiced_bt_dev_status_t \n
 *                  <b> WICED_BT_ILLEGAL_VALUE </b>  : If parameter is invalid \n
 *                  <b> WICED_BT_NO_RESOURCES </b>    : If no memory to issue the command \n
 *                  <b> WICED_BT_SUCCESS </b>     : If command started \n
 *                  <b> WICED_BT_PENDING </b>     :  If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_set_multi_advertisements_random_address( wiced_bt_device_address_t randomAddr, uint8_t adv_instance );

/**
 * Allows the application to register a callback that will be invoked
 * just before an ADV packet is about to be sent out and immediately after.
 *
 * @param[in]       adv_instance                : 1 to #MULTI_ADV_MAX_NUM_INSTANCES
 * @param[in]       clientCallback              : Pointer to a function that will be invoked in application thread context
 *                  with WICED_BT_ADV_NOTIFICATION_READY for before ADV and WICED_BT_ADV_NOTIFICATION_DONE after ADV packet is complete.
 * @param[in]       advanceNoticeInMicroSeconds : Number of microseconds before the ADV the notification is to be sent. Will be rounded down to
 *                  the nearest 1.25mS. Has to be an even multiple of 625uS.
 *
 * @return          wiced_bool_t \n
 *                 <b> WICED_TRUE </b> if command succeeded
 *                 <b> WICED_FALSE </b> Otherwise.
 */
wiced_bool_t wiced_bt_notify_multi_advertisement_packet_transmissions( uint8_t adv_instance, void (*clientCallback)( uint32_t ),
                                                                       uint32_t advanceNoticeInMicroSeconds );

/**@} btm_ble_multi_adv_functions */

/**
 * @addtogroup     btm_ble_sec_api_functions
 * @ingroup     btm_ble_api_functions
 *
 * @{
 */

/**
 *
 * API to grant or deny security access. Used in response to #BTM_SECURITY_REQUEST_EVT event. This event is received in the \ref wiced_bt_management_cback_t registered via #wiced_bt_stack_init.
 *
 * @param[in]       bd_addr     : Bluetooth address of remote device
 * @param[in]       res         : <b> WICED_BT_SUCCESS </b> : To grant access.\n
                                  <b> WICED_BT_UNSUPPORTED </b> : If local device does not allow pairing.\n
                                  <b> WICED_BT_REPEATED_ATTEMPTS </b> : Otherwise \n
 *
 * @return          <b> None </b>
 *
 */
void wiced_bt_ble_security_grant(wiced_bt_device_address_t bd_addr, wiced_bt_dev_status_t res);

/**
 * API to sign the data using AES128 CMAC algorithm.
 *
 * @param[in]       bd_addr: Bluetooth address of peer device, the data to be signed for.
 * @param[in]       p_text: Pointer to the data to be signed
 * @param[in]       len: Length of the data to be signed
 * @param[out]      signature: Output parameter where data signature is going to be stored (refer #wiced_dev_ble_signature_t)
 *
 * @return          #WICED_TRUE if signing successful, otherwise #WICED_FALSE.
 *
 */
wiced_bool_t wiced_bt_ble_data_signature(wiced_bt_device_address_t bd_addr,
                                         uint8_t *p_text,
                                         uint16_t len,
                                         wiced_dev_ble_signature_t signature);

/**
 * Verify the data signature using AES128 CMAC algorithm.
 *
 * @param[in]       bd_addr: Bluetooth address of the peer device, the data to be signed for.
 * @param[in]       p_orig:  Pointer to Original data before signature.
 * @param[in]       len: Length of the signing data
 * @param[in]       counter: Counter used when doing data signing
 * @param[in]       p_comp: Pointer to the Signature to be compared against.
 *
 * @return          #WICED_TRUE if signature verified correctly; otherwise #WICED_FALSE.
 *
 */
wiced_bool_t wiced_bt_ble_verify_signature(wiced_bt_device_address_t bd_addr,
                                           uint8_t *p_orig,
                                           uint16_t len,
                                           uint32_t counter,
                                           uint8_t *p_comp);

/**
 * Get security mode 1 flags and encryption key size for LE peer device.
 *
 * @param[in]       bd_addr         : Bluetooth address of peer address
 * @param[out]      p_le_sec_flags  : Pointer to security flags (see #wiced_bt_ble_sec_flags_e)
 * @param[out]      p_le_key_size   : Pointer to size of encryption key
 *
 * @return          #TRUE if successful, #FALSE if otherwise
 *
 */
wiced_bool_t wiced_bt_ble_get_security_state(wiced_bt_device_address_t bd_addr,
                                             uint8_t *p_le_sec_flags,
                                             uint8_t *p_le_key_size);

/**
 * API to update privacy mode if remote device is already available in controller resolving list
 *
 * @param[in]       remote_bda      : Bluetooth address of remote device received during connection up
 * @param[in]       rem_bda_type    : Address type of remote device received during connection up (see @ref WICED_BT_ADDR_TYPE "Bluetooth Address Types")
 * @param[in]       privacy_mode    : Privacy mode (see #wiced_bt_ble_privacy_mode_t)
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_ILLEGAL_VALUE </b>  : if parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>    : if command not supported \n
 * <b> WICED_BT_UNKNOWN_ADDR </b>   : if bd_addr is wrong \n
 * <b> WICED_BT_ILLEGAL_ACTION </b> : if device not added to resolving list or peer irk is not valid \n
 * <b> WICED_BT_ERROR </b>      : error while processing the command \n
 * <b> WICED_BT_SUCCESS</b>     : if command started
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_privacy_mode(wiced_bt_device_address_t remote_bda,
                                                    wiced_bt_ble_address_type_t rem_bda_type,
                                                    wiced_bt_ble_privacy_mode_t privacy_mode);

/**
 * Get the configured local random device address.
 *
 * @note Random address depends on below settings in that priority order. \n
 *      1) Global privacy configuration using \ref wiced_bt_cfg_ble_t.rpa_refresh_timeout (see #wiced_bt_cfg_settings_t). \n
 *      2) else, configured for static random bd_address while downloading using BT_DEVICE_ADDRESS=random build setting.
 *
 * @param[out]       random_bd_addr     : device random bluetooth address
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_SUCCESS </b> : if random address is configured.\n
 * <b> WICED_BT_WRONG_MODE </b> : if random address not configured.\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_read_device_random_address(wiced_bt_device_address_t random_bd_addr);

/**
*
* This API is called by the application to request for notification on change in device address.
* Application receives #BTM_BLE_DEVICE_ADDRESS_UPDATE_EVENT event in the \ref wiced_bt_management_cback_t which is registered via #wiced_bt_stack_init.
*
* @param[in] enable  : Enable change of address notification
*
* @return #wiced_bt_dev_status_t \n
* <b> WICED_BT_SUCCESS </b> : if Enabled.\n
* <b> WICED_NOT_AVAILABLE </b> : Otherwise.\n
*/
wiced_bt_dev_status_t wiced_bt_ble_notify_on_device_address_change(wiced_bool_t enable);

/**@} btm_ble_sec_api_functions */


/**
 * @addtogroup  btm_ble_adv_scan_functions        Advertisement & Scan
 * @ingroup     btm_ble_api_functions
 *
 * @{
 */
/**
 * Check if the local Bluetooth controller supports extended advertising
 *
 * @return          #wiced_bool_t, TRUE if extended advertising is supported, Otherwise FALSE.
 *
 */
wiced_bool_t wiced_bt_ble_is_ext_adv_supported(void);

/**
 * Check if the local Bluetooth controller supports periodic advertising
 *
 * @return          #wiced_bool_t, TRUE if periodic advertising is supported, Otherwise FALSE.
 *
 */
wiced_bool_t wiced_bt_ble_is_periodic_adv_supported(void);

/**
 * Sends HCI command to set the random address for an advertising set
 *
 * @param[in]       adv_handle  : Handle of the advertising set
 * @param[in]       random_addr : Random address to use for this set
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_SUCCESS </b>       : If random addr is set successfully\n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_ext_adv_random_address(wiced_bt_ble_ext_adv_handle_t adv_handle,
                                                              wiced_bt_device_address_t random_addr);

/**
 * Sends the HCI command HCI_LE_Set_Extended_Advertising_Parameters [v1] to set the parameters for extended advertisement
 *
 *@note This API sends the V2 command if controller supports it.
 *
 * @param[in]        adv_handle                  : Advertisement set handle
 * @param[in]        event_properties            : Bit mask to speicify connectable,scannable,low duty,high duty,directed,legacy adv
 * @param[in]        primary_adv_int_min         : Range: 0x000020 to 0xFFFFFF (20 ms to 10,485.759375 s)
 * @param[in]        primary_adv_int_max         : Range: 0x000020 to 0xFFFFFF(20 ms to 10,485.759375 s)
 * @param[in]        primary_adv_channel_map     : LE advertisement channel map (see #wiced_bt_ble_advert_chnl_map_e)
 * @param[in]        own_addr_type               : Ignored in case of anonymous adv. See event_properties
 * @param[in]        peer_addr_type              : Peer device address type
 * @param[in]        peer_addr                   : Peer device address
 * @param[in]        adv_filter_policy           : Advertising filter policy
 * @param[in]        adv_tx_power                : -127 to +126. 127 means host has no preference
 * @param[in]        primary_adv_phy             : Phy used to transmit ADV packets on Primary ADV channels
 * @param[in]        secondary_adv_max_skip      : Valid only in case of extended ADV. Range 0 to 0xFF.
                                                                                         Maximum advertising events controller can skip before sending
                                                                                         auxiliary adv packets on the secondary adv channel
 * @param[in]        secondary_adv_phy           : Phy used to transmit ADV packets on secondary ADV channels. Valid only in case of extended ADV
 * @param[in]        adv_sid                     : Advertisement set identifier is the value to be transmitted in extended ADV PDUs

 * @param[in]        scan_request_not            : Enable or Disable Scan request received notification

 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_SUCCESS </b>       : If all extended adv params are set successfully\n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_ext_adv_parameters(
    wiced_bt_ble_ext_adv_handle_t adv_handle,
    wiced_bt_ble_ext_adv_event_property_t event_properties,
    uint32_t primary_adv_int_min,
    uint32_t primary_adv_int_max,
    wiced_bt_ble_advert_chnl_map_t primary_adv_channel_map,
    wiced_bt_ble_address_type_t own_addr_type,
    wiced_bt_ble_address_type_t peer_addr_type,
    wiced_bt_device_address_t peer_addr,
    wiced_bt_ble_advert_filter_policy_t adv_filter_policy,
    int8_t adv_tx_power,
    wiced_bt_ble_ext_adv_phy_t primary_adv_phy,
    uint8_t secondary_adv_max_skip,
    wiced_bt_ble_ext_adv_phy_t secondary_adv_phy,
    wiced_bt_ble_ext_adv_sid_t adv_sid,
    wiced_bt_ble_ext_adv_scan_req_notification_setting_t scan_request_not);

/**
 * Sends the HCI command HCI_LE_Set_Extended_Advertising_Parameters [v2] to set the parameters for extended advetisement
 *
 * @param[in]        adv_handle : Advertisement set handle
 * @param[in]        p_params   : Extended advertisement parameters

 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_SUCCESS </b>       : If all extended advertisment params are set successfully\n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is not valid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_ext_adv_parameters_v2(wiced_bt_ble_ext_adv_handle_t adv_handle,
                                                             wiced_bt_ble_ext_adv_params_t *p_params);


/**
 * Sends HCI command to write the extended advertising data
 * @note This API allows sending data formatted with \ref wiced_bt_ble_build_raw_advertisement_data.
 * @note This API cannot be used for the advertising handle with the event_properties that doesn't support advertising data;
 * viz., #WICED_BT_BLE_EXT_ADV_EVENT_DIRECTED_ADV, #WICED_BT_BLE_EXT_ADV_EVENT_HIGH_DUTY_DIRECTED_CONNECTABLE_ADV
 *
 * @param[in]       adv_handle  : Handle of the advertising set
 * @param[in]       data_len    : Length of the advertising data to use for this set
 * @param[in]       p_data      : Pointer to the advertising data to use for this set
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_SUCCESS </b>       : If all extended adv data set successfully\n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_ext_adv_data(wiced_bt_ble_ext_adv_handle_t adv_handle,
    uint16_t data_len,
    uint8_t *p_data);

/**
 * Sends HCI command to write the legacy adv data
 * @note This API allows sending data formatted with \ref wiced_bt_ble_build_raw_advertisement_data.
 *
 * @param[in]       data_len : Length of the advertising data to use, max size 31 bytes
 * @param[in]       p_data   : Pointer to the advertising data to use
 *
 * @return          wiced_bt_dev_status_t \n
 * <b> WICED_BT_SUCCESS </b>       : If all extended advertising data set successfully\n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_legacy_adv_data(uint16_t data_len, uint8_t *p_data);

/**
 * Sends HCI command HCI_LE_Set_Extended_Scan_Response_Data to write the extended scan response data
 *
 * @param[in]       adv_handle  : Handle of the advertising set
 * @param[in]       data_len    : Length of the scan response data to use for this set
 * @param[in]       p_data      : Pointer to the scan response data to use for this set
 *
 * @return          #wiced_bt_dev_status_t
 *
 * <b> WICED_BT_SUCCESS </b>       : If all extended scan response data set successfully\n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_ext_scan_rsp_data(wiced_bt_ble_ext_adv_handle_t adv_handle,
                                                         uint16_t data_len,
                                                         uint8_t *p_data);

/**
 * Sends the HCI command HCI_LE_Set_Extended_Advertising_Enable to start or stop the extended advertisements
 *
 * @param[in]       enable    : True to enable, false to disable
 * @param[in]       num_sets  : Number of sets to enable, unused if disabling
 * @param[in]       p_dur     : Pointer to adv handle(s) and duration configuration
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_start_ext_adv(uint8_t enable,
                                                 uint8_t num_sets,
                                                 wiced_bt_ble_ext_adv_duration_config_t *p_dur);

/**
 * Sends the HCI command to remove an extended advertisement set (which is currently not advertising)
 *
 * @param[in]       adv_handle    : Handle to advertisement set
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_remove_adv_set(wiced_bt_ble_ext_adv_handle_t adv_handle);

/**
 * Sends the HCI command to remove all extended advertisement sets which are currently not advertising
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successfuly\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_clear_adv_sets(void);

/**
 * Read the number of ADV sets supported by the controller.
 *
 * @return       Number of supported extended Advertisment sets.
 *
 */
uint8_t wiced_bt_ble_read_num_ext_adv_sets(void);

/**
 * Read the maximum ADV data length supported by the controller.
 *
 * @return       Maximum Extended Advertisment data length set.
 *
 */
uint16_t wiced_bt_ble_read_max_ext_adv_data_len(void);

/**
 * Sends the HCI command HCI_LE_Set_Periodic_Advertising_Parameters[v1] to set the parameters for periodic advertising.
 *@note This API sends V2 command if controller supports it.
 *
 * @param[in]       adv_handle         :   Advertisement set handle
 * @param[in]       periodic_adv_int_min :  Range N: 0x0006 to 0xFFFF, Time = N * 1.25 ms
 * @param[in]       periodic_adv_int_max   : Range N: 0x0006 to 0xFFFF, Time = N * 1.25 ms
 * @param[in]       periodic_adv_properties  :  Periodic adv property indicates which field should be include in periodic adv
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_periodic_adv_params(wiced_bt_ble_ext_adv_handle_t adv_handle,
                                                           uint16_t periodic_adv_int_min,
                                                           uint16_t periodic_adv_int_max,
                                                           wiced_bt_ble_periodic_adv_prop_t periodic_adv_properties);

/**
 * Sends the HCI command HCI_LE_Set_Periodic_Advertising_Parameters[v2]
 * to set the parameters for periodic advertising
 *
 * @param[in]       adv_handle         :  Advertisement set handle
 * @param[in]       p_adv_params       :  Pointer to periodic advertising parameters
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_periodic_adv_params_v2(wiced_bt_ble_ext_adv_handle_t adv_handle,
                                                           wiced_bt_ble_periodic_adv_params_t  *p_adv_params);


/**
 * Sends the HCI command HCI_LE_Set_Periodic_Advertising_Data to write the periodic advertising data
 *
 * @param[in]    adv_handle       : Advertisement set handle
 * @param[in]    adv_data_length  : Periodic data length
 * @param[in]    p_adv_data       : Pointer to the periodic data
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_periodic_adv_data(wiced_bt_ble_ext_adv_handle_t adv_handle,
                                                         uint16_t adv_data_length,
                                                         uint8_t *p_adv_data);

/**
 * Sends the HCI command HCI_LE_Set_Periodic_Advertising_Enable to start/stop periodic advertisements

 * @param[in]       adv_handle  : Handle of the advertising set
 * @param[in]       enable      : True to enable, false to disable
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_start_periodic_adv(wiced_bt_ble_ext_adv_handle_t adv_handle, wiced_bool_t enable);

/**
 * Stores extended scan configuration to apply when API #wiced_bt_ble_observe is invoked
 *
 * @param[in]       p_ext_scan_cfg    : Pointer to scan configuration
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_cache_ext_scan_config(wiced_bt_ble_ext_scan_config_t *p_ext_scan_cfg);

/**
 * Stores the extended ADV connection configuration and used during LE connection.
 *
 * @param[in]       p_ext_conn_cfg    : Pointer to connection configuration
 *
 * @note The adv_handle and sub_event parameters of connection configuration shall be set to 0xFF if
 *        \ref wiced_bt_ble_ext_conn_cfg_t.adv_handle and \ref wiced_bt_ble_ext_conn_cfg_t.sub_event parameters are not to be used
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_cache_ext_conn_config(wiced_bt_ble_ext_conn_cfg_t *p_ext_conn_cfg);

/**
 * Sends the HCI command HCI_LE_Periodic_Advertising_Create_Sync to synchronize with periodic advertising from an advertiser and begin receiving periodic
 * advertising packets.
 *
 * @param[in]       options         : Refer #wiced_bt_ble_adv_sync_options_t
 * @param[in]       adv_sid         : Min SID / Max SID
 * @param[in]       adv_addr_type   : Advertiser blueooth address type
 * @param[in]       adv_addr        : Advertiser bluetooth address
 * @param[in]       skip            : Number of consecutive periodic advertising events that the receiver may skip(Range : 0x0000 to 0x01F3)
 * @param[in]       sync_timeout    : Timeout value
 * @param[in]       sync_cte_type   : Bit 0 - Do not sync to packets with an AoA Constant Tone Extension \n
 *                                    Bit 1 - Do not sync to packets with an AoD Constant Tone Extension with 1 μs slots \n
 *                                    Bit 2 - Do not sync to packets with an AoD Constant Tone Extension with 2 μs slots \n
 *                                    Bit 3 - Do not sync to packets with a type 3 Constant Tone Extension \n
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_create_sync_to_periodic_adv(wiced_bt_ble_adv_sync_options_t options,
                                                               wiced_bt_ble_ext_adv_sid_t adv_sid,
                                                               wiced_bt_ble_address_type_t adv_addr_type,
                                                               wiced_bt_device_address_t adv_addr,
                                                               uint16_t skip,
                                                               uint16_t sync_timeout,
                                                               uint8_t sync_cte_type);

/**
 * Sends HCI command HCI_LE_Periodic_Advertising_Create_Sync_Cancel to cancel the create sync command while it is pending.
 *
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported. \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command. \n
 * <b> WICED_BT_SUCCESS </b>       : If successful. \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_cancel_sync_to_periodic_adv(void);

/**
 * Sends the HCI command HCI_LE_Periodic_Advertising_Terminate_Sync to stop reception of periodic advertising identified by the \p sync_handle
 *@note  \p sync_handle received in #WICED_BT_BLE_PERIODIC_ADV_SYNC_ESTABLISHED_EVENT of callback function registered via API #wiced_bt_ble_register_adv_ext_cback
 *
 * @param[in]       sync_handle      : Sync handle
 *
 * @return          #wiced_bt_dev_status_t \n
 *
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 * <b> WICED_BT_SUCCESS </b>       : If successful \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_terminate_sync_to_periodic_adv(uint16_t sync_handle);

/**
 * Sends the HCI command HCI_LE_Add_Device_To_Periodic_Advertiser_List to add the given advertiser to Periodic Advertiser list.
 *
 * @note Caller shall not attempt to add more than max list size
 *       Shall not attempt to call this API, while create to periodic sync command is pending.
 *
 * @param[in]      advertiser_addr_type : Periodic advertiser address type
 * @param[in]      advetiser_addr       : Periodic advertiser addreess
 * @param[in]      adv_sid              : Periodic advertiser sid
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_add_device_to_periodic_adv_list(wiced_bt_ble_address_type_t advertiser_addr_type,
                                                                   wiced_bt_device_address_t advetiser_addr,
                                                                   wiced_bt_ble_ext_adv_sid_t adv_sid);

/**
 * Sends the HCI command HCI_LE_Remove_Device_From_Periodic_Advertiser_List to remove the given advertiser from Periodic Advertiser list.
 *
 *@note  Shall not attempt to call this API, while create to periodic sync command is pending.
 *
 * @param[in]      advertiser_addr_type : Periodic advertiser address type
 * @param[in]      advetiser_addr       : Periodic advertiser address
 * @param[in]      adv_sid              : Periodic advertiser sid
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_ILLEGAL_VALUE </b> : If parameter is invalid \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_remove_device_from_periodic_adv_list(
    wiced_bt_ble_address_type_t advertiser_addr_type,
    wiced_bt_device_address_t advetiser_addr,
    wiced_bt_ble_ext_adv_sid_t adv_sid);

/**
 * Sends the HCI command HCI_LE_Clear_Periodic_Advertiser_List to remove all devices from the the Periodic Advertisers list.
 *
 * @note  Shall not attempt to call this API, while create to periodic sync command is pending.
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 * <b> WICED_BT_SUCCESS </b>       : If successful \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_clear_periodic_adv_list(void);

/**
 * Sends the HCI command HCI_LE_Read_Periodic_Advertiser_List_Size to Read the Periodic Advertisers list size.
 *
 * @return          uint8_t : List size
 *
 */
uint8_t wiced_bt_ble_read_periodic_adv_list_size(void);

/**
 * Register an application callback function to receive extended advertising events.
 *
 * @param[in]       p_app_adv_ext_event_cb      : Pointer to function to receive extended adv events.
 *
 * @return          wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_PENDING </b>       : If command queued to send down \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
void wiced_bt_ble_register_adv_ext_cback(wiced_bt_ble_adv_ext_event_cb_fp_t p_app_adv_ext_event_cb);

/**
 * Sends the HCI command HCI_LE_Set_Periodic_Advertising_Receive_Enable to enable or disable receiving periodic advertising data for a \p sync_handle.
 *
 * @param[in]       sync_handle : Sync handle
 * @param[in]       enable      : Boolean for enable/disable.
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNSUPPORTED </b>   : If command not supported \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_periodic_adv_rcv_enable(wiced_bt_ble_periodic_adv_sync_handle_t sync_handle, wiced_bool_t enable);

/**
 * Sends the HCI command to send synchronization information about the periodic advertising train identified by the \p sync_handle parameter to given device
 *
 * @param[in]       peer_bda        : Peer Bluetooth Address
 * @param[in]       service_data    : Service Data value
 * @param[in]       sync_handle : Sync handle
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNKNOWN_ADDR </b> :  If Unknown remote BD address \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_periodic_adv_sync_transfer(wiced_bt_device_address_t peer_bda,
                                                              uint16_t service_data,
                                                              wiced_bt_ble_periodic_adv_sync_handle_t sync_handle);

/**
 * Sends the HCI command  to send synchronization information about the periodic advertising in an advertising set to given device.
 *
 * @param[in]       peer_bda        : Peer Bluetooth Address
 * @param[in]       service_data    : Service Data value
 * @param[in]       adv_handle  : Handle of the advertising set
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNKNOWN_ADDR </b> :  If Unknown remote BD address \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If command queued to send down \n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_periodic_adv_set_info_transfer(wiced_bt_device_address_t peer_bda,
                                                                  uint16_t service_data,
                                                                  wiced_bt_ble_ext_adv_handle_t adv_handle);

/**
 * Sends the HCI command to set synchronize periodic transfer parameter
 *
 * @param[in]       peer_bda        : Peer Bluetooth Address
 * @param[in]       mode            : Refer #wiced_bt_ble_periodic_adv_sync_transfer_mode_t
 * @param[in]       skip            : The number of periodic advertising packets that can be skipped after a successful receive
 * @param[in]       sync_timeout    : Timeout value
 * @param[in]       sync_cte_type   : Bit 0 - Do not sync to packets with an AoA Constant Tone Extension \n
 *                                    Bit 1 - Do not sync to packets with an AoD Constant Tone Extension with 1 μs slots \n
 *                                    Bit 2 - Do not sync to packets with an AoD Constant Tone Extension with 2 μs slots \n
 *                                    Bit 3 - Do not sync to packets with a type 3 Constant Tone Extension \n
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_UNKNOWN_ADDR </b> :  If Unknown remote BD address \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_periodic_adv_sync_transfer_param(
    wiced_bt_device_address_t peer_bda,
    wiced_bt_ble_periodic_adv_sync_transfer_mode_t mode,
    uint16_t skip,
    uint16_t sync_timeout,
    uint8_t sync_cte_type);

/**
 * Sends the HCI command HCI_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters  to set Default synchronize periodic transfer parameter
 *
 * @param[in]       mode         : Refer \ref wiced_bt_ble_periodic_adv_sync_transfer_mode_t
 * @param[in]       skip         : The number of periodic advertising packets that can be skipped after a successful receive
 * @param[in]       sync_timeout : Timeout value
 * @param[in]       sync_cte_type : Bit 0 - Do not sync to packets with an AoA Constant Tone Extension \n
 *                                  Bit 1 - Do not sync to packets with an AoD Constant Tone Extension with 1 μs slots \n
 *                                  Bit 2 - Do not sync to packets with an AoD Constant Tone Extension with 2 μs slots \n
 *                                  Bit 3 - Do not sync to packets with a type 3 Constant Tone Extension \n
 *
 * @return          #wiced_bt_dev_status_t \n
 * <b> WICED_BT_NO_RESOURCES </b>  : If no memory to issue the command \n
 * <b> WICED_BT_SUCCESS </b>       : If successful\n
 *
 */
wiced_bt_dev_status_t wiced_bt_ble_set_default_periodic_adv_sync_transfer_param(
    wiced_bt_ble_periodic_adv_sync_transfer_mode_t mode,
    uint16_t skip,
    uint16_t sync_timeout,
    uint8_t sync_cte_type);


/**
 *
 * This API verifies whether given device address is Resolvable Private Address or not
 *
 * @param rpa       : LE Resolvable Private Address
 * @param irk       : LE IRK
 * @return          #wiced_result_t \n
 *                 <b> WICED_BT_SUCCESS </b>  : The identity of device address has been resolved. \n
 *                 <b> WICED_BT_ERROR </b>  : Otherwise.
 */
wiced_result_t wiced_ble_private_device_address_resolution(wiced_bt_device_address_t rpa, BT_OCTET16 irk);

/**
 *
 * This API returns the features supported by the \p bda
 *
 * @param[in]  bda     :  Bluetooth device address pointer, pass NULL for local device
 * @param[out] features : Pointer to store the supported features
 * @return          #wiced_result_t \n
 *                  <b> WICED_BT_SUCCESS </b> : Contents of features are valid \n
 *                  <b> WICED_BT_ERROR </b> : Otherwise.
 */
wiced_result_t wiced_bt_ble_read_le_features(wiced_bt_device_address_t bda, wiced_bt_features_t features);

/**
 * This API clears the address resolution list and disables the address resolution feature.
 *
 * @return          #wiced_result_t \n
 *                  <b> WICED_BT_SUCCESS </b> : If address resolution list is cleared and adress resolution feature is disabled. \n
 *                  <b> WICED_BT_ERROR </b>   : Otherwise.
 */
wiced_result_t wiced_bt_ble_address_resolution_list_clear_and_disable(void);

/* @cond PAWR_API
   APIs for Periodic Advertising with Response*/
/**
*
* This API is called on a central to set the PAWR parameters
*@note This API sends HCI command  HCI_LE_Set_Periodic_Advertising_Parameters[v2] if periodic advertiser role is supported by the controller else [V1] command.
*
* @param[in]  adv_handle   : Handle of the Advertising Set
* @param[out] p_adv_params : Pointer to  \p p_adv_params
* @return          #wiced_result_t \n
*                 <b> WICED_BT_SUCCESS </b> : Contents of features are valid \n
*                 <b> WICED_BT_ERROR </b>    : Otherwise.
*/
wiced_bt_dev_status_t wiced_bt_ble_set_pawr_params (wiced_bt_ble_ext_adv_handle_t adv_handle,wiced_bt_ble_periodic_adv_params_t  *p_adv_params);

/**
* This API is called on a peripheral to set the subevent indication data
* @note This API sends HCI command HCI_LE_Set_Periodic_Advertising_Subevent_Data
*
* @param[in]  adv_handle    : Handle of the Advertising Set
* @param[in] num_subevents  : Number of subevent data in the command
* @param[in] p_se_data      : Pointer to the subevent data
* @return          #wiced_result_t \n
*                  <b> WICED_BT_SUCCESS </b> : Contents of features are valid \n
*                  <b> WICED_BT_ERROR </b>  : Otherwise.
*/
wiced_bt_dev_status_t wiced_bt_ble_set_pawr_subevent_ind_data (wiced_bt_ble_ext_adv_handle_t adv_handle,
    int  num_subevents, wiced_bt_ble_pawr_subevent_ind_data_t *p_se_data);

/**
* This API is called on a peripheral to set the subevent response data
* @note This API sends HCI command HCI_LE_Set_Periodic_Advertising_Response_Data
*
* @param[in]  sync_handle  :  Handle of the synchronized advertising train
* @param[out] p_rsp_data  : Pointer to p_rsp_data
* @return          #wiced_result_t \n
*                  <b> WICED_BT_SUCCESS </b> : Contents of features are valid \n
*                  <b> WICED_BT_ERROR </b>   : Otherwise.
*/
wiced_bt_dev_status_t wiced_bt_ble_set_pawr_subevent_rsp_data (uint16_t sync_handle,wiced_bt_ble_pawr_subevent_rsp_data_t *p_rsp_data);


/**
*
* This API is called on a peripheral to set the PAwR subevents that it wants to sync to.
* @note This API sends HCI command HCI_LE_Set_Periodic_Sync_Subevent
*
* @param[in]  sync_handle   :  Handle of the synchronized periodic advertising train
* @param[in]  properties    :  Properties of the synchronized periodic advertising train
* @param[in]  num_subevents :  Number of subevents
* @param[in]  p_subevents    : Pointer to an array of subevents
*
* @return          #wiced_result_t \n
*                  <b> WICED_BT_SUCCESS </b> : Contents of features are valid \n
*                  <b> WICED_BT_ERROR </b>   : Otherwise

*/
wiced_bt_dev_status_t wiced_bt_ble_set_pawr_sync_subevents (uint16_t sync_handle, uint16_t properties,
                                int num_subevents, uint8_t *p_subevents);

/* @endcond */


/**
*
* This API is called to set the supported host features.
*
* @param[in]  feature   : Bit position of required feature
* @param[in]  bit_value : Value to enable or disable Advertising Coding Selection Host Support feature bit<br>
*             0x00 :The Host feature is disabled \n
*             0x01 :The Host feature is enabled \n
*
* @return          #wiced_result_t \n
*                   <b> WICED_BT_SUCCESS </b> : Advertising Coding Selection Host Support feature bit is modified \n
*                   <b> WICED_BT_ERROR </b>    : Otherwise.
*/
wiced_bt_dev_status_t wiced_bt_ble_set_host_features(wiced_bt_ble_feature_bit_t feature, uint8_t bit_value);

/**
* This API is called to encrypt advertising data. It encrypts data at \p p_plaintext of length \p payload_len into
*    \p p_encrypted of length \p payload_len
*
* @param[in] p_key         : Session key
* @param[in] p_iv          : Initialization vector
* @param[in] p_randomizer  : Randomizer
* @param[in] p_plaintext   : Plaintext to be encoded
* @param[in] p_encrypted   : Encrypted output data
* @param[in] payload_len   : Plaintext/encrypted data len
*
* @return uint32_t MIC (Message Integrity Check) derived from the data
*/
uint32_t wiced_bt_ble_encrypt_adv_packet(
    uint8_t *p_key, uint8_t *p_iv, uint8_t *p_randomizer, const uint8_t *p_plaintext, uint8_t *p_encrypted, int payload_len);

/**
*
* This API is called to decrypt advertising data. It decrypts data at \p p_encrypted of length \p coded_len into
*    \p p_plaintext of length \p coded_len
*
* @param[in] p_key        : Session key
* @param[in] p_iv         : Initialization vector
* @param[in] p_randomizer : Randomizer
* @param[in] p_encrypted  : Encrypted data input
* @param[in] p_plaintext  : Plaintext output
* @param[in] coded_len    : Encrypted data len
*
* @return uint32_t MIC (Message Integrity Check) derived from the data
*/
uint32_t wiced_bt_ble_decrypt_adv_packet(
    uint8_t *p_key, uint8_t *p_iv, uint8_t *p_randomizer, const uint8_t *p_encrypted, uint8_t *p_plaintext, int coded_len);

/**@} btm_ble_adv_scan_functions */

/**@} btm_ble_api_functions */

#ifdef __cplusplus
}
#endif

#endif //__WICED_BT_BLE_H__
