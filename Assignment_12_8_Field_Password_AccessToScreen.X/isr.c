/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : isr.c
 *   Title          : ISR Driver
 *   Description    : Module to make ISR work 
 *-----------------------------------------------------------------------------------------------*/

#include <xc.h>
#include "main.h"
#include "timers.h"

extern unsigned int flag;
unsigned short blink;

void __interrupt() isr(void) {
    static unsigned short count;

    if (TMR0IF == 1) //If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
    {
        TMR0 = TMR0 + 8; //Update the Timer0 register value to maintain the continuity of the count. (TMR0 = TMR0 + 6 + 2 {2 Instruction cycle for the adding operation}).

        if (count++ == 20000) {
            blink++; //Increment the 'blink' for Blinking the Cursor.
            count = 0; //Reset the 'count' as 0.
        }
    }
    TMR0IF = 0; //To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
}
