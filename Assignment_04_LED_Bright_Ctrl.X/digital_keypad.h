/*Name         : Indra
File          :   digital_keypad.h
Description  : Implement a Point Brightness control using PWM (Timer ISR Based). The LED should dim to a fixed brightness (say 10% Duty Cycle).
Once the user presses a switch the LED should glow at 100% duty cycle for 5 seconds and then after 5 seconds time out, the LED should dim back to 10% duty cycle.
1. As soon as the board is powered on or reset, LED should glow with half brightness (Duty cycle = 10%).
2. On Interrupt, LED should glow with 100% brightness for 5 seconds.
3. After 5 seconds, the LED should go back to 10% brightness.
 */
#ifndef DIGITAL_KEYPAD_H
#define	DIGITAL_KEYPAD_H

/* MACRO for the PORTS and STATES */

#define LEVEL_DETECTION         0
#define LEVEL                   0

#define STATE_DETECTION         1
#define STATE                   1

#define KEYPAD_PORT             PORTB
#define KEYPAD_PORT_DDR         TRISB

#define INPUT_LINES             0x3F

#define SW1                     0x3E
#define SW2                     0x3D
#define SW3                     0x3B
#define SW4                     0x37
#define SW5                     0x2F
#define SW6                     0x1F

#define ALL_RELEASED            INPUT_LINES

unsigned char read_digital_keypad(unsigned char mode);
void init_digital_keypad(void);

#endif	/* DIGITAL_KEYPAD_H */

