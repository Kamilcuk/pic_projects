/**
 * created by Kamil Cukrowski
 * under beerware license
 */
#ifndef COMMON_H
#define	COMMON_H

#define CONFIG(num) (*(const __far unsigned char *)(0x300000+num))
#define  DEVID(num) (*(const __far unsigned char *)(0x3ffffe+num))

#define BITMASK_GET(val, mask)                         (    (mask) & (val) )
#define BITMASK_CLEAR(val, mask)         do{ (val) = ( ( (~(mask)) & (val) ) | (         ~(mask) ) ); }while(0);
#define BITMASK_SET(val, mask)           do{ (val) = ( ( (~(mask)) & (val) ) | (          (mask) ) ); }while(0);
#define BITMASK_WRITE(val, mask, bitval) do{ (val) = ( ( (~(mask)) & (val) ) | ( (bitval)&(mask) ) ); }while(0);

#endif	/* COMMON_H */

