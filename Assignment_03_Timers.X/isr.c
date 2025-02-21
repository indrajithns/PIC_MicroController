/*
 * File:   isr.c
 * Author: indra
 *
 * Created on 7 December, 2024, 6:41 PM

 * Description : Implement the time separator with Timer 0, Timer 1 and Timer 2
 */
#include <xc.h>
#include "main.h"

/* Interrupt function  */
void __interrupt() isr(void)
{
	static unsigned short count1,count2,count3;     //declare count variables to give delay 
     
	if (TMR0IF)                                     //check whether interrupt occured or not
	{
		TMR0 = TMR0 + 8;                           //adding timer in order to not to miss any ticks 

		if (count1++ == 20000)                     //after certain delay toggle Led1
		{
			count1 = 0;                            
			LED1 = !LED1;                         //toggle the LED1
		}
		TMR0IF = 0;                               //set back flag to 0 to avoid function call again and again 
	} 
	if (TMR1IF)                                 //check whether interrupt occured or not
	{
		TMR1 = TMR1 + 3038;                     //adding timer in order to not to miss any ticks for timer1

		if (count2++ == 80)                     //after certain delay toggle Led2
		{
			count2 = 0;
			LED2 = !LED2;                       //toggle LED2      
		}
		TMR1IF = 0;                             //set back flag to 0 to avoid function call again and again
	}
    if (TMR2IF)
	{
		//TMR2 = TMR2 + 8;

		if (count3++ == 20000)
		{
			count3 = 0;
			LED3 = !LED3;
		}
		TMR2IF = 0;
	}
}

