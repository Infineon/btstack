# BTSTACK Library 
BTSTACK is Cypress's Bluetooth Host Protocol Stack implementation. The stack is optimized to work on Cypress Bluetooth controllers.
The BTSTACK supports Bluetooth BR/EDR and BLE core protocols.

The stack is available as libraries built for CM3 and CM4 ARM (TM) cores using ARM, GCC and IAR tool-chains. Further there are two build variants of stack libraries, LE only and Dual-mode. Applications that use LE can take advantage of reduced size of LE only library and build LE peripheral or even central applications. Dual-mode library supports both LE and BR/EDER protocols.

# Features
Protocols supported include (but not limited to)
 - ATT/GATT
 - Secure Connections
 - Multi-Advertisements
 - LE 2M
 - LECOC
 - SDP
 - AVDT/AVRC
 - RFCOMM/SPP
Please note that some of these features depend on the BT controller as well.

Refer to the [API reference manual](https://cypresssemiconductorco.github.io/btstack/api_reference_manual/html/index.html)

