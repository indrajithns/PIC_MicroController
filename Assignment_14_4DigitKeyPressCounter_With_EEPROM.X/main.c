/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : main.c
 *   Description    : Implement a 4 digit key press counter.Implement a 4 digit key press counter
                      On every key press counter value should increment by 1.On a long key press (2 seconds), 
                      count should reset to zero.
                      Inputs:
                      DKS1 (Digital Keypad Switch 1) as Count Input 
                      DKS1 long press (2 secs approx) to reset the count 
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "main.h"
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned char eeprom_test(unsigned int count) {
    /* Store the count value in the internal EEPROM */
    /* In SSD, the MSB bit will be represented on the left-most side */
    write_ext_eeprom(0x01, (count / 1000)); /* Storing the thousands place at 0x01 */
    write_ext_eeprom(0x02, (count / 100) % 10); /* Storing the hundreds place at 0x02 */
    write_ext_eeprom(0x03, (count / 10) % 10); /* Storing the tens place at 0x03 */
    write_ext_eeprom(0x04, (count % 10)); /* Storing the units place at 0x04 */
    write_ext_eeprom(0x00, 1); /* occupying the 0x00 address to say the data is written into EEPROM */
}

static void init_config(void) { //initial declaration function of ssd and digital keypad
    init_ssd();
    init_digital_keypad();
    init_i2c(100000); //To initialize the Basic Configuration for I2C Communication.

}

static unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE}; //MACRO array for lighting the Seven Segment Display for the particular digit.
unsigned char ssd[MAX_SSD_CNT] = {ZERO, ZERO, ZERO, ZERO}; //Seven Segment Display data array.

void main(void) {

    unsigned char key;
    static unsigned int key_pressed_time; //Initialize the Counter as '0' and Timer as '0'.
    int once = 0;
    static unsigned int count; /*initial values of a static variables will be 0*/

    init_config(); //To configure the PORT and PINS initially.

    if (read_ext_eeprom(0x00) == 1) {
        count = read_ext_eeprom(0x01)*1000 + read_ext_eeprom(0x02)*100 + read_ext_eeprom(0x03)*10 + read_ext_eeprom(0x04);
    } else {
        count = 0;
    }
    display_ssd(count); //To initialize the 'ssd' array with the value of 'count' mapped to the corresponding MACRO of the SSD.

    while (1) {

        key = read_digital_keypad(); //To detect the Key Press.

        /* If the SW1 is pressed, then increment the 'count' and if the SW1 is long pressed, then make reset the 'count' to 0 */
        if (key == 1) {
            key_pressed_time++; //If the SW1 is pressed, increment the 'key_pressed_time' to judge if it is a Short Press or Long Press.
        }
        if (key == 1 && key_pressed_time > 100) //long press,If the SW1 is pressed and 'key_pressed_time' becomes greater than 100; it is a Long Press.
        {
            count = 0; //Reset the 'count' to 0.
            once = 1;
        }
        if ((!key) && (once == 1)) { //if key released then reset, making the key_pressed_time to 0
            key_pressed_time = 0;
            once = 0;
        }
        if ((!key) && (key_pressed_time > 0 && key_pressed_time < 100)) { //if key not released and key pressed time is like to increment count, then increment count
            count += 1; //Increment the 'count' by 1.
            key_pressed_time = 0; //Reset the Timer.
        }
        if (key == 2) {
            eeprom_test(count); /* Store the current count in EEPROM */
        }

        /* Assume count = 4579, then apply the below logic to display on SSD */
        ssd[0] = digits[count / 1000]; /* Thousands place - first digit*/
        ssd[1] = digits[(count / 100) % 10]; /* Hundreds place - second digit*/
        ssd[2] = digits[(count / 10) % 10]; /* Tens place - third digit*/
        ssd[3] = digits[count % 10]; /* Units place -  last digit*/

        display(ssd); /* Function call to display the counter values on SSD */
    }
}

