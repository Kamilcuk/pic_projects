/*
 * rrbuffer.c - ring buffer implementation with multiple buffer positions
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski 
 * 
 * 
 * 
 */
#include "types.h"
#include "rrbuffer_internal.h"
#include "rrbuffer.h"
#include "interrupt.h"

/* note: any buffer in pic18f2550 memory can be max 0xFF long
 * cause one DATABANK is 0xFF long */

#define BUFFER_COUNT (( sizeof((rrbuffer))/sizeof((*rrbuffer)) )) 

struct rrbuffer_list {
	unsigned char num;
	unsigned char pos;
};

static struct rrbuffer_list buffer_head, buffer_tail;

struct rrbuffer_info_struct rrbuffer_info;

void rrbuffer_init()
{
	unsigned char i;
	
	/* calculate how many bytes of free buffer do we have */
	rrbuffer_info.free = 0;
	for(i=0; i<sizeof(rrbuffer); i++) {
		rrbuffer_info.free += rrbuffer[i].size;
	}
	rrbuffer_info.used=0;
	buffer_head.pos = 0;
	buffer_head.num = 0;
	buffer_tail.pos = 0;
	buffer_tail.num = 0;
}

void rrbuffer_put(unsigned char __near *p, unsigned char cnt)
{
	unsigned char i;
	unsigned char num;
	unsigned char pos;
	
	if (rrbuffer_info.free < cnt)
		cnt = rrbuffer_info.free;
	rrbuffer_info.free -= cnt;
	rrbuffer_info.used += cnt;
	
	num = buffer_head.num;
	pos = buffer_head.pos;
	
	for (i=0; i<cnt ; i++) {
		rrbuffer[num].buff[pos] = *p;
		p++;
		pos++;
		if (pos >= rrbuffer[num].size) {
			pos=0;
			num++;
			if (num >= BUFFER_COUNT)
				num=0;
		}
	}
	
	buffer_head.num = num;
	buffer_head.pos = pos;
	
	//return cnt;
}

void rrbuffer_get(unsigned char __near *p, unsigned char cnt)
{
	unsigned char i;
	unsigned char num;
	unsigned char pos;
	
	if (rrbuffer_info.used < cnt)
		cnt = rrbuffer_info.used;
	rrbuffer_info.free += cnt;
	rrbuffer_info.used -= cnt;
	
	num = buffer_tail.num;
	pos = buffer_tail.pos;
	
	for (i=0; i<cnt ; i++) {
		*p = rrbuffer[num].buff[pos];
		p++;
		pos++;
		if (pos >= rrbuffer[num].size) {
			pos=0;
			num++;
			if (num >= BUFFER_COUNT)
				num=0;
		}
	}
	
	buffer_tail.num = num;
	buffer_tail.pos = pos;
	
	//return cnt;
}
