/*
 * File:   main.c
 * Author: Indrajith N S
 * Description: Blinking Multiple LEDs
 * Created on 19 February, 2025, 10:17 PM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000 // 20MHz Clk Frequency
#pragma config WDTE = OFF

void init_config(void) {
    //Do initialization
    TRISD = 0x00; // Making all Port D as Output
}

void main(void) {
    init_config();
    while (1) {
        //Application here
        PORTD = 0x02; // 0000 0010 Making RD7 Low Condition and RD1 High Condition
        __delay_ms(3000); //Delay of 3 sec
        
        PORTD = 0x80; // 1000 0000 Making RD7 High Condition and RD1 Low Condition
        __delay_ms(3000); //Delay of 3 sec
        
        PORTD = 0x82; // 1000 0010 Making RD7 High Condition and RD1 High Condition
        __delay_ms(3000); //Delay of 3 sec
        
          PORTD = 0x00; // 0000 0000 Making RD7 Low Condition and RD1 Low Condition
        __delay_ms(3000); //Delay of 3 sec
    }
    return;
}
