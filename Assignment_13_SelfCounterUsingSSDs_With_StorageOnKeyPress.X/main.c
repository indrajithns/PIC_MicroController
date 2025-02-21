/*-------------------------------------------------------------------------------------------------
 *   Author         : Indrajith
 *   File           : main.c
 *   Title          : Self counter using SSDs with storage EEPROM on key press
 *   Description    :  As soon as the board is powered up or reset, counter should start self incrementing at rate of 1Hz from 0000 up to 9999 and then roll of to 0000 (Approximately, Non Timer Implementation).
                       On save key press, count value should be  stored in internal EEPROM.
                       On subsequent power ups or reset the counter should start from the previous stored value.
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"
#include "main.h"
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)

unsigned char eeprom_test(unsigned int count) {
    /* Store the count value in the internal EEPROM */
    /* In SSD, the MSB bit will be represented on the left-most side */
    eeprom_write(0x01, (count / 1000)); /* Storing the thousands place at 0x01 */
    eeprom_write(0x02, (count / 100) % 10); /* Storing the hundreds place at 0x02 */
    eeprom_write(0x03, (count / 10) % 10); /* Storing the tens place at 0x03 */
    eeprom_write(0x04, (count % 10)); /* Storing the units place at 0x04 */
    eeprom_write(0x00, 1); /* Mark EEPROM as written */
}

static void init_config(void) {
    /* Initialization of digital keypad (DKP) and seven-segment display (SSD) */
    init_digital_keypad();
    init_ssd();
}

void main(void) {
    unsigned char key; /* Declaration of local variables */
    static unsigned int count; /*static variables take initial vlaues 0*/
    unsigned int wait = 100;

    /* Storing the value to start the counter when SW2 is pressed */
    if (eeprom_read(0x00) == 1) {
        count = eeprom_read(0x01) * 1000 + eeprom_read(0x02) * 100 + eeprom_read(0x03) * 10 + eeprom_read(0x04);
    } else {
        count = 0;
    }

    unsigned char ssd[MAX_SSD_CNT] = {ZERO, ZERO, ZERO, ZERO};
    unsigned char digits[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

    /* Initialize the configuration (e.g., DKP and SSD) */
    init_config();

    while (1) {
        if (wait-- == 0) { /* Creating a non-blocking delay */
            wait = 100;
            if (count < 9999) {
                count++;
            } else if (count == 9999) {
                count = 0;
            }
        }

        key = read_digital_keypad(STATE); /* Read the SW2 press */
        if (key == SW2) {
            eeprom_test(count); /* Store the current count in EEPROM */
        }

        /* Assume count = 4579, then apply the below logic to display on SSD */
        ssd[0] = digits[count / 1000]; /* Thousands place */
        ssd[1] = digits[(count / 100) % 10]; /* Hundreds place */
        ssd[2] = digits[(count / 10) % 10]; /* Tens place */
        ssd[3] = digits[count % 10]; /* Units place */

        display(ssd); /* Function call to display the counter values on SSD */
    }

    return;
}
