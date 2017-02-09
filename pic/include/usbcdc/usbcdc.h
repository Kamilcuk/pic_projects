/* 
File: usbcdc.h

 Copyright (c) 2010,2013 Kustaa Nyholm / SpareTimeLabs

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 
Version 1.1     Compatible with SDCC 3.x 
                Respond to GET_LINE_CODING to work with overzealous 
                Windows software (like Hyperterminal)
*/

#ifndef USBCDC_H
#define USBCDC_H

#define USBCDC_BUFFER_LEN 32
#define USBCDC_SELF_POWERED 0
#define USBCDC_MAXPOWER 100

/**
 * everything in usbram5
 */
#pragma udata usbram5 setup_packet control_transfer_buffer cdc_rx_buffer cdc_tx_buffer cdcint_buffer


/* ----------------------------- USB interrupts ----------------------- */
#define USB_interrupt_priority_high()  do{ IPR2bits.USBIP = 1; }while(0)
#define USB_interrupt_priority_low()   do{ IPR2bits.USBIP = 0; }while(0)
#define USB_interrupt_enable()         do{ PIE2bits.USBIE = 1; }while(0)
#define USB_interrupt_disable()        do{ PIE2bits.USBIE = 0; }while(0)
#define USB_interrupt()                ((PIR2bits.USBIF))
#define USB_interrupt_clear()          do{ PIR2bits.USBIF = 0; } while(0)
#define USB_interrupt_set()            do{ PIR2bits.USBIF = 1; } while(0)
#define USB_interrupt_service() do { \
	if (PIR2bits.USBIF) { \
		usbcdc_handler(); \
		PIR2bits.USBIF = 0; \
	} \
}while(0)

/**
 * exported cdc device state
 */
extern unsigned char usbcdc_device_state;
/**
 * initialize usbcdc module
 */
void usbcdc_init(void);
/**
 * waitiuntil the device is configured
 */
#define usbcdc_wait_config() while(usbcdc_device_state != CONFIGURED)
/**
 * handle usb control messages, poll atleast every 1ms or call from IRQ
 */
void usbcdc_handler(void);
/**
 * puts char into rx buffer.
 * if buffer is full, calls usbcdc_flush()
 */
void usbcdc_putchar(char c) __wparam;
/**
 * flushes rx buffer
 */
void usbcdc_flush();
/**
 * gets char from tx buffer.
 * if buffer is empty, call usbcdc_read();
 * this function will block() until next char is ready
 * @return character readed
 */
char usbcdc_getchar();
/**
 * checks if usbcdc_getchat will block on next read
 */
#define usbcdc_getchar_ready() (usbcdc_rd_ready())
/**
 * this is tx buffer
 */
extern volatile unsigned char usbcdc_tx_buffer[USBCDC_BUFFER_LEN];
/**
 * to write to usbcdc, fill out cdc_tx_buffe and then call usbcdc_write
 */
void usbcdc_write(unsigned char len) __wparam;
/**
 * use this to check, if usbcdc_write has ended
 * @return 1 if busy, 0 if not busy
 */
char usbcdc_wr_busy();
/**
 * rx_buffer
 * usb driver starts reading data after usbcdc_read() call
 * you may use this buffer, when ucbcdc_rd_ready() == true
 */
extern volatile unsigned char usbcdc_rx_buffer[USBCDC_BUFFER_LEN];
/**
 * checks wheater cdc_rc_buffer is ready to receive from
 * @return 1 if ready, 0 if not ready
 */
unsigned char usbcdc_rd_ready();
/**
 * discard cdc_rx_buffer, and starts new reading transaction
 * new data appnded to usbcdc_rx_buffer
 */
void usbcdc_read();
/**
 *
 * @return how much data was read into cdc_rc_buffer during last transaction
 */
unsigned char usbcdc_rd_len();

#endif
