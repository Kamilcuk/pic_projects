/*
 * usbcdc_stdio.h
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef XC8_PIC_INCLUDE_USBCDC_USBCDC_STDIO_H_
#define XC8_PIC_INCLUDE_USBCDC_USBCDC_STDIO_H_

#include "system.h"

#if USBHID_STDIO_ENABLE

#include "stdio_ex.h"

#include <usb_device.h>

#include <stdio.h> // getchar() putchar() printf() _IO{L,N,F}BF
#include <stdbool.h>
#include <stdint.h>

/**
 * Buffer configuration, see `man setbuf`
 */
#ifndef USBCDC_STDIO_SETBUF
#define USBCDC_STDIO_SETBUF _IOLBF
#endif

/**
 * Synchronizes output with flush() callback.
 * If this flag is set, putchar does not call flush() when buffer is ready.
 * This flag exists to preserve ReturnAddressStack.
 */
#ifndef USBCDC_STDIO_SYNC
#define USBCDC_STDIO_SYNC 0 /* 0 - disabled, 1 - enabled */
#endif

/**
 * Checks is usb backend is ready for service
 * @return
 */
#define usbReady() ( USBGetDeviceState() >= CONFIGURED_STATE && !USBIsDeviceSuspended() )

/**
 * referenced by ../stdio_ex.h
 */
bool getchar_ready(void);

/**
 * referenced by ../stdio_ex.h
 */
void flush(void);

/* ---------------------------------- usefull defines used in main program ------------------------------------------- */

/**
 * Initialize usb stdio backend with specified interrupt priotity
* @param interruptPriority 1 - high priority, 0 - low priority
 */
#ifdef USB_INTERRUPT
#define usbStdioInit(interruptPriority) do{ \
		USBDeviceInit(); \
		if (interruptPriority == 0) { \
			IPR2bits.USBIP = interruptPriority; INTCONbits.GIEL = 1; \
		} \
	}while(0)
#else
#define usbStdioInit(interruptPriority) do{ USBDeviceInit(); }while(0)
#endif

/**
 * To be called in an interrupt handler.
 */
#ifdef USB_INTERRUPT
#define usbStdioInterruptHandler() do{ \
		if(USBInterruptFlag) { USBDeviceTasks(); USBClearUSBInterrupt(); } \
	}while(0)
#else
#define usbStdioInterruptHandler()
#endif

/* ------- usbStdioService helpers ------ */
#if USBCDC_STDIO_SYNC == 1
#define usbStdioService_flush() flush()
#else
#define usbStdioService_flush()
#endif
#if defined( USE_USB_BUS_SENSE_IO ) && defined( USB_INTERRUPT )
#define usbStdioService_busSense() do{ \
	if ( USB_BUS_SENSE != 1 && USBDeviceState != DETACHED_STATE ) { \
		USBDeviceDetach(); \
		__delay_ms(50); \
	} else { \
		USBDeviceAttach(); \
		__delay_ms(50); \
	} \
}while(0)
#else
#define usbStdioService_busSense()
#endif
#ifdef USB_POLLING
#define USBDeviceTasksHandler() USBDeviceTasks()
#else
#define USBDeviceTasksHandler()
#endif

/**
 * To be called in main loop in regular intervals, see USBDeviceTasks description
 */
#define usbStdioService() do{ \
	USBDeviceTasksHandler(); \
	usbStdioService_flush(); \
	usbStdioService_busSense(); \
}while(0);

/**
 * Initialize usbStdio in a blocking way.
 * This function waits in a blocking way for usb initialization.
 * User for systems powered from usb.
 * @param interruptPriority 1 - high priority, 0 - low priority
 */
#define usbStdioInitBlocking(interruptPriority) do{ \
		usbStdioInit(interruptPriority); \
		USBDeviceAttach(); \
		while( !usbReady() ) { USBDeviceTasksHandler(); } \
	}while(0)
/* ------------------------------------------------------------------------------------------------------------------- */

/**
 * Used by usb_events.c in usb initialization, don't use anywhere in main();
 */
void USB_APP_DeviceCustomHIDInitialize();

#endif

#endif /* XC8_PIC_INCLUDE_USBCDC_USBCDC_STDIO_H_ */
