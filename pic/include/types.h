/*
 * types.h
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
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
