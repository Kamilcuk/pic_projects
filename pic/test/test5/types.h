#ifndef __TYPES_H__
#define __TYPES_H__

// default definitions

typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;

/* Unsigned.  */
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;



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



//#define __inline static inline
//#define __once static inline 
#define __once
#define __inline


// little endian
//#define cpu_to_le16(x)  (uint16_t)((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))


#endif // __TYPES_H__
