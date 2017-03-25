#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>

#define USB_PING_PONG__FULL_PING_PONG 2
#define USB_PING_PONG__ALL_BUT_EP0 3
#define USB_PING_PONG_MODE USB_PING_PONG__FULL_PING_PONG

#define XSTR(x) #x
#define STR(x) XSTR(x)
#define ASSERT_PARAM(expr) do{ \
	if( !(expr) ) \
		printf("assert failed:" __FUNCTION__ ":" __FILE__  ":" STR(__LINE__) ":" STR(expr)); \
}while(0)

#define USBHID_STDIO_ENABLE 1

#define getline test_getline

#define USB_HANDLE void*

#include <stdint.h>
#define USBEnableEndpoint(a,b)
#define HIDRxPacket(a,b,c) 1
#define USBGetDeviceState() 0
#define CONFIGURED_STATE 0
#define USBIsDeviceSuspended() 0
#endif
