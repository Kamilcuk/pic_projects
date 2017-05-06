/*
 * rrbuffer.h
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
#ifndef __RRBUFFER_H_
#define __RRBUFFER_H_

struct rrbuffer_info_struct {
	unsigned short free;
	unsigned short used;
};

extern struct rrbuffer_info_struct rrbuffer_info;

#define rrbuffer_get_free_place() (( rrbuffer_info.free ))
#define rrbuffer_get_used_place() (( rrbuffer_info.used ))
#define rrbuffer_get_size() (( rrbuffer_info.used+rrbuffer_info.free ))

extern void rrbuffer_init();
extern void rrbuffer_put(unsigned char __near *p, unsigned char cnt);
extern void rrbuffer_get(unsigned char __near *p, unsigned char cnt);

#endif //  __RRBUFFER_H_
