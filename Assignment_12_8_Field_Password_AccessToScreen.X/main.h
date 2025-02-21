/* 
 * File: main.h
*/

#ifndef MAIN_H
#define MAIN_H

#define LED_ARRAY1_DDR    TRISB
#define LED_ARRAY1        PORTB
#define LED1              RB7


#define ON 1
#define OFF 0
// Constants for maximum attempts and password length
#define ZERO_ATTEMPTS 0
#define PASSWORD_LENGTH 9
void read_input(void);
#endif

