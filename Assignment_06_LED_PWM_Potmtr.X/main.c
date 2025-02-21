/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indra
 *   File           : main.c
 *   Title          : A06 - Implement a LED dimmer application using PWM (Timer ISR Based)
 *   Description    : The brightness of the LED illumination should be based on the user input tuning the Knob of potentiometer.
                      Output Requirements:
                      On giving power supply to the board, read the value of pot. Based on that value, set the duty cycle. Again read the pot value
                      If it is different from previous value, update duty cycle accordingly.If it is same do nothing.Repeat the same on regular interval or continuously. 
                      Use timer to generate PWM
                      Inputs:
                      Potentiometer 1 as Knob
                      Timer for PWM
 *-------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "main.h"
#include "adc.h"
#include "timer.h"
#pragma config WDTE = OFF      // Watchdog Timer ~Enable bit (WDT ~enabled)

unsigned long int duty_cycle = 50, period = 100, wait = 250, loop_counter = 0;

static void init_config(void) {
    LED_ARRAY1 = OFF;
    LED_ARRAY1_DDR = 0x00; //configuration
    init_timer0();

    /* Enable all the Global Interrupts */
    GIE = 1;
    PEIE = 1; //To set the Peripheral Interrupt Enable bit.

    init_adc();             //calling adc function
}

void main(void) {
    unsigned short adc_reg_val;         //declaring a variable to store the value read by the read_adc as per the position of POT
    init_config();

    while (1) {
        if (wait-- == 0) { //set the non-blocking delay
            wait = 250;
            adc_reg_val = read_adc(CHANNEL0); //read the adc_reg value 
            duty_cycle = adc_reg_val / 10.23;   //making the POT value in duty_cycle limits i.e less than 100
        }
        //software PWN function call to control the brightness of LED
        software_pwm();         

    }
    return;
}
