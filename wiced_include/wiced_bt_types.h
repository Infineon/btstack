/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 *
 * Generic types
 *
 */
#pragma once
#include "wiced_data_types.h"
#include "wiced_result.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT_PSM_SDP                      0x0001 /* Service Discovery Protocol) */
#define BT_PSM_RFCOMM                   0x0003 /* RFCOMM with TS 07.10 */
#define BT_PSM_TCS                      0x0005 /* (deprecated) */
#define BT_PSM_CTP                      0x0007 /* (deprecated) */
#define BT_PSM_BNEP                     0x000F /* Bluetooth Network Encapsulation Protocol */
#define BT_PSM_HIDC                     0x0011 /* Human Interface Device (Control) */
#define BT_PSM_HIDI                     0x0013 /* Human Interface Device (Interrupt) */
#define BT_PSM_UPNP                     0x0015 /* Universal PlugNPlay */
#define BT_PSM_AVCTP                    0x0017 /* Audio/Video Control Transport Protocol */
#define BT_PSM_AVDTP                    0x0019 /* Audio/Video Distribution Transport Protocol */
#define BT_PSM_AVCTP_13                 0x001B /* Advanced Control - Browsing */
#define BT_PSM_UDI_CP                   0x001D /* Unrestricted Digital Information C-Plane  */
#define BT_PSM_ATT                      0x001F /* Attribute Protocol  */
#define BT_PSM_3DS                      0x0021 /* 3D sync */
#define BT_LE_PSM_IPSP                  0x0023 /* Internet Protocol Support (IPv6/6LoWPAN) */


#define BT_EIR_FLAGS_TYPE                   0x01
#define BT_EIR_MORE_16BITS_UUID_TYPE        0x02
#define BT_EIR_COMPLETE_16BITS_UUID_TYPE    0x03
#define BT_EIR_MORE_32BITS_UUID_TYPE        0x04
#define BT_EIR_COMPLETE_32BITS_UUID_TYPE    0x05
#define BT_EIR_MORE_128BITS_UUID_TYPE       0x06
#define BT_EIR_COMPLETE_128BITS_UUID_TYPE   0x07
#define BT_EIR_SHORTENED_LOCAL_NAME_TYPE    0x08
#define BT_EIR_COMPLETE_LOCAL_NAME_TYPE     0x09
#define BT_EIR_TX_POWER_LEVEL_TYPE          0x0A
#define BT_EIR_OOB_BD_ADDR_TYPE             0x0C
#define BT_EIR_OOB_COD_TYPE                 0x0D
#define BT_EIR_OOB_SSP_HASH_C_TYPE          0x0E
#define BT_EIR_OOB_SSP_RAND_R_TYPE          0x0F
#define BT_EIR_OOB_SSP_HASH_C_256_TYPE      0x1D
#define BT_EIR_OOB_SSP_RAND_R_256_TYPE      0x1E
#define BT_EIR_3D_SYNC_TYPE                 0x3D
#define BT_EIR_MANUFACTURER_SPECIFIC_TYPE   0xFF

#define BT_OOB_COD_SIZE            3
#define BT_OOB_HASH_C_SIZE         16
#define BT_OOB_RAND_R_SIZE         16
#define BT_OOB_HASH_C_256_SIZE     16
#define BT_OOB_RAND_R_256_SIZE     16

#ifndef WICED_BT_DEVICE_ADDRESS
#define WICED_BT_DEVICE_ADDRESS
#define BD_ADDR_LEN     6
typedef uint8_t         wiced_bt_device_address_t[BD_ADDR_LEN]; /**< Device address length */
#endif

typedef uint8_t *BD_ADDR_PTR;                 /* Pointer to Device Address */

#define BD_NAME_LEN     248
typedef uint8_t wiced_bt_remote_name_t[BD_NAME_LEN + 1];        /**< Device name */

typedef uint8_t *wiced_bt_device_address_ptr_t;                 /**< Device address Pointer */

#define DEV_CLASS_LEN   3
typedef uint8_t         wiced_bt_dev_class_t[DEV_CLASS_LEN];    /**< Device class */

