/*
 *        File: main.c
 *  Created on: 15.06.2017
 *      Author: Kamil Cukrowski
 */

#include <xc.h>
#include <plib/adc.h>
#include <stdbool.h>
#include <stdint.h>
#include <usbhid_stdio/usbhid_stdio.h>
#include <bitmask.h>

#define ADC_CH_NUM 13
#define ADC_SET_CH(x) BITMASK_WRITE(ADCON0, 0b00111100, (x<<2))
bool ADCupdated[ADC_CH_NUM];
bool ADCenabled[ADC_CH_NUM] = {1,0};
uint16_t ADCpos = 0;
uint16_t ADCresult[ADC_CH_NUM];

void __interrupt(high_priority) SYS_InterruptHigh(void)
{
	usbStdioInterruptHandler();
}

void __interrupt( low_priority) SYS_InterruptLow(void)
{
	if(PIR1bits.ADIF) {

        ADCresult[ADCpos] = ADRES;
        ADCupdated[ADCpos] = true;
        uint8_t i;
        for(i=0;i<ADC_CH_NUM;++i) {
        	if ( ADCenabled[i] ) {
        		break;
        	}
        }
        if ( i == ADC_CH_NUM ) {
        	i=0;
        }
    	ADC_SET_CH(i);
        ConvertADC();

        PIR1bits.ADIF = 0;
	}
}

void a() {
	int a=0;
	a=2+2;
}

int main() {
	IPR1bits.ADIP = 0;
	OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_20_TAD,
			ADC_INT_ON & ADC_REF_VDD_VSS,
			ADC_15ANA);
	ADC_SET_CH(0);
	ConvertADC();

	while(1){
		a();

	}
}
