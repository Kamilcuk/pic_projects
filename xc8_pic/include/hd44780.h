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

/**
 * For 2-line display, convert second line (0x40-0x67) cursor position to normal (0x28-0x4f) numbers
 */
#if HD44780_DISP_ROWS == 1
#define hd44780_curpos_from_raw(curpos)       ( curpos )
#define hd44780_curpos_to_raw(curpos)         ( curpos )
#define hd44780_rowcol_to_rawcurpos(row, col) ( col )
#define hd44780_row_from_rawcurpos(rawcurpos) ( 0 )
#define hd44780_col_from_rawcurpos(rawcurpos) ( rawcurpos )
#define hd44780_rawcurpos_check(rawcurpos)    ( rawcurpos < HD44780_DISP_COLS )
#else
#define hd44780_curpos_from_raw(curpos)       ( (curpos) >= 0x40 ? (curpos) - 24 : (curpos) )
#define hd44780_curpos_to_raw(curpos)         ( (curpos) >=   40 ? (curpos) + 24 : (curpos) )
#define hd44780_rowcol_to_rawcurpos(row, col) ( ( (row) ? 0x40 : 0x00 ) | (col) )
#define hd44780_row_from_rawcurpos(rawcurpos) ( ( (rawcurpos) & 0x40 ) != 0 )
#define hd44780_col_from_rawcurpos(rawcurpos) ( (rawcurpos) & 0x3f )
#define hd44780_rawcurpos_check(rawcurpos)    ( ( (rawcurpos) & 0x3f ) < HD44780_DISP_COLS )
#endif

#if !HD44780_NO_BF_CHECKING
#include <bit.h>
#define HD44780_BFCHECK_DISABLE(ctrl)          BIT_SET(hd44780.nobfcheck, (ctrl))
#define HD44780_BFCHECK_ENABLE(ctrl)         BIT_CLEAR(hd44780.nobfcheck, (ctrl))
#define HD44780_BFCHECK_IS_DISABLED(ctrl)     BIT_READ(hd44780.nobfcheck, (ctrl))
#define HD44780_BFCHECK_IS_ENABLED(ctrl)     !BIT_READ(hd44780.nobfcheck, (ctrl))
#define HD44780_BFCHECK_IS_ANY_DISABLED()            ( hd44780.nobfcheck != 0 )
#define HD44780_BFCHECK_IS_ANY_ENABLED()             ( hd44780.nobfcheck != 0xFF )
#define HD44780_BFCHECK_ENABLE_ALL()                 ( hd44780.nobfcheck =  0 )
#define HD44780_BFCHECK_DISABLE_ALL()                ( hd44780.nobfcheck =  0xFF )
#else
#define HD44780_BFCHECK_DISABLE(ctrl)
#define HD44780_BFCHECK_ENABLE(ctrl)
#define HD44780_BFCHECK_IS_DISABLED(ctrl)
#define HD44780_BFCHECK_IS_ENABLED(ctrl)
#define HD44780_BFCHECK_ENABLE_ALL()
#define HD44780_BFCHECK_DISABLE_ALL()
#endif

/* ---------------------------------------------------------------------------------- */

struct hd44780_s {
#if !HD44780_NO_BF_CHECKING

#if HD44780_NUM_CONTROLLERS    <=  8
#define HD44780_DISABLED_TYPE  uint8_t
#elif HD44780_BUSYFLAG_STUCK   <= 16
#define HD44780_DISABLED_TYPE uint16_t
#else // HD44780_BUSYFLAG_STUCK
#error redefine hd44780.disabled member in struct hd44780_s with bigger size
#endif // HD44780_BUSYFLAG_STUCK

