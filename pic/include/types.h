/*
 * types.h
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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
