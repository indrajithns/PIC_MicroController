/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : main.c
 *   Description    : A15 - Implement system sleep and wake up while Interrupt on change
                      As soon as the board is powered up or reset, a message (say 1234) should be displayed in SSD.
                      A LED is toggled  every second.
                      System should go into sleep mode if no activity is detected.
                      System should wake up from sleep on detecting interrupt key. 
 *-----------------------------------------------------------------------------------------------*/

#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

extern unsigned char key_detected;

static void init_config(void) {

    LED_ARRAY1 = 0x00; //PORTB
    LED_ARRAY1_DDR = 0x00; //TRSISB
    LED1 = OFF; /*Putting LED in OFF state initially */
    init_timer0();
    init_ext_int();
    init_ssd();
    /* Enable all the Global Interrupts */
    GIE = 1;

    PEIE = 1; //peripheral int enable bit 

}
int a = 0;

void main(void) {
    init_config();
    unsigned char ssd[MAX_SSD_CNT];
    unsigned short flag = 0;

    while (1) {
        if (flag == 0) { /*as the start of the program, display the SSD*/
            ssd[0] = ONE;
            ssd[1] = TWO;
            ssd[2] = THREE;
            ssd[3] = FOUR;
            display(ssd); /*calling the display ssd function*/

            if (a == 5) //If the 'a' is 5, make the 'flag' as 1 and change to Sleep mode, value updated from the isr.
            {
                a = 0;
                flag = 1;
                display(0);
                SLEEP(); //To make the Controller to Sleep.
            }
        }
        if (key_detected) { /*when the key is detected, set the flag to 0 and reset the values*/
            key_detected = 0;
            a = 0;
            flag = 0;
        }
    }
    return;
}