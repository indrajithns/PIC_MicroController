/*------------------------------------------------------------------------------------------------- 			    
* Name         : Indrajith
* File         : main.c
* Description  : Implement a Dynamic Scrolling Number Marquee with Rotation Control.
 *               As soon as the board is powered up or reset, CLCD display the title in the first line
 *              In second line, should prompt for feeding user msg. The cursor should be blinking at rate of 0.5Hz 
 *              (approx non timer implementation) with a default character 0 .Let's call this as preset mode
               You should be able to set the required digit with the help of Up / Left or Down / Right Key
                On selection of the required char you should press the Accept Key and move the cursor to the 
 *              next location.
               On entering the required message you could start the Marquee using Start / Stop Key.
                The default direction should be from left to right for first character position, You may change 
 *              the scroll direction using Up / Left or Down / Right Key
                The Start / Stop Key could be used to Stop the scroll
                One press of the Edit Key any instance the system should enter to Preset Mode
                In preset mode the Backspace Key is used to remove the accepted characters
 *-----------------------------------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

char temp; /* Temp variable to store the backup of msg */
char msg[] = "000000000"; /* Hardcoded msg to be scrolled on the CLCD */

static void init_config(void) {
    init_matrix_keypad();
    init_clcd(); /* Initialization of CLCD function */
}

void update_clcd_msg(int count) {
    if (count < 0)
        count = 0;
    if (count > 9999)
        count = 0;

    // Update individual characters in msg
    msg[7] = '0' + count % 10;
    count /= 10;
    msg[6] = '0' + count % 10;
    count /= 10;
    msg[5] = '0' + count % 10;
    count /= 10;
    msg[4] = '0' + count % 10;

    // Clear the CLCD
    CLEAR_DISP_SCREEN; // Assuming a macro or function to clear the CLCD

    // Update the CLCD characters
    for (int i = 4; i <= 7; i++) {
        clcd_putch(msg[i], LINE2(i));
    }
}

void main(void) {
    init_config();
    clcd_print("Enter a number", LINE1(0)); /* Hardcoded msg to display on CLCD for right scrolling in LINE0 */
    clcd_print("msg:", LINE2(0));
    unsigned char key;
    static int count = 0; // Start count from 0
    int run_edit_flag = 0; // Edit mode initially disabled
    int right_marquee = 1;
    int left_marquee = 0;

    while (1) { /* Super loop to run the operation indefinitely */
        temp = msg[8]; // 9 characters, so use index 8 (0-based index)

        key = read_matrix_keypad(STATE);
        if (!run_edit_flag) { // If not in edit mode
            if (key == SW1) { /* Increment the count for SW1 */
                if (count < 9) {
                    count++;
                } else {
                    count = 0;
                }
                update_clcd_msg(count);
            } else if (key == SW2) { /* Decrement the count for SW2 */
                if (count > 0) {
                    count--;
                } else {
                    count = 9;
                }
                update_clcd_msg(count);
            } else if (key == SW5) { // Enter edit mode
                run_edit_flag = 1;
            }
        } else { // In edit mode
            if (key == SW6) { // Backspace
                count = count / 10;
                update_clcd_msg(count);
            } else if (key == SW5) { // Accept edit
                run_edit_flag = 0;
            }
        }

        if (key == SW3) { // Toggle scrolling direction
            int len = strlen(msg);
            if (right_marquee) {
                temp = msg[len - 1];
                right_marquee = 0;
                left_marquee = 1;
                CLEAR_DISP_SCREEN; // Assuming a macro or function to clear the CLCD
                for (int i = len - 1; i > 0; i--) {
                    msg[i] = msg[i - 1];
                    clcd_putch(msg[i], LINE2(i));
                }
                msg[0] = temp;
            } else if (left_marquee) { /* Start left marquee */
                temp = msg[0];
                right_marquee = 1;
                left_marquee = 0;
                CLEAR_DISP_SCREEN; // Assuming a macro or function to clear the CLCD
                for (int i = 0; i < len - 1; i++) {
                    msg[i] = msg[i + 1];
                    clcd_putch(msg[i], LINE2(i));
                }
                msg[len - 1] = temp;
            }
        }
    }
    return;
}
