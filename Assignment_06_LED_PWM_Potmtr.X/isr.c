/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indra
 *   File           : isr.c
 *   Title          : Timer Module - Timer 0 ISR
 *   Description    : An ISR code to generate 1 second timing
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "main.h"

//declared the variables with extern keyword to access them from the other files
extern unsigned long int duty_cycle, period, loop_counter;
extern unsigned int flag; //To extend the Scope of Visibility for the variable from the main.c file.

void software_pwm(void) {
    //as long as the counter is less than the duty cycle, turn ON the LED
    if (loop_counter < duty_cycle) {
        LED1 = 1;
        //when the LED reaches one full period i.e 100 turn OFF the LED
    } else if (loop_counter < period) {
        LED1 = 0;
    }
    //and reset the loop_counter after each full period cycle
    if (loop_counter++ == period) {
        loop_counter = 0;
    }
}

void __interrupt() isr(void) {
    static unsigned int count = 0;

    if (TMR0IF == 1) {
        /* TMR0 Register value + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;

        if (++count == req_time) {
            count = 0;

            // brightness back 10%
        }

        TMR0IF = 0;
    }
}

