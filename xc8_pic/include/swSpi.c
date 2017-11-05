/*
 * swSpiWrite.c
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#include <common.h> // PORT() TRIS() or PORT1() TRIS1()
#include <swSpi.h>
#include <system.h> // SW_SPI_PORT , SW_SPI_PIN

#ifdef SW_SPI_SCK_PORTPIN
#define PORTSCK PORT(SW_SPI_SCK_PORTPIN)
#define TRISSCK TRIS(SW_SPI_SCK_PORTPIN)
#endif

#ifdef SW_SPI_OUT_PORTPIN
#define PORTOUT PORT(SW_SPI_OUT_PORTPIN)
#define TRISOUT TRIS(SW_SPI_OUT_PORTPIN)
#endif

#ifdef SW_SPI_IN_PORTPIN
#define PORTIN PORT(SW_SPI_IN_PORTPIN)
#define TRISIN TRIS(SW_SPI_IN_PORTPIN)
#endif

#ifndef SwSpiSckInit
#define SwSpiSckInit() TRISSCK = 0;
#endif

#ifndef SwSpiOutInit
#define SwSpiOutInit() TRISOUT = 0;
#endif

#ifndef SwSpiInInit
#define SwSpiInInit()  TRISIN = 0;
#endif

#ifdef PORTSCK

#ifdef PORTOUT

void SwSpiTransmit(char input)
{
	char BitCount;
	BitCount = 8;

	SwSpiSckInit();
	SwSpiOutInit();

	// SCK idles low
	// Data output after falling edge of SCK
	// Data sampled before rising edge of SCK
	PORTOUT = input&0x80;
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
		PORTOUT = input&0x80;
		BitCount--;
	} while(BitCount);
}

#endif // PORTOUT

#ifdef PORTIN

char SwSpiReceive(void)
{
	// TODO:
	for(;;);
}

#endif // PORTIN

#if defined(PORTIN) && defined(PORTOUT)

char SwSpiTransmit(char input)
{
	// TODO:
	for(;;);
}

#endif // defined(PORTIN) && defined(PORTOUT)

#endif // PORTSCK
