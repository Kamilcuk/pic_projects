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

#include "hd44780-inst-def.h"

#include <system.h> // _XTAL_FREQ
#include <hd44780-config.h> // all configuration(!) and customization
#include <bit.h>
#include <string.h>

/* -------------------- placeholders  ---------------- */
#define PDEBUG( printf_args ) // printf printf_args ;
#define PWARN(  printf_args ) // printf printf_args ;

/**
 * out struct
 */
struct hd44780_s hd44780;

/* ------------------------- checker -------------------------- */

#ifdef HD44780_CHECKER

/**
 * saved cursor position of all displays
 */
unsigned char cur_pos[HD44780_NUM_CONTROLLERS];

#ifndef HD44780_CHECKER_DISABLE_DEFAULT

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

unsigned char *hd44780_state[HD44780_NUM_CONTROLLERS] = {
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
	unsigned char i;
	for(i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
		memset(hd44780_state[i], ' ', HD44780_DISP_SIZE);
	}
}

#endif // HD44780_CHECKER_DISABLE_DEFAULT

static void hd44780_parse(unsigned char ctrl_nr, unsigned char flags, unsigned char command)
{
	unsigned char i;
	if ( ctrl_nr != HD44780_NUM_CONTROLLERS ) {
		switch(flags) {
		case HD44780_RW_WRITE|HD44780_RS_INST:
			if ( command&0x80 ) {
				cur_pos[ctrl_nr] = command&0x7f;
			} else
			if ( command&0x03 ) {
				cur_pos[ctrl_nr] = 0;
			}
			break;
		case HD44780_RW_WRITE|HD44780_RS_DATA:
			i = cur_pos[ctrl_nr];
			if ( i <= 0x27 ) {
				*(hd44780_state[ctrl_nr]+i) = command;
			} else {
				*(hd44780_state[ctrl_nr]+40+i) = command;
			}
			break;
		}
	} else {
		switch(flags) {
		case HD44780_RW_WRITE|HD44780_RS_INST:
			if ( command&0x80 ) {
				memset(cur_pos, command&0x7f, HD44780_NUM_CONTROLLERS);
			} else
			if ( command&0x03 ) {
				memset(cur_pos,            0, HD44780_NUM_CONTROLLERS);
			}
			break;
		case HD44780_RW_WRITE|HD44780_RS_DATA:
			for(; ctrl_nr; --ctrl_nr) {
				i = cur_pos[ctrl_nr-1];
				if ( i <= 0x27 ) {
					*(hd44780_state[ctrl_nr]+i) = command;
				} else {
					*(hd44780_state[ctrl_nr]+40+i) = command;
				}
			}
			break;
		}
	}
}

void hd44780_check(void)
{
	unsigned char i, j;
	for(i = 0; i < HD44780_NUM_CONTROLLERS; ++i) {
		unsigned char cur_sav, *state;
		
		if ( BIT_READ(i, hd44780.disabled) )
			continue;
		
		state = hd44780_state[i];
		
		// save current cursosr position
		cur_sav = hd44780_recv(i, HD44780_RS_INST)&0x7f;
		// move cursor
		hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | 0 );
		
		for(j = 0; j < HD44780_DISP_SIZE; ++j) {
			unsigned char recv, buff_state;
			recv = hd44780_recv(i, HD44780_RS_DATA);
			buff_state = *state;
			if ( recv != buff_state ) {
				unsigned char curpos;
#ifdef HD44780_COUNTERS
				++hd44780.errors_count[i];
#endif // HD44780_COUNTERS
				if ( j < 40 ) {
					curpos = j;
				} else {
					curpos = ( 1 << 6 ) | j-40;
				}
				hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | curpos );
				hd44780_write_data(i, buff_state);
			}
			
			++state;
		}
		// restore cursor position
		hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | cur_sav );
	}
}


#endif // HD44780_CHECKER

/* ---------------- low-medium-level help functinons ---------------  */

#ifdef HD44780_NO_BF_CHECKING

/**
 * waits for hd44780 to complete send thing
 */
