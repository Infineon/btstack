# Overview

This document lists the Application Programming Interfaces exposed by Bluetooth LE Mesh library for Application developers to use and create Mesh Applications.
LE Mesh library is used in conjuction with a BTStack and porting layer such as the [one available for FreeRTOS on PSOC](https://github.com/Infineon/btstack-integration).

## Description
Mesh API provides a developer a simple way to incorporate BLE mesh functionality in a WICED application.
Most application will only need access to Mesh Models library. The applications that supports adding new devices to the mesh network (provisioning) and network configuration may also use Mesh Provisioning library.
Applications that use Vendor specific models in addition to standard Bluetooth SIG models, may also need to access Mesh Core library functions directly.
