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

#include "usb_device.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Configuration: set to 1 to flush on newline
 */
#define USBCDC_STDIO_FLUSH_ON_NEWLINE 1


/**
 * For XC8 compiler these are defined in stdio.h
 * @return
 */
#ifndef getchar
#define	getchar()	getche()
#endif
#ifndef putchar
#define	putchar(x)	putch(x)
#endif

/**
 * Checks is usb backend is ready for service
 * @return
 */
#define usbReady() ( USBGetDeviceState() >= CONFIGURED_STATE && !USBIsDeviceSuspended() )

/**
 * Repeated predeclaration in stdio.h
 * @return
 */
char getche(void);

/**
 * Repeated predeclaration in stdio.h
 * @param byte
 */
void putch(unsigned char byte);

/**
 * getchar() is a blocking function.
 * If this returns true, means getchar() will not block.
 * @return
 */
bool getchar_ready(void);

/**
 * putch buffers output buffer
 */
void flush(void);

/**
 * Simple getline implementation
 * @param lineptr pointer to be filled with chars
 * @param n length of lineptr
 * @return returns length of characters read
 */
uint8_t getline(char *lineptr, uint8_t n);

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
 * initialize usbStdio in a blocking way.
 * This function waits in a blocking way for usb initialization.
 * @param interruptPriority
 */
#define usbStdioInitBlocking(interruptPriority) do{ usbStdioInit(interruptPriority); while( !usbReady() ); }while(0)

/**
 * To be called in an interrupt handler.
 */
#define usbStdioInterruptHandler() do{ if(USBInterruptFlag) { USBDeviceTasks(); USBClearUSBInterrupt(); }}while(0)

/**
 * To be called in main loop in regular intervals, see USBDeviceTasks description
 */
#define usbStdioService() do{ USBDeviceTasks(); }while(0);

/* ------------------------------------------------------------------------------------------------------------------- */

/**
 * Used by usb_events.c in usb initialization, don't use anywhere in main();
 */
void usbhidStdio_APP_DeviceCustomHIDInitialize();

#endif

#endif /* XC8_PIC_INCLUDE_USBCDC_USBCDC_STDIO_H_ */
