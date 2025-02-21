/* 
 * File:   main.h
*/

#ifndef MAIN_H
#define	MAIN_H
#include "timers.h"
#include "isr.h"
#include "external_interrupt.h"
#include "ssd.h"


#define LED_ARRAY1          PORTB
#define LED_ARRAY1_DDR      TRISB

#define LED1                RB7
#define LED2                RB0 /*to test the key detection*/

#define ON                  1
#define OFF                 0

#define PRESSED             0

#endif	/* MAIN_H */