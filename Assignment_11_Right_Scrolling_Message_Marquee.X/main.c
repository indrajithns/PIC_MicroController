/*
 * Name : Indrajith
 * File : main.c
 * Description : As soon as the board is powered up or reset, a static message (hardcoded) should start scrolling from left to right CLCD. 
        The scroll should repeat indefinitely. 
        The scroll frequency should be 0.5Hz (Approximately, Non Timer Based).
*/

#include <xc.h>
#include "clcd.h"

#pragma config WDTE = OFF       /* Watchdog Timer Enable bit (WDT disabled) */

void main(void) {
    init_clcd(); /*Initialization of CLCD function*/

    char temp; /*Temp variable to store the backup of msg*/
    char msg[] = "__GOOD MORNING__"; /*hardcoded msg to be scrolled on the CLCD*/
    clcd_print("Right Scrolling", LINE1(0)); /*Hardcoded msg to display on CLCD for right scrolling in LINE0*/

    while (1) { /*super loop to run the operation indefinitely*/
        temp = msg[15];
        for (int i = 15; i > 0; i--) {
            msg[i] = msg[i - 1];
        }
        msg[0] = temp;
        clcd_print(msg, LINE2(0)); /*Hardcoded msg to display on CLCD for right scrolling in LINE1*/
    }
    return;
}