/*
 * usb.h
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
#ifndef _USB_H_
#define _USB_H_

#include <pic18fregs.h>

#define NUM_CONFIGURATIONS	1
#define NUM_INTERFACES		1

#ifndef USB_BUFFER_DESCRIPTOR_MODE
#define USB_BUFFER_DESCRIPTOR_MODE 0
#endif
#ifndef EP0_BUFFER_SIZE
#define EP0_BUFFER_SIZE 8
#endif
#if EP0_BUFFER_SIZE != 8 && EP0_BUFFER_SIZE != 16 &&  EP0_BUFFER_SIZE != 32 &&  EP0_BUFFER_SIZE != 64
#error Incorrect EP0_BUFFER_SIZE. Value MUST be one of the numbers: 8, 16, 32, 64.
#endif
#ifndef USB_VENDOR_REQUEST
#define USB_VENDOR_REQUEST() USB_request_error()
#endif
#ifndef USB_CLASS_REQUEST
#define USB_CLASS_REQUEST() USB_request_error()
#endif

/* -----------  endpoints -------------- */

/* how to add new endpoint?
 * new endpoint needs to:
 * init function -> all will be called as USB_CONFIG_ENDPOINTS_INIT(); macro
 * transmission function -> define USB_EPx_TRANSMISSION(); macro -> will be called when this endp gets a transmission
 * define endpoint description -> add to USB_EPx_DESCRIPTOR() macro
 * and thats all 
 * */

/* --------------- end of config -------------- */


/* ******* configuration -> bConfigurationValue
 * every configuration needs to have unique number different then 0 */
#define CONFIGURATION0_BCONFIGURATIONVALUE 1


// USB internal variables ; managed in USB_EP0 and somewhere else too..
struct usb_device_info {
	unsigned char status : 2; // USB device status, USB documentation chapter 9
	unsigned char state : 3; // there are 6 states from usb documentation
	/* i have now only one configuration, so this bit is only 1 bit long
	 * but if you will add a config you need to increase it */
	unsigned char config; // number of current configuration used
};


/* *************************** USB BUFFER DESCRIPTOR ************************** */

/* buffer descritors typedef
 * 
 * PIC documentation page 171 and whole section 17 
 * BDnSTAT (CPU MODE) : UOWN DTS KEN INCDIS DTSEN BSTALL BC9 BC8 
 * DBnSTAT (SIE MODE) : UOWN - PID3 PID2 PID1 PID0 BC9 Bc8 or UOWN PID:4 - -
 * BDnCNT: BC7 BC6 BC5 BC4 BC3 BC2 BC1 BC0 
 * BDnADRH and BDnADRL no aliases... 
 * BDnADRH and BDnADRL - 16 bits long
 * __near - lets creating pointers to the data space
 * __near and __data - its the same
 * 
 * BDstat - BufferDescriptor stat
 * 
 * name: usb_bd_t - USB_BufferDescriptor_typedef
 * */
 
/* Buffer Descriptor Status Register */
union usb_bd_stat {
    unsigned char uc;
    struct{
        unsigned BC8:1;
        unsigned BC9:1;
        unsigned BSTALL:1; // Buffer Stall Enable
        unsigned DTSEN:1;  // Data Toggle Synch Enable
        unsigned INCDIS:1; // Address Increment Disable
        unsigned KEN:1;    // BD Keep Enable
        unsigned DTS:1;    // Data Toggle Synch Value
        unsigned UOWN:1;   // USB Ownership
    };
    struct{
        unsigned :2;
        unsigned PID0:1;   // Packet Identifier, bit 0
        unsigned PID1:1;   // Packet Identifier, bit 1
        unsigned PID2:1;   // Packet Identifier, bit 2
        unsigned PID3:1;   // Packet Identifier, bit 3
        unsigned :2;
    };
    struct{
        unsigned :2;
        unsigned PID:4;    // Packet Identifier
        unsigned :2;
    };
};

union usb_bd_cnt {
	unsigned char uc;
	struct {
		unsigned char BC0 : 1;
		unsigned char BC1 : 1;
		unsigned char BC2 : 1;
		unsigned char BC3 : 1;
		unsigned char BC4 : 1;
		unsigned char BC5 : 1;
		unsigned char BC6 : 1;
		unsigned char BC7 : 1;
	};
};


typedef struct {
	union { //  BDnSTAT 8 bits
		unsigned char stat; 
		union usb_bd_stat statbits;
	};
	union {  // BDnCNT 8 bits
		unsigned char cnt;
		union usb_bd_cnt cntbits;
	};
	union { // BDnADRH and BDnADRL - 16 bits long
		unsigned char __near *adr; 
		struct {
			unsigned char adrl; // Buffer Address Low
			unsigned char adrh; // Buffer Address High
		};
	};
} usb_bd_t;


