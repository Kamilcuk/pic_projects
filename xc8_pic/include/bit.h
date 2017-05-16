/*
 *        File: bit.h
 *  Created on: 07.05.2017
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

#ifndef BIT_H_
#define BIT_H_

#define BIT_READ(REG, BIT)    ( (REG) &   (1<<(BIT)) )
#define BIT_CLEAR(REG, BIT)   ( (REG) &= ~(1<<(BIT)) )
#define BIT_SET(REG, BIT)     ( (REG) |=  (1<<(BIT)) )
#define BIT_TOGGLE(REG, BIT)  ( (REG) ^=  (1<<(BIT)) )

#define BIT_WRITE(REG, BIT, VAL) do{ \
	if((VAL)) { \
		BIT_SET(REG,BIT); \
	} else { \
		BIT_CLEAR(REG,BIT); \
	} \
}while(0)

#define BIT_WRITE_EXPRESSION(REG, BIT, VAL) ( (REG) = ( (REG)& ~(1<<(BIT)) ) | ( (VAL)<<(BIT) ) )

//#define BIT_WRITE(REG, BIT, VAL) ( (REG) = ((VAL) ? ((REG) | (1<<(BIT))) : ((REG) & (1<<(BIT))) ) )
//#define BIT_WRITE(REG, BIT, VAL) ( (REG)  = ((REG)&(~(1<<(BIT)))) | ((VAL)?(1<<(BIT):0)) )

#endif /* BIT_H_ */
