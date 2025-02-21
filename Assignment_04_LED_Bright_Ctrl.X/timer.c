/*
Name         : Indra
Description  : ISR function to handle the interrupt
 */

#include<xc.h>
#include "timer.h"

void init_timer2(void)
{
	PR2 = 250;			//To set the Timer2 Period register value as '250' for the Overflow to happen after that particular count.
    TMR2ON = 1;			//To enable the Timer2.
    TMR2IE = 1;			//To set the Timer2 Overflow Interrupt Enable Bit.
    TMR2IF = 0;
}
