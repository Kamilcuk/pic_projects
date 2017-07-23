/*
 * fifo.c
 *
 *  Created on: 19 lip 2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 * Kamil Cukrowski wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */
#include "fifo.h"

void FifoPut(struct fifo_s *f, uint8_t elem)
{
	f->end = FifoNext( f, f->end );
	if ( f->begin == f->end ) {
		f->full = true;
	}
	f->buff[f->end] = elem;
}

uint8_t FifoGet(struct fifo_s *f)
{
	const uint8_t next = FifoNext( f, f->begin );
	if ( f->begin == f->end ) {
		f->full = false;
	}
	f->begin = next;
	return f->buff[next];
}

/* fifomul ------------------------------------------------------------------ */

struct fifomul_pos_s FifoexNext(struct fifomul_s *f, struct fifomul_pos_s pos)
{
	++pos.pos;
	if ( pos.pos >= f->blocks[pos.block].size ) {
		pos.pos = 0;
		++pos.block;
		if ( pos.block >= f->blocks_size ) {
			pos.block = 0;
		}
	}
	return pos;
}

void FifomulPut(struct fifomul_s *f, uint8_t elem)
{
	const struct fifomul_pos_s pos = FifoexNext(f, f->end);
	f->end = pos;
	if ( FIFOMUL_POS_EQUAL(&(f->begin), &pos) ) {
		f->full = true;
	}
	f->blocks[pos.block].buff[pos.pos] = elem;
}

uint8_t FifomulGet(struct fifomul_s *f)
{
	const struct fifomul_pos_s pos = FifoexNext(f, f->begin);
	if ( FIFOMUL_POS_EQUAL(&pos, &(f->end)) ) {
		f->full = false;
	}
	f->begin = pos;
	return f->blocks[pos.block].buff[pos.pos];
}

uint16_t FifomulUsed(struct fifomul_s *f)
{
	uint16_t ret = 0;
	uint8_t i, start, stop;
	if ( f->full ) {
		return FifomulSize(f);
	}
	if ( f->end.block > f->begin.block ) {
		ret = f->blocks[f->begin.block].size - f->begin.pos
				+ f->end.pos;
		for(i =  f->begin.block + 1; i < f->end.block; ++i) {
			ret += f->blocks[i].size;
		}
	} else if ( f->begin.block == f->end.block ) {
		if ( f->end.pos < f->begin.pos ) {
			ret = FifomulSize(f) - f->begin.pos + f->end.pos;
		} else {
			ret = f->end.pos - f->begin.pos;
		}
	} else { // ( f->end.block < f->begin.block )
		ret = f->end.pos;
		for( i = 0; i < f->end.block; ++i) {
			ret += f->blocks[i].size;
		}
		for(i = f->begin.block; i < f->blocks_size; ++i) {
			ret += f->blocks[i].size;
		}
		ret -= f->begin.pos;
	}
	return ret;
}

uint16_t FifomulFree(struct fifomul_s *f)
{
	return f->full ? 0 : FifomulSize(f) - FifomulUsed(f);
}

uint16_t FifomulSize(struct fifomul_s *f)
{
	uint16_t ret = 0;
	for(uint8_t i = 0; i < f->blocks_size; ++i) {
		ret += f->blocks[i].size;
	}
	return ret;
}

#if 1

/* fifo tests --------------------------------------------------------------------------- */

#include "assert.h"
#include <stdbool.h>
#include <stdio.h>

void FifoPrintf(struct fifo_s *f)
{
#define LAZY(x) printf( #x "=%d ", x)
	LAZY(f->full);
	LAZY(f->begin);
	LAZY(f->end);
	LAZY(f->size);
#undef LAZY
	printf("\n");
}

void FifomulPrintf(struct fifomul_s *f)
{
#define LAZY(x) printf( #x "=%d ", x)
	LAZY(f->full);
	LAZY(f->begin.block);
	LAZY(f->begin.pos);
	LAZY(f->end.block);
	LAZY(f->end.pos);
	LAZY(f->blocks_size);
#undef LAZY
	printf("\n");
}

