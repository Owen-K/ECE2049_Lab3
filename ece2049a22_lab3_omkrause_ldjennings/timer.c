/*
 * timer.c
 *
 *  Created on: Oct 3, 2022
 *      Author: Liam
 */
#include <msp430.h>
#include "timer.h"

unsigned long int timer_cnt = 0;

void setupTimerA2(void)
{
  TA2CTL = TASSEL_1 | MC_1 | ID_0;
  TA2CCR0 = 32767;
  TA2CCTL0 = CCIE;     // enable Timer A2 interrupt
}

#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR (void) {
    timer_cnt++;
}
