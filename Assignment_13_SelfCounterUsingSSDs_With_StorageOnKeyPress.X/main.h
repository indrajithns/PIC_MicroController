/* 
 * File:   main.h
*/

#ifndef MAIN_H
#define MAIN_H


extern void eeprom_write(unsigned char addr, unsigned char value);
extern unsigned char eeprom_read(unsigned char addr);
unsigned char eeprom_test(unsigned int count);


#endif