static inline void FifoFifoTest()
{
	static uint8_t buff[19];
	struct fifo_s f = FIFO_INIT(buff, sizeof(buff));
	FifoInitStatic(&f, buff);
	static_assert(sizeof(buff) > 5);

	assert( FifoSize(&f) == sizeof(buff) );

	for(uint8_t k = 0; k < 200 ; ++k ) {

		assert( FifoIsEmpty(&f) == true );
		assert( FifoIsFull(&f) == false );
		assert( FifoUsed(&f) == 0 );
		assert( FifoFree(&f) == sizeof(buff) );
		assert( FifoFree(&f) + FifoUsed(&f) == FifoSize(&f) );

		for(uint8_t i = 0; i < 5; i++) {
			FifoPut(&f, i);
		}

		assert( FifoUsed(&f) == 5 );
		assert( FifoFree(&f) == sizeof(buff) - 5 );
		assert( FifoFree(&f) + FifoUsed(&f) == FifoSize(&f) );
		assert( FifoIsEmpty(&f) == false );
		assert( FifoIsFull(&f) == false );

		for(uint8_t i = 0; i < 5; i++) {
			assert( FifoGet(&f) == i );
		}
	}

	FifoFlush(&f);

	for(uint8_t i = 0; i < FifoSize(&f); i++) {
		FifoPut(&f, i);
	}

	assert( FifoIsEmpty(&f) == false );
	assert( FifoIsFull(&f) == true );
	assert( FifoFree(&f) == 0 );
	assert( FifoUsed(&f) == sizeof(buff) );
	assert( FifoFree(&f) + FifoUsed(&f) == FifoSize(&f) );

	for(uint8_t i = 0; i < FifoSize(&f); i++) {
		assert( FifoGet(&f) == i );
	}
}



static inline void FifoFifomulTest()
{
	static uint8_t buff1[2];
	static uint8_t buff2[4];
	static uint8_t buff3[6];
	static uint8_t buff4[1];
	static struct fifomul_block_s blocks[] = {
			FIFOMUL_BLOCK_INIT_STATIC(buff1),
			FIFOMUL_BLOCK_INIT_STATIC(buff2),
			FIFOMUL_BLOCK_INIT_STATIC(buff3),
			FIFOMUL_BLOCK_INIT_STATIC(buff4),
	};
	struct fifomul_s f = FIFOMUL_INIT_STATIC(blocks);
	const uint16_t size = sizeof(buff1) + sizeof(buff2) + sizeof(buff3) + sizeof(buff4);
	assert( FifomulSize(&f) == size );

	for(uint8_t k = 0; k < 200 ; ++k ) {

		assert( FifomulUsed(&f) == 0 );
		assert( FifomulFree(&f) == size - 0 );
		assert( FifomulFree(&f) + FifomulUsed(&f) == FifomulSize(&f) );
		assert( FifomulIsEmpty(&f) == true );
		assert( FifomulIsFull(&f) == false );

		for(uint8_t i = 0; i < 5; i++) {
			FifomulPut(&f, i);
		}

		assert( FifomulUsed(&f) == 5 );
		assert( FifomulFree(&f) == size - 5 );
		assert( FifomulFree(&f) + FifomulUsed(&f) == FifomulSize(&f) );
		assert( FifomulIsEmpty(&f) == false );
		assert( FifomulIsFull(&f) == false );

		for(uint8_t i = 0; i < 5; i++) {
			assert( FifomulGet(&f) == i );
		}

	}

	FifomulFlush(&f);

	for(uint8_t i = 0; i < FifomulSize(&f); i++) {
		FifomulPut(&f, i);
	}

	assert( FifomulIsEmpty(&f) == false );
	assert( FifomulIsFull(&f) == true );
	assert( FifomulFree(&f) == 0 );
	assert( FifomulUsed(&f) == size );
	assert( FifomulFree(&f) + FifomulUsed(&f) == FifomulSize(&f) );

	for(uint8_t i = 0; i < FifomulSize(&f); i++) {
		assert( FifomulGet(&f) == i );
	}

}

void FifoTest()
{
	FifoFifoTest();
	FifoFifomulTest();
}

#endif
