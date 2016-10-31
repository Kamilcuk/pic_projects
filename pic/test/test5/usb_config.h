#ifndef _USB_CONFIG_H_
#define _USB_CONFIG_H_

#define USB_CONFIG_NUM_ENDPOINTS 	(0) // bNumEndpoints (excluding EP0)


#define USB_CONFIG_DEVICE_CLASS 0x00
#define USB_CONFIG_DEVICE_SUBCLASS 0x00
#define USB_CONFIG_DEVICE_PROTOCOL 0x00
#define USB_CONFIG_DEVICE_VENDOR 0xd805
#define USB_CONFIG_DEVICE_PRODUCT 0x0011
#define USB_CONFIG_DEVICE_RELEASE 0x0101

/* USB_BUFFER_DESCRITION_MODE
 * usb buffer description mapping mode:
 * Table: pic18f2550 documentatino page 176 Table 17-4
 * Mode 0 - without ping-pong buffers - 64 buffers
 * Mode 1 - Ping-Pong on Ep0 OUT only
 * Mode 2 - Ping-Pong on all endpoints
 * Mode 3 - Ping-Pong on all endpoints exept EP0 */
#define USB_BUFFER_DESCRIPTOR_MODE 0

/* EP0 biffer size 
 * for low-speed peripherals must be 8 bytes
 * for full-speed peripherals one of the folliwing: 8, 16, 32, or 64 bytes */
#define EP0_BUFFER_SIZE 8


#define USB_CONFIG_STRING2_DESCRIPTOR_() \
_('K')_('o')_('l')_('o')_('r')_('s')_(' ') \
_('U')_('S')_('B')_(' ')_('f')_('i')_('r')_('m')_('w')_('a')_('r')_('e')_(' ')_('e')_('x')_('a')_('m')_('p')_('l')_('e')_(' ')


#endif // _USB_CONFIG_H_

