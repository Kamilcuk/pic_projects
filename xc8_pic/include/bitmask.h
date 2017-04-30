/*
 * bitmask.h
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#ifndef BITMASK_H_
#define BITMASK_H_

#define BITMASK_GET(val, mask)                         (    (mask) & (val) )
#define BITMASK_CLEAR(val, mask)         do{ (val) = ( ( (~(mask)) & (val) ) | (         ~(mask) ) ); }while(0);
#define BITMASK_SET(val, mask)           do{ (val) = ( ( (~(mask)) & (val) ) | (          (mask) ) ); }while(0);
#define BITMASK_WRITE(val, mask, bitval) do{ (val) = ( ( (~(mask)) & (val) ) | ( (bitval)&(mask) ) ); }while(0);

#endif /* BITMASK_H_ */