#define MAX_UUID_SIZE              16  /**< Maximum UUID size - 16 bytes, and structure to hold any type of UUID. */

#define BT_DB_HASH_LEN 16
typedef uint8_t wiced_bt_db_hash_t[BT_DB_HASH_LEN];

/** UUID Type */
typedef struct
{
#define LEN_UUID_16     2
#define LEN_UUID_32     4
#define LEN_UUID_128    16

    uint16_t        len;     /**< UUID length */

    union
    {
        uint16_t    uuid16; /**< 16-bit UUID */
        uint32_t    uuid32; /**< 32-bit UUID */
        uint8_t     uuid128[MAX_UUID_SIZE]; /**< 128-bit UUID */
    } uu;

} wiced_bt_uuid_t;

#define BT_OCTET8_LEN    8
typedef uint8_t BT_OCTET8[BT_OCTET8_LEN];   /* octet array: size 8 */

#define BT_OCTET16_LEN    16                /**<  length: 16 */
typedef uint8_t BT_OCTET16[BT_OCTET16_LEN]; /**< octet array: size 16 */

#define BT_OCTET32_LEN    32
typedef uint8_t BT_OCTET32[BT_OCTET32_LEN];   /* octet array: size 32 */

/** Bluetooth QoS defintions */
typedef struct {
    uint8_t         qos_flags;              /**< TBD */
    uint8_t         service_type;           /**< service type (NO_TRAFFIC, BEST_EFFORT, or GUARANTEED) */
    uint32_t        token_rate;             /**< token rate (bytes/second) */
    uint32_t        token_bucket_size;      /**< token bucket size (bytes) */
    uint32_t        peak_bandwidth;         /**< peak bandwidth (bytes/second) */
    uint32_t        latency;                /**< latency (microseconds) */
    uint32_t        delay_variation;        /**< delay variation (microseconds) */
} wiced_bt_flow_spec_t;

/* Values for swiced_bt_flow_spec_t service_type */
#define NO_TRAFFIC      0
#define BEST_EFFORT     1
#define GUARANTEED      2

/**
 * @anchor WICED_BT_TRANSPORT_TYPE
 * @name Transport types
 * @{
 */
#define BT_TRANSPORT_BR_EDR         1       /**< BR/EDR transport */
#define BT_TRANSPORT_LE             2       /**< BLE transport */
typedef uint8_t wiced_bt_transport_t;       /**< Transport type (see @ref WICED_BT_TRANSPORT_TYPE "BT Transport Types") */
/** @} WICED_BT_TRANSPORT_TYPE */

/**
 * @anchor WICED_BT_DEVICE_TYPE
 * @name Device Types
 * @{
 */
#define BT_DEVICE_TYPE_BREDR        0x01    /**< BR/EDR device */
#define BT_DEVICE_TYPE_BLE          0x02    /**< LE device */
#define BT_DEVICE_TYPE_BREDR_BLE    0x03    /**< Dual Mode device */
typedef uint8_t wiced_bt_device_type_t;     /**< Bluetooth device type (see @ref WICED_BT_DEVICE_TYPE "BT Device Types") */
/** @} WICED_BT_DEVICE_TYPE */

/**
 * @anchor WICED_BT_ADDR_TYPE
 * @name Address Types
 * @{
 */
#define BLE_ADDR_PUBLIC             0x00        /**< Public address */
#define BLE_ADDR_RANDOM             0x01        /**< Random address */
#define BLE_ADDR_PUBLIC_ID          0x02        /**< Public ID      */
#define BLE_ADDR_RANDOM_ID          0x03        /**< Random ID      */
typedef uint8_t wiced_bt_ble_address_type_t;    /**< BLE device address type (see @ref WICED_BT_ADDR_TYPE "BT Address Types")*/
/** @} WICED_BT_ADDR_TYPE */

typedef struct
{
    wiced_bt_ble_address_type_t type;
    wiced_bt_device_address_t   bda;
} wiced_bt_ble_address_t;

#define LINK_KEY_LEN    16
typedef uint8_t wiced_bt_link_key_t[LINK_KEY_LEN];

