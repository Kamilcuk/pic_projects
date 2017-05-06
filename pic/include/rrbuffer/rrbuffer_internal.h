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
