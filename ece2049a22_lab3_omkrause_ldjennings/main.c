#include <msp430.h> 
#include "peripherals.h"
#include "display.h"
#include "timer.h"

#define TEMP_ARRAY_LENGTH 36

/**
 * main.c
 */
float TempsC[TEMP_ARRAY_LENGTH];
float CurrTemp;



float averageArray(float* array){
    int i;
    float average = 0;
    for( i = 0; i < TEMP_ARRAY_LENGTH; i++){
        average += array[i];
    }
    return average / TEMP_ARRAY_LENGTH;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	_BIS_SR(GIE);               // enable interrupts
	
	configDisplay();

	setupTimerA2();

	setupADC12Scroll();
	/*CurrTemp = getTempC();
	int i;
	for(i = 0; i < TEMP_ARRAY_LENGTH; i++){
	    TempsC[i] = CurrTemp;
	}*/

	unsigned int prevCount = 0;
	while(1){
	    /*if(timer_cnt > prevCount){
	        prevCount++;
	        CurrTemp = getTempC();
	        TempsC[timer_cnt % 36] = CurrTemp;
	        displayTemp(averageArray(TempsC));
	    }*/
	    displayTime((unsigned long) getScrollVal());
	}

	return 0;
}