/* Define a Data Received Buffer structure, which is used to pass received data back
** up through the stack. 
*/
typedef struct
{
    uint16_t            drb_data_len;               /* The amount of data in the DRB              */
    uint16_t            drb_data_offset;            /* The starting offset of the data in the DRB */
    uint8_t             drb_data[1];                /* The actual received data                   */
} tDRB;
#define DRB_OVERHEAD_SIZE   (sizeof (uint16_t) + sizeof (uint16_t))     /* length and offset */

#define EATT_CHANNELS_PER_TRANSACTION 5


/********************************************************************************
** Macros to get and put bytes to and from a stream (Little Endian format).
*/
#define UINT128_TO_STREAM(p, u128) {*(p)++ = (uint8_t)(u128);       *(p)++ = (uint8_t)((u128) >> 8);*(p)++ = (uint8_t)((u128) >> 16); *(p)++ = (uint8_t)((u128) >> 24); \
                                    *(p)++ = (uint8_t)((u128) >> 32); *(p)++ = (uint8_t)((u128) >> 40);*(p)++ = (uint8_t)((u128) >> 48); *(p)++ = (uint8_t)((u128) >> 56); \
                                    *(p)++ = (uint8_t)((u128) >> 64); *(p)++ = (uint8_t)((u128) >> 72);*(p)++ = (uint8_t)((u128) >> 80); *(p)++ = (uint8_t)((u128) >> 88); \
                                    *(p)++ = (uint8_t)((u128) >> 96); *(p)++ = (uint8_t)((u128) >> 104);*(p)++ = (uint8_t)((u128) >> 112); *(p)++ = (uint8_t)((u128) >> 120); }
#define UINT64_TO_STREAM(p, u64) {*(p)++ = (uint8_t)(u64);       *(p)++ = (uint8_t)((u64) >> 8);*(p)++ = (uint8_t)((u64) >> 16); *(p)++ = (uint8_t)((u64) >> 24); \
                                    *(p)++ = (uint8_t)((u64) >> 32); *(p)++ = (uint8_t)((u64) >> 40);*(p)++ = (uint8_t)((u64) >> 48); *(p)++ = (uint8_t)((u64) >> 56);}
#define UINT48_TO_STREAM(p, u48) {*(p)++ = (uint8_t)(u48); *(p)++ = (uint8_t)((u48) >> 8); *(p)++ = (uint8_t)((u48) >> 16); *(p)++ = (uint8_t)((u48) >> 24); *(p)++ = (uint8_t)((u48) >> 32); *(p)++ = (uint8_t)((u48) >> 40);}
#define UINT40_TO_STREAM(p, u40) {*(p)++ = (uint8_t)(u40); *(p)++ = (uint8_t)((u40) >> 8); *(p)++ = (uint8_t)((u40) >> 16); *(p)++ = (uint8_t)((u40) >> 24); \
                                  *(p)++ = (uint8_t)((u40) >> 32);}
#define UINT24_TO_STREAM(p, u24) {*(p)++ = (uint8_t)(u24); *(p)++ = (uint8_t)((u24) >> 8); *(p)++ = (uint8_t)((u24) >> 16);}
#define UINT8_TO_STREAM(p, u8)   {*(p)++ = (uint8_t)(u8);}
#define INT8_TO_STREAM(p, u8)    {*(p)++ = (INT8)(u8);}
#define ARRAY32_TO_STREAM(p, a)  {register int ijk; for (ijk = 0; ijk < 32;           ijk++) *(p)++ = (uint8_t) a[31 - ijk];}
#define ARRAY16_TO_STREAM(p, a)  {register int ijk; for (ijk = 0; ijk < 16;           ijk++) *(p)++ = (uint8_t) a[15 - ijk];}
#define ARRAY8_TO_STREAM(p, a)   {register int ijk; for (ijk = 0; ijk < 8;            ijk++) *(p)++ = (uint8_t) a[7 - ijk];}
#define LAP_TO_STREAM(p, a)      {register int ijk; for (ijk = 0; ijk < LAP_LEN;      ijk++) *(p)++ = (uint8_t) a[LAP_LEN - 1 - ijk];}
#define DEVCLASS_TO_STREAM(p, a) {register int ijk; for (ijk = 0; ijk < DEV_CLASS_LEN;ijk++) *(p)++ = (uint8_t) a[DEV_CLASS_LEN - 1 - ijk];}
#define ARRAY_TO_STREAM(p, a, len) {register int ijk; for (ijk = 0; ijk < len;        ijk++) *(p)++ = (uint8_t) a[ijk];}
#define REVERSE_ARRAY_TO_STREAM(p, a, len)  {register int ijk; for (ijk = 0; ijk < len; ijk++) *(p)++ = (uint8_t) a[len - 1 - ijk];}

