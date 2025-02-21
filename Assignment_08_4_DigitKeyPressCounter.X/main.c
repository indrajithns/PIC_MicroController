/*
 * Name : Indrajith
 * File : main.c
 * Description :Implement a 4 digit key press counter.
        Output Requirement:
        Implement a 4 digit key press counter
        On every key press counter value should increment by 1.
        On a long key press (2 seconds), count should reset to zero.
        Inputs:
        DKS1 (Digital Keypad Switch 1) as Count Input 
        DKS1 long press (2 secs) to reset the count 
 */

#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_ssd();
    init_digital_keypad();
}

void main(void) {
    
    static unsigned char digit [] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE}; //MACRO array for lighting the Seven Segment Display for the particular digit.
    unsigned char ssd [] = {ZERO, ZERO, ZERO, ZERO}; //Seven Segment Display data array.
    unsigned char key, reset;
    static unsigned int count = 0, key_pressed_time = 0; //Initialize the Counter as '0' and Timer as '0'.
    init_config(); //To configure the Ports and Pins initially.

    display(ssd); //At the start, the default value shown on SSD is '0'.

    while (1) {
        key = key_press(); //To check if the Digital Key is pressed or not.
        //        key = read_digital_keypad(LEVEL);
        if (key == 1) //If the Key is pressed.
        {
            key_pressed_time += 1; //Start the Timer to store the duration for which the Key is pressed.
        }
        if ((key == 1) && (key_pressed_time > 100)) //If the Key is pressed and the Timer value goes more than 200; it is a Long press.
        {
            count = 0; //The Counter shall be reset.
            reset = 1; //The Reset key shall be set.
        }
        // if ((key == 0) && (reset == 1))		//If the Key is released and Reset key is set, reset the Timer and Reset key for the next Key press.
        if ((!key) && (reset == 1)) {
            key_pressed_time = 0;
            reset = 0;
        }
        // if ((key == 0) && (key_pressed_time > 20 && key_pressed_time < 200))	//If the Key is released and the Timer value lies in the range of 20-200; it is a Short press.
        if ((!key) && (key_pressed_time > 0 && key_pressed_time < 100)) {
            count += 1; //Increment the 'count' by 1.
            key_pressed_time = 0; //Reset the Timer.
        }

        ssd [3] = digit [count % 10]; //Units place digit.
        ssd [2] = digit [(count / 10) % 10]; //Tenth place digit.
        ssd [1] = digit [(count / 100) % 10]; //Hundred place digit.
        ssd [0] = digit [(count / 1000) % 10]; //Thousandth place digit.

        display(ssd); //Display the Counter on Seven Segment Display.

        if (count == 9999) //If the Counter reaches the maximum 4-digit number; reset the Counter.
            count = 0;
    }
}