/* USB_BUFFER_DESCRITPTORS
 * 
 * USB buffers start at 0x400 and end 0x4FF. 
 * THere are up to 64 buffer descriptors to define
 * but the number depends on your configuration
 * refer to PIC documentation page 175
 * there is everything exmplained
 * Ping=pong buffer  first is even, then odd
 * Table: documentatino page 176 Table 17-4
 * Mode 0 - without ping-pong buffers - 64 buffers
 * Mode 1 - Ping-Pong on Ep0 OUT only
 * Mode 2 - Ping-Pong on all endpoints
 * Mode 3 - Ping-Pong on all endpoints exept EP0
 -------------------------------------------------
     |           number of BD assigned to Endpoint ( BDx )
 EP  |        Mode 0        |        Mode 1         |        Mode 2         |         Mode 3        |
     | OUT       | IN       | OUT       | IN        | OUT       | IN        | OUT       | IN        |
 ----------------------------------------------------------------------------------------------------
  0  |  0        |  1       | 0(E) 1(O) |  2        | 0(E) 1(O) | 2(E) 3(O) |     0     |      1    |
  1  |  2        |  3       |  3        |  4        | 4(E) 5(O) | 6(E) 7(O) | 2(E) 3(O) | 4(E) 5(O) |
 ..
 * and so on....
 */

#define USB_BUFFER_DESCRIPTOR_MODE_NO_PING_PONG_BUFFERS 0
#define USB_BUFFER_DESCRIPTOR_MODE_PING_PONG_ON_EP0_OUT_ONLY 1
#define USB_BUFFER_DESCRIPTOR_MODE_PING_PONG_ON_ALL_ENDPOINTS 2
#define USB_BUFFER_DESCRIPTOR_MODE_PING_PONG_ON_ALL_ENDPOINTS_EXEPT_EP0 3

/* ************ DEFINES to buffer descriptors ****************
 * USB_BD_*_EP_PREV() - the last transmission occured here
 * USB_BD_*_EP() - the next transmission will occur here, this needs to be set/filled 
 * USB_BD_*_EP_NEXT() - the secend next transissino will occur here, this needs to be set/filled  */

#define USB_BD_OUT_EP_PREV(num)         USB_BD_OUT_EP_PP(num, USB_BD_PP_OUT_PNT_GET_NEXT(num))
#define USB_BD_OUT_EP(num) 	            USB_BD_OUT_EP_PP(num, USB_BD_PP_OUT_PNT_GET(num))
#define USB_BD_OUT_EP_NEXT(num)         USB_BD_OUT_EP_PP(num, USB_BD_PP_OUT_PNT_GET_NEXT(num))
#define USB_BD_OUT_EP_NEXT_NEXT(num)    USB_BD_OUT_EP_PP(num, USB_BD_PP_OUT_PNT_GET(num))

#define USB_BD_IN_EP_PREV(num) 	        USB_BD_IN_EP_PP(num, USB_BD_PP_IN_PNT_GET_NEXT(num))
#define USB_BD_IN_EP(num)               USB_BD_IN_EP_PP(num, USB_BD_PP_IN_PNT_GET(num))
#define USB_BD_IN_EP_NEXT(num) 	        USB_BD_IN_EP_PP(num, USB_BD_PP_IN_PNT_GET_NEXT(num))
#define USB_BD_IN_EP_NEXT_NEXT(num)     USB_BD_IN_EP_PP(num, USB_BD_PP_IN_PNT_GET(num))
 
#if USB_BUFFER_DESCRIPTOR_MODE == 0
	#define USB_BUFFERING_NUMBER 0
	#define USB_BUFFERING_NORMAL 1
	#define USB_BUFFER_DESCRIPTORS_NUMBER 32

	#define USB_BD_OUT_EP_PP(endp, pp) 		(( &usb_bd[(endp<<1)    ] ))
	#define USB_BD_IN_EP_PP(endp, pp)  		(( &usb_bd[(endp<<1) + 1] ))

#elif  USB_BUFFER_DESCRIPTOR_MODE == 1
	#define USB_BUFFERING_NUMBER 0
	#define USB_BUFFERING_NORMAL 1
	#define USB_BUFFER_DESCRIPTORS_NUMBER 33
	
	#define USB_BD_OUT_EP_PP(endp, pp) 		(( &usb_bd[(endp<<1) + 1] ))
	#define USB_BD_IN_EP_PP(endp, pp)  		(( &usb_bd[(endp<<1) + 2] ))

