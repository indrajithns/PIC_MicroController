/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : matrix_keypad.c
 *   Title          : Digital Keypad - Level Triggering
 *   Description    : A digital keypad module providing both level and edge triggering
 *                    functions
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h> 
#include "matrix_keypad.h"

void init_matrix_keypad(void) {
    // Setting the Columns (RB2 - RB0) as Inputs
    MATRIX_KEYPAD_COLUMN_PORT_DDR |= 0x07; // TRISB |= 0x07

    // Setting the Rows (RD3 - RD0) as Outputs
    MATRIX_KEYPAD_ROW_PORT_DDR &= 0xF0; // TRISD &= 0xF0

    // Enabling PORTB Pullups
    nRBPU = 0;

    // Making all Rows HIGH to start with
    ROW1 = HI;
    ROW2 = HI;
    ROW3 = HI;
    ROW4 = HI;
}

static unsigned char scan_keypad(void) {
    unsigned char key = ALL_RELEASED;

    // Check each row for a key press
    for (int row = 0; row < 4; row++) {
        // Set all rows HIGH
        ROW1 = HI;
        ROW2 = HI;
        ROW3 = HI;
        ROW4 = HI;

        // Activate the current row
        switch (row) {
            case 0: ROW1 = LOW; break;
            case 1: ROW2 = LOW; break;
            case 2: ROW3 = LOW; break;
            case 3: ROW4 = LOW; break;
        }

        // Short delay to stabilize
        for (volatile int i = 100; i--;); // Simple delay loop

        // Check each column for a key press
        if (COL1 == LOW) {
            switch (row) {
                case 0: key = 1; break;
                case 1: key = 4; break;
                case 2: key = 7; break;
                case 3: key = '*'; break;
            }
            break; // Exit the loop as key is detected
        }
        if (COL2 == LOW) {
            switch (row) {
                case 0: key = 2; break;
                case 1: key = 5; break;
                case 2: key = 8; break;
                case 3: key = 0; break;
            }
            break;
        }
        if (COL3 == LOW) {
            switch (row) {
                case 0: key = 3; break;
                case 1: key = 6; break;
                case 2: key = 9; break;
                case 3: key = '#'; break;
            }
            break;
        }
    }

    // Set all rows HIGH after scanning
    ROW1 = HI;
    ROW2 = HI;
    ROW3 = HI;
    ROW4 = HI;

    return key;
}

unsigned char read_matrix_keypad(unsigned char mode) {
    static unsigned char once = 1;
    unsigned char key;

    key = scan_keypad(); // 0 1 2 3 4 5 6 7 8 9 '*' '#' ALL_RELEASED

    if (mode == LEVEL) {
        return key;
    } else { // EDGE-triggered mode
        if ((key != ALL_RELEASED) && once) {
            once = 0;
            return key;
        } else if (key == ALL_RELEASED) {
            once = 1;
        }
    }

    return ALL_RELEASED;
}

