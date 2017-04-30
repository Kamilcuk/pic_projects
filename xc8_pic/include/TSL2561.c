/*
 * tls2561.c
 *
 *  Created on: 23.03.2017
 *      Author: Kamil Cukrowski
 *
 *      Modified the file for speed and to be able to work with PIC device
 *      file downloaded from: https://github.com/adafruit/TSL2561-Arduino-Library/blob/master/TSL2561.cpp
 */

#include <stdio.h>

/**************************************************************************/
/*!
    @file     tsl2561.c
    @author   K. Townsend (microBuilder.eu / adafruit.com)
    @section LICENSE
    Software License Agreement (BSD License)
    Copyright (c) 2010, microBuilder SARL, Adafruit Industries
    All rights reserved.
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**************************************************************************/

#include "TSL2561.h"
#include <system.h> // _XTAL_FREQ for __delay_ms
#include <xc.h> // __delay_ms
#include <GenericTypeDefs.h> // UINT16_BITS
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cdefs.h> // __XSTRING
#include <stdio.h>
#define delay(x) __delay_ms(x) // __delay_ms defined in xc.h

static int8_t _addr;
static tsl2561IntegrationTime_t _integration;
static tsl2561Gain_t _gain;

//#define TSL2561_DBG( printf_param ) do { printf("TSL2561:"__XSTRING(__LINE__)":"); printf printf_param ; printf("\n"); }while(0)
#define TSL2561_DBG( printf_param )

#ifndef TSL2561_CUSTOM_I2C

#include <i2c.h>

static void TSL2561_wire_begin() {
	CloseI2C();
	OpenI2C(MASTER, SLEW_OFF);
#define CALC_SSPADD(speed) ( ( _XTAL_FREQ / ( speed * 4 ) ) - 1 )
	SSPADD = 15; // CALC_SSPADD(4000);
#undef CALC_SSPADD
	IdleI2C();
}

uint16_t TSL2561_read16(uint8_t reg)
{
	// Figure 17. SMBus Block Read or I2C Read (Combined Format) Protocols
	UINT16_BITS data;
	// S - Start Condition
	StartI2C();
	IdleI2C();
	// Slave Address Wr
	WriteI2C((_addr<<1)|0x00);
	IdleI2C();
	// command code
	WriteI2C(reg);
	IdleI2C();
	// Sr - Repeated Start Condition
	RestartI2C();
	// Slave Address Rd
	WriteI2C((_addr<<1)|0x01);
	IdleI2C();
	// Data Byte 1
	data.byte.LB = ReadI2C();
	IdleI2C();
	// A - Acknowledge
	AckI2C();
	// Data Byte 2
	data.byte.HB = ReadI2C();
	IdleI2C();
	// A - Acknowledge - send NACK - this is the last byte
	NotAckI2C();
	// stop bit
	StopI2C();
	return data.Val;
}

uint8_t TSL2561_read8(uint8_t reg)
{
	uint8_t data;
	// S - Start Condition
	StartI2C();
	IdleI2C();
	// Slave Address Wr
	WriteI2C((_addr<<1)|0x00);
	IdleI2C();
	// command code
	WriteI2C(reg);
	IdleI2C();
	// S - Start Condition
	StartI2C();
	// Slave Address Rd
	WriteI2C((_addr<<1)|0x01);
	IdleI2C();
	// Data Byte
	data = ReadI2C();
	IdleI2C();
	// A - Acknowledge - send NACK - this is the last byte
	NotAckI2C();
	// stop bit
	StopI2C();
	return data;
}

void TSL2561_write8(uint8_t reg, uint8_t value)
{
	// S - Start Condition
	StartI2C();
	IdleI2C();
	// Slave Address Wr
	WriteI2C((_addr<<1)|0x00);
	IdleI2C();
	// Command Code
	WriteI2C(reg);
	IdleI2C();
	// Data Byte
	WriteI2C(value);
	IdleI2C();
	// P - Stop Condition
	StopI2C();
}

#else
#error TODO: define functions : TSL2561_write_begin() TSL2561_write8() TSL2561_read8() TSL2561_read16()
#endif


void TSL2561_init(uint8_t addr) {
	_addr = addr;
	_integration = TSL2561_INTEGRATIONTIME_402MS;
	_gain = TSL2561_GAIN_16X;

	// we cant do wire initialization till later, because we havent loaded Wire yet
}

bool TSL2561_begin(void)
{
	unsigned char x;

	TSL2561_wire_begin();

	// Initialise I2C
	x = TSL2561_read8(TSL2561_REGISTER_ID);

	if ( !(x&0x0a) ) {
		TSL2561_DBG(("TSL2561 not found, x=%02x", x));
		return false;
	}

	TSL2561_enable();

	// Set default integration time and gain
	TSL2561_setTiming(_integration);
	TSL2561_setGain(_gain);
	// Note: by default, the device is in power down mode on bootup
	TSL2561_disable();

	return true;
}

void TSL2561_enable(void)
{
	// Enable the device by setting the control bit to 0x03
	TSL2561_write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWERON);
}

void TSL2561_disable(void)
{
	// Disable the device by setting the control bit to 0x03
	TSL2561_write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWEROFF);
}


void TSL2561_setGain(tsl2561Gain_t gain)
{
	TSL2561_enable();
	_gain = gain;
	TSL2561_write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, _integration | _gain);
	TSL2561_disable();
}

void TSL2561_setTiming(tsl2561IntegrationTime_t integration)
{
	TSL2561_enable();
	_integration = integration;
	TSL2561_write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, _integration | _gain);
	TSL2561_disable();
}

