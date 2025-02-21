/*
 * Filename : timer.c
 Name       : Indra
Description : To implement the 1 sec Timer.
 */
#include <xc.h> // include processor files - each processor file is guarded.  
#include"timer.h"

void init_timer(void) {

    TMR2ON = 1;
    PR2 = 250;
    TMR2IF = 0;
}
