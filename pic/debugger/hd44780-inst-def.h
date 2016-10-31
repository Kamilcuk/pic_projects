/*
 * hd44780-inst-def.h
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
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
 
#ifndef _hd44780_inst_def_
#define _hd44780_inst_def_

/* hd44780 instructions definitions */
#define HD44780_CLRDISP 		0b00000001
#define HD44780_RETURNHOME 		0b00000010
/* EMS - Entry Mode Set */
#define HD44780_EMS_INC 		0b00000110
#define HD44780_EMS_DEC 		0b00000100
#define HD44780_EMS_SHIFT 		0b00000101
#define HD44780_EMS_NOSHIFT 		0b00000100
/* DOOC - Display On/Off Control */
#define HD44780_DOOC_DISPLAYON 		0b00001100
#define HD44780_DOOC_DISPLAYOFF		0b00001000
#define HD44780_DOOC_CURSORON		0b00001010
#define HD44780_DOOC_CURSOROFF		0b00001000
#define HD44780_DOOC_CURSORBLINK	0b00001001
#define HD44780_DOOC_CURSORNOBLINK	0b00001000
/* CDS - Cursor and Display Shift */
#define HD44780_CDS_DISPSHIFT		0b00011000
#define HD44780_CDS_CURSORSHIFT		0b00010000
#define HD44780_CDS_SHIFTRIGHT		0b00010100
#define HD44780_CDS_SHIFTLEFT		0b00010000
/* FS - Function Set */
#define HD44780_FS_DATAWIDTH8BIT 	0b00110000
#define HD44780_FS_DATAWIDTH4BIT	0b00100000
#define HD44780_FS_TWOLINES		0b00101000
#define HD44780_FS_ONELINE		0b00100000
#define HD44780_FS_5x10DOTS		0b00100100
#define HD44780_FS_5x8DOTS		0b00100000
/* cgram ddram adress */
#define HD44780_CGRAM_ADDRESS 		0b01000000
#define HD44780_DDRAM_ADDRESS 		0b10000000

#endif /* _hd44780_inst_def_ */
