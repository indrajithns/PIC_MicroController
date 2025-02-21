/*
 * File:   main.c
 * Author: indra
 *
 * Created on 7 December, 2024, 6:42 PM
 * Description : Implement the time separator with Timer 0, Timer 1 and Timer 2
*/


#include <xc.h>
#include "main.h"
#pragma config WDTE = OFF

void init_config(void) {
    //Do initialization
    PEIE = 1;
	/* Clear old content */
	PORTD = 0x00;

	/* Set PORTD as a Output */
	TRISD = 0x00;

	/* Config PORTD as digital */
	/* ADCON1 = 0x0F;

    /* function call to configure the timers */
	init_timer0();
    init_timer1();
    init_timer2();

	GIE = 1;   // Enable global interrupts
}

void main(void) {
    init_config();
    while (1) {
       ; //Application here
    }
    return;
}