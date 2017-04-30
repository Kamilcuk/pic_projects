/*
 * seconddelay.h
 * 
 * Under BEER-WARE license 2014 Kamil Cukrowski <kamil@dyzio.pl>
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
