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

#if USBCDC_STDIO_ENABLE

#include "usb_device.h"
#include "usb_device_cdc.h"

#include <stdio.h>
#include <stdbool.h>

// putch(byte) will call flush() is byte == newline
#define USBCDC_STDIO_FLUSH_ON_NEWLINE 1

/**
 * checks is usb backend is ready for service
 * @return
 */
#define usbcdcReady() ( USBGetDeviceState() >= CONFIGURED_STATE && !USBIsDeviceSuspended() )

/**
 * predeclaration in stdio.h
 * @return
 */
char getche(void);

/**
 * predeclaration in stdio.h
 * @param byte
 */
void putch(unsigned char byte);

/**
 * getchar() is a blocking function.
 * If this returns true, means getchar() will not block.
 * @return
 */
#define getchar_ready() ( usbcdcReady() && USBUSARTIsTxTrfReady() )

/**
 * putch buffers output buffer
 */
void flush(void);

/**
 *
 */
uint8_t getline(char *lineptr, uint8_t n);

#ifdef USB_INTERRUPT
#define usbcdcInitBlockingCDCInterrupt(interruptPriority) \
	do{ USBDeviceAttach(); \
	}while(0)
//if (interruptPriority == 0) { IPR2bits.USBIP = interruptPriority; INTCONbits.GIEL = 1; }
#endif
#ifdef USB_POLLING
#define usbcdcInitBlockingCDCInterrupt(interruptPriority)
#endif

#define usbcdcInitBlocking(interruptPriority) \
	do{ USBDeviceInit(); usbcdcInitBlockingCDCInterrupt(0); while( !usbcdcReady() ) continue; }while(0)
#define usbcdcInitInterruptHighBlocking() usbcdcInitBlocking(1)
#define usbcdcInitInterruptLowBlocking()  usbcdcInitBlocking(0)

#ifdef USB_INTERRUPT
#define usbcdcService() do{ if(USBInterruptFlag) { USBDeviceTasks(); USBClearUSBInterrupt(); }}while(0)
#else
#define usbcdcService() do{ USBDeviceTasks(); BCDCTxService(); }while(0);
#endif

#endif

#endif /* XC8_PIC_INCLUDE_USBCDC_USBCDC_STDIO_H_ */
