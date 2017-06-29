/*
 * Copyright 2010 Microchip Technology Inc, all rights reserved
 *
 * This file defines the standard integer types per ISO/IEC 9899:1999
 *
 */

#include <stdint.h>

/**
 * Kamil Cukrowski:
 * this code fixes lacking int24_t definitions in stdint.h in XC8 version 1.42 and above
 * http://www.microchip.com/forums/m989939.aspx
 */

#ifdef __XC8
#if __XC8_VERSION == 1420

#ifndef __CCI__
#ifndef int24_t
typedef signed short long int int24_t;
#define int24_t int24_t
#define INT24_MIN (-8388608L)
#define INT24_MAX (8388607L)
#endif
#endif

#ifndef __CCI__
#ifndef uint24_t
typedef unsigned short long int uint24_t;
#define uint24_t uint24_t
#define UINT24_MAX (16777215UL)
#endif
#endif

#ifndef int_least24_t
#ifdef __CCI__
typedef signed long int int_least24_t;
#define INT_LEAST24_MIN (-2147483648L)
#define INT_LEAST24_MAX (2147483647L)
#else
typedef signed short long int int_least24_t;
#define INT_LEAST24_MIN (-8388608L)
#define INT_LEAST24_MAX (8388607L)
#endif
#define int_least24_t int_least24_t
#endif

#ifndef uint_least24_t
#ifdef __CCI__
typedef unsigned long int uint_least24_t;
#define UINT_LEAST24_MAX (4294967295UL)
#else
typedef unsigned short long int uint_least24_t;
#define UINT_LEAST24_MAX (16777215UL)
#endif
#define uint_least24_t uint_least24_t
#endif

#ifndef int_fast24_t
#ifdef __CCI__
typedef signed long int int_fast24_t;
#define INT_FAST24_MIN (-2147483648L)
#define INT_FAST24_MAX (2147483647L)
#else
typedef signed short long int int_fast24_t;
#define INT_FAST24_MIN (-8388608L)
#define INT_FAST24_MAX (8388607L)
#endif
#define int_fast24_t int_fast24_t
#endif

#ifndef uint_fast24_t
#ifdef __CCI__
typedef unsigned long int uint_fast24_t;
#define UINT_FAST24_MAX (4294967295UL)
#else
typedef unsigned short long int uint_fast24_t;
#define UINT_FAST24_MAX (16777215UL)
#endif
#define uint_fast24_t uint_fast24_t
#endif

#endif // __XC8_VERSION >= 1420
#endif // __XC8
