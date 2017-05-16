/*
 * swSpiWrite.c
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#include "swSpiWrite.h"

#include <common.h> // PORT() TRIS() or PORT1() TRIS1()
#include <system.h> // SW_SPI_PORT , SW_SPI_PIN

#if defined(SW_SPI_SCK_PORT) && defined(SW_SPI_SCK_PIN) && defined(SW_SPI_OUT_PORT) && defined(SW_SPI_OUT_PIN)

#define PORTSCK PORT(SW_SPI_SCK_PORT, SW_SPI_SCK_PIN)
#define TRISSCK TRIS(SW_SPI_SCK_PORT, SW_SPI_SCK_PIN)
#define PORTOUT PORT(SW_SPI_OUT_PORT, SW_SPI_OUT_PIN)
#define TRISOUT TRIS(SW_SPI_OUT_PORT, SW_SPI_OUT_PIN)

#elif defined(SW_SPI_SCK_PORTPIN) && defined(SW_SPI_OUT_PORTPIN)

#define PORTSCK PORT1(SW_SPI_SCK_PORTPIN)
#define TRISSCK TRIS1(SW_SPI_SCK_PORTPIN)
#define PORTOUT PORT1(SW_SPI_OUT_PORTPIN)
#define TRISOUT TRIS1(SW_SPI_OUT_PORTPIN)

#else
#error In order to swSpiWrite define either \
SW_SPI_SCK_PORT, SW_SPI_SCK_PIN, SW_SPI_OUT_PORT and SW_SPI_OUT_PIN \
or define SW_SPI_SCK_PORTPIN and SW_SPI_OUT_PORTPIN
#endif

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
