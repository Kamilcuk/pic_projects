/*
 * hd44780.c - communicate with hd44780 compatible controllers
 * look in hd44780-config.h for more information!
 * 
 * 2013 Kamil Cukrowski <kamil@dyzio.pl>
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 * 
 * 
 * 
 */

#include "hd44780.h"

#include <system.h> // _XTAL_FREQ
#include "hd44780-config.h" // all configuration(!) and customization

#include "hd44780-inst-def.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* -------------------- private defines ---------------------- */

#define HD44780_CHECK_RAWCURPOS               1

#if HD44780_DEBUG
#define HD44780_PDEBUG(         printf_args ) do{ ( printf printf_args ); }while(0)
#else // HD44780_DEBUG
#define HD44780_PDEBUG(         printf_args )
#endif // HD44780_DEBUG

#if HD44780_DEBUG || HD44780_PRINT_ERRORS
#define HD44780_PERR(           printf_args ) do{ ( printf printf_args ); }while(0)
#else // HD44780_PRINT_ERRORS
#define HD44780_PERR(           printf_args )
#endif // HD44780_PRINT_ERRORS
#if HD44780_DEBUG || HD44780_DEBUG_CHECKER
#define HD44780_PDEBUG_CHECKER( printf_args ) do{ ( printf printf_args ); }while(0)
#else // HD44780_DEBUG_CHECKER
#define HD44780_PDEBUG_CHECKER( printf_args )
#endif // HD44780_DEBUG_CHECKER
#if HD44780_DEBUG || HD44780_USE_ASSERT
#define HD44780_ASSERT(expr)                  do{ if(!(expr)) { HD44780_PERR(("ERR "#expr"\n")); for(;;); } }while(0)
#else // HD44780_USE_ASSERT
#define HD44780_ASSERT(expr)
#endif // HD44780_USE_ASSERT

/* wrappers around user functions callbacks */

#ifndef HD44780_DATA_SET
	#ifndef HD44780_DATA_SET_CALLBACK
		#error HD44780_DATA_SET_CALLBACK not defined
	#endif // HD44780_DATA_SET_CALLBACK
	#ifndef HD44780_DATA_SET_UP_TIME
		#error HD44780_DATA_SET_UP_TIME not defined
	#endif // HD44780_DATA_SET_UP_TIME
	#define HD44780_DATA_SET(flags, data, upper) do{ \
		HD44780_DATA_SET_CALLBACK(flags, data, upper); \
		HD44780_DATA_SET_UP_TIME(); \
	}while(0)
#endif

#ifndef HD44780_ADDRESS_SET_READ
	#ifndef HD44780_ADDRESS_SET_READ_CALLBACK
		#error HD44780_ADDRESS_SET_READ_CALLBACK not defined
	#endif // HD44780_ADDRESS_SET_READ_CALLBACK
	#ifndef HD44780_ADDRESS_SET_UP_TIME
		#error HD44780_ADDRESS_SET_UP_TIME not defined
	#endif // HD44780_ADDRESS_SET_UP_TIME
	#define HD44780_ADDRESS_SET_READ(flags) do{ \
		HD44780_ADDRESS_SET_READ_CALLBACK((flags)); \
		HD44780_ADDRESS_SET_UP_TIME(); \
	}while(0)
#endif // HD44780_ADDRESS_SET_READ

#ifndef HD44780_ADDRESS_SET_WRITE
	#ifndef HD44780_ADDRESS_SET_WRITE_CALLBACK
		#error HD44780_ADDRESS_SET_WRITE_CALLBACK not defined
	#endif // HD44780_ADDRESS_SET_WRITE_CALLBACK
	#ifndef HD44780_ADDRESS_SET_UP_TIME
		#error HD44780_ADDRESS_SET_UP_TIME not defined
	#endif // HD44780_ADDRESS_SET_UP_TIME
	#define HD44780_ADDRESS_SET_WRITE(flags) do{ \
		HD44780_ADDRESS_SET_WRITE_CALLBACK((flags)); \
		HD44780_ADDRESS_SET_UP_TIME(); \
	}while(0)