static void _hd44780_sleep_on_write_(unsigned char flags, unsigned char command)
{
	if ( IS_RS_INST(flags) && ( command&0x03 ) ) {
		LONG_DELAY();
	} else {
		NORMAL_DELAY();
	}
}

#define _hd44780_wait_for_ready_(ctrl_nr) /* empty */

#else

#define _hd44780_sleep_on_write_(flags, command) /* empty */

/** _hd44780_wait_for_busyflag_
 * wait for busyflag to go low on ctrl_num, mutex is locked
 */
static void _hd44780_wait_for_ready_(unsigned char ctrl_nr)
{
	unsigned int count;
	PDEBUG((" ^ waiting for ctrl %d to lower the busyflag.\n", NUM_CONTROLLERS));
	
	_hd44780_data_reverse_();
	_hd44780_capable_(HD44780_RW_READ | HD44780_RS_INST);
	_hd44780_enable_(HD44780_RW_READ | HD44780_RS_INST, ctrl_nr);
	for ( count = BUSYFLAG_STUCK; count; --count ) {
		if ( ! _hd44780_data_get_busyflag_() ) {
			break;
		}
		_hd44780_disable_(HD44780_RW_READ | HD44780_RS_INST);
		
		BUSYFLAG_DELAY();
		
		_hd44780_enable_(HD44780_RW_READ | HD44780_RS_INST, ctrl_nr);
	}
	_hd44780_disable_(HD44780_RW_READ | HD44780_RS_INST);
	
#ifdef HD44780_CHECKER
	hd44780.bfchecks_count[ctrl_nr] += count;
#endif
	
	if ( !count ) {
		PWARN(("Reading busyflag ctrl %d stuck: checked %d times!", base, BUSYFLAG_STUCK));
		PWARN(("Disabling this lcd on this port!\n"));
		BIT_SET(hd44780.disabled, ctrl_nr);
	}
}

#endif

/* ------------------- low-high-level functions ---------------  */

void hd44780_send(unsigned char ctrl_nr, unsigned char flags, unsigned char command)
{
	if ( ctrl_nr > HD44780_NUM_CONTROLLERS ) return;
	if ( BIT_READ(hd44780.disabled, ctrl_nr) ) return;

#ifndef HD44780_NO_BF_CHECKING
	_hd44780_wait_for_ready_(ctrl_nr);
#endif
	
	/** write data */
	flags |= HD44780_RW_WRITE;
	_hd44780_data_forward_();
	_hd44780_data_set_(command);
	_hd44780_capable_(flags);
	_hd44780_enable_(flags, ctrl_nr);
	_hd44780_disable_(flags);
	
#ifdef HD44780_COUNTERS
	++hd44780.write_count[ctrl_nr];
#endif
	
#ifdef HD44780_CHECKER
	hd44780_parse(ctrl_nr, flags, command);
#endif
#ifdef HD44780_NO_BF_CHECKING
	if ( !BIT_READ(hd44780.disabled, ctrl_nr) )
		_hd44780_sleep_on_write_(flags, command);
#endif
}

#ifndef HD44780_WRITE_ONLY
unsigned char hd44780_recv(unsigned char ctrl_nr, unsigned char flags)
{
	unsigned char status;

	if ( ctrl_nr > HD44780_NUM_CONTROLLERS ) return 0;
	if ( BIT_READ(hd44780.disabled, ctrl_nr) ) return 0x7a;

#ifndef HD44780_NO_BF_CHECKING
	_hd44780_wait_for_ready_(ctrl_nr);
#endif

	/** read data */
	flags |= HD44780_RW_READ;
	_hd44780_data_reverse_();
	_hd44780_capable_(flags);
	_hd44780_enable_(flags, ctrl_nr);
	READ_EXTRA_DELAY();
	status = _hd44780_data_get_();
	_hd44780_disable_(flags);


#ifdef HD44780_COUNTERS
	++hd44780.read_count[ctrl_nr];
#endif

#ifdef HD44780_CHECKER
	hd44780_parse(ctrl_nr, flags, 0);
#endif
#ifdef HD44780_NO_BF_CHECKING
	if ( !BIT_READ(hd44780.disabled, ctrl_nr) )
		_hd44780_sleep_on_write_(flags, command);
#endif
	return status;
}
#endif