#define STREAM_TO_UINT8(u8, p)   {u8 = (uint8_t)(*(p)); (p) += 1;}
#define STREAM_TO_UINT24(u32, p) {u32 = (((uint32_t)(*(p))) + ((((uint32_t)(*((p) + 1)))) << 8) + ((((uint32_t)(*((p) + 2)))) << 16) ); (p) += 3;}
#define STREAM_TO_UINT40(u40, p) {u40 = (((uint64_t)(*(p))) + ((((uint64_t)(*((p) + 1)))) << 8) + ((((uint64_t)(*((p) + 2)))) << 16) + ((((uint64_t)(*((p) + 3)))) << 24) + ((((uint64_t)(*((p) + 4)))) << 32)); (p) += 5;}
#define STREAM_TO_ARRAY32(a, p)  {register int ijk; register uint8_t *_pa = (uint8_t *)a + 31; for (ijk = 0; ijk < 32; ijk++) *_pa-- = *p++;}
#define STREAM_TO_ARRAY16(a, p)  {register int ijk; register uint8_t *_pa = (uint8_t *)a + 15; for (ijk = 0; ijk < 16; ijk++) *_pa-- = *p++;}
#define STREAM_TO_ARRAY8(a, p)   {register int ijk; register uint8_t *_pa = (uint8_t *)a + 7; for (ijk = 0; ijk < 8; ijk++) *_pa-- = *p++;}
#define STREAM_TO_DEVCLASS(a, p) {register int ijk; register uint8_t *_pa = (uint8_t *)a + DEV_CLASS_LEN - 1; for (ijk = 0; ijk < DEV_CLASS_LEN; ijk++) *_pa-- = *p++;}
#define STREAM_TO_LAP(a, p)      {register int ijk; register uint8_t *plap = (uint8_t *)a + LAP_LEN - 1; for (ijk = 0; ijk < LAP_LEN; ijk++) *plap-- = *p++;}
#define STREAM_TO_ARRAY(a, p, len) {register int ijk; for (ijk = 0; ijk < len; ijk++) ((uint8_t *) a)[ijk] = *p++;}
#define REVERSE_STREAM_TO_ARRAY(a, p, len) {register int ijk; register uint8_t *_pa = (uint8_t *)a + len - 1; for (ijk = 0; ijk < len; ijk++) *_pa-- = *p++;}

#define STREAM_TO_UINT8(u8, p)   {u8 = (uint8_t)(*(p)); (p) += 1;}
#define STREAM_TO_INT8(i8, p)   {i8 = (INT8)(*(p)); (p) += 1;}

#define BCM_STRNCPY_S(x1,x2,x3,x4)  strncpy((x1),(x3),(x4))

/* Based on the BT Controller ARM architecture, or possibly other hosts, we can optimize these macros. */
#if ((defined STACK_INSIDE_BT_CTRLR) && (STACK_INSIDE_BT_CTRLR == TRUE)) || (defined OPTIMISE_FOR_LITTLE_ENDIAN)
#define UINT32_TO_STREAM(p, u32) {*(uint32_t *)(p) = u32; (p) += 4;}
#define UINT16_TO_STREAM(p, u16) {*(uint16_t *)(p) = u16; (p) += 2;}

#define STREAM_TO_UINT32(u32, p) {u32 = *(uint32_t *)(p); (p) += 4;}
#define STREAM_TO_UINT16(u16, p) {u16 = *(uint16_t *)(p); (p) += 2;}
#else
#define UINT32_TO_STREAM(p, u32) {*(p)++ = (uint8_t)(u32); *(p)++ = (uint8_t)((u32) >> 8); *(p)++ = (uint8_t)((u32) >> 16); *(p)++ = (uint8_t)((u32) >> 24);}
#define UINT16_TO_STREAM(p, u16) {*(p)++ = (uint8_t)(u16); *(p)++ = (uint8_t)((u16) >> 8);}

