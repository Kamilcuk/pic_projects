/*
 * usbcdc_stdio.c
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#include "system.h"

#if USBCDC_STDIO_ENABLE

#include "usb_config.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include <stdbool.h>
#include <stdint.h>
#include <usbcdc/usbcdc_stdio.h>

/**
 * read buffer
 */
static uint8_t readBuffer[1];
#define readBufferLen 1
static uint8_t readBufferPos = 0;
static uint8_t numBytesRead = 0;

/**
 * write buffer
 */
static uint8_t writeBuffer[1];
#define writeBufferLen 1
static uint8_t writeBufferPos = 0;

/**
 * handles from cdc_device_cdc.c, used for checking if transmissino ended
 */
extern USB_HANDLE CDCDataOutHandle;
extern USB_HANDLE CDCDataInHandle;

/**
 * if USB_INTERRUPT is defined, then USBDeviceTasks should be runned from interrupt routing
 * if not, we run it.
 */
#ifndef USB_INTERRUPT
#define USBDeviceTasksHandler() USBDeviceTasks()
#else
#define USBDeviceTasksHandler()
//do{ USBMaskInterrupts(); USBDeviceTasks(); USBUnmaskInterrupts(); }while(0)
#endif

#define for_timeout(expr) for(uint16_t Timeout = 0x8fff; Timeout && (expr); --Timeout)

#define usbcdcReadyHandler() usbcdcReady()

char getche(void)
{
	char c;
	// nothing in the buffer?
	if ( readBufferPos >= numBytesRead ) {
		// sanity
		if ( !usbcdcReadyHandler() ) return 0;
		// wait for in transmission
		for_timeout( !USBHandleBusy(CDCDataOutHandle) ) {
			USBDeviceTasksHandler();
		}
		// read bytes from CDC backend
	    numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
	    // reset buffer pos...
	    readBufferPos = 0;
	}
	// read one char from the buffer, increment buffer pos
	c = readBuffer[readBufferPos];
	++readBufferPos;
	// return c
	return c;
}

void putch(unsigned char byte)
{

	writeBuffer[writeBufferPos] = byte;
	++writeBufferPos;

	if (
#ifdef USBCDC_STDIO_FLUSH_ON_NEWLINE
			byte == '\n' ||
#endif
			writeBufferPos >= writeBufferLen ||
			USBUSARTIsTxTrfReady() ) {
		flush();
		writeBufferPos = 0;
	}
}

void flush(void)
{
	PORTB=0xff;

	// sanity
	if ( !usbcdcReadyHandler() ) return;
	// check anything is to be flushed
	if ( writeBufferPos == 0 ) return;

	// call CDCTxService backend until its finished
	// wait for DataInHande to finish last transmission (*DataInHandle is for sending chars)
	for_timeout( !USBUSARTIsTxTrfReady() || USBHandleBusy(CDCDataInHandle) ) {
		USBDeviceTasksHandler();
        CDCTxService();
	}

	putUSBUSART(&writeBuffer[0], writeBufferPos);

	for_timeout( !USBUSARTIsTxTrfReady() || USBHandleBusy(CDCDataInHandle) ) {
		USBDeviceTasksHandler();
        CDCTxService();
	}
    
    for_timeout(1);
    for_timeout(1);
    for_timeout(1);
    for_timeout(1);

	PORTB=0x00;
}

uint8_t getline(char *lineptr, uint8_t n)
{
	char c;
	uint8_t len = 0;
	for(; n; --n, ++len ) {
		c = getchar();
		*lineptr = c;
		if ( c == '\n' ) {
			break;
		}
	}
	return len;
}

#endif

