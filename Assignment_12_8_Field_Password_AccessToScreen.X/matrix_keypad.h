/*
 * File: matrix_keypad.h
*/

#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include <xc.h>

// Define the matrix keypad ports and pins
#define MATRIX_KEYPAD_COLUMN_PORT PORTB
#define MATRIX_KEYPAD_ROW_PORT PORTD
#define MATRIX_KEYPAD_COLUMN_PORT_DDR TRISB
#define MATRIX_KEYPAD_ROW_PORT_DDR TRISD

// Define individual row pins
#define ROW1 PORTDbits.RD0
#define ROW2 PORTDbits.RD1
#define ROW3 PORTDbits.RD2
#define ROW4 PORTDbits.RD3

// Define individual column pins
#define COL1 PORTBbits.RB0
#define COL2 PORTBbits.RB1
#define COL3 PORTBbits.RB2

// Define high and low for readability
#define HI 1
#define LOW 0

// Function declarations
void init_matrix_keypad(void);
char read_matrix_keypad(void);

#endif /* MATRIX_KEYPAD_H */
