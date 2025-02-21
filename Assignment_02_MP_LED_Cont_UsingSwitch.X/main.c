/*
 * File:   main.c
 * Author: indra
 * To toggle direction of LED using digital keypad
 * Created on 5 December, 2024, 8:20 PM
 */




#include <xc.h>
#include "main.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)

#define DELAY_TIME 50000

static void init_config(void) {
    /* Turn off LEDs initially */
    LED_ARRAY1 = 0x00;
    
    /* Configure as Output Port */
    LED_ARRAY1_DDR = 0x00;

    /* Initialize digital keypad */    
    init_digital_keypad();
}

void delay(void) {
    unsigned int i;
    for (i = 0; i < DELAY_TIME; i++) {
        // Empty loop for delay
    }
}

// Function to implement Pattern 1: LEDs glow from Top to Bottom and Bottom to Top (without turning off previous LEDs)
void pattern_1(void) {
    unsigned char led_pattern = 0x01;  // Start with the first LED (0x01)

    // Glow LEDs from top to bottom
    for (unsigned char i = 0; i < 8; i++) {
        LED_ARRAY1 |= led_pattern;  // Use OR to keep previous LEDs on
        delay();
        led_pattern <<= 1;          // Shift to the next LED (top to bottom)
    }

    // Turn off all LEDs after top to bottom is complete
    LED_ARRAY1 = 0x00;  // Turn off all LEDs
    delay();

    // Glow LEDs from bottom to top
    led_pattern = 0x80;  // Start with the last LED (0x80)
    for (unsigned char i = 0; i < 8; i++) {
        LED_ARRAY1 |= led_pattern;  // Use OR to keep previous LEDs on
        delay();
        led_pattern >>= 1;          // Shift to the next LED (bottom to top)
    }
}

// Function to implement Pattern 2: LEDs glow from Top to Bottom and switch off from Top to Bottom
void pattern_2(void) {
    unsigned char led_pattern = 0x01;  // Start with the first LED (0x01)

    // Glow LEDs from top to bottom, without turning off previous LEDs
    for (unsigned char i = 0; i < 8; i++) {
        LED_ARRAY1 |= led_pattern;  // Use OR to keep previous LEDs on
        delay();
        led_pattern <<= 1;          // Shift to the next LED (top to bottom)
    }

    // Turn off LEDs from top to bottom, one by one
    led_pattern = 0x01;  // Start with the first LED (0x01)
    for (unsigned char i = 0; i < 8; i++) {
        LED_ARRAY1 &= ~led_pattern;  // Use AND with NOT to turn off the current LED
        delay();
        led_pattern <<= 1;           // Shift to the next LED (top to bottom)
    }
}

void pattern_3(void) {
    /* LEDs blink alternately */
    unsigned char i;
    for (i = 0; i < 10; i++) {  // Run for 10 cycles (or a specific number)
        LED_ARRAY1 = 0x55;  // Pattern 01010101
        delay();
        LED_ARRAY1 = 0xAA;  // Pattern 10101010
        delay();
    }
}

void pattern_4(void) {
    /* LEDs blink in nibbles */
    unsigned char i;
    for (i = 0; i < 10; i++) {  // Run for 10 cycles (or a specific number)
        LED_ARRAY1 = 0xF0;  // First 4 LEDs ON, next 4 OFF
        delay();
        LED_ARRAY1 = 0x0F;  // First 4 LEDs OFF, next 4 ON
        delay();
    }
}

void main(void) {
    unsigned char key;
    
    init_config();

    while(1) {
        /* Read digital keypad value and store it in variable called key */
        key = read_digital_keypad(STATE);
        
        /* Execute pattern based on key press */
        if (key == SW1) {
            /* Pattern 1: Top to bottom and bottom to top without turning off LEDs */
            pattern_1();
            LED_ARRAY1 = 0x00;
        } 
        else if (key == SW2) {
            /* Pattern 2: Top to bottom and off top to bottom */
            pattern_2();
            LED_ARRAY1 = 0x00;
        } 
        else if (key == SW3) {
            /* Pattern 3: Blink alternately */
            pattern_3();
            LED_ARRAY1 = 0x00;
        } 
        else if (key == SW4) {
            /* Pattern 4: Blink in nibbles */
            pattern_4();
            LED_ARRAY1 = 0x00;
        }
    }

    return;
}
