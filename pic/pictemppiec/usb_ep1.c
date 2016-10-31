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

#include <pic18freqs.h>
#include "usb_config.h"
#include "usb/usb.h"
#include "usb_ep1.h"
#include <adc.h>

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

void USB_EP1_transmission(void)
{
	usb_bd_t __near * const bdpnt = USB_BD_IN_EP(1);
	usb_bd_t __near * const bdpnt_next = USB_BD_IN_EP_NEXT(1);
	
	int __near *adr = (int __near *)bdpnt_next->adr;
	unsigned char i;
	
	for(i=0; i<10; i++) {
		*adr = 0;	// read value
		adr++;
	}
	
	bdpnt_next->cnt = 20;
	
	// toggle the DATA01 bit, clear the PIDs bits, and set the UOWN and DTS bits
	bdpnt_next->stat = BD_STAT_USIE | ( (bdpnt->stat^0x40)&0x40 ) | BD_STAT_DTSEN;
}
