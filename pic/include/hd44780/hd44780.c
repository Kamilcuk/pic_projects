/*
 * hd44780.c - communicate with hd44780 compatible controllers
 * look in hd44780-config.h for more information!
 * 
 * Copyright 2013 Kamil Cukrowski <kamil@dyzio.pl>
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

#include <delay.h>
#include "types.h"
#include "bitops.h"
#include "hd44780-inst-def.h"
#include "hd44780.h"

/* -------------------- placeholders  ---------------- */
#define PDEBUG_hd44780( ... )
#define PWARN( ... )

struct pic_device lcddev;

/* ------------------------- checker -------------------------- */

#ifdef HD44780_CHECKER

unsigned char __near * __near lcd_state[8];
unsigned char cur_pos[MAX_NUM_CONTROLLERS];
unsigned char state1[6*40];
unsigned char state2[6*40];
unsigned char state3[4*40];


void hd44780_init_checker()
{
	unsigned char i;
	for(i=0;i<4*40;i++) {
		state1[i] = ' ';
		state2[i] = ' ';
		state3[i] = ' ';
	}
	for(;i<6*40;i++) {
		state1[i] = ' ';
		state2[i] = ' ';
	}
	lcd_state[0] = state1;
	lcd_state[1] = state1+80;
	lcd_state[2] = state1+160;
	lcd_state[3] = state2;
	lcd_state[4] = state2+80;
	lcd_state[5] = state2+160;
	lcd_state[6] = state3;
	lcd_state[7] = state3+80;
}

void hd44780_check()
{
	unsigned char i, j;
	unsigned char cur_sav, c;
	unsigned char __near * __near pnt;
	
	for(i=0;i<MAX_NUM_CONTROLLERS;i++) {
		
		if ( test_bit(i, lcddev.disabled) )	
			continue;
		
		pnt = lcd_state[i];
		
		// get current cursosr position
		cur_sav = hd44780_recv(i, RS_INST)&0x7f;
		hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | 0 );
		
		for(j=0;j<80;j++) {
			c = hd44780_recv(i, RS_DATA);
			if ( c != *pnt ) {
#ifdef HD44780_COUNTERS
				lcddev.errors_count[i]++;
#endif
				if ( j < 40 ) {
					hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 0 << 6 ) | j );
				} else {
					hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | ( 1 << 6 ) | j-40 );
				}
				hd44780_write_data(i, *pnt);
			}
			
			(pnt)++;
		}
		
		hd44780_write_inst(i, HD44780_DDRAM_ADDRESS | cur_sav );
	}
}

void hd44780_parse(unsigned char all, unsigned char flags, unsigned char command)
{
	unsigned char i;
	if ( all != MAX_NUM_CONTROLLERS ) {
		if ( flags ==  RW_WRITE|RS_INST && command&0x03 ) {
			cur_pos[all] = 0;
		} else if ( flags == RW_WRITE|RS_INST && command&0x80 ) {
			cur_pos[all] = command&0x7f;
		} else if ( flags == RW_WRITE|RS_DATA ) {
			i = cur_pos[all];
			if ( i <= 0x27 ) {
				*(lcd_state[all]+i) = command;
			} else {
				*(lcd_state[all]+40+i) = command;
			}
		} else if ( flags == RW_READ|RS_DATA ) {
			cur_pos[all] = hd44780_recv(all, RS_INST)&0x7f;
		}
	} else {
		if ( flags == RW_WRITE|RS_INST && command&0x03 ) {
			for(; all; --all)
				cur_pos[all-1] = 0;
		} else if ( flags == RW_WRITE|RS_INST && command & 0x80 ) {
			for(; all; --all)
				cur_pos[all-1] = command&0x7f;
		} else if ( flags == RW_WRITE|RS_DATA ) {
			for(; all; --all) {
				i = cur_pos[all-1];
				if ( i <= 0x27 ) {
					*(lcd_state[all]+i) = command;
				} else {
					*(lcd_state[all]+40+i) = command;
				}
			}
		}
	}
}

#endif

/* ---------------- low-medium-level help functinons ---------------  */

/** _hd44780_wait_after_operation
 * waits for hd44780 to complete send thing
 */
/*
static void _hd44780_sleep_on_write_(unsigned char flags, unsigned char command)
{
	LONG_DELAY(); return;
		if ( IS_RS_INST(flags) && ( command&0x03 ) ) {
			LONG_DELAY();
		} else {
			NORMAL_DELAY();
		}
}
*/

/** _hd44780_wait_for_busyflag_
 * wait for busyflag to go low on ctrl_num, mutex is locked
 */
