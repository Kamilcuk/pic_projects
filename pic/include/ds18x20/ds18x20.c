/* 
 * modifications to make it work with PIC and sdcc compiler by Kamil Cukrowski <kamil@dyzio.pl> 
 * */
/*********************************************************************************
Title:    DS18X20-Functions via One-Wire-Bus
Author:   Martin Thomas <eversmith@heizung-thomas.de>   
          http://www.siwawi.arubi.uni-kl.de/avr-projects
          http://siwawi.bauing.uni-kl.de/avr_projects/tempsensor/
Software: avr-gcc 4.3.3 / avr-libc 1.6.7 (WinAVR 3/2010) 
Hardware: any AVR - tested with ATmega16/ATmega32/ATmega324P and 3 DS18B20

Partly based on code from Peter Dannegger and others.

changelog:
20041124 - Extended measurements for DS18(S)20 contributed by Carsten Foss (CFO)
200502xx - function DS18X20_read_meas_single
20050310 - DS18x20 EEPROM functions (can be disabled to save flash-memory)
           (DS18X20_EEPROMSUPPORT in ds18x20.h)
20100625 - removed inner returns, added static function for read scratchpad
         . replaced full-celcius and fractbit method with decicelsius
           and maxres (degreeCelsius*10e-4) functions, renamed eeprom-functions,
           delay in recall_e2 replaced by timeout-handling
20100714 - ow_command_skip_last_recovery used for parasite-powerd devices so the
           strong pull-up can be enabled in time even with longer OW recovery times
20110209 - fix in DS18X20_format_from_maxres() by Marian Kulesza
**********************************************************************************/

#include <stdlib.h>
#include <stdint.h>

#include "ds18x20.h"
#include "onewire.h"
#include "crc8.h"

#if DS18X20_EEPROMSUPPORT
// for 10ms delay in copy scratchpad
#include <sdelay/sdelay.h>
#endif /* DS18X20_EEPROMSUPPORT */

#define uart_puts_P_verbose(s__)

/* search all sensors on 1-Wire-Bus
 * sensors - table of maxsensors rows and OW_ROMCODE_SIZE cols - gets written with all the ids 
 * maxsensrs - number of rows in table senssrs - maximum number of sensors
 * return value - number of sensors found
 * example:
 * 
#define MAXSENSORS 15
uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];
ret = DS18X20_search_sensors(gSensorIDs, MAXSENSORS);
* * whatever *
 * */
uint8_t DS18X20_search_sensors(__near uint8_t *sensors, const uint8_t maxsensors)
{
	__near uint8_t id[OW_ROMCODE_SIZE];
	uint8_t diff, nSensors;
	uint8_t i;
	
	ow_reset();

	nSensors = 0;
	diff = OW_SEARCH_FIRST;
	
	while ( diff != OW_LAST_DEVICE && nSensors < maxsensors ) {
		
		DS18X20_find_sensor( &diff, &id[0] );
		
		if( diff == OW_PRESENCE_ERR ) {
			break;
		}
		
		if( diff == OW_DATA_ERR ) {
			break;
		}
		
		for ( i=0; i < OW_ROMCODE_SIZE; i++ )
			sensors[nSensors*OW_ROMCODE_SIZE+i] = id[i];
		
		nSensors++;
	}
	
	return nSensors;
}

/* find DS18X20 Sensors on 1-Wire-Bus
   input/ouput: diff is the result of the last rom-search
                *diff = OW_SEARCH_FIRST for first call
   output: id is the rom-code of the sensor found */
uint8_t DS18X20_find_sensor(__near uint8_t *diff, __near uint8_t id[] )
{	
	for(;;) {
		*diff = ow_rom_search( *diff, &id[0] );
		if ( *diff == OW_PRESENCE_ERR || *diff == OW_DATA_ERR ||
		     *diff == OW_LAST_DEVICE ) { 
			return DS18X20_ERROR;
		} else {
			if ( id[0] == DS18B20_FAMILY_CODE || id[0] == DS18S20_FAMILY_CODE ||
			     id[0] == DS1822_FAMILY_CODE ) { 
				break;
			}
		}
	}
	return DS18X20_OK;
}

/* get power status of DS18x20 
   input:   id = rom_code 
   returns: DS18X20_POWER_EXTERN or DS18X20_POWER_PARASITE */
uint8_t DS18X20_get_power_status(__near uint8_t *id)
{
	uint8_t pstat;

	ow_reset();
	ow_command( DS18X20_READ_POWER_SUPPLY, id );
	pstat = ow_bit_io( 1 );
	ow_reset();
	return ( pstat ) ? DS18X20_POWER_EXTERN : DS18X20_POWER_PARASITE;
}

/* start measurement (CONVERT_T) for all sensors if input id==NULL 
   or for single sensor where id is the rom-code */
