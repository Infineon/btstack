/*
 * $ Copyright Cypress Semiconductor $
 */


#pragma once

#define WICED_BTSTACK_VERSION_MAJOR    3      /**< Stack Major version */
#define WICED_BTSTACK_VERSION_MINOR    2      /**< Stack Minor version */
#define WICED_BTSTACK_VERSION_PATCH    0      /**< Stack Patch version */

/*Stack version macro for use in BTSDK*/
#define BTSTACK_VER   ( ((WICED_BTSTACK_VERSION_MAJOR & 0xff) << 24) | ((WICED_BTSTACK_VERSION_MINOR & 0xff) << 16) | (WICED_BTSTACK_VERSION_PATCH & 0xffff) )
