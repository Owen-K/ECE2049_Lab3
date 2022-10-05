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

unsigned long int day, hour, min, sec;
unsigned long int potval;

enum States{Run, ChangeTime};
enum TimeUnits{Month, Day, Hour, Min, Sec};


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
	
	enum States state;
	state = Run;

	enum TimeUnits currentTimeUnit;

	configDisplay();
	configButtons();
	setupTimerA2();

	setupADC12Temp();

	CurrTemp = getTempC();
	int i;
	for(i = 0; i < TEMP_ARRAY_LENGTH; i++){
	    TempsC[i] = CurrTemp;
	}

	unsigned int prevCount = 0;
	while(1){
	    /*if(timer_cnt > prevCount){
	        prevCount++;
	        CurrTemp = getTempC();
	        TempsC[timer_cnt % 36] = CurrTemp;
	        displayTemp(averageArray(TempsC));
	    }*/
	    //displayTime((unsigned long) getScrollVal());
	    switch(state) {
	    case Run:
	        if(timer_cnt > prevCount){
                prevCount = timer_cnt;
                CurrTemp = getTempC();
                TempsC[timer_cnt % 36] = CurrTemp;
                Graphics_clearDisplay(&g_sContext);
                displayTime(timer_cnt);
                displayTemp(averageArray(TempsC));
            }
	        if (getButtons() == 0x01){
	                        stopTimerA2();
	                        currentTimeUnit = Day;
	                        setupADC12Scroll();
	                        state = ChangeTime;
	                    }
	        break;
	    case ChangeTime:
	        potval = getScrollVal();
	        if (getButtons() == 0x08){
	            timer_cnt = day + hour + min + sec;
	            startTimerA2();
	            setupADC12Temp();
	            state = Run;
	        }
	        switch(currentTimeUnit){
	        case Day:
	            if (getButtons() == 0x01)
	                currentTimeUnit = Hour;
	            day = (potval / (4095/365)) * 86400;
	            break;
	        case Hour:
	            if (getButtons() == 0x01)
                    currentTimeUnit = Min;
	            hour = (potval / (4095/24)) * 60 * 60;
	            break;
	        case Min:
	            if (getButtons() == 0x01)
                    currentTimeUnit = Sec;
	            min = (potval / (4095/60)) * 60;
	            break;
	        case Sec:
	            if (getButtons() == 0x01)
                    currentTimeUnit = Day;
	            sec = (potval / (4095/60));
	            break;
	        }
	        Graphics_clearDisplay(&g_sContext);
            displayTime(day + hour + min + sec);
	        break;
	    }

	}

	return 0;
}
