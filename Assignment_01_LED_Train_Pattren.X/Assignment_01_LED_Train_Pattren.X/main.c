/*
 * File:   main.c
 * Author: indra
 *
 * Created on 21 October, 2024, 11:36 PM
 */


#include <xc.h>
#pragma config WDTE = OFF


/* function to configure the led */
void init_config()
{
    TRISB = 0x00; //set direction as output
    PORTB = 0x00; //set all LEDs in OFF State
}
void main(void) {
    /* function call to configure the led's */
    init_config();  
    
    unsigned int x = 0, flag = 0; //declare variable to add delay   
    while(1)
    {
        if(x++ == 50000) //condition for delay
        {
            x = 0;           //clear a delay variable for next delay 
            if(flag >= 1 && flag <= 8) //condition to turn on all the LEDs from left to right
            {
                PORTB = (PORTB << 1) | 1; //turn on the LEDs one by one
            }
            else if(flag >= 9 && flag <= 16) //condition to turn off all the LEDs from left to right
            {
                PORTB = PORTB << 1; //turn off the LEDs one by one
            }
            else if(flag >= 17 && flag <= 24) //condition to turn on all the LEDs from right to left
            {
                PORTB = (PORTB >> 1) | 128; //turn on the LEDs one by one
            }
            else if(flag >= 25 && flag <= 32) //condition to turn off all the LEDs from right to left
            {
                PORTB = PORTB >> 1; //turn off the LEDs one by one
            }
            else
            {
                flag = 0; //to continue the process until the disconnection of power
            }
            flag++; //to perform the function of LEDs
        }
    }
}
