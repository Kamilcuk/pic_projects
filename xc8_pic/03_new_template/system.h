/*
 * system.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#include <system_defaults.h>

#define USBHID_STDIO_ENABLE  1
//#define USE_USB_BUS_SENSE_IO 1
//#define USB_BUS_SENSE        PORTCbits.RC0
//#define USB_POLLING          1
#define USB_INTERRUPT        1
#include <usbhid_stdio/usb_config.h>

// cmdline.h
#define CMDLINE_ENABLED

#define USE_ASSERT_PRINTF 1
#include "assert.h"

#endif //SYSTEM_H
