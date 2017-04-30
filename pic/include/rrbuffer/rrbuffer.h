/*
 * rrbuffer.h
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
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
