/*
 * usbcdc_stdio.c
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 *
 * Some commends and lines taken from Microchip hid_custom example, which is under Apache license.
 * But i wrote this file myself, so i leave beerware here, and say:
 * Thank You Microchip for Your example!
 */

#include "system.h"

#if USBHID_STDIO_ENABLE

#include "usbhid_stdio.h"
#include "fixed_address_memory.h"
#include "usb_config.h"

#include "usb_device.h"
#include "usb_device_hid.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * read buffer
 */
#define READ_BUFFER_SIZE 64
static unsigned char usbReadBuffer[READ_BUFFER_SIZE]
#ifdef __XC8__
									  @ HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
#endif
									  ;
static unsigned char readBuffer[READ_BUFFER_SIZE];
static uint8_t readBufferPos = 0;
static uint8_t numBytesRead = 0;

/**
 * write buffer
 */
#define WRITE_BUFFER_SIZE 64
static unsigned char usbWriteBuffer[WRITE_BUFFER_SIZE]
#ifdef __XC8__
									   @ HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
#endif
									   ;
static unsigned char writeBuffer[WRITE_BUFFER_SIZE];
static uint8_t writeBufferPos = 0;

/**
 * handles from cdc_device_cdc.c, used for checking if transmissino ended
 */
volatile USB_HANDLE USBOutHandle;
volatile USB_HANDLE USBInHandle;

/**
 * if usb will be disconnected while looping... we need timeout
 */
#define for_timeout(expr) for(uint16_t Timeout = 0xffff; (expr) && Timeout; --Timeout)

/**
 * handle undefined assert_param
 */
#ifndef ASSERT_PARAM
#define ASSERT_PARAM(expr)
#endif

/* -------------------------------------------- initialization -------------------------------------- */

void USB_APP_DeviceCustomHIDInitialize()
{
	readBufferPos = 0;
	numBytesRead = 0;
	writeBufferPos = 0;

    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(HID_EP, (uint8_t*)&usbReadBuffer[0], READ_BUFFER_SIZE);
}

/* ----------------------------------------- reading ----------------------------------------------------- */

char getchar( /*void*/ )
{
	char c;

	if ( readBufferPos >= numBytesRead ) {
		if ( !usbReady() ) return 0;

		for_timeout( HIDRxHandleBusy(USBOutHandle) ) {
			USBDeviceTasksHandler();
			usbStdioService_busSense();
#ifdef USE_USB_BUS_SENSE_IO
			if ( USBDeviceState == DETACHED_STATE ) {
				return 0xA0;
			}
#endif
		}

		numBytesRead = USBHandleGetLength(USBOutHandle);
		//ASSERT_PARAM(numBytesRead <= sizeof(readBuffer));
		memcpy(readBuffer, usbReadBuffer, numBytesRead);

        USBOutHandle = HIDRxPacket(HID_EP, (uint8_t*)&usbReadBuffer[0], READ_BUFFER_SIZE);

	    readBufferPos = 0;
	}

	// read one char from the buffer, increment buffer pos
	ASSERT_PARAM(readBufferPos < sizeof(readBuffer));
	c = readBuffer[readBufferPos];
	++readBufferPos;
	// return c
	return c;
}

bool getchar_ready(void)
{
	return usbReady() && (
				// there is something in the buffer left
				( readBufferPos < numBytesRead ) ||
				// buffer is empty, but next USBOutHandle has finished - just call getchar() to flush it
				( readBufferPos >= numBytesRead && !HIDRxHandleBusy(USBOutHandle) )
			);
}

/* ------------------------------------------ writing -------------------------------------------------------- */

#if USBCDC_STDIO_SETBUF == _IOLBF && USBCDC_STDIO_SYNC == 1
static bool should_flush = false;
#endif

void putchar(unsigned char byte)
{
	ASSERT_PARAM(writeBufferPos < sizeof(writeBuffer));
	writeBuffer[writeBufferPos] = byte;
	++writeBufferPos;

#if USBCDC_STDIO_SETBUF == _IOLBF
	if ( byte == '\n' || writeBufferPos >= WRITE_BUFFER_SIZE ) {
#if USBCDC_STDIO_SYNC == 1
		should_flush = true;
#else
		flush();
#endif
	}
#elif USBCDC_STDIO_SETBUF == _IOFBF && USBCDC_STDIO_SYNC == 0
	if ( writeBufferPos >= WRITE_BUFFER_SIZE ) {
		flush();
	}
#elif USBCDC_STDIO_SETBUF == _IONBF
	flush();
#endif

}

void flush(void)
{

#if USBCDC_STDIO_SYNC == 1
#if USBCDC_STDIO_SETBUF == _IOLBF
	if ( ! ( should_flush || writeBufferPos >= WRITE_BUFFER_SIZE ) ) {
		return;
	}
	should_flush = false;
#elif USBCDC_STDIO_SETBUF == _IOFBF
	if ( !( writeBufferPos >= WRITE_BUFFER_SIZE ) ) {
		flush();
	}
#endif
#endif

	// sanity
	if ( !usbReady() ) return;
	// check anything is to be flushed
	if ( writeBufferPos == 0 ) return;

	for_timeout( HIDTxHandleBusy(USBInHandle) ) {
		USBDeviceTasksHandler();
		usbStdioService_busSense();
#ifdef USE_USB_BUS_SENSE_IO
		if ( USBDeviceState == DETACHED_STATE ) {
			return;
		}
#endif
	}

    ASSERT_PARAM(writeBufferPos <= sizeof(writeBuffer));
	memcpy(usbWriteBuffer, writeBuffer, writeBufferPos);
    USBInHandle = HIDTxPacket(HID_EP, (uint8_t*)&usbWriteBuffer[0], writeBufferPos);
	
	writeBufferPos = 0;
}

#endif

