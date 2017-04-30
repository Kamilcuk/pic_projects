/*
 * rrbuffer.c
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 */
#include <rrbuffer/rrbuffer.h>
#include "usb_config.h"
#include "usb/usb.h"

#define RRBUFFER_IN_INTERRUPT

/* databank0 is taken by global variables */
//#pragma udata databank0 rrbuffer_databank0
//unsigned char rrbuffer_databank0[128];

#pragma udata databank1 rrbuffer_databank1
unsigned char rrbuffer_databank1[0xf];

#pragma udata databank2 rrbuffer_databank2
unsigned char rrbuffer_databank2[0xFF];

/* databank 3 is taken by stack */
//#pragma udata databank3 rrbuffer_databank3
//unsigned char rrbuffer_databank3[1];

// get rest of databank4, taken by buffer descriptors from usb
#if USB_BUFFER_DESCRIPTOR_MODE != 2
#pragma udata databank4 rrbuffer_databank4
unsigned char rrbuffer_databank4[ 0xff-(( USB_BUFFER_DESCRIPTORS_NUMBER*4 )) ];
#endif

/* get rest of databank 5 taken by EP0 */
#pragma udata databank5 rrbuffer_databank5
#if USB_BUFFER_DESCRIPTOR_MODE == 0 || USB_BUFFER_DESCRIPTOR_MODE == 3
unsigned char rrbuffer_databank5[ 0xff-(2*EP0_BUFFER_SIZE) ];
#elif USB_BUFFER_DESCRIPTOR_MODE == 1
unsigned char rrbuffer_databank5[ 0xff-(3*EP0_BUFFER_SIZE) ];
#elif USB_BUFFER_DESCRIPTOR_MODE == 2
unsigned char rrbuffer_databank5[ 0xff-(4*EP0_BUFFER_SIZE) ];
#endif

/* taken by ep1 and ep2 */
//#pragma udata databank6 rrbuffer_databank6
//unsigned char rrbuffer_databank6[0xFF];

#pragma udata databank7 rrbuffer_databank7
unsigned char rrbuffer_databank7[0xFF];

DEF_RRBUFFER()
//	DEF_BUFF(rrbuffer_databank0)
	DEF_BUFF(rrbuffer_databank1)
	DEF_BUFF(rrbuffer_databank2)
//	DEF_BUFF(rrbuffer_databank3)
#if USB_BUFFER_DESCRIPTORS_NUMBER < 64
	DEF_BUFF(rrbuffer_databank4)
#endif
	DEF_BUFF(rrbuffer_databank5)
//	DEF_BUFF(rrbuffer_databank6)
	DEF_BUFF(rrbuffer_databank7)
END_DEF_RRBUFFER()

/* rrbuffer implementation */
#include <rrbuffer/rrbuffer.c>
