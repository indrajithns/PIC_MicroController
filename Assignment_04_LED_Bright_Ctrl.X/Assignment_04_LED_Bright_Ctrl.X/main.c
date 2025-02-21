/*
Name         : Indra
Description  : Implement a Point Brightness control using PWM (Timer ISR Based). The LED should dim to a fixed brightness (say 10% Duty Cycle).
Once the user presses a switch the LED should glow at 100% duty cycle for 5 seconds and then after 5 seconds time out, the LED should dim back to 10% duty cycle.
1. As soon as the board is powered on or reset, LED should glow with half brightness (Duty cycle = 10%).
2. On Interrupt, LED should glow with 100% brightness for 5 seconds.
3. After 5 seconds, the LED should go back to 10% brightness.
 */

#include<xc.h>
#include "main.h"
#include "digital_keypad.h"
#include "timer.h"

extern unsigned int flag;
unsigned int duty_cycle = 50;
unsigned int PERIOD = 100;
unsigned int long loop_counter = 0;

static void init_config(void) {
    /* Basic Configuration for all the PORTS and other Peripherals */
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    init_digital_keypad();
    init_timer2();
    TMR2IF = 0; //To clear the Timer2 Overflow Interrupt Flag Bit.
    GIE = 1;
    PEIE = 1;
}

void main(void) {
    unsigned char key;
    init_config();

    while (1) {
        /* Reading SW from Digital Keypad */
        key = read_digital_keypad(STATE);

        if (flag == 1 || key == SW1) {
            if (key == SW1) //If the SW1 is pressed, then make the Duty Cycle as 100 percent.
            {
                duty_cycle = PERIOD; //100
            } else {
                duty_cycle = 10; //Otherwise, make the Duty Cycle as 10 percent.
            }
            flag = 0;
        }
    }
}
