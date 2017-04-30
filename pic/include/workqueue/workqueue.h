/*
 * workqueue.h
 * 
 * Under BEER-WARE license 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * 
 */

#ifndef _WORKQUEUE_H_
#define _WORKQUEUE_H_
extern void workqueue_init(void);
extern void workqueue_queue(void __code (*func)() );
extern void workqueue_dequeue(void);
#endif /* _WORKQUEUE_H_ */
