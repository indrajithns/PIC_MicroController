/* 
 * File:   main.h
 */

#ifndef MAIN_H
#define	MAIN_H

#define LED_ARRAY1_DDR    TRISD
#define LED_ARRAY1        PORTD
#define LED1              RD0
#define ON                1
#define OFF               0
unsigned int req_time;
void software_pwm(void);
static void init_config(); //Calling initializing function

#endif	/* MAIN_H */

