/*
 * hd44780.c - communicate with hd44780 compatible controllers
 * look in hd44780-config.h for more information!
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
#include "bitops.h"
#include "hd44780-inst-def.h"
#include "hd44780-config.h"
#include "hd44780.h"

struct pic_device lcddev;

/* -------------- low-low-level operations functions -------------- */
/* ** those are defines, cause i care for speed, not for space */

/* set port for writing to port */
#define _hd44780_data_forward_() TRISB=0x00;
/* set port for reading from port */
#define _hd44780_data_reverse_() TRISB=0xFF;
/** set a specifed DB0 to DB7 bits */
#define _hd44780_data_set_(y) PORTB=(y);
/** read DB0 to DB7  */
#define _hd44780_data_get_() ((PORTB))
/** read only busyflag (discard rest of data) */
#define _hd44780_data_get_busyflag_() ((PORTBbits.RB7))

/* sets the flags/data for the controler */
#define _hd44780_capable_(flags) \
do { \
	PORTC = flags; \
	ADDRESS_SET_UP_TIME(); \
} while(0)
/* enables controler */
#define _hd44780_enable_(flags, ctrl_nr) \
do { \
	u8 n; \
	n = (ctrl_nr == 7) ? (1) : ( (0x02)<<(ctrl_nr) ); \
	PORTA = n&0x3f; \
	PORTC = ( n&0xc0 ) | flags; \
	ENABLE_PULSE_WIDTH(); \
} while(0);
/* enables all controllers */
#define _hd44780_enable_all_(flags) \
do { \
	PORTA = 0x3f; \
	PORTC = 0xc0 | flags; \
	ENABLE_PULSE_WIDTH(); \
} while(0)
/* disables controler */
#define _hd44780_disable_(flags) \
do { \
	PORTA = 0x00; \
	PORTC = flags; \
	DATA_HOLD_TIME(); \
} while(0)

/* ---------------- low-medium-level help functinons ---------------  */

/** _hd44780_wait_for_busyflag_
 * wait for busyflag to go low on ctrl_num, mutex is locked
 */
static void _hd44780_wait_for_ready_(u8 ctrl_nr)
{
	u16 count;
	PDEBUG_hd44780(" ^ waiting for ctrl %d to lower the busyflag.\n", NUM_CONTROLLERS);
	
	_hd44780_data_reverse_();
	_hd44780_capable_(RW_READ | RS_INST);
	_hd44780_enable_(RW_READ | RS_INST, ctrl_nr);
	for ( count = BUSYFLAG_STUCK; count && _hd44780_data_get_busyflag_(); --count ) {
		_hd44780_disable_(RW_READ | RS_INST);
		
		BUSYFLAG_DELAY();
		
		_hd44780_enable_(RW_READ | RS_INST, ctrl_nr);
	}
	_hd44780_disable_(RW_READ | RS_INST);
	
#ifdef HD44780_COUNTERS
	lcddev.lcd[ctrl_nr].bfchecks_count += count;
#endif
	
	if ( !count ) {
		PWARN("Reading busyflag ctrl %d stuck: checked %d times!", base, BUSYFLAG_STUCK);
		PWARN("Disabling busyflag checking on this port!\n");
		set_bit(FLAG_NOBFCHECK, lcddev.flags);
	}
}

/* ------------------- low-high-level functions ---------------  */

/** init the port */
__once void hd44780_init_port(void)
{
	ADCON0=0x00; // turn off analog to digital conversion module
	ADCON1=0x0f; // set all analog to digital conversion module inputs as digital inputs/outputs
	CMCON=0x07; // turn off comparator module
	
	/* port A */
	PORTA=0x00;
	LATA=0x00;
	TRISA=0x00;
	
	// port b
	PORTB=0x00;
	LATB=0x00;
	TRISB=0x00;
	
	// port c
	PORTC=0x00;
	LATC=0x00;
	TRISC=0x00;
	
	_hd44780_data_set_(0x00);
	_hd44780_data_reverse_();
}


u8 hd44780_recv(u8 ctrl_nr, u8 flags)
{
	u8 status;
	
	if ( ctrl_nr >= NUM_CONTROLLERS ) return 0;
	
	flags |= RW_READ;
	
	if ( !test_bit(FLAG_NOBFCHECK, lcddev.flags) ) 
		_hd44780_wait_for_ready_(ctrl_nr);
	/** read data */
	_hd44780_data_reverse_();
	_hd44780_capable_(flags);
	_hd44780_enable_(flags, ctrl_nr);
	READ_EXTRA_DELAY();
	status = _hd44780_data_get_();
	_hd44780_disable_(flags);
	
	
#ifdef HD44780_COUNTERS
	lcddev.lcd[ctrl_nr].read_count++;
#endif
	
	return status;
}