uint32_t TSL2561_calculateLux(uint16_t ch0, uint16_t ch1)
{
	unsigned long chScale;
	unsigned long channel1;
	unsigned long channel0;

	switch (_integration)
	{
	case TSL2561_INTEGRATIONTIME_13MS:
		chScale = TSL2561_LUX_CHSCALE_TINT0;
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		chScale = TSL2561_LUX_CHSCALE_TINT1;
		break;
	default: // No scaling ... integration time = 402ms
		chScale = (1 << TSL2561_LUX_CHSCALE);
		break;
	}

	// Scale for gain (1x or 16x)
	if (!_gain) chScale = chScale << 4;

	// scale the channel values
	channel0 = (ch0 * chScale) >> TSL2561_LUX_CHSCALE;
	channel1 = (ch1 * chScale) >> TSL2561_LUX_CHSCALE;

	// find the ratio of the channel values (Channel1/Channel0)
	unsigned long ratio1 = 0;
	if (channel0 != 0) ratio1 = (channel1 << (TSL2561_LUX_RATIOSCALE+1)) / channel0;

	unsigned int b, m;

	{
		// round the ratio value
		unsigned long ratio = (ratio1 + 1) >> 1;

#ifdef TSL2561_PACKAGE_CS
		if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1C))
		{b=TSL2561_LUX_B1C; m=TSL2561_LUX_M1C;}
		else if (ratio <= TSL2561_LUX_K2C)
		{b=TSL2561_LUX_B2C; m=TSL2561_LUX_M2C;}
		else if (ratio <= TSL2561_LUX_K3C)
		{b=TSL2561_LUX_B3C; m=TSL2561_LUX_M3C;}
		else if (ratio <= TSL2561_LUX_K4C)
		{b=TSL2561_LUX_B4C; m=TSL2561_LUX_M4C;}
		else if (ratio <= TSL2561_LUX_K5C)
		{b=TSL2561_LUX_B5C; m=TSL2561_LUX_M5C;}
		else if (ratio <= TSL2561_LUX_K6C)
		{b=TSL2561_LUX_B6C; m=TSL2561_LUX_M6C;}
		else if (ratio <= TSL2561_LUX_K7C)
		{b=TSL2561_LUX_B7C; m=TSL2561_LUX_M7C;}
		else if (ratio > TSL2561_LUX_K8C)
		{b=TSL2561_LUX_B8C; m=TSL2561_LUX_M8C;}
#else
		if (/*(ratio >= 0) && */(ratio <= TSL2561_LUX_K1T))
		{b=TSL2561_LUX_B1T; m=TSL2561_LUX_M1T;}
		else if (ratio <= TSL2561_LUX_K2T)
		{b=TSL2561_LUX_B2T; m=TSL2561_LUX_M2T;}
		else if (ratio <= TSL2561_LUX_K3T)
		{b=TSL2561_LUX_B3T; m=TSL2561_LUX_M3T;}
		else if (ratio <= TSL2561_LUX_K4T)
		{b=TSL2561_LUX_B4T; m=TSL2561_LUX_M4T;}
		else if (ratio <= TSL2561_LUX_K5T)
		{b=TSL2561_LUX_B5T; m=TSL2561_LUX_M5T;}
		else if (ratio <= TSL2561_LUX_K6T)
		{b=TSL2561_LUX_B6T; m=TSL2561_LUX_M6T;}
		else if (ratio <= TSL2561_LUX_K7T)
		{b=TSL2561_LUX_B7T; m=TSL2561_LUX_M7T;}
		else if (ratio > TSL2561_LUX_K8T)
		{b=TSL2561_LUX_B8T; m=TSL2561_LUX_M8T;}
#endif
	}

	unsigned long temp;
	{
		// do not allow negative lux value
		unsigned long channel0b = channel0 * b;
		unsigned long channel1m = channel1 * m;
		temp = channel0b > channel1m ? channel0b-channel1m : channel1m-channel0b;
	}

	// round lsb (2^(LUX_SCALE-1))
	temp += (1 << (TSL2561_LUX_LUXSCALE-1));

	// strip off fractional portion
	uint32_t lux = temp >> TSL2561_LUX_LUXSCALE;

	// Signal I2C had no errors
	return lux;
}

uint32_t TSL2561_getFullLuminosity (void)
{
	// Enable the device by setting the control bit to 0x03
	TSL2561_enable();

	// Wait x ms for ADC to complete
	switch (_integration)
	{
	case TSL2561_INTEGRATIONTIME_13MS:
		delay(14);
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		delay(102);
		break;
	default:
		delay(403);
		break;
	}

	UINT32_VAL x;
	x.word.LW = TSL2561_read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW);
	TSL2561_DBG(("LW=%x",  x.word.LW));
	x.word.HW = TSL2561_read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW);
	TSL2561_DBG(("HW=%x",  x.word.HW));

	TSL2561_disable();

	return x.Val;
}
uint16_t TSL2561_getLuminosity (uint8_t channel) {

	UINT32_VAL x;
	x.Val = TSL2561_getFullLuminosity();

	if (channel == 0) {
		// Reads two byte value from channel 0 (visible + infrared)
		return x.word.LW;
	} else if (channel == 1) {
		// Reads two byte value from channel 1 (infrared)
		return x.word.HW;
	} else if (channel == 2) {
		// Reads all and subtracts out just the visible!
		return x.word.LW - x.word.HW;
	}

	// unknown channel!
	return 0;
}
