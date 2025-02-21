/*
 * File:   timer.c
 * Author: indra
 * Description : Implement the time separator with Timer 0, Timer 1 and Timer 2
*/

#include <xc.h>
#include "main.h"

void init_timer0(void)
{
	



/* Selecting internal clock source */
	T0CS = 0;

/* disabling prescaler*/
	PSA = 1;

	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}
void init_timer1(void)
{
    /* enabling timer1 */
	TMR1ON = 1;

	TMR1 = 3036;

    /* set timer1 flag to zero */
	TMR1IF = 0;

    /* set enable pin */
	TMR1IE = 1;
}
void init_timer2(void)
{
    /* enabling timer2 */
	TMR2ON = 1;
	
	PR2 = 249;
	
    /* set flag to 0 */
	TMR2IF = 0;

    /* set enable pin */
	TMR2IE = 1;
}