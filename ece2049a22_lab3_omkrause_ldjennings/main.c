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

	displayTemp(30);

	while(1){
	}

	return 0;
}
