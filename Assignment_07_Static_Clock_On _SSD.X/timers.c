/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : timer0.c
 *   Title          : Timer Module - Timer 0 Initialiation
 *   Description    : A initialization code to enable timer 0 module
 *-----------------------------------------------------------------------------------------------*/
#include<xc.h>

void init_timer0(void) {
    /* Setting the internal clock source */
    T0CS = 0;
    /* Assigning the prescaler to Watchdog Timer */
    PSA = 1;
    TMR0 = 6;
    /* The timer interrupt is enabled */
    TMR0IE = 1;
}