#elif  USB_BUFFER_DESCRIPTOR_MODE == 2
	#define USB_BUFFERING_NUMBER 1
	#define USB_BUFFERING_PING_PONG 1
	#define USB_BUFFER_DESCRIPTORS_NUMBER 64
	
	#define USB_BD_OUT_EP_PP(endp, pp) 		(( &usb_bd[(endp<<2) + pp    ] ))
	#define USB_BD_IN_EP_PP(endp, pp)		(( &usb_bd[(endp<<2) + pp + 2] ))

#elif  USB_BUFFER_DESCRIPTOR_MODE == 3
	#define USB_BUFFERING_NUMBER 1
	#define USB_BUFFERING_PING_PONG 1
	#define USB_BUFFER_DESCRIPTORS_NUMBER 62
	
	#define USB_BD_OUT_EP_PP(endp, pp)		(( &usb_bd[(endp<<2) + pp - 2] ))
	#define USB_BD_IN_EP_PP(endp, pp)		(( &usb_bd[(endp<<2) + pp    ] ))
	
#else
	#error USB_BUFFER_DESCRIPTOR_MODE is wrong.
#endif


/* USB_BD_SET_STAT - making live easier with ping-pong buffering */
#ifdef USB_BUFFERING_NORMAL
	// toggle the DATA01 bit, clear the PIDs bits, and set the UOWN and DTS bits
	#define USB_BD_SET_STAT(bdpnt) do { bdpnt->stat = BD_STAT_USIE | ( (bdpnt->stat&BD_STAT_MASK_DTS)^BD_STAT_MASK_DTS ) | BD_STAT_DTSEN; }while (0)
#else
	// leave the DATA01 bit, clear the PIDs bits, and set the UOWN and DTS bits
	#define USB_BD_SET_STAT(bdpnt) do { bdpnt->stat = BD_STAT_USIE | (bdpnt->stat&BD_STAT_MASK_DTS) | BD_STAT_DTSEN; }while (0)
#endif



/* ****************** USB_BD_PingPong_PoiNTers ************** */
/* bits indicating pointers to banks even/odd
 * it indicates the bank where the _NEXT_ transaction will be on [not like USTATbits.PPBI] !!!!
 * USB_BD_PP_IN_PNT_GET(1) == 0 - next transaction will be to EVEN bank
 * USB_BD_PP_IN_PNT_GET(1) == 1 - next transaction will be to ODD bank
 * it gets inverted *before* going function called after SIE processed specifed token
 * so right after SIE  gets transmission, but before going into a specified function
 * every bit is assigned to another endpoint and every bit indicates bank that will be next used in a transaction for in endpoint
 * in endpoints must be filled BEFORE an in token occurs, so we need to keep track of them.
 * look also at macros USB_BD_PP_IN_{GET,INC} 
 * it is used only for in endpoint, cause banks for out endpoints can be readed from USTATbits.PPBI bit
 * */

#define USB_BD_PP_OUT_PNT_INC(endp)      USB_BD_PP_PNT_INC( usb_ustat.pp_out_pnt, endp)
#define USB_BD_PP_OUT_PNT_GET(endp)      USB_BD_PP_PNT_GET( usb_ustat.pp_out_pnt, endp)
#define USB_BD_PP_OUT_PNT_GET_NEXT(endp) USB_BD_PP_PNT_GET_NEXT( usb_ustat.pp_out_pnt, endp)

#define USB_BD_PP_IN_PNT_INC(endp)      USB_BD_PP_PNT_INC( usb_ustat.pp_in_pnt, endp)
#define USB_BD_PP_IN_PNT_GET(endp)      USB_BD_PP_PNT_GET( usb_ustat.pp_in_pnt, endp)
#define USB_BD_PP_IN_PNT_GET_NEXT(endp) USB_BD_PP_PNT_GET_NEXT( usb_ustat.pp_in_pnt, endp)

#if USB_BUFFER_DESCRIPTOR_MODE >= 2
#define USB_BD_PP_PNT_NUMBER ((USB_CONFIG_NUM_ENDPOINTS/8+1))