void hd44780_send_all(uint8_t flags, uint8_t command)
{
	uint8_t i;

#ifndef HD44780_NO_BF_CHECKING
	/* feature/bug - jesli wszystkie ctrl są disablowane,
	 * to oznacza po prostu że nie będzie sprawdzana flaga zajętości
	 * a i tak będzie program szedł dalej - Vnie ma returna. */
	for (i=0; i<HD44780_NUM_CONTROLLERS ; ++i) {
			if ( !BIT_READ(hd44780.disabled, i) )
				_hd44780_wait_for_ready_(i);
	}
#endif
	
	/** write data */
	flags |= HD44780_RW_WRITE;
	_hd44780_data_forward_();
	_hd44780_data_set_(command);
	_hd44780_capable_(flags);
	_hd44780_enable_all_(flags);
	_hd44780_disable_(flags);
	
#ifdef HD44780_COUNTERS
	for (i=0; i<HD44780_NUM_CONTROLLERS; ++i) {
		++hd44780.write_count[i];
	}
#endif
	
#ifdef HD44780_CHECKER
	hd44780_parse(HD44780_NUM_CONTROLLERS, flags, command);
#endif
#ifdef HD44780_NO_BF_CHECKING
	if ( lcddev.nobfcheck != 0x00 ) // if at least one hd44780 has nobf checking
		_hd44780_sleep_on_write_(flags, command);
#endif
}

/* ------------------- high level functions ---------------  */

/* 
 * hd44780_initialize_by_instruction
 * hd44780 documentation page 45 
 * If the power supply conditions for correctly operating the internal reset circuit are not met, initialization by 
 * instructions becomes necessary.
 * we do it anyway.
 */
static void hd44780_initialize_by_instruction(void)
{
	unsigned char i;
	
	/* no BF checking here */
	for(i=0; i<HD44780_NUM_CONTROLLERS; ++i) {
		BIT_SET(hd44780.disabled, i);
	}
	
	/* wait for more then 15 ms after vcc reises bla bla bla*/
	__delay_ms(15);
	hd44780_send_all(HD44780_RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 1.4 ms */
	__delay_us(1400);
	hd44780_send_all(HD44780_RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 100 us */
	__delay_us(100);
	hd44780_send_all(HD44780_RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	
	/* now we can start checking busyflag, but i do not want to do it, cause 
	 * there can be a situation, when reading from devices is not available
	 * (for technical or programmical reasons i dont care)
	 * so i just wait the execution time */
	 
	NORMAL_DELAY();
	hd44780_send_all(HD44780_RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	NORMAL_DELAY();
	hd44780_send_all(HD44780_RS_INST, 
			HD44780_DOOC_DISPLAYOFF | 
			HD44780_DOOC_CURSOROFF | 
			HD44780_DOOC_CURSORNOBLINK); /* display off */
	NORMAL_DELAY();
	hd44780_send_all(HD44780_RS_INST,
			HD44780_CLRDISP); /* display clear */
	NORMAL_DELAY();
	hd44780_send_all(HD44780_RS_INST,
			HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	NORMAL_DELAY();
	
	/* re-allow BFchecking on all displays */
	hd44780.disabled = 0;
}

void hd44780_init(void) 
{
	_hd44780_init_callback_();

#ifdef HD44780_CHECKER
	hd44780_init_checker();
#endif
	
	hd44780_initialize_by_instruction();
	
	/* now bf checking is set on all hd-s,
	 * autodetection and disabling busyflag detection will
	 * happen automagically in _hd44780_wait_for_ready_ */
	
	/* initialize user-specified configuration */
	hd44780_write_inst_all( HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_TWOLINES |
			HD44780_FS_5x8DOTS);
	hd44780_write_inst_all( HD44780_DOOC_DISPLAYON |
			HD44780_DOOC_CURSORON |
			HD44780_DOOC_CURSORNOBLINK);
	hd44780_write_inst_all( HD44780_CLRDISP);
	hd44780_write_inst_all( HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
}

