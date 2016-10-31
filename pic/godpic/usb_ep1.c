/*
 * usb_ep1.c
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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
 * 
 */

#include <pic18fregs.h>
#include "usb_config.h"
#include <usb/usb_usb.h>
#include "usb_ep1.h"
#include <usart.h>

// EP1 in pic
// EP2 out pic

#pragma udata databank6 USB_EP1_buffer
static volatile unsigned char USB_EP1_buffer[USB_BUFFERING_NUMBER+1][EP1_BUFFER_SIZE];
#pragma udata databank6 USB_EP2_buffer
static volatile unsigned char USB_EP2_buffer[USB_BUFFERING_NUMBER+1][EP2_BUFFER_SIZE];

void USB_EP1_init(void)
{
	usb_bd_t __near *bdpnt;
	unsigned char i;
	for (i=0; i<sizeof(USB_EP1_buffer); i++)
		((unsigned char *)USB_EP1_buffer)[i] = 0;
	
	bdpnt = USB_BD_OUT_EP_PP(1, 0);
	bdpnt->cnt = EP1_BUFFER_SIZE;
	bdpnt->adr = USB_EP1_buffer[0];
	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN;
	
	UEP1 = UEP_EPHSHK | UEP_EPOUTEN;
}


void USB_EP2_init(void)
{
	__near usb_bd_t *bdpnt;
	unsigned char i;
	for (i=0; i<sizeof(USB_EP2_buffer); i++)
		((unsigned char *)USB_EP2_buffer)[i] = 0;
	
	bdpnt = USB_BD_IN_EP_PP(2, 0);
	bdpnt->adr = USB_EP2_buffer[0];
	bdpnt->cnt = 0;
	bdpnt->stat = BD_STAT_UCPU | BD_STAT_DATA0 | BD_STAT_DTSEN;
	
	UEP2 = UEP_EPHSHK | UEP_EPINEN;
}

void USB_EP2_send(char *src)
{
	usb_bd_t __near *bdpnt = USB_BD_IN_EP(2);
	unsigned char __near *dst = bdpnt->adr;
	unsigned char i;
	unsigned char end = 0;
	
	
	while( *src != '\0' ) {
		while ( bdpnt->statbits.UOWN ) ; // wait for it tobecame ours.
	
		/* copy buffer */
		for (i=0; i<EP2_BUFFER_SIZE; i++) {
			*dst = *src;
			if ( *src == '\0' ) {
				break;
			}
			dst++;
			src++;
		}
		
		/* set count */
		bdpnt->cnt = i;
		
		USB_BD_SET_STAT(bdpnt);
	}
}

void USB_EP2_transmission(void)
{
	;
	/* empty */
	
}
#include <delay.h>

void USB_EP1_transmission(void)
{
	usb_bd_t __near * const bdpnt = USB_BD_OUT_EP_NEXT(1);
	unsigned char __near *msg = bdpnt->adr;
	unsigned char cnt = bdpnt->cnt;
	unsigned char i;
	
	/* while (cnt) {
		while ( usart_busy() ) {}
		usart_putc(*msg);
		
		msg++;
		cnt--;
		
	} */
	
	
	while ( usart_busy() ) {}
	usart_putc(0xf0);
	delay100tcy(1);
	while ( usart_busy() ) {}
	usart_putc(0x0f);
	delay100tcy(1);
	while ( usart_busy() ) {}
	usart_putc(0xf0);
	delay100tcy(1);
	while ( usart_busy() ) {}
	usart_putc(0x0f);
	delay100tcy(1);
	
	bdpnt->cnt = EP1_BUFFER_SIZE;
	
	USB_BD_SET_STAT(bdpnt);
}
