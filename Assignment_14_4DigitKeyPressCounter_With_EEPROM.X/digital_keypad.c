/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : digital_keypad.c
 *   Title          : Digital Keypad 
 *   Description    : A digital keypad module providing both level and edge triggering
 *                    functions
 *-----------------------------------------------------------------------------------------------*/
#include "main.h"

void init_digital_keypad(void) {
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(void) {
    /*The Digital Keypad are connected in a Pull Up circuit. So, if the Switch is pressed; the value at the Pin shall be 0.*/
    if ((KEYPAD_PORT & 0x01) == 0) /*checking for SW1*/
        return 1;
    else if ((KEYPAD_PORT & 0x02) == 0) /*checking for SW2*/
        return 2;
    else
        return 0;
}
