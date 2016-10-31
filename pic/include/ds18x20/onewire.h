/* 
 * modifications to make it work with PIC and sdcc compiler by Kamil Cukrowski <kamil@dyzio.pl> 
 * */
#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "onewire-config.h"
#include <stdint.h>

/*****************************************************************************************/

#ifndef OW_RECOVERY_TIME
// Recovery time (T_Rec) minimum 1usec - increase for long lines 
// 5 usecs is a value give in some Maxim AppNotes
// 30u secs seem to be reliable for longer lines
//#define OW_RECOVERY_TIME        5  /* usec */
//#define OW_RECOVERY_TIME      300 /* usec */
#define OW_RECOVERY_TIME         10 /* usec */
#endif

#ifndef OW_USE_INTERNAL_PULLUP
// Use AVR's internal pull-up resistor instead of external 4,7k resistor.
// Based on information from Sascha Schade. Experimental but worked in tests
// with one DS18B20 and one DS18S20 on a rather short bus (60cm), where both 
// sensores have been parasite-powered.
#define OW_USE_INTERNAL_PULLUP     0  /* 0=external, 1=internal */
#endif

#ifndef ow_parasite_enable
	#define ow_parasite_enable() do{ OW_OUT_HIGH(); OW_DIR_OUT(); } while(0)
#endif
#ifndef ow_parasite_disable
	#if OW_USE_INTERNAL_PULLUP
		#define ow_parasite_disable() OW_DIR_IN();
	#else
		#define ow_parasite_disable() do{ OW_DIR_IN(); OW_OUT_LOW(); } while(0)
	#endif
#endif

/* Define OW_ONE_BUS if only one 1-Wire-Bus is used
   in the application -> shorter code.
   If not defined make sure to call ow_set_bus() before using 
   a bus. Runtime bus-select increases code size by around 300 
   bytes so use OW_ONE_BUS if possible */
// #define OW_ONE_BUS

#ifdef OW_ONE_BUS

/* define those ! */
//#define OW_GET_IN()   ( OW_IN & (1<<OW_PIN))
//#define OW_OUT_LOW()  ( OW_OUT &= (~(1 << OW_PIN)) )
//#define OW_OUT_HIGH() ( OW_OUT |= (1 << OW_PIN) )
//#define OW_DIR_IN()   ( OW_DDR &= (~(1 << OW_PIN )) )
//#define OW_DIR_OUT()  ( OW_DDR |= (1 << OW_PIN) )


#if !defined(OW_GET_IN) || !defined(OW_OUT_LOW) || !defined(OW_OUT_HIGH) || !defined(OW_DIR_IN) || !defined(OW_DIR_OUT)
# error OW_things not defined
#endif

#define OW_CONF_DELAYOFFSET 0

#else 
#if ( F_CPU < 1843200 )
#warning | Experimental multi-bus-mode is not tested for 
#warning | frequencies below 1,84MHz. Use OW_ONE_WIRE or
#warning | faster clock-source (i.e. internal 2MHz R/C-Osc.).
#endif
#define OW_CONF_CYCLESPERACCESS 13
#define OW_CONF_DELAYOFFSET ( (uint16_t)( ((OW_CONF_CYCLESPERACCESS) * 1000000L) / F_CPU ) )
#endif

/**********************************************************************************/


#define OW_MATCH_ROM    0x55
#define OW_SKIP_ROM     0xCC
#define OW_SEARCH_ROM   0xF0

#define OW_SEARCH_FIRST 0xFF        // start new search
#define OW_PRESENCE_ERR 0xFF
#define OW_DATA_ERR     0xFE
#define OW_LAST_DEVICE  0x00        // last device found

// rom-code size including CRC
#define OW_ROMCODE_SIZE 8

#define ow_input_pin_state() OW_GET_IN()

extern uint8_t ow_reset(void);

extern uint8_t ow_bit_io( uint8_t b );
extern uint8_t ow_byte_wr( uint8_t b );
extern uint8_t ow_byte_rd( void );

extern uint8_t ow_rom_search( uint8_t diff, __near uint8_t *id );

#define OW_COMMAND_INTERN_NO_PARASITE 0
#define OW_COMMAND_INTERN_PARASITE 1
extern void ow_command_intern( uint8_t command, __near uint8_t *id, uint8_t with_parasite_enable );
#define ow_command(command, id ) ow_command_intern(command, id, OW_COMMAND_INTERN_NO_PARASITE)
#define ow_command_with_parasite_enable(command, id ) ow_command_intern(command, id, OW_COMMAND_INTERN_PARASITE)

#ifndef OW_ONE_BUS
extern void ow_set_bus(
	__near volatile uint8_t* in,
	__near volatile uint8_t* out,
	__near volatile uint8_t* ddr,
	uint8_t pin );
#endif

#ifdef __cplusplus
}
#endif

#endif