#define STREAM_TO_UINT32(u32, p) {u32 = (((uint32_t)(*(p))) + ((((uint32_t)(*((p) + 1)))) << 8) + ((((uint32_t)(*((p) + 2)))) << 16) + ((((uint32_t)(*((p) + 3)))) << 24)); (p) += 4;}
#define STREAM_TO_UINT16(u16, p) {u16 = ((uint16_t)(*(p)) + (((uint16_t)(*((p) + 1))) << 8)); (p) += 2;}
#endif

extern uint8_t *BTU_copyBdaToStream(uint8_t *pStream, uint8_t *pBDA);
extern uint8_t *BTU_copyStreamToBda(uint8_t *pBDA, uint8_t *pStream);

#define BDADDR_TO_STREAM(p, a)   { p = BTU_copyBdaToStream(p, (uint8_t *)(a)); }
#define STREAM_TO_BDADDR(a, p)   { p = BTU_copyStreamToBda((uint8_t *)(a), p);}


/********************************************************************************
** Macros to get and put bytes to and from a field (Little Endian format).
** These are the same as to stream, except the pointer is not incremented.
*/
#define UINT32_TO_FIELD(p, u32) {*(uint8_t *)(p) = (uint8_t)(u32); *((uint8_t *)(p)+1) = (uint8_t)((u32) >> 8); *((uint8_t *)(p)+2) = (uint8_t)((u32) >> 16); *((uint8_t *)(p)+3) = (uint8_t)((u32) >> 24);}
#define UINT24_TO_FIELD(p, u24) {*(uint8_t *)(p) = (uint8_t)(u24); *((uint8_t *)(p)+1) = (uint8_t)((u24) >> 8); *((uint8_t *)(p)+2) = (uint8_t)((u24) >> 16);}
#define UINT16_TO_FIELD(p, u16) {*(uint8_t *)(p) = (uint8_t)(u16); *((uint8_t *)(p)+1) = (uint8_t)((u16) >> 8);}
#define UINT8_TO_FIELD(p, u8)   {*(uint8_t *)(p) = (uint8_t)(u8);}


/********************************************************************************
** Macros to get and put bytes to and from a stream (Big Endian format)
*/
#define UINT128_TO_BE_STREAM(p, u128) {*(p)++ = (uint8_t)(u128)>> 120;       *(p)++ = (uint8_t)((u128) >> 112);*(p)++ = (uint8_t)((u128) >> 104); *(p)++ = (uint8_t)((u128) >> 96); \
                                    *(p)++ = (uint8_t)((u128) >> 88); *(p)++ = (uint8_t)((u128) >> 80);*(p)++ = (uint8_t)((u128) >> 72); *(p)++ = (uint8_t)((u128) >> 64); \
                                    *(p)++ = (uint8_t)((u128) >> 56); *(p)++ = (uint8_t)((u128) >> 48);*(p)++ = (uint8_t)((u128) >> 40); *(p)++ = (uint8_t)((u128) >> 32); \
                                    *(p)++ = (uint8_t)((u128) >> 24); *(p)++ = (uint8_t)((u128) >> 16);*(p)++ = (uint8_t)((u128) >> 8); *(p)++ = (uint8_t)(u128); }
#define UINT64_TO_BE_STREAM(p, u64) {*(p)++ = (uint8_t)((u64) >> 56); *(p)++ = (uint8_t)((u64) >> 48);*(p)++ = (uint8_t)((u64) >> 40); *(p)++ = (uint8_t)((u64) >> 32); \
                                     *(p)++ = (uint8_t)((u64) >> 24); *(p)++ = (uint8_t)((u64) >> 16);*(p)++ = (uint8_t)((u64) >> 8); *(p)++ = (uint8_t)(u64); }