#if USB_CONFIG_NUM_ENDPOINTS < 8
#define USB_BD_PP_PNT_INC(val, endp) do{ const unsigned char _n = (endp); val[0] ^= (1<<(_n)); }while(0)
#define USB_BD_PP_PNT_GET(val, endp) (( ( val[0]>>(endp) )&(0x01) ))
#else
#define USB_BD_PP_PNT_INC(val, endp) do{ const unsigned char _n = (endp); val[_n/8] ^= (1<<(_n%8)); }while(0)
#define USB_BD_PP_PNT_GET(val, endp) (( ( val[(((endp)/8))]>>((endp)%8) )&(0x01) ))
#endif

#define USB_BD_PP_PNT_GET_NEXT(val, endp) (( USB_BD_PP_PNT_GET(val, endp)^(0x01) ))

#else
#define USB_BD_PP_PNT_NUMBER 0
#define USB_BD_PP_PNT_INC(val, endp) do{ }while(0)
#define USB_BD_PP_PNT_GET(val, endp) (0)
#define USB_BD_PP_PNT_GET_NEXT(val, endp) (0)
#endif


/* ********************** ENDOF USB BUFFER DESCRIPTOR ********************* */

/* UEPn Initialization Parameters */
// Handshake should be disable for isoch
#define UEP_EPHSHK           0x10 // Enable handshake packet
#define UEP_EPCONDIS         0x08
#define UEP_EPOUTEN          0x04
#define UEP_EPINEN           0x02
#define UEP_EPSTALL          0x01

                                    
/* Buffer Descriptor Status Register Parameters */
#define BD_STAT_BSTALL          0x04 //Buffer Stall enable
#define BD_STAT_DTSEN           0x08 //Data Toggle Synch enable
#define BD_STAT_INCDIS          0x10 //Address increment disable
#define BD_STAT_KEN             0x20 //SIE keeps buff descriptors enable
#define BD_STAT_DATA0           0x00 //DATA0 packet expected next
#define BD_STAT_DATA1           0x40 //DATA1 packet expected next
#define BD_STAT_USIE            0x80 //SIE owns buffer
#define BD_STAT_UCPU            0x00 //CPU owns buffer

#define BD_STAT_MASK_BSTALL     0x04
#define BD_STAT_MASK_DTSEN      0x08
#define BD_STAT_MASK_INCDIS     0x10
#define BD_STAT_MASK_KEN        0x20
#define BD_STAT_MASK_DTS        0x40
#define BD_STAT_MASK_UOWN       0x80

/* USB device states */
#define DETACHED_STATE              0x00
#define ATTACHED_STATE              0x01
#define POWERED_STATE               0x02
#define DEFAULT_STATE               0x03
#define ADDRESS_PENDING_STATE       0x04 // preparing to change state
#define ADDRESS_STATE               0x05
#define CONFIGURED_PENDING_STATE    0x06 // preparing to change configuration
#define CONFIGURED_STATE            0x07

/* usb documentatino table 8-1 - PID_TYPE_NAME */
#define USB_PID_EXT                     0x0    /* USB 2.0 LPM ECN */
#define USB_PID_OUT                     0x1
#define USB_PID_ACK                     0x2
#define USB_PID_DATA0                   0x3
#define USB_PID_PING                    0x4    /* USB 2.0 */
#define USB_PID_SOF                     0x5
#define USB_PID_NYET                    0x6    /* USB 2.0 */
#define USB_PID_DATA2                   0x7    /* USB 2.0 */
#define USB_PID_SPLIT                   0x8    /* USB 2.0 */
#define USB_PID_IN                      0x9
#define USB_PID_NAK                     0xa
#define USB_PID_DATA1                   0xb
#define USB_PID_PREAMBLE                0xc    /* Token mode */
#define USB_PID_ERR                     0xc    /* USB 2.0: handshake mode */
#define USB_PID_SETUP                   0xd
#define USB_PID_STALL                   0xe
#define USB_PID_MDATA                   0xf    /* USB 2.0 */


#ifndef USB_ACTIVE_FUNCTION
#define USB_ACTIVE_FUNCTION()
#endif


#ifndef USB_SUSPEND_FUNCTION
#define USB_SUSPEND_FUNCTION()
#endif


struct usb_ustat_save {
	union {
		unsigned char USTAT;
		__USTATbits_t USTATbits;
	};
#if defined(USB_BD_PP_PNT_NUMBER) && USB_BD_PP_PNT_NUMBER != 0
	unsigned char pp_in_pnt[USB_BD_PP_PNT_NUMBER];
	unsigned char pp_out_pnt[USB_BD_PP_PNT_NUMBER];
#endif
};

#ifndef __USB__
extern struct usb_ustat_save usb_ustat;
extern volatile usb_bd_t __near usb_bd[USB_BUFFER_DESCRIPTORS_NUMBER];
#endif

#endif // _USB_H_
