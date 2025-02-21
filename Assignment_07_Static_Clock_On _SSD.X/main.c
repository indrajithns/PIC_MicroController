/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : main.c
 *   Title          : Implement a static clock on SSD using internal timer
 *   Description    : Implement a static (non configurable) clock on SSD (Shown in the video) using internal timer.
                    Output Requirements:
                    As soon as the board is powered on or reset, the clock should start at 12.00.
                    The decimal point of the hours field (one?s place) should blink every 500 msecs (0.5 Hz)
                    The clock format should be 24 Hrs.
                    Inputs:
                    Timer
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "ssd.h"
#include"main.h"
#include "timers.h"
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned char ssd[] = {ONE, TWO, ZERO, ZERO}; //Seven Segment Display data array.
//unsigned char count = 0;
extern unsigned char count = 0;

static void init_config(void) {
    //initialize ssd
    init_ssd();
    init_timer0(); /*function call to enable the timer0*/
    PEIE = 1; /* set Global Interrupt Enable bit , peripheral interrupt enable bit*/
    GIE = 1;
}

void main() {
    init_config();

    unsigned char hour = 12, minute = 0;        //declaring

    while (1) {
        if (count % 2 == 1) {
            ssd [1] = digit [(hour % 10)] | DOT; //Display with dot. Toggle the 4th bit of the Macro in SSD3 i.e at 0x80
        } else //for every 10000 ticks count will become an even number
            ssd [1] = digit [(hour % 10)];

        if (count == 120) //If the 'count' becomes 120; 60 seconds have passed as assumption and increment the 'minute' by 1.
        { // as for 0.5 sec 1 tick happen, by the time count = 120, 60 seconds happen
            minute += 1;
            count = 0;
        }

        if (minute == 60) //If the 'minute' becomes 60,it is 1 hour; reset to 0 and increment the 'hour' by 1.
        {
            hour += 1;
            minute = 0;
        }

        if (hour == 24) //If the 'hour' becomes 24; reset to 0 as 24 hr format has range from 0 to 23.
        {
            hour = 0;
        }

        ssd [3] = digit [minute % 10]; //Units place digit.
        ssd [2] = digit [(minute / 10) % 10]; //Tenth place digit.
        ssd [0] = digit [(hour / 10) % 10]; //Thousandth place digit.
        display(ssd);
    }
}



