/*
 * Filename : main.h
 Name       : Indra
Description : declaration of LED and function prototypes
 */

#ifndef MAIN_H
#define MAIN_H

#define LED_ARRAY PORTD
#define LED_ARRAY_DDR TRISD

#define LED RD0
#define ON 1
#define OFF 0

void software_pwm(void);
static void init_config(); //Calling initializing function
void init_digital_keypad();

#endif