void hd44780_send(u8 ctrl_nr, u8 flags, u8 command)
{
	if ( ctrl_nr >= NUM_CONTROLLERS ) return;
	
	flags |= RW_WRITE;
	
	if ( !test_bit(FLAG_NOBFCHECK, lcddev.flags) ) 
		_hd44780_wait_for_ready_(ctrl_nr);
		
	/** write data */
	_hd44780_data_forward_();
	_hd44780_data_set_(command);
	_hd44780_capable_(flags);
	_hd44780_enable_(flags, ctrl_nr);
	_hd44780_disable_(flags);
	
#ifdef HD44780_COUNTERS
	lcddev.lcd[ctrl_nr].write_count++;
#endif
	
}

void hd44780_send_all(u8 flags, u8 command)
{
	flags |= RW_WRITE;
	
	if ( !test_bit(FLAG_NOBFCHECK, lcddev.flags) ) {
		unsigned char i;
		for (i=0; i<NUM_CONTROLLERS ; i++) {
			_hd44780_wait_for_ready_(i);
		}
	}
	/** write data */
	_hd44780_data_forward_();
	_hd44780_data_set_(command);
	_hd44780_capable_(flags);
	_hd44780_enable_all_(flags);
	_hd44780_disable_(flags);
	
#ifdef HD44780_COUNTERS
	for (i=0; i<NUM_CONTROLLERS; i++)
		lcddev.lcd[i].write_count++;
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
__once void hd44780_initialize_by_instruction(void)
{
	u8 i, j;
	
	/* no BF checking here */
	set_bit(FLAG_NOBFCHECK, lcddev.flags);
	
	/* wait for more then 15 ms */
	for (i = 43; i; --i)
		for (j=0xff; j; --j);
			do { }while(0);
		
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 1.4 ms */
	for (i = 17; i; --i)
		for (j = 0xff; j; --j)
			do { }while(0);
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 100 us */
	for (i = 2; i; --i)
		for (j = 0xff; j; --j);
			do { }while(0);
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	
	/* now we can start checking busyflag, but i do not want to do it, cause 
	 * there can be a situation, when reading from devices is not available
	 * (for technical or programmical reasons i dont care)
	 * so i wait the execution time */
	 
	/* wait for more then 37 us */
	for (i = 112; i; --i)
		do { }while(0);
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 37 us */
	for (i = 112; i; --i)
		do { }while(0);
	hd44780_send_all(RS_INST, 
			HD44780_DOOC_DISPLAYOFF | 
			HD44780_DOOC_CURSOROFF | 
			HD44780_DOOC_CURSORNOBLINK); /* display off */
	/* wait for more then 37 us */
	for (i = 112; i; --i)
		do { }while(0);
	hd44780_send_all(RS_INST,
			HD44780_CLRDISP); /* display clear */
	/* wait for more then 37 us */
	for (i = 112; i; --i)
		do { }while(0);
	hd44780_send_all(RS_INST,
			HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	/* wait for more then 37 us */
	for (i = 112; i; --i)
		do { }while(0);
	
	/* allow BFchecking */
	clear_bit(FLAG_NOBFCHECK, lcddev.flags);
}

#ifdef HD44780_COUNTERS
__once lcddev_counters_reset(void)
{
	u8 i;
	for (i=0; i<NUM_CONTROLLERS; i++) {
		lcddev.lcd[i].write_count = 0;
		lcddev.lcd[i].read_count = 0;
		lcddev.lcd[i].bfchecks_count = 0;
	}
}
#else
#define lcddev_counters_reset() do { ; } while(0)
#endif

#define lcddev_init() do { lcddev.flags = 0; lcddev_counters_reset(); }while(0)

void hd44780_init(void) 
{
	hd44780_init_port();
	
	hd44780_initialize_by_instruction();
	
	lcddev_init();
	
	/* initialize user-specified configuration */
	write_inst_all( HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_TWOLINES |
			HD44780_FS_5x8DOTS);
	write_inst_all( HD44780_DOOC_DISPLAYON |
			HD44780_DOOC_CURSORON |
			HD44780_DOOC_CURSORBLINK);
	write_inst_all( HD44780_CLRDISP);
	write_inst_all( HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
}
