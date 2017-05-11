/*
 * bitmask.h
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#ifndef BITMASK_H_
#define BITMASK_H_

#define BITMASK_GET(val, mask)                       ( (val) &            (mask)   )
#define BITMASK_CLEAR(val, mask)         do{ (val) = ( (val) | (         ~(mask) ) ); }while(0);
#define BITMASK_SET(val, mask)           do{ (val) = ( (val) | (          (mask) ) ); }while(0);
#define BITMASK_WRITE(val, mask, bitval) do{ (val) = ( (val) | ( (bitval)&(mask) ) ); }while(0);

#endif /* BITMASK_H_ */
