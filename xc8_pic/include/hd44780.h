/*
 * hd44780.h
 * 
 * 2013 Kamil Cukrowski <kamil@dyzio.pl>
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#ifndef _HD44780_H_
#define _HD44780_H_ 1

#include <hd44780-config.h> // all configuration(!) and customization

#include "hd44780-inst-def.h"

#include <stdint.h>

/* ---------------------------------------------------------------------------------- */

#define HD44780_DISP_SIZE   ((HD44780_DISP_COLS  * HD44780_DISP_ROWS))        /* one display size */
#define HD44780_DISPS_COLS  ((HD44780_DISP_COLS))                             /* all displays columns */
#define HD44780_DISPS_ROWS  ((HD44780_DISP_ROWS  * HD44780_NUM_CONTROLLERS))  /* all displays rows */
#define HD44780_DISPS_SIZE  ((HD44780_DISPS_COLS * HD44780_DISPS_ROWS))       /* all displays display size */

/* ---------------------------------------------------------------------------------- */

struct hd44780_s {
	// This is a bitmap. If a bit numer X is set, that means that display numer X is disabled.
#if HD44780_NUM_CONTROLLERS <= 8
	uint8_t disabled;
#else
#error redefine hd44780.disabled member in struct hd44780_s with bigger size
#endif

#ifdef HD44780_COUNTERS
	uint24_t write_count[HD44780_NUM_CONTROLLERS];
	uint24_t read_count[HD44780_NUM_CONTROLLERS];
	uint24_t bfchecks_count[HD44780_NUM_CONTROLLERS];
#ifdef HD44780_CHECKER
	uint24_t errors_count[HD44780_NUM_CONTROLLERS];
#endif

#endif
};

extern struct hd44780_s hd44780;

/* ---------------------------------------------------------------------------------- */

void hd44780_init(void);

void hd44780_send(unsigned char ctrl_nr, unsigned char flags, unsigned char command);

#ifndef HD44780_WRITE_ONLY
unsigned char hd44780_recv(unsigned char ctrl_nr, unsigned char flags);
#endif

void hd44780_send_all(unsigned char flags, unsigned char command);

#define hd44780_write_inst(ctrl, inst)		 hd44780_send(ctrl, HD44780_RS_INST, inst)
#define hd44780_write_data(ctrl, data)		 hd44780_send(ctrl, HD44780_RS_DATA, data)
#define hd44780_read_inst(ctrl)				 hd44780_recv(ctrl, HD44780_RS_INST)
#define hd44780_read_data(ctrl)				 hd44780_recv(ctrl, HD44780_RS_DATA)
#define hd44780_write_inst_all(inst)		 hd44780_send_all(HD44780_RS_INST, inst)
#define hd44780_write_data_all(data)		 hd44780_send_all(HD44780_RS_DATA, data)
#define hd44780_get_cursor_pos(ctrl)         hd44780_recv(ctrl, HD44780_RS_INST)&0x7f
#define hd44780_set_cursor_pos(ctrl, curpos) hd44780_write_inst(ctrl, HD44780_DDRAM_ADDRESS | curpos )

#ifdef HD44780_CHECKER

/**
 * Pointer of HD44780_NUM_CONTROLLERS length to array of pointers, each with the length of HD44780_DISP_SIZE.
 * This represents all that is on the hd44780 screen.
 * Must be declared and filled with pointers by user implementation.
 */
extern unsigned char *hd44780_state[HD44780_NUM_CONTROLLERS];

/**
 * Checks and corrects error on hd44780 displays.
 */
void hd44780_check(void);

#endif

#endif // _HD44780_H_
