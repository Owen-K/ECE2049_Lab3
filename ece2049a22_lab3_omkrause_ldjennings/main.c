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

	displayTime(7243463);

	return 0;
}
