/*
 * cmdline.c
 *
 *  Created on: 31.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#include "cmdline.h"

#include "cdefs.h" // __XSTRING
#include "stdio_ex.h" // getchar_ready() flush()

#include <common.h> // CONFIG(x) DEVID(x)

#include <system.h> // CMDLINE_ENABLED

#include <xc.h> // di()
#include <stdio.h> // printf() getchar()
#include <ctype.h> // isprint()
#include <stdbool.h>

#ifndef CMDLINE_HAS_GETCHAR_READY
#define CMDLINE_HAS_GETCHAR_READY 1
#endif // CMDLINE_HAS_GETCHAR_READY

/**
 * Just like PS1 in bash
 */
#ifndef CMDLINE_PROMPT
#define CMDLINE_PROMPT "$ "
#endif // CMDLINE_PROMPT

struct cmdline_s cmdline = {0};

bool cmdlineGetCmd_busy = false;

void cmdlineGetCmd_nonblock(void)
{
	if ( !cmdlineGetCmd_busy ) {
		cmdlineGetCmd_busy = true;
AGAIN:
		// "first run"
		cmdline.buffpos = 0;
		printf( CMDLINE_PROMPT );
	}

	do {
		char c; // optimization

#if CMDLINE_HAS_GETCHAR_READY
		if ( !getchar_ready() ) {
			goto END;
		}
#endif // CMDLINE_HAS_GETCHAR_READY

		c = getchar();

		flush();

		if ( c == '\n' ) {
			break;
		} else
#ifdef CMDLINE_BACKSPACE_ENABLED
		if ( c == '\b' || c == 0x7f ) { // '\b' is backspace , 0x7f is DEL
			putchar( '\n' );
			printf( CMDLINE_PROMPT );
			if ( cmdline.buffpos ) {
				uint8_t i, *pnt;
				--cmdline.buffpos;
				pnt = &cmdline.buff[0];
				for(i = cmdline.buffpos; i; --i) {
					putchar( *pnt++ );
				}
			}
			continue;
		}
#endif
		if ( isprint(c) ) {

			putchar( c );

			cmdline.buff[cmdline.buffpos++] = c;
		}

	} while( cmdline.buffpos < ( (sizeof(cmdline.buff)/sizeof(*cmdline.buff)) - 1 ) );
	putchar( '\n' );

	// if we received only newline character, start over
	if ( !cmdline.buffpos ) {
		goto AGAIN;
	}
	// last byte fill with '\0' sign
	cmdline.buff[cmdline.buffpos] = '\0';
	// success
	cmdlineGetCmd_busy = false;

END:
	flush();
}

void cmdlineService_standard(void)
{
	switch(cmdline.buff[0]) {
	case 'B':
		di();
		asm("goto 0x001C");
		break;
	case 'R':
		asm("reset");
		break;
	case 'C': { /* Configuration bits */
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
	}	break;
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
		break;
	default:
		printf("Unrecognized command %c = 0x%02x\n", cmdline.buff[0], cmdline.buff[0]);
		break;
	}
}

