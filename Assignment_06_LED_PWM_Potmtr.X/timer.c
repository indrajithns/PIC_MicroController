/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indra
 *   File           : timers.c
 *   Title          : Timer Module - Timer 0 ISR
 *   Description    : An ISR code to generate 1 second timing
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>

void init_timer0(void)
{
    /* Setting the internal clock source */
    T0CS = 0;
    
    /* Assinging the prescaler to Watchdog Timer */
    PSA = 1;

    TMR0 = 6;
    
    /* The timer interrupt is enabled */
    TMR0IE = 1;
}
