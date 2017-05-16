/**
 * common.h
 *
 * created by Kamil Cukrowski
 * under beerware license
 *
 * declaration staged to move elsewhere
 */
#ifndef COMMON_H
#define	COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <GenericTypeDefs.h>
#include <stdlib.h>
#include <errata.h>

#define CONFIG(num)                  (*(const __far unsigned char *)(0x300000+num))
#define  DEVID(num)                  (*(const __far unsigned char *)(0x3ffffe+num))


/**
 * PORT and TRIS usage example:
 * #define LIB_PORT A
 * #define LIB_PIN  5
 * TRIS(LIB_PORT, LIB_PIN) = 0;
 * PORT(LIB_PORT, LIB_PIN) = 1;
 *
 * PORT1 and TRIS1 usage example:
 * #define LIB_PORTPIN A, 5
 * TRIS1(LIB_PORTPIN) = 0;
 * PORT1(LIB_PORTPIN) = 1;
 */
#define __CONCAT5(a,b,c,d,e)         a ## b ## c ## d ## e
#define PORT(PORTNAME, PINNUMBER)    ( __CONCAT5( PORT , PORTNAME , bits.R , PORTNAME , PINNUMBER ) )
#define TRIS(PORTNAME, PINNUMBER)    ( __CONCAT5( TRIS , PORTNAME , bits.R , PORTNAME , PINNUMBER ) )
#define LAT(PORTNAME, PINNUMBER)     ( __CONCAT5( LAT  , PORTNAME , bits.R , PORTNAME , PINNUMBER ) )
#define PORT1(PORTNAMEPINNUMBER)     PORT(PORTNAMEPINNUMBER)
#define TRIS1(PORTNAMEPINNUMBER)     TRIS(PORTNAMEPINNUMBER)
#define LAT1(PORTNAMEPINNUMBER)      LAT(PORTNAMEPINNUMBER)

enum TRIS_DIRECTION {
	TRIS_OUT = 0,
	TRIS_IN  = 1,
};

#define ARRAY_SIZE(x)               ( sizeof(x) / sizeof((x)[0]) )

// sadly no typeof in xc8
#define MAX(X,Y) ( ((X) > (Y)) ? (X) : (Y))
#define MIN(X,Y) ( ((X) < (Y)) ? (X) : (Y))


/**
 * PIC18f2550 documentation page 111 to 120:
On a Power-on Reset, RA5 and RA3:RA0
are configured as analog inputs and read
as ‘0’. RA4 is configured as a digital input.

On a Power-on Reset, RB4:RB0 are
configured as analog inputs by default and
read as ‘0’; RB7:RB5 are configured as
digital inputs.
By programming the Configuration bit,
PBADEN (CONFIG3H<1>), RB4:RB0 will
alternatively be configured as digital inputs
on POR

On a Power-on Reset, these pins, except
RC4 and RC5, are configured as digital
inputs. To use pins RC4 and RC5 as digital
inputs, the USB module must be disabled
(UCON<3> = 0) and the on-chip
USB transceiver must be disabled
(UCFG<3> = 1).
 */
#define CONFIG_ALL_PORTS_AS_INPUTS() do{ \
	LATA = PORTA = LATB = PORTB = LATC = PORTC = 0x00; \
	ADCON1 = 0x0f; CMCON = 0x07; /* all A/D Ports as Digital I/O */ \
	/* UCON = 0x00; UCFG = 0x03; *//* disable usb - RC4 and RC5 as digital */ \
	TRISA = TRISB = TRISC = 0xff; \
}while(0)
#define CONFIG_ALL_PORTS_AS_OUTPUTS() do{ \
	LATA = PORTA = LATB = PORTB = LATC = PORTC = 0x00; \
	ADCON1 = 0x0f; CMCON = 0x07; /* all A/D Ports as Digital I/O */ \
	/* UCON = 0x00; UCFG = 0x03; *//* disable usb - RC4 and RC5 as digital */ \
	TRISA = TRISB = TRISC = 0x00; \
}while(0)

#endif	/* COMMON_H */