#define UINT32_TO_BE_STREAM(p, u32) {*(p)++ = (uint8_t)((u32) >> 24);  *(p)++ = (uint8_t)((u32) >> 16); *(p)++ = (uint8_t)((u32) >> 8); *(p)++ = (uint8_t)(u32); }
#define UINT24_TO_BE_STREAM(p, u24) {*(p)++ = (uint8_t)((u24) >> 16); *(p)++ = (uint8_t)((u24) >> 8); *(p)++ = (uint8_t)(u24);}
#define UINT16_TO_BE_STREAM(p, u16) {*(p)++ = (uint8_t)((u16) >> 8); *(p)++ = (uint8_t)(u16);}
#define UINT8_TO_BE_STREAM(p, u8)   {*(p)++ = (uint8_t)(u8);}
#define ARRAY_TO_BE_STREAM(p, a, len) {register int ijk; for (ijk = 0; ijk < len; ijk++) *(p)++ = (uint8_t) a[ijk];}

#define BE_STREAM_TO_UINT8(u8, p)   {u8 = (uint8_t)(*(p)); (p) += 1;}
#define BE_STREAM_TO_UINT16(u16, p) {u16 = (uint16_t)(((uint16_t)(*(p)) << 8) + (uint16_t)(*((p) + 1))); (p) += 2;}
#define BE_STREAM_TO_UINT24(u32, p) {u32 = (((uint32_t)(*((p) + 2))) + ((uint32_t)(*((p) + 1)) << 8) + ((uint32_t)(*(p)) << 16)); (p) += 3;}
#define BE_STREAM_TO_UINT32(u32, p) {u32 = ((uint32_t)(*((p) + 3)) + ((uint32_t)(*((p) + 2)) << 8) + ((uint32_t)(*((p) + 1)) << 16) + ((uint32_t)(*(p)) << 24)); (p) += 4;}
#define BE_STREAM_TO_UINT64(u64, p) {u64 = ((UINT64)(*((p) + 7)) + ((UINT64)(*((p) + 6)) << 8) + ((UINT64)(*((p) + 5)) << 16) + ((UINT64)(*((p) + 4)) << 24) + \
                                           ((UINT64)(*((p) + 3)) << 32) + ((UINT64)(*((p) + 2)) << 40) + ((UINT64)(*((p) + 1)) << 48) + ((UINT64)(*(p)) << 56)); (p) += 8;}
#define BE_STREAM_TO_ARRAY(p, a, len) {register int ijk; for (ijk = 0; ijk < len; ijk++) ((uint8_t *) a)[ijk] = *p++;}


/********************************************************************************
** Macros to get and put bytes to and from a field (Big Endian format).
** These are the same as to stream, except the pointer is not incremented.
*/
#define UINT32_TO_BE_FIELD(p, u32) {*(uint8_t *)(p) = (uint8_t)((u32) >> 24);  *((uint8_t *)(p)+1) = (uint8_t)((u32) >> 16); *((uint8_t *)(p)+2) = (uint8_t)((u32) >> 8); *((uint8_t *)(p)+3) = (uint8_t)(u32); }
#define UINT24_TO_BE_FIELD(p, u24) {*(uint8_t *)(p) = (uint8_t)((u24) >> 16); *((uint8_t *)(p)+1) = (uint8_t)((u24) >> 8); *((uint8_t *)(p)+2) = (uint8_t)(u24);}
#define UINT16_TO_BE_FIELD(p, u16) {*(uint8_t *)(p) = (uint8_t)((u16) >> 8); *((uint8_t *)(p)+1) = (uint8_t)(u16);}
#define UINT8_TO_BE_FIELD(p, u8)   {*(uint8_t *)(p) = (uint8_t)(u8);}

/* Macros to Print the BD_ADDRESS */
#define EXPAND_BDADDR(bd)                 bd[0],bd[1],bd[2],bd[3],bd[4],bd[5]
#define BDADDR_FORMAT                     "%02x:%02x:%02x:%02x:%02x:%02x"
#define NUM_ELEMENTS(x)                   (sizeof(x) / sizeof((x)[0]))

#ifndef MIN
#define MIN( a, b )                                             ( ( (a) < (b) ) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX( a, b )                                             ( ( (a) > (b) ) ? (a) : (b) )
#endif

#ifdef __cplusplus
}
#endif