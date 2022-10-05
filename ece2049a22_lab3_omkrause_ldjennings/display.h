/*
 * display.h
 *
 *  Created on: Sep 28, 2022
 *      Author: okrause
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <msp430.h>
#include <math.h>
#include "peripherals.h"


void displayTime(long unsigned int inTime);
void displayTemp(float inAvgTempC);


#endif /* DISPLAY_H_ */
