/*
Name         : Indra
Description  : ISR function to handle the interrupt
 */
#include <xc.h>
#include "main.h"
#include "timer.h"

extern unsigned int duty_cycle;
extern unsigned int PERIOD;
unsigned int long req_time = 0;
unsigned int long loop_counter = 0;
unsigned int flag = 0;

void software_pwm(void) {
    /*If the Program cycle value is less than the Duty Cycle, the LED shall be ON */
    if (loop_counter++ < duty_cycle) {
        LED1 = ON;
    }/*If the Program cycle value is greater than the Duty Cycle and greater than duty_cycle,*/
        //the LED shall be OFF 
    else {
        LED1 = OFF;
    }
    /*If the Program Cycle becomes greater than PERIOD, reset it to 0.*/
    if (loop_counter >= PERIOD) {
        loop_counter = 0;
    }
}

void __interrupt() isr(void) {
    static unsigned int count = 0;
    software_pwm();
    /*If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt. */
    if (TMR2IF == 1) {
        TMR2 = TMR2 + 2 + 6;
        /*The formula for the Timer2 yields the result as: 1 count for every 20000 ticks. */
        if (count++ == 20000) {
            if (req_time++ == 500) //If req_time is 500 msec, set the 'flag' as 1.
            {
                req_time = 0;
                flag = 1;
            }
            count = 0; //Reset the 'count' to 0 for the next cycle.
        }
        TMR2IF = 0; //To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
    }
}
