/*
 * cmdline.h
 *
 *  Created on: 31.03.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */

#ifndef CMDLINE_H_
#define CMDLINE_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * Reprints current line when backspace key is pressed.
 */
#ifndef CMDLINE_BACKSPACE_ENABLED
#define CMDLINE_BACKSPACE_ENABLED 1
#endif

/**
 * Buff size should be longer then the longest command you expect.
 */
#ifndef CMDLINE_BUFF_SIZE
#define CMDLINE_BUFF_SIZE 20
#endif

/**
 * State struct
 */
struct cmdline_s {
	char buff[ CMDLINE_BUFF_SIZE ];
#if CMDLINE_BUFF_SIZE < 256
	uint8_t buffpos;
#else
#error
#endif
};

/**
 * state variable
 */
extern struct cmdline_s cmdline;

/**
 * Flag to indicate if cmdlineGetCmd has parsed a whole command
 */
extern bool cmdlineGetCmd_busy;

/**
 * User callback function.
 * cmdline.buff is filled with command line string.
 * cmdline.buffpos means cmdline.buff position.
 */
void cmdlineService_callback(void);

/**
 * Services my (Kamil Cukrowski) standard requests
 * May be called by cmdlineService_callback()
 */
void cmdlineService_standard(void);

/**
 * Read until '\n' is received or until cmdline.buff is full
 * All non-printable (except '\n') characters are omitted.
 * During read, buffer cmdline.buff is filled and cmdline.buffpos is set to number chars read.
 * Upper layers are notified of oparation end via cmdlineGetCmd_busy flag.
 */
void cmdlineGetCmd_nonblock(void);

/**
 * Service command line in a blocking fashion.
 */
#define cmdlineService() do { \
	do { \
		cmdlineGetCmd_nonblock(); \
	} while( cmdlineGetCmd_busy ); \
	cmdlineService_callback(); \
} while(0)

/**
 * Service command line in a non-blocking fashion.
 */
#define cmdlineService_nonblock() do{ \
	cmdlineGetCmd_nonblock(); \
	if ( !cmdlineGetCmd_busy ) { \
		cmdlineService_callback(); \
	} \
} while(0)

#endif /* CMDLINE_H_ */
