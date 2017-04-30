/**
 * created by Kamil Cukrowski
 * under beerware license
 */
#ifndef COMMON_H
#define	COMMON_H

#define CONFIG(num) (*(const __far unsigned char *)(0x300000+num))
#define  DEVID(num) (*(const __far unsigned char *)(0x3ffffe+num))

#define __CONCAT5(a,b,c,d,e) a ## b ## c ## d ## e
#define GETPORT(portname, pinnumber) __CONCAT5( PORT, portname, bits.R, portname, pinnumber )
#define GETTRIS(portname, pinnumber) __CONCAT5( TRIS, portname, bits.R, portname, pinnumber )

#endif	/* COMMON_H */