#endif // HD44780_ADDRESS_SET_WRITE

#ifndef HD44780_ENABLE
	#ifndef HD44780_ENABLE_PULSE_WIDTH
		#error HD44780_ENABLE_PULSE_WIDTH not defined
	#endif // HD44780_ENABLE_PULSE_WIDTH
	#if defined(HD44780_ENABLE_CALLBACK)
		#define HD44780_ENABLE(flags, ctrl_nr) do{ \
			HD44780_ENABLE_CALLBACK((flags), (ctrl_nr)); \
			HD44780_ENABLE_PULSE_WIDTH(); \
		}while(0)
	#elif defined(HD44780_ENABLE_ALL_CALLBACK)
		#define HD44780_ENABLE(flags, ctrl_nr) HD44780_ENABLE_ALL((flags))
	#else
		#error in hd44780-config.h you must define at least HD44780_ENABLE_ALL_CALLBACK or HD44780_ENABLE_CALLBACK
	#endif
#endif // HD44780_ENABLE

#ifndef HD44780_ENABLE_ALL
	#ifndef HD44780_ENABLE_PULSE_WIDTH
		#error HD44780_ENABLE_PULSE_WIDTH not defined
	#endif // HD44780_ENABLE_PULSE_WIDTH
	#if defined(HD44780_ENABLE_ALL_CALLBACK)
		#define HD44780_ENABLE_ALL(flags) do{ \
			HD44780_ENABLE_ALL_CALLBACK((flags)); \
			HD44780_ENABLE_PULSE_WIDTH(); \
		}while(0)
	#elif defined(HD44780_ENABLE_CALLBACK)
		#define HD44780_ENABLE_ALL(flags) do{ \
			for(unsigned char i = 0; i < HD44780_NUM_CONTROLLERS; ++i) { \
				HD44780_ENABLE_CALLBACK((flags), (i)); \
			} \
			HD44780_ENABLE_PULSE_WIDTH(); \
		}while(0)
	#else
		#error in hd44780-config.h you must define at least HD44780_ENABLE_ALL_CALLBACK or HD44780_ENABLE_CALLBACK
	#endif
#endif // HD44780_ENABLE_ALL

#ifndef HD44780_DISABLE_ALL
	#ifndef HD44780_DISABLE_ALL_CALLBACK
		#error HD44780_DISABLE_ALL_CALLBACK not defined
	#endif // HD44780_DISABLE_ALL_CALLBACK
	#ifndef HD44780_DATA_HOLD_TIME
		#error HD44780_DATA_HOLD_TIME not defined
	#endif // HD44780_DATA_HOLD_TIME
	#define HD44780_DISABLE_ALL(flags) do{ \
		HD44780_DISABLE_ALL_CALLBACK((flags)); \
		HD44780_DATA_HOLD_TIME(); \
	}while(0)
#endif // HD44780_DISABLE_ALL

/* ---------------- wrappers around flags --------------- */
#ifndef HD44780_RW_READ
	#error HD44780_RW_READ not defined
#endif // HD44780_RW_READ
#ifndef HD44780_RW_WRITE
	#error HD44780_RW_WRITE not defined
#endif // HD44780_RW_WRITE
#ifndef HD44780_RS_INST
	#error HD44780_RS_INST not defined
#endif // HD44780_RS_INST
#ifndef HD44780_RS_DATA
	#error HD44780_RS_DATA not defined
#endif // HD44780_RS_DATA

/* ------------------ check user defines ---------- */
#ifndef HD44780_LONG_DELAY
	#error HD44780_LONG_DELAY not defined
#endif // HD44780_LONG_DELAY
#ifndef HD44780_NORMAL_DELAY
	#error HD44780_NORMAL_DELAY not defined