static void _hd44780_wait_for_ready_(unsigned char ctrl_nr)
{
	unsigned int count;
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
	
#ifdef HD44780_CHECKER
	lcddev.bfchecks_count[ctrl_nr] += count;
#endif
	
	if ( !count ) {
		PWARN("Reading busyflag ctrl %d stuck: checked %d times!", base, BUSYFLAG_STUCK);
		PWARN("Disabling this lcd on this port!\n");
		set_bit(ctrl_nr, lcddev.disabled);
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

#ifndef HD44780_WRITE_ONLY
unsigned char hd44780_recv(unsigned char ctrl_nr, unsigned char flags)
{
	unsigned char status;
	
	if ( ctrl_nr > MAX_NUM_CONTROLLERS ) return 0;
	if ( test_bit(ctrl_nr, lcddev.disabled) ) return 0x7a;
	
	_hd44780_wait_for_ready_(ctrl_nr);
	
	/** read data */
	flags |= RW_READ;
	_hd44780_data_reverse_();
	_hd44780_capable_(flags);
	_hd44780_enable_(flags, ctrl_nr);
	READ_EXTRA_DELAY();
	status = _hd44780_data_get_();
	_hd44780_disable_(flags);
	
	
#ifdef HD44780_COUNTERS
	lcddev.read_count[ctrl_nr]++;
#endif
	
#ifdef HD44780_CHECKER
	hd44780_parse(ctrl_nr, flags, 0);
#endif

	return status;
}
#else
unsigned char hd44780_recv(unsigned char ctrl_nr, unsigned char flags)
{
	ctrl_nr;
	flags;
	return 1;
}
#endif

void hd44780_send(unsigned char ctrl_nr, unsigned char flags, unsigned char command)
{
	if ( ctrl_nr > MAX_NUM_CONTROLLERS ) return;
	if ( test_bit(ctrl_nr, lcddev.disabled) ) return;
	
	_hd44780_wait_for_ready_(ctrl_nr);
	
	/** write data */
	flags |= RW_WRITE;
	_hd44780_data_forward_();
	_hd44780_data_set_(command);
	_hd44780_capable_(flags);
	_hd44780_enable_(flags, ctrl_nr);
	_hd44780_disable_(flags);
	
#ifdef HD44780_COUNTERS
	lcddev.write_count[ctrl_nr]++;
#endif
	
#ifdef HD44780_CHECKER
	hd44780_parse(ctrl_nr, flags, command);
#endif

	//if ( test_bit(ctrl_nr, lcddev.nobfcheck) )
	//	_hd44780_sleep_on_write_(flags, command);
}

void hd44780_send_all(u8 flags, u8 command)
{
	unsigned char i;
	
	/* feature/bug - jesli wszystkie ctrl są disablowane,
	 * to oznacza po prostu że nie będzie sprawdzana flaga zajętości
	 * a i tak będzie program szedł dalej - Vnie ma returna. */
	for (i=0; i<MAX_NUM_CONTROLLERS ; i++) {
			if ( !test_bit(i, lcddev.disabled) )
				_hd44780_wait_for_ready_(i);
	}
	
	/** write data */
	flags |= RW_WRITE;
	_hd44780_data_forward_();
	_hd44780_data_set_(command);
	_hd44780_capable_(flags);
	_hd44780_enable_all_(flags);
	_hd44780_disable_(flags);
	
#ifdef HD44780_COUNTERS
	for (i=0; i<MAX_NUM_CONTROLLERS; i++)
		lcddev.write_count[i]++;
#endif
	
#ifdef HD44780_CHECKER
	hd44780_parse(MAX_NUM_CONTROLLERS, flags, command);
#endif
	//if ( lcddev.nobfcheck != 0x00 ) // if at least one hd44780 has nobf checking
	//	_hd44780_sleep_on_write_(flags, command);
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
	unsigned char i;
	
	/* no BF checking here */
	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
		set_bit(i, lcddev.disabled);
	
	
	/* wait for more then 15 ms after vcc reises bla bla bla*/
	delay10ktcy(50);
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 1.4 ms */
	delay10ktcy(5);
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	/* wait for more then 100 us */
	delay10ktcy(1);
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	
	/* now we can start checking busyflag, but i do not want to do it, cause 
	 * there can be a situation, when reading from devices is not available
	 * (for technical or programmical reasons i dont care)
	 * so i just wait the execution time */
	 
	NORMAL_DELAY();
	hd44780_send_all(RS_INST,
			HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_ONELINE |
			HD44780_FS_5x8DOTS);
	NORMAL_DELAY();
	hd44780_send_all(RS_INST, 
			HD44780_DOOC_DISPLAYOFF | 
			HD44780_DOOC_CURSOROFF | 
			HD44780_DOOC_CURSORNOBLINK); /* display off */
	NORMAL_DELAY();
	hd44780_send_all(RS_INST,
			HD44780_CLRDISP); /* display clear */
	NORMAL_DELAY();
	hd44780_send_all(RS_INST,
			HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	NORMAL_DELAY();
	
	/* allow BFchecking */
	for(i=0; i<MAX_NUM_CONTROLLERS; i++)
		clear_bit(i, lcddev.disabled);
}

#ifdef HD44780_COUNTERS
__once void lcddev_counters_reset(void)
{
	unsigned char i;
	for (i=0; i<MAX_NUM_CONTROLLERS; i++) {
		lcddev.write_count[i] = 0;
		lcddev.read_count[i] = 0;
		lcddev.bfchecks_count[i] = 0;
#ifdef HD44780_CHECKER
		lcddev.errors_count[i] = 0;
#endif
	}
}
#endif

#define lcddev_init() do { lcddev.disabled = 0; }while(0)

void hd44780_init(void) 
{
	hd44780_init_port();
	lcddev_init();
#ifdef HD44780_COUNTERS
	lcddev_counters_reset(); 
#endif
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

