/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : main.c
 *   Title          : A09- Implement a temperature sensor node with CLCD displayAssignment
 *   Description    : As soon as the board is powered up or reset, a static message (hardcoded) 
 *                    should start scrolling from left to right CLCD.The scroll should repeat indefinitely. 
                      The scroll frequency should be 0.5Hz (Approximately, Non Timer Based).
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "clcd.h"
#include "adc.h"

#pragma config WDTE = OFF       /* Watchdog Timer Enable bit (WDT disabled) */

static void init_config(void) {
    init_clcd(); /*Initialization of CLCD function*/
    init_adc(); /*Initialization of ADC function*/

    clcd_print("TEMPERATURE", LINE1(3)); /*Hardcoded msg to display on CLCD for right scrolling in LINE0*/
}

void main(void) {
    init_config(); /*calling function for initialization*/
    unsigned short adc_reg_val;
    unsigned int val;

    while (1) { /*super loop to run the operation indefinitely*/
        adc_reg_val = read_adc(CHANNEL0); /*as our PIC16F877A uses channels 0-4, i used 0*/

        val = (adc_reg_val * 500) / 1024;   /*forumula to convert the ADC value into Degree Celsius.*/ 
        /* Print the value on CLCD */
        clcd_putch(((val / 10) % 10) + '0', LINE2(5)); /*geting the units place*/
        clcd_putch((val % 10) + '0', LINE2(6)); /*getting the ten's place*/
        clcd_print(".0", LINE2(7)); /*printing .0 on the clcd*/
        clcd_putch(0xDF, LINE2(9)); /*printing degree symbol*/
        clcd_print("C", LINE2(10)); /*printing the Celcius symbol*/

    }
    return;
}