#endif // HD44780_NORMAL_DELAY
#ifndef HD44780_INIT_CALLBACK
	#error HD44780_INIT_CALLBACK not defined
#endif // HD44780_INIT_CALLBACK

/* ------------------------ static vars ------------------- */

/**
 * our struct
 */
struct hd44780_s hd44780 = {0};

/* -------------------------- predeclarations -------------------- */

/* ------------------------- checker -------------------------- */

#if HD44780_CHECKER

/**
 * Remember cursor position for all hd44780 controllers
 */
unsigned char hd44780_checker_curpos[HD44780_NUM_CONTROLLERS];

#if !HD44780_CHECKER_DISABLE_DEFAULT

/**
 * You may be wondering why there are so many of theese.
 * For 2*40 hd44780 controller we get 80 chars per display.
 * With 8 controllers i get 8*2*40=640 chars to keep in memory.
 * One bank slot in PIC18 has the length of 256 - i need to split this in parts.
 * It is here splitted in HD44780_DISP_SIZE chars size parts,
 * One state?? variable handles one display.
 * The linker can choose the proper positions for every of these variables.
 * The hd44780_state variable is then initialized with pointers to these state variables.
 */
#if HD44780_NUM_CONTROLLERS >= 1
static unsigned char state1[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 2
static unsigned char state2[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 3
static unsigned char state3[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 4
static unsigned char state4[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 5
static unsigned char state5[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 6
static unsigned char state6[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 7
static unsigned char state7[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 8
static unsigned char state8[HD44780_DISP_SIZE];
#endif
#if HD44780_NUM_CONTROLLERS >= 9
#error ADD LINES HERE
#endif

unsigned char *hd44780_checker_state[HD44780_NUM_CONTROLLERS] = {
#if HD44780_NUM_CONTROLLERS >= 1
		state1,
#endif
#if HD44780_NUM_CONTROLLERS >= 2
		state2,
#endif
#if HD44780_NUM_CONTROLLERS >= 3
		state3,
#endif
#if HD44780_NUM_CONTROLLERS >= 4
		state4,
#endif
#if HD44780_NUM_CONTROLLERS >= 5
		state5,
#endif
#if HD44780_NUM_CONTROLLERS >= 6
		state6,
#endif
#if HD44780_NUM_CONTROLLERS >= 7
		state7,
#endif
#if HD44780_NUM_CONTROLLERS >= 8
		state8,
#endif
#if HD44780_NUM_CONTROLLERS >= 9
#error ADD LINES HERE
#endif
};

void hd44780_init_checker()
{
	for(uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
		memset(hd44780_checker_state[i], ' ', HD44780_DISP_SIZE);
	}
}

#endif // HD44780_CHECKER_DISABLE_DEFAULT

static void _hd44780_checker_curpos_inc_(const unsigned char ctrl)
{
	HD44780_PDEBUG_CHECKER(("check inc\n"));
	if ( ctrl != HD44780_NUM_CONTROLLERS ) {
		if ( hd44780_checker_curpos[ctrl] < HD44780_DISP_SIZE-1 ) {
			++hd44780_checker_curpos[ctrl];
		} else {
			hd44780_checker_curpos[ctrl] = 0;
		}
	} else {
		for(uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
			if ( hd44780_checker_curpos[i] < HD44780_DISP_SIZE-1 ) {
				++hd44780_checker_curpos[i];
			} else {
				hd44780_checker_curpos[i] = 0;
			}
		}
	}
}

/**
 * After every write and read we need to remember what have we done (and the cursor position).
 * This function does that.
 */
static inline void hd44780_checker_parse(const unsigned char ctrl, const unsigned char flags, const unsigned char command)
{
	if ( ctrl == HD44780_NUM_CONTROLLERS ) {
		switch(flags) {
		case HD44780_RW_WRITE|HD44780_RS_INST:
			HD44780_PDEBUG_CHECKER(("parse inst all %x\n", command));
			if ( command&0x80 ) {
				uint8_t optimize = command&0x7f;
				memset(hd44780_checker_curpos, hd44780_curpos_from_raw(optimize), HD44780_NUM_CONTROLLERS);
			} else
			if ( command&0x03 ) {
				memset(hd44780_checker_curpos,            0, HD44780_NUM_CONTROLLERS);
			}
			break;
		case HD44780_RW_WRITE|HD44780_RS_DATA:
			HD44780_PDEBUG_CHECKER(("parse data all %x\n", command));
			for(uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
				hd44780_checker_state[i][hd44780_checker_curpos[i]] = command;
			}
			_hd44780_checker_curpos_inc_(ctrl);
			break;
		}
	} else {
		switch(flags) {
		case HD44780_RW_WRITE|HD44780_RS_INST:
			HD44780_PDEBUG_CHECKER(("parse inst %d %x\n", ctrl, command));
			if ( command&0x80 ) {
				uint8_t optimize = command&0x7f;
				hd44780_checker_curpos[ctrl] = hd44780_curpos_from_raw(optimize);
			} else
			if ( command&0x03 ) {
				hd44780_checker_curpos[ctrl] = 0;
			}
			break;
		case HD44780_RW_WRITE|HD44780_RS_DATA:
			HD44780_PDEBUG_CHECKER(("parse data %d %x\n", ctrl, command));
			hd44780_checker_state[ctrl][hd44780_checker_curpos[ctrl]] = command;
			/* no break */
		case HD44780_RW_READ|HD44780_RS_DATA:
			_hd44780_checker_curpos_inc_(ctrl);
			break;
		}
	}
}

void hd44780_checker_check(void)
{
	for(uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) { // for every controller
#if !HD44780_NO_BF_CHECKING
		if ( HD44780_BFCHECK_IS_DISABLED(i) )
			continue;
#endif //HD44780_NO_BF_CHECKING
		
		const uint8_t *state = hd44780_checker_state[i];
		
		// save current cursosr position
		const uint8_t rawcur_sav = hd44780_get_rawcurpos(i);

		// move cursor to (0,0)
		hd44780_write_inst(i, HD44780_DDRAM_ADDRESS);
		HD44780_PDEBUG_CHECKER(("Checking dispay %d\n", i));

		for(uint8_t j = 0; j < HD44780_DISP_SIZE; /* ++j is below in the if */) { // for every character
			const uint8_t recv = hd44780_read(i, HD44780_RS_DATA);
			const uint8_t state_buff = state[0];
			HD44780_PDEBUG_CHECKER(("Check[%d] recv=%x state=%x\n", j, recv, state_buff));

			if ( recv != state_buff ) {
				HD44780_PERR(("Check corr i=%u recv=%u state=%u\n", j, recv, state_buff));
#if HD44780_COUNTERS
				++hd44780.errors_count[i];
#endif // HD44780_COUNTERS
				// restore cursor
				hd44780_set_rawcurpos(i, hd44780_curpos_to_raw(j));
				// write cursor one back
				hd44780_write_data(i, state_buff);
				 // restore cursor
				hd44780_set_rawcurpos(i, hd44780_curpos_to_raw(j));
				// correct error again - no counter incrementing - may loop forever
			} else {
				// not correcting error - increment counters
				++j;
				++state;
			}
		}
		// restore cursor position
		hd44780_set_rawcurpos(i, rawcur_sav);
	}
}


#endif // HD44780_CHECKER

/* ---------------- low-medium-level help functinons ---------------  */

/**
 * waits for hd44780 to complete send thing
 */
#define _hd44780_sleep_on_write_(flags, command) do{ \
	if ( ( flags == (HD44780_RW_WRITE|HD44780_RS_INST) ) && ( command & 0x03 ) ) { \
		HD44780_LONG_DELAY(); \
	} else { \
		HD44780_NORMAL_DELAY(); \
	} \
}while(0)

#if HD44780_NO_BF_CHECKING
#define _hd44780_wait_for_ready_(ctrl) /* empty */
#else //HD44780_NO_BF_CHECKING

/** _hd44780_wait_for_busyflag_
 * wait for busyflag to go low on ctrl_num, mutex is locked
 */
static void _hd44780_wait_for_ready_(unsigned char ctrl)
{
	uint8_t readbuff;

	HD44780_PDEBUG(("hd wait_for_ready(%d)\n", ctrl));

	HD44780_ADDRESS_SET_READ(HD44780_RW_READ|HD44780_RS_INST);
#ifdef HD44780_BUSYFLAG_STUCK
	uint16_t count;
	for ( count = HD44780_BUSYFLAG_STUCK; count; --count )
#else
	for(;;)
#endif
	{

		HD44780_EXTRA_ENABLE_CYCLE_TIME();
		HD44780_ENABLE(HD44780_RW_READ|HD44780_RS_INST, ctrl);
		readbuff = HD44780_DATA_GET_CALLBACK();
		HD44780_DISABLE_ALL(HD44780_RW_READ|HD44780_RS_INST);

#if !HD44780_MODE_4_BIT
		if ( ! ( readbuff & 0x80 ) ) {
			break;
		}
#else
		HD44780_EXTRA_ENABLE_CYCLE_TIME();
		HD44780_ENABLE(HD44780_RW_READ|HD44780_RS_INST, ctrl);
		/* ignore second byte */
		HD44780_DISABLE_ALL(HD44780_RW_READ|HD44780_RS_INST);
		if ( ! ( readbuff & 0x08 ) ) {
			break;
		}
#endif

	}
	
#if HD44780_CHECKER && defined(HD44780_BUSYFLAG_STUCK)
	hd44780.bfchecks_count[ctrl] += ( HD44780_BUSYFLAG_STUCK - count );
#endif //HD44780_CHECKER
	
	if ( !count ) {
		HD44780_PERR(("hd wait_for_ready err (%d)\n", ctrl));
		HD44780_BFCHECK_DISABLE(ctrl);
	}
}

#endif //HD44780_NO_BF_CHECKING

/* ------------------- low-high-level functions ---------------  */

#if !HD44780_MODE_4_BIT
#define hd44780_write_8bit_op hd44780_write
#else

/**
 * Write to all controllers in 8-bit mode once, for doing initialization.
 * The lower bits of command are ignored.
 * The body of this function should be synchronized with hd44780_write
 * Gets called by hd44780_initializa_by_instruction();
 */
static void hd44780_write_8bit_op(const unsigned char ctrl, unsigned char flags, const unsigned char command)
{
	HD44780_PDEBUG(("hd44780_write_8bit_op(%x,%x,%x)\n", ctrl, flags, command));

	const bool all = ( ctrl == HD44780_NUM_CONTROLLERS ) ? true : false;

	/** write data */
	flags |= HD44780_RW_WRITE;
	HD44780_ADDRESS_SET_WRITE(flags);
	HD44780_DATA_SET(flags, command, 1);
	if ( all ) {
		HD44780_ENABLE_ALL(flags);
	} else {
		HD44780_ENABLE(flags, ctrl);
	}
	HD44780_DISABLE_ALL(flags);
}

#endif

static void inline _hd44780_write_(const unsigned char ctrl, const unsigned char flags, const unsigned char data)
{
	HD44780_ASSERT(ctrl <= HD44780_NUM_CONTROLLERS );

	const bool all = ( ctrl == HD44780_NUM_CONTROLLERS ) ? true : false;

#if HD44780_CHECK_RAWCURPOS
	// if this is a command to set cursor position && if the rawcursor position is outside the window
	if ( ( flags == (HD44780_RW_WRITE|HD44780_RS_INST) ) && ( data & HD44780_DDRAM_ADDRESS ) &&
			!hd44780_rawcurpos_check(data) ) {
		HD44780_PERR(("rawcurpos_check command=%x flags=%x ret=%x col=%x\n",
				data, flags, hd44780_rawcurpos_check(data), hd44780_col_from_rawcurpos(data)
		));
	}
#endif

#if !HD44780_NO_BF_CHECKING
	if ( all ) {
		// check enabled controllers busyflag
		for (uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
			// if controller i is enabled
			if ( HD44780_BFCHECK_IS_ENABLED(i) ) {
				_hd44780_wait_for_ready_(i);
			}
		}
	} else {
		// if this controller is not disabled, check it's busyflag
		if ( HD44780_BFCHECK_IS_ENABLED(ctrl) ) {
			_hd44780_wait_for_ready_(ctrl);
		}
	}
#endif // HD44780_NO_BF_CHECKING

	HD44780_ADDRESS_SET_WRITE(flags);

#if HD44780_MODE_4_BIT
	for(uint8_t upper = 0; upper < 2; ++upper)
#endif
	{
		/** write data */
#if !HD44780_MODE_4_BIT
		HD44780_PDEBUG(("hd_write(%x,%x,%x)\n", ctrl, flags, data));
		HD44780_DATA_SET(flags, data, 0);
#else //HD44780_MODE_4_BIT
		HD44780_EXTRA_ENABLE_CYCLE_TIME();
		HD44780_PDEBUG(("hd_4write(%x,%x,%x) upper=%x\n", ctrl, flags, data, upper));
		HD44780_DATA_SET(flags, data, upper);
#endif //HD44780_MODE_4_BIT
		if ( all ) {
			HD44780_ENABLE_ALL(flags);
		} else {
			HD44780_ENABLE(flags, ctrl);
		}
		HD44780_DISABLE_ALL(flags);
	}

#if HD44780_COUNTERS
	if ( all ) {
		for(uint8_t i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
			++hd44780.write_count[i];
		}
	} else {
		++hd44780.write_count[ctrl];
	}
#endif //HD44780_COUNTERS

#if HD44780_NO_BF_CHECKING
	_hd44780_sleep_on_write_(flags, data);
#else
	if ( all ) {
		// if any of the controllers is bfcheck disabled
		if ( HD44780_BFCHECK_IS_ANY_DISABLED() ) {
			_hd44780_sleep_on_write_(flags, data);
		}
	} else {
		// if bfcheck on this controller is disabled
		if ( HD44780_BFCHECK_IS_DISABLED(ctrl) ) {
			_hd44780_sleep_on_write_(flags, data);
		}
	}
#endif //HD44780_NO_BF_CHECKING
#if HD44780_CHECKER
	hd44780_checker_parse(ctrl, flags, data);
#endif
}


void hd44780_write(const unsigned char ctrl, unsigned char flags, const unsigned char data)
{
	HD44780_ASSERT(ctrl <= HD44780_NUM_CONTROLLERS );

	const bool all = ( ctrl == HD44780_NUM_CONTROLLERS ) ? true : false;

	flags |= HD44780_RW_WRITE;

#if HD44780_CHECK_EVERY_WRITE
#if HD44780_CHECK_EVERY_WRITE_MAX
	uint8_t check_every_write_times = HD44780_CHECK_EVERY_WRITE_MAX;
#endif // HD44780_CHECK_EVERY_WRITE_MAX
	uint8_t rawcurpossave;
	if ( !all && ( flags == (HD44780_RW_WRITE|HD44780_RS_DATA) ) ) {
		// save cursor position
		rawcurpossave = hd44780_get_rawcurpos(ctrl);
	}

write_again:
#endif // HD44780_CHECK_EVERY_WRITE

	_hd44780_write_(ctrl, flags, data);

#if HD44780_CHECK_EVERY_WRITE
	if ( !all && ( flags == (HD44780_RW_WRITE|HD44780_RS_DATA) )
#if !HD44780_NO_BF_CHECKING
			&& HD44780_BFCHECK_IS_ENABLED(ctrl)
#endif // HD44780_NO_BF_CHECKING
		) {
		// restore cursor position
		_hd44780_write_(ctrl, HD44780_RW_WRITE|HD44780_RS_INST, HD44780_DDRAM_ADDRESS|rawcurpossave);
		// read character, compare to command
		if ( hd44780_read(ctrl, HD44780_RW_READ|HD44780_RS_DATA) != data ) {

#if HD44780_CHECK_EVERY_WRITE_MAX
			--check_every_write_times;
			if ( !check_every_write_times ) {
				HD44780_PERR(("HD MAX_TIMES_CHECK_EVERY_WRITE times=%u MAX=%u\n",
						check_every_write_times, HD44780_CHECK_EVERY_WRITE_MAX));
				// meh, errors happen - we should probably implement reseting display here
			} else
#endif //HD44780_CHECK_EVERY_WRITE_MAX
			{
				// if false, try writing the character again
				HD44780_PERR(("HD check_every_write goto write_again\n"));
				// restore cursor position
				_hd44780_write_(ctrl, HD44780_RW_WRITE|HD44780_RS_INST, HD44780_DDRAM_ADDRESS|rawcurpossave);
				goto write_again;
			}
		}
	}
#endif // HD44780_CHECK_EVERY_WRITE
}

#if !HD44780_WRITE_ONLY
unsigned char hd44780_read(const unsigned char ctrl, unsigned char flags)
{
	unsigned char data;

	HD44780_ASSERT( ctrl < HD44780_NUM_CONTROLLERS );
	flags |= HD44780_RW_READ;

#if !HD44780_NO_BF_CHECKING
	if ( HD44780_BFCHECK_IS_ENABLED(ctrl) ) {
		_hd44780_wait_for_ready_(ctrl);
	}
#endif

	// prepare read data
	HD44780_ADDRESS_SET_READ(flags);

#if HD44780_MODE_4_BIT
	for(uint8_t upper = 0; upper < 2; ++upper)
#endif
	{
		// read data
		HD44780_ENABLE(flags, ctrl);
#if !HD44780_MODE_4_BIT
		data = HD44780_DATA_GET_CALLBACK();
		HD44780_PDEBUG(("hd_read(%x,%x)=%x\n", ctrl, flags, data));
#else //HD44780_MODE_4_BIT
		HD44780_EXTRA_ENABLE_CYCLE_TIME();
		if ( upper == 0 ) {
			data = HD44780_DATA_GET_CALLBACK();
		} else {
			data = (data<<4) | HD44780_DATA_GET_CALLBACK();
		}
		HD44780_PDEBUG(("hd_4read(%x,%x)=%x upper=%x\n", ctrl, flags, data, upper));
#endif //HD44780_MODE_4_BIT
		HD44780_DISABLE_ALL(flags);
	}

#if HD44780_COUNTERS
	++hd44780.read_count[ctrl];
#endif // HD44780_COUNTERS
#if HD44780_CHECKER
	hd44780_checker_parse(ctrl, flags, data);
#endif // HD44780_CHECKER
#if HD44780_NO_BF_CHECKING
	HD44780_NORMAL_DELAY();
#else // HD44780_NO_BF_CHECKING
	if ( HD44780_BFCHECK_IS_DISABLED(ctrl) ) {
		HD44780_NORMAL_DELAY();
	}
#endif // HD44780_NO_BF_CHECKING

#if HD44780_CHECK_RAWCURPOS
	// if we have read cursor position, we can check if its ok
	if ( ( flags == (HD44780_RW_WRITE|HD44780_RS_INST) ) && ( data & HD44780_DDRAM_ADDRESS ) &&
				!hd44780_rawcurpos_check(data) ) {
		HD44780_PERR(("rawcurpos_check command=%x flags=%x ret=%x col=%x\n",
				data, flags, hd44780_rawcurpos_check(data), hd44780_col_from_rawcurpos(data)
		));
	}
#endif // HD44780_CHECK_RAWCURPOS

	return data;
}
#endif

/* ------------------- high level functions ---------------  */

/* 
 * hd44780_initialize_by_instruction
 * hd44780 documentation page 45 
 * If the power supply conditions for correctly operating the internal reset circuit are not met, initialization by 
 * instructions becomes necessary.
 * we do it anyway.
 */
static void hd44780_initialize_by_instruction(uint8_t ctrl)
{
	HD44780_PDEBUG(("hd_initialize_by_instruction(%u) in\n", ctrl));

#if !HD44780_NO_BF_CHECKING
	/* no BF checking here */
	HD44780_BFCHECK_DISABLE_ALL();
#endif //HD44780_NO_BF_CHECKING

	/* Wait for more then 15 ms after Vcc raises to 4.5V */
	__delay_ms(15);
	/* Function set (Interface is 8 bits long.) */
	hd44780_write_8bit_op(ctrl, HD44780_RS_INST, 0b00110000);
	/* Wait for more then 4.1 ms */
	__delay_ms(5);
	/* Function set (Interface is 8 bits long.) */
	hd44780_write_8bit_op(ctrl, HD44780_RS_INST, 0b00110000);
	/* Wait for more then 100 us */
	__delay_us(100);
	/* Function set (Interface is 8 bits long.) */
	hd44780_write_8bit_op(ctrl, HD44780_RS_INST, 0b00110000);
	HD44780_LONG_DELAY();

#if HD44780_MODE_4_BIT
	/* Function set (Interface is 8 bits long.)
	 * Set Interface to be 4 bits long*/
	hd44780_write_8bit_op(ctrl, HD44780_RS_INST, 0b00100000);
	HD44780_LONG_DELAY();
#endif

	/* initialize user-specified configuration
	 * done twice, to be sure */
	for(uint8_t i = 0; i < 2; ++i) {

#if !HD44780_MODE_4_BIT
		hd44780_write_inst(ctrl,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_TWOLINES |
			HD44780_FS_5x8DOTS);
#else
		hd44780_write_inst(ctrl,
			HD44780_FS_DATAWIDTH4BIT |
			HD44780_FS_TWOLINES |
			HD44780_FS_5x8DOTS);
#endif
		HD44780_LONG_DELAY();
		hd44780_write_inst(ctrl,
			HD44780_DOOC_DISPLAYON |
			HD44780_DOOC_CURSORON |
			HD44780_DOOC_CURSORNOBLINK);
		HD44780_LONG_DELAY();
		hd44780_write_inst(ctrl,
			HD44780_CLRDISP);
		HD44780_LONG_DELAY();
		hd44780_write_inst(ctrl,
			HD44780_EMS_INC |
			HD44780_EMS_NOSHIFT);
		HD44780_LONG_DELAY();

#if !HD44780_NO_BF_CHECKING
		if ( i == 0 ) {
			/* re-allow BFchecking on all displays */
			HD44780_BFCHECK_ENABLE_ALL();
			/* now bf checking is set on all hd-s,
			 * autodetection and disabling busyflag detection will
			 * happen automagically in _hd44780_wait_for_ready_ */
		}
#endif

	}

	HD44780_PDEBUG(("hd_initialize_by_instruction(%u) out\n", ctrl));
}

void hd44780_init(void) 
{
	HD44780_PDEBUG(("HD44780_INIT_CALLBACK()\n"));
	HD44780_INIT_CALLBACK();

#if HD44780_CHECKER
	hd44780_init_checker();
#endif
	hd44780_initialize_by_instruction(HD44780_NUM_CONTROLLERS);
}

