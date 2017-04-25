/*
 * cmdline.c
 *
 *  Created on: 31.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#include "cmdline.h"
#include "system.h"
#include "cdefs.h"
#include "stdio_ex.h"
#include "common.h"
#include <stdio.h>
#include <ctype.h>

#define CMDLINE_ENABLED
#ifdef CMDLINE_ENABLED

#define CMDLINE_PS1 "$ "

/**
 * state variable
 */
struct cmdline_s cmdline = { {0}, 0};

/**
 * Blocking read/wait until '\n' is received or until buff is full
 * All non-printable (except '\n') characters are omitted.
 * During read, buffer buff is filled and cmdline.buffpos is set to number chars read.
 */
static void cmdlineGetCmd(void)
{
	char c; // optimization

	{
AGAIN:
		printf(CMDLINE_PS1);
		cmdline.buffpos = 0;
	}

	do {

		flush();

		c = getchar();

		if ( c == '\n' ) {
			break;
		}
#ifdef CMDLINE_BACKSPACE_ENABLED
		if ( c == '\b' || c == 0x7f ) { // '\b' is backspace , 0x7f is DEL
			printf("\n");
			if ( cmdline.buffpos ) {
				uint8_t i;
				--cmdline.buffpos;
				cmdline.buff[cmdline.buffpos] = '\0';
				printf(CMDLINE_PS1"%s", cmdline.buff);
			}
			continue;
		}
#endif
		if ( !isprint(c) ) {
			continue;
		}

		printf("%c", c);

		cmdline.buff[cmdline.buffpos] = c;
		++cmdline.buffpos;
	} while( cmdline.buffpos < (sizeof(cmdline.buff)-1) );
	printf("\n");
	// last byte fill with '\0' sign
	cmdline.buff[cmdline.buffpos] = '\0';
	// if we received only newline character, start over
	if ( cmdline.buffpos == 0 ) {
		goto AGAIN;
	}
}

/**
 * Same as cmdGetCmd but in a non-blocking fashion.
 * @return 0xff if '\n' was received and reading is done, 0 otherwise
 */
static uint8_t cmdlineGetCmd_thread()
{
	static char state = 0xff;
	volatile char c; // optimization

	if ( state ) {
		state = 0;
AGAIN:
		// "first run"
		cmdline.buffpos = 0;
		printf(CMDLINE_PS1);
	}
	do {

		if ( !getchar_ready() ) {
			flush();
			return 0;
		}
		c = getchar();

		flush();

		if ( c == '\n' ) {
			break;
		}
#ifdef CMDLINE_BACKSPACE_ENABLED
		if ( c == '\b' || c == 0x7f ) { // '\b' is backspace , 0x7f is DEL
			printf("\n"CMDLINE_PS1);
			if ( cmdline.buffpos ) {
				uint8_t i;
				--cmdline.buffpos;
				for(i=0;i<cmdline.buffpos;++i) {
					printf("%c", cmdline.buff[i]);
				}
			}
			continue;
		}
#endif
		if ( !isprint(c) ) {
			continue;
		}

		printf("%c", c);

		cmdline.buff[cmdline.buffpos] = c;
		++cmdline.buffpos;
	} while( cmdline.buffpos < (sizeof(cmdline.buff)-1) );
	printf("\n");
	// if we received only newline character, start over
	if ( cmdline.buffpos == 0 ) {
		goto AGAIN;
	}
	// last byte fill with '\0' sign
	cmdline.buff[cmdline.buffpos] = '\0';
	// success
	state = 0xff;
	return 0xff;
}

void cmdlineService_standard(void)
{
	switch(cmdline.buff[0]) {
	case 'B':
		di();
		asm("goto 0x001C");
		return;
	case 'R':
		asm("reset");
		return;
	case 'C': /* Configuration bits */
	{
		uint8_t i;
		char c1, c2;
		for(i=0;i<7;++i) {
			c1 = CONFIG(i*2  );
			c2 = CONFIG(i*2+1);
			printf(
				"CONFIG%dL=%02x\n"
				"CONFIG%dH=%02x\n"
				,
				i+1, c1,
				i+1, c2
			);
		}
		c1 = DEVID(0);
		c2 = DEVID(1);
		printf(
				"  DEVID1=%02x\n"
			    "  DEVID2=%02x\n"
				"  DEVICE=PIC18F2550\n"
				,
				c1,
				c2
		);
	}
		return;
	default:
		printf("Unrecognized command %c = 0x%02x\n", cmdline.buff[0], cmdline.buff[0]);
		/* no break */
	case 'h':
	case 'H': // usage
	case 'v':
	case 'V': // print version
		printf(
				"\n"
				"Compiled=XC8 version " __XSTRING(__XC8_VERSION) " on " __DATE__ " " __TIME__ "\n"
				"Input buffer length: %u\n"
				"Available standard commands: \n"
				" [H|h|V|v]         - print usage and version info\n"
				" C                 - print out configuration bits and device id\n"
				" B                 - switch to bootloader\n"
				" R                 - soft reset\n"
				"\n"
				,
				sizeof(cmdline.buff[0])
		);
		return;
	}
}

void cmdlineService(void)
{
	cmdlineGetCmd();
	cmdlineService_callback();
}

void cmdlineServiceThread()
{
	if ( cmdlineGetCmd_thread() ) {
		cmdlineService_callback();
	}
}

#endif
