/*
 * usb_config.h
 * 
 * Under BEER-WARE license 2012 Unknown <kamil@leonidas>
 * 
 * 
 */
#ifndef _USB_CONFIG_H_
#define _USB_CONFIG_H_

#include "usb_ep1.h"
#include "usb_ep2.h"


#define USB_CONFIG_NUM_ENDPOINTS 	2

#define USB_CONFIG_DEVICE_CLASS 0x00
#define USB_CONFIG_DEVICE_SUBCLASS 0x00
#define USB_CONFIG_DEVICE_PROTOCOL 0x00
#define USB_CONFIG_DEVICE_VENDOR 0xffff
#define USB_CONFIG_DEVICE_PRODUCT 0x0003 //uhcpic
#define USB_CONFIG_DEVICE_RELEASE 0x0008

#define USB_BUFFER_DESCRIPTOR_MODE 0

#define EP0_BUFFER_SIZE 64
#define EP1_BUFFER_SIZE 64
#define EP2_BUFFER_SIZE 64


#define USB_CONFIG_ENDPOINTS_DESCRIPTORS() \
	{ \
		USB_DT_ENDPOINT_SIZE, \
		USB_DT_ENDPOINT, \
		1 | USB_DIR_OUT, \
		USB_ENDPOINT_XFER_BULK, \
		EP1_BUFFER_SIZE, \
		0 \
	}, \
	{ \
		USB_DT_ENDPOINT_SIZE, \
		USB_DT_ENDPOINT, \
		2 | USB_DIR_IN, \
		USB_ENDPOINT_XFER_BULK, \
		EP2_BUFFER_SIZE, \
		0 \
	}

#define USB_CONFIG_STRING2_DESCRIPTOR_() _('u')_('h')_('c')_('p')_('i')_('c')_(' ')

// initialize all other enpoints then ep0
#define USB_CONFIG_ENDPOINTS_INIT() do{ USB_EP1_init();USB_EP2_init(); } while(0)

#define USB_EP1_TRANSMISSION()  USB_EP1_transmission()
#define USB_EP2_TRANSMISSION()  USB_EP2_transmission()


#endif // _USB_CONFIG_H_

