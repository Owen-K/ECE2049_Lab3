#include <msp430.h> 
#include "peripherals.h"
#include "display.h"
#include "timer.h"


/**
 * main.c
 */


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	_BIS_SR(GIE);               // enable interrupts
	
	configDisplay();

	setupTimerA2();

	setupADC12();
	unsigned int prevCount = 0;
	while(1){
	    if(timer_cnt > prevCount){
	        prevCount++;
	        float temp = getTempC();
	        displayTemp(temp);
	    }

	}

	return 0;
}
