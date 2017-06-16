/*
 *        File: xc_ex.h
 *  Created on: 08.05.2017
 *      Author: Kamil Cukrowski
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
 */

#ifndef XC_EX_H_
#define XC_EX_H_

/**
 * In xc8:
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

/**
 * XC8 PreProcessor cast to LONG
 */
#define XC8PP_LONG(x)           ( FUCK_XC8_CAST_TO_LONG * x )

#endif /* XC_EX_H_ */
