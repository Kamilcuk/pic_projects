/*
 * usb_ep1.c
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
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

#include <pic18f2550.h>
#include "usb_config.h"
#include "usb/usb_usb.h"
#include "cake.h"
#include "usb_ep1.h"


#pragma udata usb_buff USB_EP1_out_buffer
static volatile unsigned char USB_EP1_out_buffer[(USB_BUFFERING_NUMBER+1)][EP1_BUFFER_SIZE];


void USB_EP1_init(void)
{
	usb_bd_t __near *bdpnt;
	unsigned char i;
	for (i=0; i<sizeof(USB_EP1_out_buffer); i++)
		((unsigned char *)USB_EP1_out_buffer)[i] = 0;
	
	bdpnt = USB_BD_OUT_EP_PP(1, 0);
	bdpnt->cnt = EP1_BUFFER_SIZE;
	bdpnt->adr = USB_EP1_out_buffer[0];
	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA0 | BD_STAT_DTSEN;

#ifdef USB_BUFFERING_PING_PONG
	bdpnt = USB_BD_OUT_EP_PP(1, 1);
	bdpnt->cnt = EP1_BUFFER_SIZE;
	bdpnt->adr = USB_EP1_out_buffer[1];
	bdpnt->stat = BD_STAT_USIE | BD_STAT_DATA1 | BD_STAT_DTSEN;
#endif
	
	UEP1 = UEP_EPHSHK | UEP_EPOUTEN;
}

void USB_EP1_transmission(void)
{
	usb_bd_t __near * const bdpnt = USB_BD_OUT_EP_NEXT(1);
	
	cake_eat_basket(bdpnt->adr, bdpnt->cnt);
	
	bdpnt->cnt = EP1_BUFFER_SIZE;
	
	USB_BD_SET_STAT(bdpnt);
}
