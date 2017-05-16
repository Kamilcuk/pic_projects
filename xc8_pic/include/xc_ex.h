/*
 *        File: xc_ex.h
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ----------------------------------------------------------------------------
 *  "THE BEER-WARE LICENSE" (Revision 42):
 *  Kamil Cukrowski wrote this file. As long as you retain this notice you
 *  can do whatever you want with this stuff. If we meet some day, and you think
 *  this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifndef XC_EX_H_
#define XC_EX_H_

/**
 * In stupid xc8:
 * If an "static" equation has no numbers higher then "int" (2^16), then equations are done with int resolution.
 * Example:
 *  uint16_t a = ( 500*256/256 );
 *    gives a = 0;
 * However adding a stupid ( bignumer/bignumer ) devision "upscales" the (preprocessor?) resolution to long
 * Examples:
 *  uint16_t a = ( 100000/100000 * 500*256/256 );
 *    gives a = 500;
 *
 * Usage:
 *   uint16_t a = ( FUCK_XC8_CAST_TO_LONG * 500*256/256 );
 */
#define FUCK_XC8_BIG_NUMBER     1073741824 // = 2^30
#define FUCK_XC8_CAST_TO_LONG   ( (FUCK_XC8_BIG_NUMBER) / (FUCK_XC8_BIG_NUMBER) )

#endif /* XC_EX_H_ */