uint8_t DS18X20_start_meas(uint8_t with_power_extern, __near uint8_t id[])
{
	ow_reset();
	
	if( !ow_input_pin_state() ) { // only send if bus is "idle" = high
		uart_puts_P_verbose( "DS18X20_start_meas: Short Circuit!\r" );
		return DS18X20_START_FAIL;
	}
	
	if ( with_power_extern == DS18X20_POWER_EXTERN ) {
		ow_command( DS18X20_CONVERT_T, id );
	} else {
		ow_command_with_parasite_enable( DS18X20_CONVERT_T, id );
	}
	
	return DS18X20_OK;
}

uint8_t DS18X20_read_scratchpad(__near uint8_t id[],__near uint8_t sp[], uint8_t n )
{
	uint8_t i;
	
	ow_reset();

	if( !ow_input_pin_state() ) { // only send if bus is "idle" = high
		uart_puts_P_verbose( "DS18X20_read_scratchpad: Short Circuit!\r" );
		return DS18X20_ERROR;
	}
	
	ow_command( DS18X20_READ_SCRATCHPAD, id );
	for ( i = 0; i < n; ++i ) {
		sp[i] = ow_byte_rd();
	}
	if ( crc8( &sp[0], DS18X20_SP_SIZE ) ) {
		return DS18X20_ERROR_CRC;
	}
	return DS18X20_OK;
}

uint8_t DS18X20_write_scratchpad(__near uint8_t id[], uint8_t th, uint8_t tl, uint8_t conf)
{
	ow_reset();
	
	if( !ow_input_pin_state() ) { // only send if bus is "idle" = high
		uart_puts_P_verbose( "DS18X20_write_scratchpad: Short Circuit!\r" );
		return DS18X20_ERROR;
	}
	
	ow_command( DS18X20_WRITE_SCRATCHPAD, id );
	ow_byte_wr( th );
	ow_byte_wr( tl );
	if ( id[0] == DS18B20_FAMILY_CODE || id[0] == DS1822_FAMILY_CODE ) {
		ow_byte_wr( conf ); // config only available on DS18B20 and DS1822
	}
	return DS18X20_OK;
}

#if DS18X20_DECICELSIUS

/* convert scratchpad data to physical value in unit decicelsius */
static int16_t DS18X20_raw_to_decicelsius(uint8_t familycode, __near uint8_t sp[] )
{
	uint16_t measure;
	uint8_t  negative;
	int16_t  decicelsius;
	uint16_t fract;

	measure = sp[0] | (sp[1] << 8);
	//measure = 0xFF5E; // test -10.125
	//measure = 0xFE6F; // test -25.0625

	if( familycode == DS18S20_FAMILY_CODE ) {   // 9 -> 12 bit if 18S20
		/* Extended measurements for DS18S20 contributed by Carsten Foss */
		measure &= (uint16_t)0xfffe;   // Discard LSB, needed for later extended precicion calc
		measure <<= 3;                 // Convert to 12-bit, now degrees are in 1/16 degrees units
		measure += (16 - sp[6]) - 4;   // Add the compensation and remember to subtract 0.25 degree (4/16)
	}

	// check for negative 
	if ( measure & 0x8000 )  {
		negative = 1;       // mark negative
		measure ^= 0xffff;  // convert to positive => (twos complement)++
		measure++;
	} else {
		negative = 0;
	}

	// clear undefined bits for DS18B20 != 12bit resolution
	if ( familycode == DS18B20_FAMILY_CODE || familycode == DS1822_FAMILY_CODE ) {
		switch( sp[DS18B20_CONF_REG] & DS18B20_RES_MASK ) {
		case DS18B20_9_BIT:
			measure &= ~(DS18B20_9_BIT_UNDF);
			break;
		case DS18B20_10_BIT:
			measure &= ~(DS18B20_10_BIT_UNDF);
			break;
		case DS18B20_11_BIT:
			measure &= ~(DS18B20_11_BIT_UNDF);
			break;
		default:
			// 12 bit - all bits valid
			break;
		}
	}

	decicelsius = (measure >> 4);
	decicelsius *= 10;

	// decicelsius += ((measure & 0x000F) * 640 + 512) / 1024;
	// 625/1000 = 640/1024
	fract = ( measure & 0x000F ) * 640;
	if ( !negative ) {
		fract += 512;
	}
	fract /= 1024;
	decicelsius += fract;

	if ( negative ) {
		decicelsius = -decicelsius;
	}

	if ( decicelsius < -550 || decicelsius > 1250 ) {
		return DS18X20_INVALID_DECICELSIUS;
	} else {
		return decicelsius;
	}
}

/* reads temperature (scratchpad) of sensor with rom-code id
   output: decicelsius 
   returns DS18X20_OK on success */
