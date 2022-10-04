/*
 * display.c
 *
 *  Created on: Sep 28, 2022
 *      Author: okrause
 */

#include "display.h"


void displayTime(long unsigned int inTime) {
    unsigned long int remainder = 0;
    unsigned char month[3];
    month[0] = 'e';
    month[1] = 'r';
    month[2] = 'r';
    unsigned int day, hour, min, sec;

    day = inTime / 86400 + 1;
    remainder = inTime - (day - 1) * 86400;

    if (day <= 31) {    //January
        month[0] = 'J';
        month[1] = 'A';
        month[2] = 'N';
    } else if (31 < day && day <= 59) { //February
        month[0] = 'F';
        month[1] = 'E';
        month[2] = 'B';
        day -= 31;
    } else if (59 < day && day <= 90) { //March
        month[0] = 'M';
        month[1] = 'A';
        month[2] = 'R';
        day -= 59;
    } else if (90 < day && day <= 120) {    //April
        month[0] = 'A';
        month[1] = 'P';
        month[2] = 'R';
        day -= 90;
    } else if (120 < day && day <= 151) {   //May
        month[0] = 'M';
        month[1] = 'A';
        month[2] = 'Y';
        day -= 120;
    } else if (151 < day && day <= 181) {   //June
        month[0] = 'J';
        month[1] = 'U';
        month[2] = 'N';
        day -= 151;
    } else if (181 < day && day <= 212) {   //July
        month[0] = 'J';
        month[1] = 'U';
        month[2] = 'L';
        day -= 181;
    } else if (212 < day && day <= 243) {   //August
        month[0] = 'A';
        month[1] = 'U';
        month[2] = 'G';
        day -= 212;
    } else if (243 < day && day <= 273) {   //September
        month[0] = 'S';
        month[1] = 'E';
        month[2] = 'P';
        day -= 243;
    } else if (273 < day && day <= 304) {   //October
        month[0] = 'O';
        month[1] = 'C';
        month[2] = 'T';
        day -= 273;
    } else if (304 < day && day <= 334) {   //November
        month[0] = 'N';
        month[1] = 'O';
        month[2] = 'V';
        day -= 304;
    } else if (334 < day && day <= 365) {   //December
        month[0] = 'D';
        month[1] = 'E';
        month[2] = 'C';
        day -= 334;
    }

    hour = remainder / 3600;
    remainder = remainder - hour * 3600;
    min = remainder / 60;
    sec = remainder - min * 60;

    unsigned char dayDisp[2];
    dayDisp[0] = day / 10 + '0';
    dayDisp[1] = day % 10 + '0';

    unsigned char hourDisp[2];
    hourDisp[0] = hour / 10 + '0';
    hourDisp[1] = hour % 10 + '0';

    unsigned char minDisp[2];
    minDisp[0] = min / 10 + '0';
    minDisp[1] = min % 10 + '0';

    unsigned char secDisp[2];
    secDisp[0] = sec / 10 + '0';
    secDisp[1] = sec % 10 + '0';

    unsigned char dateDisplay[7];
    unsigned char timeDisplay[9];

    dateDisplay[0] = month[0];
    dateDisplay[1] = month[1];
    dateDisplay[2] = month[2];
    dateDisplay[3] = 0x2D; // '-' character
    dateDisplay[4] = dayDisp[0];
    dateDisplay[5] = dayDisp[1];
    dateDisplay[6] = 0x00; //null terminator

    timeDisplay[0] = hourDisp[0];
    timeDisplay[1] = hourDisp[1];
    timeDisplay[2] = ':';
    timeDisplay[3] = minDisp[0];
    timeDisplay[4] = minDisp[1];
    timeDisplay[5] = ':';
    timeDisplay[6] = secDisp[0];
    timeDisplay[7] = secDisp[1];
    timeDisplay[8] = 0x00;


    //unsigned char display[] = month[0] + month[1] + month[2] + ' ' + dayDisp[0] + ' ' + hourDisp[0] + '\0';

    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, dateDisplay, AUTO_STRING_LENGTH, 48, 44, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, timeDisplay, AUTO_STRING_LENGTH, 48, 52, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
}


