/*
 * usb_ep0.h
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
#ifndef _USB_EP0_H_
#define _USB_EP0_H_

/* ----------- config ------------- */
// in usb.h
/* ------------- end of config -------------- */

/* macros to buffer descriptors used by endp0 */

#if USB_BUFFER_DESCRIPTOR_MODE == 0 || USB_BUFFER_DESCRIPTOR_MODE == 3

	#define USB_EP0_BUFFERING_NUMBER 0
	#define USB_EP0_BUFFERING_NORMAL 1

	#define USB_BD_OUT_EP0_PREV()		( (const usb_bd_t __near *)&usb_bd[0] )
	#define USB_BD_OUT_EP0()		( &usb_bd[0] )
	#define USB_BD_OUT_EP0_NEXT()		( &usb_bd[0] )
	
	#define USB_BD_IN_EP0_PREV()  		( (const usb_bd_t __near *)&usb_bd[1] )
	#define USB_BD_IN_EP0()			( &usb_bd[1] )
	#define USB_BD_IN_EP0_NEXT()		( &usb_bd[1] )

#elif USB_BUFFER_DESCRIPTOR_MODE == 1

	#define USB_EP0_BUFFERING_NUMBER 1
	#define USB_EP0_BUFFERING_PING_PONG_OUT 1
	#define USB_EP0_BUFFERING_PING_PONG_OUT_ONLY 1
	
	#define USB_BD_OUT_EP0_PREV()		( (const usb_bd_t __near *)&usb_bd[usb_ustat.USTATbits.PPBI] )
	#define USB_BD_OUT_EP0()		( &usb_bd[usb_ustat.USTATbits.PPBI^0x01] )
	#define USB_BD_OUT_EP0_NEXT()		( &usb_bd[usb_ustat.USTATbits.PPBI] )
	
	#define USB_BD_IN_EP0_PREV()  		( (const usb_bd_t __near *)&usb_bd[2] )
	#define USB_BD_IN_EP0()			( &usb_bd[2] )
	#define USB_BD_IN_EP0_NEXT()		( &usb_bd[2] )
	
#elif  USB_BUFFER_DESCRIPTOR_MODE == 2

	#define USB_EP0_BUFFERING_NUMBER 2
	#define USB_EP0_BUFFERING_PING_PONG 1
	#define USB_EP0_BUFFERING_PING_PONG_IN 1
	#define USB_EP0_BUFFERING_PING_PONG_OUT 1
	
	#define USB_BD_OUT_EP0_PREV()		( (const usb_bd_t __near *)&usb_bd[usb_ustat.USTATbits.PPBI] )
	#define USB_BD_OUT_EP0()		( &usb_bd[usb_ustat.USTATbits.PPBI^0x01] )
	#define USB_BD_OUT_EP0_NEXT()		( &usb_bd[usb_ustat.USTATbits.PPBI] )
	
	#define USB_BD_IN_EP0_PREV() 		( (const usb_bd_t __near *)&usb_bd[2 + USB_BD_PP_IN_PNT_GET_NEXT(0)] )
	#define USB_BD_IN_EP0()			( &usb_bd[2 + USB_BD_PP_IN_PNT_GET(0)] )
	#define USB_BD_IN_EP0_NEXT()		( &usb_bd[2 + USB_BD_PP_IN_PNT_GET_NEXT(0)] )

#endif

#endif // _USB_EP0_H_
