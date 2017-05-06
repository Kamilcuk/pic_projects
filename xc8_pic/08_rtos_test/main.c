/*
 * systick.h
 *
 *  Created on: 04.04.2017
 *      Author: Kamil Cukrowski
 *     License: beerware
 */
#include <xc.h>
#include <system.h>

#include <mdb.h>
#include <systick.h>

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errata.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>
#include <stdio.h>
#include <soft_return_address_stack.h>
#include <string.h>

/* ------------------------------------------------------------------------------ */

#define TASKS_NUM 4
uint8_t taskSaveReturnStack[TASKS_NUM][31*2] = {0};
uint8_t taskSaveReturnStacklen[TASKS_NUM] = {0};
uint8_t taskSaveRegisters[TASKS_NUM][17] = {0};
static uint8_t registers[17];
static bool tasksRunning = false;
static uint8_t taskCur = 1;

void task_add( void *function_pnt )
{
	volatile UINT16_VAL pnt;

	pnt.Val = (uint16_t)function_pnt;
	taskSaveReturnStack[taskCur][1] = pnt.byte.HB;
	taskSaveReturnStack[taskCur][0] = pnt.byte.LB;
	taskSaveReturnStacklen[taskCur] = 1;

	printf("%u: task_add %d %x %x \n",
			systickGet(), taskCur, pnt.byte.HB, pnt.byte.LB);

	++taskCur;
	if ( taskCur >= TASKS_NUM ) {
		taskCur = 0;
	}
}

void task_start(void)
{
	volatile UINT16_VAL pnt;

	taskCur = 0;
	tasksRunning = true;
	printf("%u: task_start %d %x %x \n", systickGet(), taskCur, TOSH, TOSL);
}

/* ------------------------------------------------------------------------------ */

void interrupt high_priority SYS_InterruptHigh(void)
{
}

#define COUNTER_MAX 10
static uint8_t counter = 0;

void interrupt  low_priority SYS_InterruptLow(void)
{
	if (SYSTICK_TIMER_IF) {
		SYSTICK_TIMER_IF = 0;
		systickServiceInterrupt_in();

		/* tasks implementation */
		if ( tasksRunning ) {
		
#define TASK_REGISTERS_SAVE(x)    asm("movff ??_SYS_InterruptLow+" #x " , _registers+" #x )
#define TASK_REGISTERS_LOAD(x) asm("movff _registers+" #x " , ??_SYS_InterruptLow+" #x )
#define TASK_APPLY_17( FUN ) do{ \
		FUN(0); FUN(1); FUN(2); FUN(3); \
		FUN(4); FUN(5); FUN(6); FUN(7); \
		FUN(8); FUN(9); FUN(10); FUN(11); \
		FUN(12); FUN(13); FUN(14); FUN(15); \
		FUN(16); \
} while(0)

			// save thread information
			TASK_APPLY_17( TASK_REGISTERS_SAVE );
			memcpy(taskSaveRegisters[taskCur], registers, 17);
			SoftReturnAddressStack_save(
					taskSaveReturnStack[taskCur],
					taskSaveReturnStacklen[taskCur]
			);

			// choose next running thread
			do {
				++taskCur;
				if ( taskCur >= TASKS_NUM ) {
					taskCur = 0;
				}
			} while( taskSaveReturnStacklen[taskCur] == 0 );

			// load thread information
			SoftReturnAddressStack_load(
					taskSaveReturnStack[taskCur],
					taskSaveReturnStacklen[taskCur]
			);
			memcpy(registers, taskSaveRegisters[taskCur], 17);
			TASK_APPLY_17( TASK_REGISTERS_LOAD );
		}
	}
}

static unsigned long next = 123456L;
int rand(void)
{
    next = next * 1103515245L + 12345L;
    return (unsigned int)(next/65536)%32767;
}
void srand(unsigned int seed)
{
    next = seed;
}


/* ----------------------------------------------------------------------------- */


void delay_10ms(unsigned char n) {
    while (n-- != 0) {
		__delay_ms(1);
	} 
}


uint8_t stack[10];
uint8_t stacklen = 0;

asm("global _task1");
void task1(void)
{
	while(1) {
		delay_10ms( 10 + rand()%10 );
        char a = rand()%255;
		di();
        if ( stacklen < sizeof(stack) ) {
            printf("%u: task1 producing %d \n", systickGet(), a);
            stack[stacklen] = a;
            ++stacklen;
    		ei();
        } else {
    		ei();
            printf("%u: task1 stack full\n", systickGet());
        }
	}
}

asm("global _task2");
void task2(void)
{
	while(1) {
		delay_10ms( 10 + rand()%10 );
        di();
        if ( stacklen ) {
            char a;
            --stacklen;
            a = stack[stacklen];
            ei();
            printf("%u: task2 eating %d \n", systickGet(), a);
        } else {
            ei();
            printf("%u: task2 stack empty \n", systickGet());
        }
	}
}

asm("global _task3");
void task3(void)
{
	while(1) {
		delay_10ms( 10 + rand()%10 );
        di();
        if ( stacklen ) {
            char a;
            --stacklen;
            a = stack[stacklen];
            ei();
            printf("%u: task3 eating %d \n", systickGet(), a);
        } else {
            ei();
            printf("%u: task3 stack empty \n", systickGet());
        }
	}
}
 
void main_preinit(void)
{
	// set all ports as inputs
	PORTA = PORTB = PORTC = 0x00;
	TRISA = TRISB = TRISC = 0xff;
	LATA = LATB = LATC = 0x00;
	// enable interrupts
	RCONbits.IPEN = 1;
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
}

MDB_UART_PUTCH_DECLARE()
void main(void)
{
	main_preinit();
	MDB_UART_INIT();

	systickInitInterrupt(0);
	printf("Startup completed.\n");

	task_add( task1 );
	task_add( task2 );
	task_add( task3 );
	printf("Tasks added.\n");

	task_start();
	printf("Tasks start.\n");

	while(1) {
		printf("%u: taskmain\n", systickGet() );
		__delay_ms( 200 );
	}
}

