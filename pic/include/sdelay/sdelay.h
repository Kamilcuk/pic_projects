/*
 * seconddelay.h
 * 
 * 2014 Kamil Cukrowski <kamil@dyzio.pl>
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 * 
 * 
 * 
 */
#ifndef SECONDDELAY_H_
#define SECONDDELAY_H_

void sdelay_us(unsigned int __us);
void sdelay_ms(unsigned int __ms);

/**
 * Agument cant be 0 
 */
void _sdelay_us(unsigned int __us);
/**
 * Agument cant be 0 
 */
void _sdelay_ms(unsigned int __ms);

#endif // SECONDDELAY_H_
