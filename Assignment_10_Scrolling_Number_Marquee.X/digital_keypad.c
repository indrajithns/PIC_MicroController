/*
 * File:   digital_keypad.c
*/


#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void) {
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char key_press(void) {
    static unsigned char left = 1, right = 1, stop = 1, start = 1; //To implement Edge-trigger Mechanism for all the 3 Switches.

    if (((KEYPAD_PORT & 0x01) == 0) && (left == 1) && (start == 1)) //If SW1 is pressed, the direction of Marquee shall be Left.
    {
        left = 0;
        return 1;
    } else if (((KEYPAD_PORT & 0x02) == 0) && (right == 1) && (start == 1)) //If SW2 is pressed, the direction of Marquee shall be Right.
    {
        right = 0;
        return 2;
    } else if (((KEYPAD_PORT & 0x04) == 0) && (stop == 1)) //If SW3 is pressed, the Marquee shall Start or Stop.
    {
        stop = 0;
        start = !start;
        return 3;
    } else {
        left = 1;
        right = 1;
        stop = 1;
        return 0;
    }
}
