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
#include <common.h> // PORT() TRIS()

// usb
//#define USE_USB_BUS_SENSE_IO  1
//#define USB_BUS_SENSE         PORT1(USB_BUS_SENSE_PORTPIN)
#define USBHID_STDIO_ENABLE   1
#define USB_INTERRUPT         1
#include <usbhid_stdio/usb_config.h>

#define CMDLINE_ENABLED

#define ASSERT_USE_PRINTF 1

#define SYSTICK_USE_TIMER 0
#define SYSTICK_TIMER_PRESCALER 4

#endif //SYSTEM_H
