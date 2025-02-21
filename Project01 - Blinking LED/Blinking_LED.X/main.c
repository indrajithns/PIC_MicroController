/*
 * File:   main.c
 * Author: Indrajith N S
 * Description: Blinking LED with Delay
 * Created on 19 February, 2025, 9:31 PM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000 // 20MHz Clk Frequency
#pragma config WDTE = OFF

void init_config(void) {
    //Do initialization
    
    TRISD = 0x00; //All Port C are Output
}

void main(void) {
    init_config();
    while (1) {
        //Application here
        
        PORTD = 0x04; // 0000 0100 RD2 is High
        __delay_ms(1000); // 1 Sec Delay
        
        PORTD = 0x00; // 0000 0000 RD2 is Low
        __delay_ms(1000); // 1 Sec Delay
    }
    return;
}
