/*
 * swSpiWrite.c
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#include "swSpiWrite.h"

#include <common.h> // GETPORT() GETTRIS()
#include <system.h> // SW_SPI_PORT , SW_SPI_PIN

#if defined(SW_SPI_SCK_PORT) && defined(SW_SPI_SCK_PIN) && defined(SW_SPI_OUT_PORT) && defined(SW_SPI_OUT_PIN)

#define PORTOUT PORT(SW_SPI_OUT_PORT, SW_SPI_OUT_PIN)
#define TRISOUT TRIS(SW_SPI_OUT_PORT, SW_SPI_OUT_PIN)
#define PORTSCK PORT(SW_SPI_SCK_PORT, SW_SPI_SCK_PIN)
#define TRISSCK TRIS(SW_SPI_SCK_PORT, SW_SPI_SCK_PIN)

void SwSpiWrite(char input)
{
	char BitCount;
	BitCount = 8;

	TRISOUT = TRISSCK = 0;

	// SCK idles low
	// Data output after falling edge of SCK
	// Data sampled before rising edge of SCK
	PORTOUT = 0;
	if(input&0x80)
		PORTOUT = 1;
	Nop();
	Nop();
	Nop();
	Nop();
	do {
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		PORTSCK = 1;
		input = input << 1;
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		PORTSCK = 0;
		PORTOUT = 0;
		if(input&0x80)
			PORTOUT = 1;
		BitCount--;
	} while(BitCount);
}

#endif
