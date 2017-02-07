/*
 * seconddelay.h
 * 
 * Copyright 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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
 * 
 */
#ifndef SECONDDELAY_H_
#define SECONDDELAY_H_

void delay_us(unsigned int __us);
void delay_ms(unsigned int __ms);

/**
 * Agument cant be 0 
 */
void _delay_us(unsigned int __us);
/**
 * Agument cant be 0 
 */
void _delay_ms(unsigned int __ms);

#endif // SECONDDELAY_H_
