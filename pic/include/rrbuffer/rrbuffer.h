/*
 * rrbuffer.h
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
