/*
 * usb_ep2.c
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 * 
 */
#include <pic18f2550.h>
#include "usb_config.h"
#include "usb/usb_usb.h"
#include "usb_ep2.h"
#include "cake.h"

#pragma udata usb_buff USB_EP2_in_buffer
static volatile unsigned char USB_EP2_in_buffer[USB_BUFFERING_NUMBER+1][EP2_BUFFER_SIZE];

struct {
	unsigned char len; /* bytes to send */
	const unsigned char __near *src; /* pointer to buff to be sended */
} static to_send;

void USB_EP2_init(void)
{
	__near usb_bd_t *bdpnt;
	unsigned char i;
	for (i=0; i<sizeof(USB_EP2_in_buffer); i++)
		((unsigned char *)USB_EP2_in_buffer)[i] = 0;
	
	bdpnt = USB_BD_IN_EP_PP(2, 0);
	bdpnt->adr = USB_EP2_in_buffer[0];
	bdpnt->cnt = 0;
	bdpnt->stat = BD_STAT_UCPU | BD_STAT_DATA0 | BD_STAT_DTSEN;
	
#ifdef USB_BUFFERING_PING_PONG
	bdpnt = USB_BD_IN_EP_PP(2, 1);
	bdpnt->adr = USB_EP2_in_buffer[1];
	bdpnt->cnt = 0;
	bdpnt->stat = BD_STAT_UCPU | BD_STAT_DATA1 | BD_STAT_DTSEN;
#endif
		
	UEP2 = UEP_EPHSHK | UEP_EPINEN;
}

static void fill_and_set_send(usb_bd_t __near * const bdpnt) 
{
	unsigned char __near * const dst = bdpnt->adr;
	const unsigned char __near * const src = to_send.src;
	unsigned char i;
	unsigned char len;
	
	if ( to_send.len < EP2_BUFFER_SIZE ) {
		len = to_send.len;
		to_send.len = 0x00;
	} else {
		/* theres something more to send */
		len = EP2_BUFFER_SIZE;
		to_send.len -= EP2_BUFFER_SIZE;
	}
	/* increase position in our buffer */
	to_send.src += len;
	
	/* copy buffer */
	for (i=0; i<len; i++) {
		dst[i] = src[i];
	}
	
	/* set count */
	bdpnt->cnt = len;
	
	USB_BD_SET_STAT(bdpnt);
}

void USB_EP2_set(const void __near *src, unsigned char len)
{
	usb_bd_t __near *bdpnt = USB_BD_IN_EP(2);
	
	if ( bdpnt->statbits.UOWN ) {
		#ifdef USB_BUFFERING_PING_PONG
		bdpnt = USB_BD_IN_EP_NEXT(2);
		if ( bdpnt->statbits.UOWN ) {
			/* both buffer descriptor already under SIE control, discard packet */
			return;
		}
		fill_and_set_send(bdpnt);
		#endif
		return;
	} else {
	
		/* set to_send struct */
		to_send.len = len;
		to_send.src = src;
		
		/* set send */
		fill_and_set_send(bdpnt);
		
		#ifdef USB_BUFFERING_PING_PONG
		if ( to_send.len ) {
			bdpnt = USB_BD_IN_EP_NEXT(2);
			if ( bdpnt->statbits.UOWN ) {
				return;
			} 
			fill_and_set_send(bdpnt);
		}
		#endif
	}
}

void USB_EP2_transmission(void)
{
	usb_bd_t __near *bdpnt = USB_BD_IN_EP_NEXT(2);
	
	if (to_send.len) {
		/* theres still something to send */
		fill_and_set_send(bdpnt);
	}
	
	/* else do nothing */
	
	/* nothing really to do here ... */
	
	return;
}


