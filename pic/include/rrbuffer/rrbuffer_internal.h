/*
 * rrbuffer.h
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 */
#ifndef __RRBUFFER_H_
#define __RRBUFFER_H_

#define DEF_RRBUFFER() const struct rrbuffer_struct __code rrbuffer[] = {
	
#define DEF_BUFF(x) { .size = sizeof((x)), .buff = (x) },

#define END_DEF_RRBUFFER() };

struct rrbuffer_struct {
	const unsigned char size; // buffer can't be bigger then 0xFF cause one DATABANK is 0xFF bits long ...
	unsigned char __near * const buff;
};

struct rrbuffer_info_struct {
	unsigned short free;
	unsigned short used;
};

#endif //  __RRBUFFER_H_
