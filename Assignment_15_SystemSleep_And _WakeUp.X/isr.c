/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : isr.c
 *   Title          : ISR Driver
 *   Description    : Module to make ISR work 
 *-----------------------------------------------------------------------------------------------*/

#include <xc.h>

#include "main.h"
unsigned short sleep_flag;
unsigned char key_detected = 0;
extern int a;

void __interrupt() isr(void) {
    static unsigned long int count;
    static unsigned long int count1;

    if (INTF == 1) //To check the External Interrupt.
    {
        key_detected = 1; //Set the 'key_detected'.
        INTF = 0; //To clear the External Interrupt Flag Bit to avoid Recursive interrupts.
    }
    if (TMR0IF == 1) //If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
    {
        TMR0 = TMR0 + 8; //Update the Timer0 register value to maintain the continuity of the count. (TMR0 = TMR0 + 6 + 2 {2 Instruction cycle for the adding operation}).

        if (count++ == 20000) {
            count = 0; //Reset the 'count' as 0.
            if (a < 5) //To blink the LED for 5 times (toggle).
            {
                LED1 = !LED1;
            }
            a++;
        }
    }
    TMR0IF = 0; //To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
}
