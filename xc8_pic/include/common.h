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

#define __CONCAT5(a,b,c,d,e)         a ## b ## c ## d ## e
#define PORT(portname, pinnumber)    __CONCAT5( PORT , portname , bits.R , portname , pinnumber )
#define TRIS(portname, pinnumber)    __CONCAT5( TRIS , portname , bits.R , portname , pinnumber )

#define ARRAY_SIZE(x)               ( sizeof(x) / sizeof((x)[0]) )

// sadly no typeof in xc8
#define MAX(X,Y) ( ((X) > (Y)) ? (X) : (Y))
#define MIN(X,Y) ( ((X) < (Y)) ? (X) : (Y))

#endif	/* COMMON_H */

