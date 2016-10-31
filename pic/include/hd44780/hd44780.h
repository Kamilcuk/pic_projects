/*
 * hd44780.h
 * 
 * Copyright 2013 Kamil Cukrowski <kamil@dyzio.pl>
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
#define _HD44780_H_ 1
#include "hd44780-config.h"
#include "hd44780-inst-def.h"


#define MAX_NUM_CONTROLLERS 8 /* MAX number of controlers per every usb device */
#define DISP_ROWS ((ROWS_PER_CTRL*MAX_NUM_CONTROLLERS))  /* number of rows */
#define ONE_CTRL_DISP_SIZE ((DISP_COLS*ROWS_PER_CTRL)) /* number of cells in one controller */
#define DISP_SIZE ((DISP_COLS*DISP_ROWS)) /* size of a whole display */

/* lcddev.flags */


/* our big struct */
struct pic_device {
	unsigned char disabled; /* if bit x is set, that means lcd number x is disabled */
#ifdef HD44780_COUNTERS
	unsigned long int write_count[MAX_NUM_CONTROLLERS];
	unsigned long int read_count[MAX_NUM_CONTROLLERS];
	unsigned long int bfchecks_count[MAX_NUM_CONTROLLERS];
#ifdef HD44780_CHECKER
	unsigned long int errors_count[MAX_NUM_CONTROLLERS];
#endif
#endif
};


#define hd44780_write_inst(ctrl, inst)		hd44780_send(ctrl, RS_INST, inst)
#define hd44780_write_data(ctrl, data)		hd44780_send(ctrl, RS_DATA, data)
#define hd44780_read_inst(ctrl)				hd44780_recv(ctrl, RS_INST)
#define hd44780_read_data(ctrl)				hd44780_recv(ctrl, RS_DATA)
#define hd44780_write_inst_all(inst)		hd44780_send_all(RS_INST, inst)
#define hd44780_write_data_all(data)		hd44780_send_all(RS_DATA, data)

extern struct pic_device lcddev;

extern void hd44780_init(void);
extern unsigned char hd44780_recv(unsigned char ctrl_nr, unsigned char flags);
extern void hd44780_send(unsigned char ctrl_nr, unsigned char flags, unsigned char command);
extern void hd44780_send_all(unsigned char flags, unsigned char command);

#endif // _HD44780_H_
