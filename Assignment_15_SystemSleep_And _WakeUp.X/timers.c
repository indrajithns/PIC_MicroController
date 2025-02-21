/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : timers.c
 *   Title          : Timers 
 *   Description    : To initialize the timers
 *-----------------------------------------------------------------------------------------------*/

#include <xc.h>
#include "timers.h"

void init_timer0(void) {
    /* Setting the internal clock source */
    T0CS = 0;

    /* Assigning the prescaler to Watchdog Timer */
    PSA = 1;

    TMR0 = 6;

    /* The timer interrupt is enabled */
    TMR0IE = 1;
}