	/**
	 * This is a bitmap. If a bit numer X is set, that means that display numer X is probably malfunctioning.
	 * If bit number X is set, we don't check busyflag on this display, we only do wait's.
	 */
	HD44780_DISABLED_TYPE nobfcheck;
#undef HD44780_DISABLED_TYPE

#endif // HD44780_NO_BF_CHECKING

#ifdef HD44780_COUNTERS
	/**
	 * Count times hd44780 controller were written to
	 */
	HD44780_COUNTERS_TYPE write_count[HD44780_NUM_CONTROLLERS];
	/**
	 * Count times hd44780 was read from.
	 */
	HD44780_COUNTERS_TYPE read_count[HD44780_NUM_CONTROLLERS];
#if !HD44780_NO_BF_CHECKING
	/**
	 * count times we checked busyflag on this controller.
	 */
	HD44780_COUNTERS_TYPE bfchecks_count[HD44780_NUM_CONTROLLERS];
#endif
#ifdef HD44780_CHECKER
	/**
	 * count times we corrected display on controller.
	 */
	HD44780_COUNTERS_TYPE errors_count[HD44780_NUM_CONTROLLERS];
#endif

#endif
};

extern struct hd44780_s hd44780;

/* ---------------------------------------------------------------------------------- */

void hd44780_init(void);

void hd44780_write(unsigned char ctrl, unsigned char flags, unsigned char data);

#if !HD44780_WRITE_ONLY
unsigned char hd44780_read(unsigned char ctrl, unsigned char flags);
#endif

#define hd44780_write_all(flags, data)    hd44780_write(HD44780_NUM_CONTROLLERS, flags, data)

#define hd44780_write_inst(ctrl, inst)		 hd44780_write(ctrl, HD44780_RS_INST, inst)
#define hd44780_write_data(ctrl, data)		 hd44780_write(ctrl, HD44780_RS_DATA, data)

#define hd44780_read_inst(ctrl)				 hd44780_read(ctrl, HD44780_RS_INST)
#define hd44780_read_data(ctrl)				 hd44780_read(ctrl, HD44780_RS_DATA)

#define hd44780_write_inst_all(inst)		 hd44780_write_all(HD44780_RS_INST, inst)
#define hd44780_write_data_all(data)		 hd44780_write_all(HD44780_RS_DATA, data)

#define hd44780_get_rawcurpos(ctrl) \
		( hd44780_read_inst(ctrl) & 0x7f )

#define hd44780_set_rawcurpos(ctrl, rawcurpos) \
		hd44780_write_inst(ctrl, HD44780_DDRAM_ADDRESS | rawcurpos)

#define hd44780_set_rawcurpos_all(rawcurpos) \
		hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | rawcurpos)

#define hd44780_set_cursor_rowcol(ctrl, row, col) \
		hd44780_write_inst(ctrl, HD44780_DDRAM_ADDRESS | hd44780_rowcol_to_rawcurpos(row,col) );

#define hd44780_set_cursor_rowcol_all(row, col) \
		hd44780_write_inst_all(HD44780_DDRAM_ADDRESS | hd44780_rowcol_to_rawcurpos(row,col) );

#define hd44780_clrscr(ctrl) do{ \
		hd44780_write_inst(ctrl, HD44780_CLRDISP); \
		hd44780_write_inst(ctrl, HD44780_DDRAM_ADDRESS); \
} while(0)

#define hd44780_clrscr_all() do{ \
		hd44780_write_inst_all(HD44780_CLRDISP); \
		hd44780_write_inst_all(HD44780_DDRAM_ADDRESS); \
} while(0)

#if HD44780_CHECKER

/**
 * Array of HD44780_NUM_CONTROLLERS length to char arrays each of HD44780_DISP_SIZE length.
 * This represents all that is on the hd44780 screen.
 * Must be declared and filled with pointers by user implementation.
 * See example implementation in hd44780.c
 */
extern unsigned char *hd44780_checker_state[HD44780_NUM_CONTROLLERS];

/**
 * Checks and corrects error on hd44780 displays.
 */
void hd44780_checker_check(void);

#else

#define hd44780_checker_check()

#endif

#endif // _HD44780_H_
