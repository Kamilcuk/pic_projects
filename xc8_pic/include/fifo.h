/*
 * fifo.h
 *
 *  Created on: 19 lip 2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>
#include <stdbool.h>

struct fifo_s {
	bool full;
	uint8_t begin;
	uint8_t end;
	uint8_t size;
	uint8_t *buff;
};

#define FIFO_INIT(BUFF, SIZE)  { false, 0, 0, SIZE, BUFF, }

#define FIFO_INIT_STATIC(BUFF) FIFO_INIT(BUFF, sizeof(BUFF)/sizeof(*BUFF))

#define FifoInit(f, BUFF, SIZE) do{ (f)->full = (f)->begin = (f)->end = 0; (f)->size = SIZE; (f)->buff = BUFF; }while(0)

#define FifoInitStatic(f, BUFF) FifoInit(f, BUFF, sizeof(BUFF)/sizeof(*BUFF))

#define FifoNext(f, index)  ( ((index)+1) % (f)->size )

void FifoPut(struct fifo_s *f, uint8_t elem);

uint8_t FifoGet(struct fifo_s *f);

#define FifoFlush(f) do{ (f)->begin = (f)->end = 0; }while(0)

#define FifoIsEmpty(f) ( !(f)->full && (f)->begin == (f)->end )

#define FifoIsFull(f)  ( (f)->full )

#define FifoUsed(f)    ( (f)->end   + ( (f)->end < (f)->begin || (f)->full ? (f)->size : 0 ) - (f)->begin )

#define FifoFree(f)    ( (f)->begin + ( (f)->end < (f)->begin || (f)->full ? 0 : (f)->size ) - (f)->end   )

#define FifoSize(f)    ( (f)->size )

/* fifomul ------------------------------------------------------------------------- */

struct fifomul_block_s {
	uint8_t size;
	uint8_t *buff;
};

#define FIFOMUL_BLOCK_INIT(BUFF, SIZE)  { SIZE, BUFF, }

#define FIFOMUL_BLOCK_INIT_STATIC(BUFF) FIFOMUL_BLOCK_INIT(BUFF, sizeof(BUFF)/sizeof(*BUFF))


struct fifomul_pos_s {
	uint8_t block;
	uint8_t pos;
};

#define FIFOMUL_POS_INIT()              { 0, 0, }

#define FIFOMUL_POS_EQUAL(POS1, POS2)   ( (POS1)->block == (POS2)->block && (POS1)->pos == (POS2)->pos )


struct fifomul_s {
	bool full;
	struct fifomul_pos_s begin;
	struct fifomul_pos_s end;
	uint8_t blocks_size;
	struct fifomul_block_s *blocks;
};

#define FIFOMUL_INIT(BLOCKS, SIZE)      { false,  FIFOMUL_POS_INIT(), FIFOMUL_POS_INIT(), SIZE, BLOCKS, }

#define FIFOMUL_INIT_STATIC(BLOCKS)     FIFOMUL_INIT(BLOCKS, sizeof(BLOCKS)/sizeof(*BLOCKS))


#define FIFOMUL_GET_AT_POS(f, POS)      ( (f)->blocks[(POS)->block].buff[(POS)->pos] )

#define FIFOMUL_PUT_AT_POS(f, POS, VAL) ( (f)->blocks[(POS)->block].buff[(POS)->pos] = (VAL) )


struct fifomul_pos_s FifoexNext(struct fifomul_s *f, struct fifomul_pos_s pos);

void FifomulPut(struct fifomul_s *f, uint8_t elem);

uint8_t FifomulGet(struct fifomul_s *f);

#define FifomulFlush(f)     do{ (f)->begin.pos = (f)->begin.block = (f)->end.pos = (f)->end.block = (f)->full = 0; }while(0)

#define FifomulIsEmpty(f)   ( !(f)->full && FIFOMUL_POS_EQUAL( &((f)->begin), &((f)->end) ) )

#define FifomulIsFull(f)    ( (f)->full )

uint16_t FifomulUsed(struct fifomul_s *f);

uint16_t FifomulFree(struct fifomul_s *f);

uint16_t FifomulSize(struct fifomul_s *f);

/* fifo test --------------------------------------------------------------------------------- */

void FifoTest();

#endif /* FIFO_H_ */
