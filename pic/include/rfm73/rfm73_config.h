//***************************************************************************//
//
// COPYRIGHT NOTICE (zlib license)
//
// Loosely based on the example application provided by HopeRF
//
// (c) Wouter van Ooijen - wouter@voti.nl
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//***************************************************************************//
// minor, very very small changes to port it with sdcc and pic18f2550 
// by Kamil Cukrowski <kamil@dyzio.pl> 2013

#ifndef _RFM73_CONFIG_H_
#define _RFM73_CONFIG_H_


#define PIN_COPY(...) 
#define WAIT_US(...) 
#define wait_ms(...)


#define RFM73_SCK( x )   PIN_COPY( PORTC, 0, (x) ) 
#define RFM73_MOSI( x )  PIN_COPY( PORTC, 1, (x) )
#define RFM73_MISO       ( TRISCbits.RC2 )
#define RFM73_CSN( x )   PIN_COPY( PORTC, 3, (x) )
#define RFM73_CE( x )    PIN_COPY( PORTC, 4, (x) )

#define RFM73_PIN_DIRECTION { \
   TRISCbits.TRISC0 = 0; \
   TRISCbits.TRISC1 = 0; \
   TRISCbits.TRISC2 = 1; \
   TRISAbits.TRISA3 = 0; \
   TRISAbits.TRISA4 = 0; \
}

#define RFM73_WAIT_US( x ) WAIT_US( x )
#define RFM73_WAIT_MS( x ) wait_ms( x )

#include "rfm73.h"

#endif
