/*
 * Author: Indrajith
 * File:   main.c
*/


#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_digital_keypad();
    init_ssd();
}

void main(void) {
    static unsigned char key;
    unsigned char count = 0, opt = 1, flag, flag_count = 0, prev;
    unsigned int wait1 = 1, wait2 = 1;
    unsigned char ssd[MAX_SSD_CNT] = {ZERO, ZERO, ZERO, ZERO};
    unsigned char digit[12] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, BLANK, BLANK};
    //     0     1   2    3       4     5    .......................
    init_config();

    while (1) {
        if (wait1++ == 100) //To generate the Non-Blocking delay.
        {
//            flag = read_digital_keypad(STATE); //To store the Key press.
            flag = key_press();
            if (flag == 1 || flag == 2) //If the SW1 or SW2 is pressed.
            {
                if (flag != opt) //If the Direction has changed, the 'opt' and 'count' shall be updated.
                {
                    if (flag == 2)
                        count += 1;
                    else
                        count -= 1;
                }
                opt = flag;
            }
            if (flag == 3) //If the SW3 is pressed, the Marquee shall be Started or Stopped.
            {
                flag_count += 1; //The 'flag_count' shall be incremented.
                if (flag_count % 2 == 1) //If the 'flag_count' value is Odd, store the Direction of the Marquee in 'prev'.
                {
                    prev = opt;
                    opt = flag; //The 'opt' shall be updated to Stop the Marquee.
                } else //If the 'flag_count' value is Even, the previous Direction of the Marquee shall be updated to 'opt'.
                {
                    flag_count = 0; //Reset the 'flag_count'.
                    opt = prev;
                }
            }
            wait1 = 1; //Reset the 'wait'.
        }
        if (wait2++ == 100) //To implement the Non-Blocking delay.
        {
            if (opt == 1) //To generate the Left Marquee.
            {
                if (count == 12)
                    count = 0;
                ssd [0] = digit [count % 12];
                ssd [1] = digit [(count + 1) % 12];
                ssd [2] = digit [(count + 2) % 12];
                ssd [3] = digit [(count + 3) % 12];

                count += 1;
                wait2 = 1;
            } else if (opt == 2) //To generate the Right Marquee.
            {
                if (count < 3)
                    count = 16 - count;
                ssd [3] = digit [count % 12];
                ssd [2] = digit [(count - 1) % 12];
                ssd [1] = digit [(count - 2) % 12];
                ssd [0] = digit [(count - 3) % 12];

                count -= 1;
                wait2 = 1;
            } else if (opt == 3) //To Stop the Marquee.
            {
                wait2 = 1;
            }
        }
        display(ssd);

    }

    return;
}