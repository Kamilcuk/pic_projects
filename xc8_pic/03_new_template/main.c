/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

#include <cmdline.h>

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>

#include "usbhid_stdio/usbhid_stdio.h"

/* ------------------------------------- interrupts ------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{    
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

/* ---------------------------------------- interaction -------------------------------------- */

void cmdlineService_callback(void)
{
	switch(cmdline.buff[0]) {
	case 'h': case 'H': case 'v': case 'V': // usage and version
		printf(
				"\n"
				"Version information:\n"
				"ultifan pic firmware\n"
				"Type=ultifan\n"
				"Version=0.1.1\n"
				"Author=Kamil Cukrowski\n"
				"Available commands: \n"
				" i                 - print current configuration\n"
				" f NUM VAL         - set fan number num to VAL voltage in percent\n"
				" l                 - get lumination value from TSL2560\n"
				"\n"
		);
		/* no break */
	default:
		cmdlineService_standard();
		break;
	}
}

/* ----------------------------------------------------------------------------------------- */

void main_preinit(void)
{
	// set all ports as inputs
	PORTA = PORTB = PORTC = 0x00;
	TRISA = TRISB = TRISC = 0xff;
	LATA = LATB = LATC = 0x00;
	// enable interrupts
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

void main(void)
{
	main_preinit();

	usbStdioInitBlocking(1);

	printf("Startup completed.\n");

	while(1) {

		cmdlineService_nonblock();

		/* user code */

	}
}

