/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include <stdint.h>
#include <plib/delays.h>
//#include "printft.h"
#include <plib/delays.h>
#include <time.h>
#include <stdlib.h>
#include "usbhid_stdio/usbhid_stdio.h"
#include "morse.h"

void interrupt high_priority SYS_InterruptHigh(void)
{
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

void test_printf()
{
    static uint8_t u8 = 123;
    printf("lala\n");
    printf("Compiled with XC8 version %d\n", __XC8_VERSION);
    printf("on %s  at %s UTC\n", __DATE__, __TIME__);
    printf("sizeof(float) = %d, sizeof(double) = %d\n",
            sizeof(float), sizeof(double));
    printf("u8 = %d = %x = %02x\n", u8, u8, u8);
    printf("\n");
    printf("\n");
    ++u8;
    flush();
}


void main(void)
{
	uint32_t counter = 0;

	usbStdioInitBlocking(1);

	PORTA = PORTB = PORTC =
			TRISA = TRISB = TRISC =
			LATA = LATB = LATC = 0x00;

    /*while(1)
    {
        printf("----------------------------\n");
    	test_printf();
    	__delay_ms(1000);
    	test_printf();
    	__delay_ms(1000);
    }*/

	while(1) {
		if ( counter < 40000 ) {
			++counter;
		} else {
			counter = 0;
			test_printf();
		}
	}
}

