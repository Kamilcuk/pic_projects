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
