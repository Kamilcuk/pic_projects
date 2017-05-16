/*
 * usb_ep0.h
 * 
 * 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
 * 
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
