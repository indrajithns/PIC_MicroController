/* 
 * File:   main.h
*/
#ifndef MAIN_H
#define MAIN_H

/* MACRO for the PORTS and STATES */

#define LED_ARRAY1          PORTD
#define LED_ARRAY1_DDR      TRISD
#define LED1	RD0
#define ON		1
#define OFF		0

/* Function declarations */
void display(unsigned char data[]);
#endif

