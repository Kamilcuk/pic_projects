/*
 * workqueue.c
 * 
 * 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * ------------------- The MIT Expat License + Beerware License ----------------
 * Copyright (c) 2017 Kamil Cukrowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * If we meet some day, and you think this stuff is worth it, you can buy me a
 * beer in return.
 * -----------------------------------------------------------------------------
 * 
 * 
 */
 
/* muhahaha fast and small my workqueue implementation */

#ifndef __pic16
#warning UCH! there can be no CPFSLT assembler function
#warning check out workqueue implementation
#endif

#ifndef WQ_MAX_WORKERS
#define WQ_MAX_WORKERS (8)
#endif

#define WQ_INLINE_ASSEMBLE

#define WQ_PDEBUG(...) //printf_tiny( __VA_ARGS__ )


struct work_struct {
	void __code (*func) (void); // 3 bytes
};

struct workqueue_struct {
	/* must be first, for inline assemble code */
	unsigned char first; /* hm.. what can this be */
	unsigned char last;  /* more hm... */
	
	/* workers */
	struct work_struct worker[WQ_MAX_WORKERS];
};

static struct workqueue_struct wq;


void workqueue_init(void) 
{
	wq.first = wq.last = 0;
}

void workqueue_queue(void __code (*func)() )
{
	wq.worker[wq.last].func = func;
	
#ifndef WQ_INLINE_ASSEMBLE
	wq-last++;
	if (wq.last >= WQ_MAX_WORKERS)
		wq.last = 0;
#else
__asm
	BANKSEL (_wq + 1)
	INCF (_wq + 1), F, B ; wq.last ++
	MOVLW WQ_MAX_WORKERS 
	CPFSLT (_wq + 1), B ; if ( wq.last >= WQ_MAX_WORKERS )
	CLRF (_wq + 1), B ; wq.last = 0
__endasm;
#endif
}

void workqueue_dequeue(void)
{
	/* dequeues all workers in a chronoligical order ! */
	
	/* find the first added worker */
	for (; wq.first != wq.last; wq.first++) {
		
#ifndef WQ_INLINE_ASSEMBLE
		if ( wq.first >= WQ_MAX_WORKERS ) 
			wq.first = 0;
#else
		__asm
		MOVLW WQ_MAX_WORKERS 
		BANKSEL (_wq + 0)
		CPFSLT (_wq + 0), B ; if ( wq.first >= WQ_MAX_WORKERS )
		CLRF (_wq + 0), B ; wq.first = 0
		__endasm;
#endif
		
		if (wq.worker[wq.first].func) {
			wq.worker[wq.first].func();
		}
	}
}

/*
 * list workqueue implementation
 * only with next thing
 * allows dynamic allocation
 * but do you really need to dynamic allocate things ?
 * malloc is something very very cpu and memory usage-full :D

struct worklist_t {
	__xdata void *worker;
	__near struct worklist_t *next; 
};

__near struct worklist_t worklist[WQ_MAX_WORKERS];
 
__near struct worklist_t *curr;

void workqueue_init()
{
	unsigned char i;
	
	curr = worklist;
	
	for (i=1; i<WQ_MAX_WORKERS ; i++) 
		worklist[i-1].next = &( worklist[i] );
	
	worklist[i-1] = &( worklist[0] );
}

void workqueue_add(void *func)
{
	curr->worker=func;
	curr=curr.next;
}

void workqueue_dequeue()
{
	unsigned char i;
	
	for (i=curr.prev ; i != curr; i=i.prev) {
		if(!i.worker)
			break;
	}
	
	i=i.next;
	
	for(;i != curr; i=i.next) {
		i.worker();
	}

}
 * */
