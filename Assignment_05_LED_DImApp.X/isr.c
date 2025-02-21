/*
 * Filename : isr.c
 Name       : Indra
Description : To perform the operations when an Interrupt is requested.
 */
#include <xc.h>
#include "main.h"

//declared the variables with extern keyword to access them from the other files
extern unsigned long int duty_cycle, period, loop_counter;
extern unsigned int flag; //To extend the Scope of Visibility for the variable from the main.c file.

void software_pwm(void) {
    //as long as the counter is less than the duty cycle, turn ON the LED
    if (loop_counter < duty_cycle) {
        LED = 1;
        //when the LED reaches one full period i.e 100 turn OFF the LED
    } else if (loop_counter < period) {
        LED = 0;
    }
    //and reset the loop_counter after each full period cycle
    if (loop_counter++ == period) {
        loop_counter = 0;
    }
}

void __interrupt() isr(void) {
    if (TMR2IF) //If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
    {
        TMR2IF = 0; //To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
    }
}

