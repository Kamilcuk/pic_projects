/*
 * hd44780.h
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
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
#ifndef _HD44780_H_
#define _HD44780_H_

#include "hd44780-config.h"
#include "types.h"

#define NUM_CONTROLLERS 5 /* number of controlers per every usb device */
#define ROWS_PER_CTRL 2 /* number of rows every hd44780 has */
#define DISP_COLS 40  /* number of columns every hd44780 has */


/* lcddev.flags */
#define FLAG_NOBFCHECK		1

#ifdef HD44780_COUNTERS
struct lcd_device {
	unsigned long int write_count;
	unsigned long int read_count;
	unsigned long int bfchecks_count;
};
#endif

/* our big struct */
struct pic_device {
#ifdef HD44780_COUNTERS
	struct lcd_device lcd[NUM_CONTROLLERS];
#endif
	
	
	unsigned char flags;
};


#define write_inst(ctrl, inst)		hd44780_send(ctrl, RS_INST, inst)
#define write_data(ctrl, data)		hd44780_send(ctrl, RS_DATA, data);
#define read_inst(ctrl)			hd44780_recv(ctrl, RS_INST)
#define read_data(ctrl)			hd44780_recv(ctrl, RS_DATA)
#define write_inst_all(inst)		hd44780_send_all(RS_INST, inst)
#define write_data_all(data)		hd44780_send_all(RS_DATA, data)

extern struct pic_device lcddev;

extern void hd44780_init(void);
extern __u8 hd44780_recv(__u8 ctrl_nr, __u8 flags);
extern void hd44780_send(__u8 ctrl_nr, __u8 flags, __u8 command);
extern void hd44780_send_all(__u8 flags, __u8 command);

#endif // _HD44780_H_
