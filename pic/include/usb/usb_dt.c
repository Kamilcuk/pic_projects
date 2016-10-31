/*
 * usb_dt.c
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

const struct usb_device_descriptor __code device_descriptor = {
	sizeof(struct usb_device_descriptor),    // Size of this descriptor in bytes
	USB_DT_DEVICE,                // Device descriptor type
	0x0200,                 // USB Spec Release Number in BCD format
	USB_CONFIG_DEVICE_CLASS,                   // Class Code
	USB_CONFIG_DEVICE_SUBCLASS,                   // Subclass code
	USB_CONFIG_DEVICE_PROTOCOL,                   // Protocol code
	EP0_BUFFER_SIZE,        // Max packet size for EP0
#ifdef USB_CONFIG_DEVICE_VENDOR
	USB_CONFIG_DEVICE_VENDOR,                 // Vendor ID
#else
	USB_CONFIG_MY_VENDOR, // vendor ID
#endif
	USB_CONFIG_DEVICE_PRODUCT,                 // Product ID
	USB_CONFIG_DEVICE_RELEASE,                 // Device release number in BCD format
	1,                      // Manufacturer string index
	2,                      // Product string index
	3,                      // Device serial number string index
	NUM_CONFIGURATIONS      // Number of possible configurations
};

struct configuration0_descriptor_t {
	struct usb_config_descriptor config_0;
	struct usb_interface_descriptor interface_0;
	struct usb_endpoint_descriptor ep[USB_CONFIG_NUM_ENDPOINTS];
};
const struct configuration0_descriptor_t __code configuration0_descriptor = {
	// Configuration Descriptor 
	{
		sizeof(struct usb_config_descriptor),    // Size of this descriptor in bytes
		USB_DT_CONFIG,                         // CONFIGURATION descriptor type
		sizeof(configuration0_descriptor),     // Total length of data for this configuration
		NUM_INTERFACES,                      // Number of interfaces in this configuration
		CONFIGURATION0_BCONFIGURATIONVALUE,                      // Index value of this configuration (must be != 0)
		0,                      // Configuration string index
		USB_CONFIG_ATT_ONE,     // Attributes
		250                     // Max power consumption (x * 2 mA) // 500mA is max
	},
	// Boot Interface Descriptor
	{
		sizeof(struct usb_interface_descriptor),   // Size of this descriptor in bytes
		USB_DT_INTERFACE,   // Interface descriptor type
		0,                      // Interface Number
		0,                      // Alternate Setting Number
		USB_CONFIG_NUM_ENDPOINTS,       // Number of endpoints in this interface
		0xff,                   // Class code
		0xff,                   // Subclass code
		0xff,                   // Protocol code
		0		// Interface string index
	}
#if USB_CONFIG_NUM_ENDPOINTS > 0
#ifdef USB_CONFIG_ENDPOINTS_DESCRIPTORS
	,
	{
		USB_CONFIG_ENDPOINTS_DESCRIPTORS()
	}
#elif USB_CONFIG_NUM_ENDPOINTS != 0
#warning USB_CONFIG_ENDPOINTS_DESCRIPTORS not defined
#endif
#endif
};


/* String descriptors */
/* Language desriptors (Unicode 3.0 (UTF-16) */
const unsigned char __code string0_descriptor[] = {
	sizeof(string0_descriptor),
	USB_DT_STRING,
	0x09, 
	0x04 // english = 0x409
};

// remember to undef it!!!!
#define _(x) (x), (0x00), 

const unsigned char __code string1_descriptor[] = {
	sizeof(string1_descriptor),	// bLength
	USB_DT_STRING,	// bDescriptorType
	_('K')_('o')_('l')_('o')_('T')_('e')_('c')_('h')_(' ')
};

const unsigned char __code string2_descriptor[] = {
	sizeof(string2_descriptor),	// bLength
	USB_DT_STRING,	// bDescriptorType
#ifdef USB_CONFIG_STRING2_DESCRIPTOR_
	USB_CONFIG_STRING2_DESCRIPTOR_()
#else
	_('K')_('o')_('l')_('o')_('r')_('s')_(' ')_('U')_('S')_('B')_(' ')_('f')_('i')_('r')_('m')_('w')_('a')_('r')_('e')_(' ')
#endif
};

const unsigned char __code string3_descriptor[] = {
	sizeof(string3_descriptor),	// bLength
	USB_DT_STRING,	// bDescriptorType
#ifdef USB_CONFIG_STRING3_DESCRIPTOR_
	USB_CONFIG_STRING3_DESCRIPTOR_()
#else
	_('4')_('7')_('1')
#endif
};

#undef _
