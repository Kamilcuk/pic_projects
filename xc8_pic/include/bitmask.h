/*
 * bitmask.h
 *
 *  Created on: 27.04.2017
 *      Author: kamil
 */

#ifndef BITMASK_H_
#define BITMASK_H_

#define BITMASK_READ(REG, MASK)          ( (REG) &   (MASK) )
#define BITMASK_CLEAR(REG, MASK)         ( (REG) &= ~(MASK) )
#define BITMASK_SET(REG, MASK)           ( (REG) |=  (MASK) )
#define BITMASK_TOGGLE(REG, MASK)        ( (REG) ^=  (MASK) )
#define BITMASK_WRITE(REG, MASK, BITVAL) ( (REG)  = ((REG)&(~(MASK))) | (BITVAL) )

#endif /* BITMASK_H_ */
