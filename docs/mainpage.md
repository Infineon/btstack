# Overview

This document lists the Application Programming Interfaces exposed by BTSTACK library for Application developers to use and create BLE or BR/EDR or Dual Mode (BLE+BR/EDR) Applications.
BTSTACK library is used in conjuction with a porting layer such as the [one available for FreeRTOS on PSOC](https://github.com/Infineon/btstack-integration). The porting layer implements the code to access memory, transport, timer and other OS functionalities required by the stack. Care must be taken to ensure to use right OS constructs. Example, if Stack APIs are invoked from an interrupt context, correct locking/mutual exclusion mechanisms that are allowed to be used from an interrupt context by the platform must be used.

Typical steps in using BTSTACK library APIs are -

## Initialization
 - The application thread typically starts the bluetooth stack with a call to #wiced_bt_stack_init.
 - The application then waits for the BTM_ENABLED event received through the registered callback.
 - Further interaction with the stack may be done in the same thread context in case of single threaded or in an application thread.
 - The BTSTACK library is thread-safe and can be operated in multi-threaded environments.

## Configuration Settings
 - An application provides stack configuration parameters via #wiced_bt_cfg_settings_t configuration structure. These are typically non-changing during the lifetime of the application. These include among others
   - The max number of links the application is expected to setup across both physical layers (LE and BR/EDR) and logical layers (GATT, L2CAP, other protocols and profiles)
   - The protocol/profile specific configurable settings.
   - For a full set of the configurable settings please refere to #wiced_bt_cfg_settings_t.

## Gatt Database
 - For all GATT server applications, the application is expected to setup a GATT database.
 - The GATT database is typically created using the BT Configurator tool
 - This GATT database will be queried by the remote GATT client device during the GATT discover procedure

## Callbacks
 - The application sets up callbacks with the BTSTACK Library.
   - For receiving Bluetooth link and general device management callbacks, appliation registers a callback using #wiced_bt_stack_init
   - For the GATT applications a GATT callback function is registered using the call to wiced_bt_gatt_register.
