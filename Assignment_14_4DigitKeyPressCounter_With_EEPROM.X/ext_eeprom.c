/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : ext_eeprom.c
 *   Title          : External EEPROM - External Interrupt Triggering
 *   Description    : TO generate an external interrupt
 *-----------------------------------------------------------------------------------------------*/
#include "main.h"

/* External EEPROM can be accessed through I2C Communication Protocol */
void write_ext_eeprom(unsigned char address, unsigned char data) {
    i2c_start(); //To initiate the START Condition.
    i2c_write(SLAVE_WRITE_EXT); //To identify the SLAVE by writing it's Address on the BUS along with the R/W bit.
    i2c_write(address); //To write the Memory Address of the SLAVE on which the Data shall be stored.
    i2c_write(data); //To write the Data at the previously sent Memory Address.
    i2c_stop(); //To initiate the STOP Condition.

    for (long int wait = 50000; wait--;); //To implement Blocking Delay.
}

unsigned char read_ext_eeprom(unsigned char address) {
    unsigned char data;

    i2c_start(); //To initiate the START Condition.
    i2c_write(SLAVE_WRITE_EXT); //To identify the SLAVE by writing it's Address on the BUS along with the R/W bit.
    i2c_write(address); //To write the Memory Address of the SLAVE from which the Data shall be read.
    i2c_rep_start(); //To initiate the REPEAT START Condition.
    i2c_write(SLAVE_READ_EXT); //To identify the SLAVE by writing it's Address on the BUS along with the R/W bit.
    /*i edited this*/
    data = i2c_read(1); //read from the buffer register
    //    data = i2c_read(0); //read from the buffer register

    i2c_stop(); //To initiate the STOP Condition.

    return data; //Return the 'data' read from the External EEPROM.
}
