/*
 * Filename : main.c
 Name       : Indra
Description : Using Timer based PWM, implement a LED dimmer application.
As soon as the board is powered on or reset, The LED should glow with 50% Duty Cycle (i.e the glow, half of its maximum intensity).
The Increment Brightness Input should increase the Duty Cycle upto 100% (Total ON)
The Decrement Brightness Input should decrease the Duty Cycle to 0% (Total OFF)
Inputs:
- DKS1 as Increase Brightness Input, Level Triggered
- DKS2 as Decrease Brightness Input, Level Triggered
- Program Cycles as Period
 */
#include <xc.h>
#include "main.h"
#include "digital_keypad.h"
#include"timer.h"

#pragma config WDTE = OFF //Watchdog timer disabled
unsigned long int duty_cycle = 50, period = 100, wait = 250, loop_counter = 0;

static void init_config(void) {
    //Write your initialization code here
    LED_ARRAY = 0x00;       //turn off the LED of PORTD initially
    LED_ARRAY_DDR = 0x00;   //set the direction of PORTD LEDS to output
    init_timer();			//call the function To initialize the ports and registers with the default values.
	GIE = 1;				//To set the Global Interrupt Enable bit.
	PEIE = 1;				//To set the Peripheral Interrupt Enable bit.

}

void main(void) {
    init_config();          //Calling initial configuring function
    init_digital_keypad();  ////Calling the function to initialize the digital keypad
    unsigned char key;
    while (1) {
        key = read_digital_keypad(LEVEL);     //read the digital keypad
        if (wait-- == 0) {                      //set the non-blocking delay
            wait = 250;
        //trigger the ISR when the switch press happens and increment duty cycle till it is completely bright
            if (key == SW1 && duty_cycle < period) {    
                duty_cycle++;
        //trigger the ISR when the switch press happens and decrement duty cycle till it is completely low
            } else if (key == SW2 && duty_cycle > 0) {
                duty_cycle--;
            }
        }
        //software PWN function call
        software_pwm();
    }
     TMR2IE = 1;
}
