/*
 * hd44780.h
 * 
 * 2013 Kamil Cukrowski <kamil@dyzio.pl>
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