uint8_t DS18X20_read_decicelsius( __near uint8_t id[], __near int16_t *decicelsius )
{
	uint8_t sp[DS18X20_SP_SIZE];
	uint8_t ret;
	
	ow_reset();
	ret = DS18X20_read_scratchpad( id, sp, DS18X20_SP_SIZE );
	if ( ret == DS18X20_OK ) {
		*decicelsius = DS18X20_raw_to_decicelsius( id[0], sp );
	}
	return ret;
}

#endif /* DS18X20_DECICELSIUS */

#if DS18X20_MAX_RESOLUTION

static int32_t DS18X20_raw_to_maxres( uint8_t familycode, __near uint8_t sp[] )
{
	uint16_t measure;
	uint8_t  negative;
	int32_t  temperaturevalue;

	measure = sp[0] | (sp[1] << 8);
	//measure = 0xFF5E; // test -10.125
	//measure = 0xFE6F; // test -25.0625

	if( familycode == DS18S20_FAMILY_CODE ) {   // 9 -> 12 bit if 18S20
		/* Extended measurements for DS18S20 contributed by Carsten Foss */
		measure &= (uint16_t)0xfffe;   // Discard LSB, needed for later extended precicion calc
		measure <<= 3;                 // Convert to 12-bit, now degrees are in 1/16 degrees units
		measure += ( 16 - sp[6] ) - 4; // Add the compensation and remember to subtract 0.25 degree (4/16)
	}

	// check for negative 
	if ( measure & 0x8000 )  {
		negative = 1;       // mark negative
		measure ^= 0xffff;  // convert to positive => (twos complement)++
		measure++;
	}
	else {
		negative = 0;
	}

	// clear undefined bits for DS18B20 != 12bit resolution
	if ( familycode == DS18B20_FAMILY_CODE || familycode == DS1822_FAMILY_CODE ) {
		switch( sp[DS18B20_CONF_REG] & DS18B20_RES_MASK ) {
		case DS18B20_9_BIT:
			measure &= ~(DS18B20_9_BIT_UNDF);
			break;
		case DS18B20_10_BIT:
			measure &= ~(DS18B20_10_BIT_UNDF);
			break;
		case DS18B20_11_BIT:
			measure &= ~(DS18B20_11_BIT_UNDF);
			break;
		default:
			// 12 bit - all bits valid
			break;
		}
	}

	temperaturevalue  = (measure >> 4);
	temperaturevalue *= 10000;
	temperaturevalue +=( measure & 0x000F ) * DS18X20_FRACCONV;

	if ( negative ) {
		temperaturevalue = -temperaturevalue;
	}

	return temperaturevalue;
}

uint8_t DS18X20_read_maxres( __near  uint8_t id[], __near int32_t *temperaturevalue )
{
	uint8_t sp[DS18X20_SP_SIZE];
	
	ow_reset();
	if ( DS18X20_read_scratchpad(id, sp, DS18X20_SP_SIZE ) == DS18X20_OK ) {
		*temperaturevalue = DS18X20_raw_to_maxres( id[0], sp );
	}
	return DS18X20_OK;
}

#endif /* DS18X20_MAX_RESOLUTION */


#if DS18X20_EEPROMSUPPORT

uint8_t DS18X20_scratchpad_to_eeprom( uint8_t with_power_extern, 
	__near uint8_t id[] )
{
	ow_reset();
	
	if( !ow_input_pin_state() ) { // only send if bus is "idle" = high
		uart_puts_P_verbose( "DS18X20_copy_scratchpad: Short Circuit!\r" );
		return DS18X20_START_FAIL;
	}
	
	if ( with_power_extern != DS18X20_POWER_EXTERN ) {
		ow_command_with_parasite_enable( DS18X20_COPY_SCRATCHPAD, id );
		/* not longer needed: ow_parasite_enable(); */
	} else {
		ow_command( DS18X20_COPY_SCRATCHPAD, id );
	}
	_delay_ms(DS18X20_COPYSP_DELAY); // wait for 10 ms 
	if ( with_power_extern != DS18X20_POWER_EXTERN ) {
		ow_parasite_disable();
	}
	return DS18X20_OK;
}

uint8_t DS18X20_eeprom_to_scratchpad(__near uint8_t id[] )
{
	uint8_t retry_count=255;

	ow_reset();
	
	if( !ow_input_pin_state() ) { // only send if bus is "idle" = high
		uart_puts_P_verbose( "DS18X20_recall_E2: Short Circuit!\r" );
		return DS18X20_ERROR;
	}
	
	ow_command( DS18X20_RECALL_E2, id );
	while( retry_count-- && !( ow_bit_io( 1 ) ) ) { 
		;
	}
	if ( !retry_count ) {
		uart_puts_P_verbose( "DS18X20_recall_E2: timeout!\r" );
		return DS18X20_ERROR;
	}	
	return DS18X20_OK;
}

#endif /* DS18X20_EEPROMSUPPORT */

