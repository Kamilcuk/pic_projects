/*
 *        File: bit.h
 *  Created on: 07.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef BIT_H_
#define BIT_H_

#define BIT_SET(REG, BIT)     ((REG) |= (BIT))

#define BIT_CLEAR(REG, BIT)   ((REG) &= ~(BIT))

#define BIT_READ(REG, BIT)    ((REG) & (BIT))

#define BIT_TOGGLE(REG, BIT)  ((REG) ^= (BIT))

#endif /* BIT_H_ */
