/*
 * usb_ep1.c
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 * 
 */

#include <pic18fregs.h>
#include "usb_config.h"
#include <usb/usb_usb.h>
#include "usb_ep1.h"

#pragma udata databank6 USB_EP1_in_buffer
static volatile unsigned char USB_EP1_in_buffer[USB_BUFFERING_NUMBER+1][EP1_BUFFER_SIZE];

void USB_EP1_init(void)
{
	__near usb_bd_t *bdpnt;
	unsigned char i;
	for (i=0; i<sizeof(USB_EP1_in_buffer); i++)
		((unsigned char *)USB_EP1_in_buffer)[i] = 0;
	
	bdpnt = USB_BD_IN_EP_PP(1, 0);
	bdpnt->adr = USB_EP1_in_buffer[0];
	bdpnt->cnt = EP1_BUFFER_SIZE;
	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
	
#ifdef USB_BUFFERING_PING_PONG
	bdpnt = USB_BD_IN_EP_PP(1, 1);
	bdpnt->adr = USB_EP1_in_buffer[1];
	bdpnt->cnt = EP1_BUFFER_SIZE;
	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN;
#endif
		
	UEP1 = UEP_EPHSHK | UEP_EPINEN;
}

static unsigned char buffer_fill = 0;

void godpic_flush()
{
	usb_bd_t __near *bdpnt = USB_BD_IN_EP(1);
	if ( buffer_fill != 0 ) {
		bdpnt->cnt = buffer_fill;
		USB_BD_SET_STAT(bdpnt);
	}
	buffer_fill = 0;
	/* block */
	while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
}

void godpic_puts(char *src)
{
	usb_bd_t __near *bdpnt = USB_BD_IN_EP(1);
	unsigned char __near *dst = bdpnt->adr;
	unsigned char i;
	
	godpic_flush();
	
	while( *src != '\0' ) {
		while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
	
		/* copy buffer */
		for (i=0; i<EP1_BUFFER_SIZE; i++) {
			*dst = *src;
			if ( *src == '\0' ) {
				break;
			}
			dst++;
			src++;
		}
		
		buffer_fill = i;
		godpic_flush();
	}
}

void godpic_putc(char src)
{
	usb_bd_t __near *bdpnt = USB_BD_IN_EP(1);
	unsigned char __near *dst = bdpnt->adr;
	
	if ( buffer_fill == EP1_BUFFER_SIZE ) {
		godpic_flush();
		while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
	}
		
	
	dst[buffer_fill] = src;
	buffer_fill++;
}

void USB_EP1_transmission(void)
{
	;
	/* empty */
	
}
