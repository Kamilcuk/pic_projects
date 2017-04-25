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

#include <usb_device.h>

#include <stdio.h> // getchar() putchar() printf() _IO{L,N,F}BF
#include <stdbool.h>
#include <stdint.h>

/**
 * Buffer configuration, see `man setbuf`
 */
#define USBCDC_STDIO_SETBUF _IOLBF

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
 * @param interruptPriority
 */
#ifdef USB_INTERRUPT
#define usbStdioInit(interruptPriority) do{ USBDeviceInit(); USBDeviceAttach(); \
	if (interruptPriority == 0) { IPR2bits.USBIP = interruptPriority; INTCONbits.GIEL = 1; } }while(0)
#else
#define usbStdioInit(interruptPriority) do{ USBDeviceInit() }while(0)
#endif

/**
 * Initialize usbStdio in a blocking way.
 * This function waits in a blocking way for usb initialization.
 * User for systems powered from usb.
 * @param interruptPriority
 */
#define usbStdioInitBlocking(interruptPriority) do{ usbStdioInit(interruptPriority); while( !usbReady() ); }while(0)

/**
 * To be called in an interrupt handler.
 */
#define usbStdioInterruptHandler() do{ if(USBInterruptFlag) { USBDeviceTasks(); USBClearUSBInterrupt(); } }while(0)

/**
 * To be called in main loop in regular intervals, see USBDeviceTasks description
 */
#define usbStdioService() do{ USBDeviceTasks(); }while(0);

/* ------------------------------------------------------------------------------------------------------------------- */

/**
 * Used by usb_events.c in usb initialization, don't use anywhere in main();
 */
void USB_APP_DeviceCustomHIDInitialize();

#endif

#endif /* XC8_PIC_INCLUDE_USBCDC_USBCDC_STDIO_H_ */
