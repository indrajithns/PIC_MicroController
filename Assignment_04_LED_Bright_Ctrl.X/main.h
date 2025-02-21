/*Name         : Indra
File          :   digital_keypad.h
Description  : Implement a Point Brightness control using PWM (Timer ISR Based). The LED should dim to a fixed brightness (say 10% Duty Cycle).
Once the user presses a switch the LED should glow at 100% duty cycle for 5 seconds and then after 5 seconds time out, the LED should dim back to 10% duty cycle.
1. As soon as the board is powered on or reset, LED should glow with half brightness (Duty cycle = 10%).
2. On Interrupt, LED should glow with 100% brightness for 5 seconds.
3. After 5 seconds, the LED should go back to 10% brightness.
 */
#ifndef MAIN_H
#define	MAIN_H

/* MACRO for the PORTS and STATES */

#define LED_ARRAY1          PORTD
#define LED_ARRAY1_DDR      TRISD
#define LED1	RD0
#define ON		1
#define OFF		0

#endif	/* MAIN_H */
