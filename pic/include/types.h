/*
 * types.h
 * 
 * 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 * 
 * 
 */
#ifndef __TYPES_H__
#define __TYPES_H__

typedef signed char __s8;
typedef signed short __s16;
typedef signed long __s32;

typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned long __u32;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef unsigned char uchar;
typedef unsigned int uint;


/* use __once for all functions that are called only once
 * they can be fully inlined with no consequences */
#define  __once static inline 

#endif // __TYPES_H__
