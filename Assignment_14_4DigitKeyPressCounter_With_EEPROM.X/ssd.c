/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : ssd.c
 *   Title          : to implement ssd 
 *-----------------------------------------------------------------------------------------------*/
#include "main.h"

void init_ssd(void) {
    /* Seeting the SSD data line as Output */
    SSD_DATA_PORT_DDR = 0x00; //RD0-RD7  i mean abcdefgh

    /* Setting SSD Control Line as Output (RA5 - RA2) */
    SSD_CONTROL_PORT_DDR = SSD_CONTROL_PORT_DDR & 0x03;
    //we need to turn OFF only RA2 to RA5
    //xx00 00xx
    SSD_CONTROL_PORT = SSD_CONTROL_PORT & 0x03; //xx00 0011 RA7 6 RA5(0) RA4(0) RA3(0) RA2(0) RA1(1) RA1(1) 
}

void display(unsigned char data[]) {
    unsigned char digit;

    for (digit = 0; digit < MAX_SSD_CNT; digit++) {
        SSD_DATA_PORT = data[digit];
        //with this condition, for 0th iteration RA1 will be on and for 1th iteration RA3 will be on and so on..
        SSD_CONTROL_PORT = (SSD_CONTROL_PORT & 0x03) | (0x04 << digit);

        for (unsigned long int wait = 400; wait--;);
    }
}

void display_ssd(unsigned int count) {
    // Implementation of the function
}