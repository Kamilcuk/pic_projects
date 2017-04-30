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
 * State struct.
 */
extern struct cmdline_s cmdline;

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
 * Service command line in a blocking fashion.
 */
void cmdlineService(void);

/**
 * Service command line in a non-blocking fashion.
 */
void cmdlineService_nonblock(void);

#endif /* CMDLINE_H_ */
