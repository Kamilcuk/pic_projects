#include <stdint.h>
#include <plib/delays.h>
//#include "printft.h"
#include <plib/delays.h>
#include <time.h>
#include <stdlib.h>
#include "usbhid_stdio/usbhid_stdio.h"
#include "printft.h"

void interrupt high_priority SYS_InterruptHigh(void)
{
	usbStdioInterruptHandler();
}

void interrupt  low_priority SYS_InterruptLow(void)
{
}

static uint8_t buff[100];
static uint8_t u8 = 1;
static uint16_t u16 = 1234;
static uint32_t u32 = 1234567;
static float f = 12.3f;
static double d = 789.1f;
void test_printf()
{
    printf("---------------------------------------------\n");
    printf("Compiled with XC8 version %d on %s  at %s UTC\n", __XC8_VERSION, __DATE__, __TIME__);
    printf("sizeof(uint8_t)  = %d, sizeof(uint16_t) = %d\n", sizeof(uint8_t), sizeof(uint16_t));
    printf("sizeof(uint32_t) = %d, sizeof(void*)    = %d\n", sizeof(uint32_t), sizeof(void*));
    printf("sizeof(float)    = %d, sizeof(double)   = %d\n", sizeof(float), sizeof(double));
    printf("u8 = %d = %x = %02x\n", u8, u8, u8);
    printf("u16 = %d = %x = %04x\n", u16, u16, u16);
    printf("u32 = %lu = %lx = %lx\n", u32, u32, u32);
    printf("f = %f | d = %f \n", f,  d);
    if ( getchar_ready() ) {
    	uint8_t i;
    	for(i=0;i<sizeof(buff)-1 && getchar_ready();++i) {
    		buff[i] = getchar();
    	}
    	buff[i] = '\0';
    	printf("Received: \"%s\"\n", buff);
    } else {
    	printf("Nothing received\n");
    }
    printf("\n");
    ++u8;
    ++u16;
    u32*=3;
    d += 5.6f;
    flush();
}

void main(void)
{
	PORTA = PORTB = PORTC =
			TRISA = TRISB = TRISC =
			LATA = LATB = LATC = 0x00;

	usbStdioInitBlocking(1);

    while(1) {
    	test_printf();
    	__delay_ms(1000);
    	test_printf();
    	__delay_ms(1000);
    }
}

