
/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : main.c
 *   Assignment     : A16- Implement a message display using UART and CLCD
 *   Description    : Any message typed on the host system should be shown in a CLCD.
                        On completion of the first line it should start on the second line.
                        One full screen the second line should be moved to first line.
                        Setup required
                        Host with a serial application (minicom in Linux, Teraterm in Windows).
                        Baud  rate of 9600, No parity and 8 data bits.
 *-----------------------------------------------------------------------------------------------*/
#include <xc.h>
#include "uart.h"
#include "clcd.h"
#include <string.h>

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_uart(9600); /*configuring the uart with a baud rate of 9600*/
    init_clcd(); /*configuring the CLCD*/
}

void main() {
    init_config(); /*calling the initial declaration function*/

    unsigned char flag = 1; // Flag to switch between LINE1 and LINE2 of the CLCD
    unsigned char ch; // Variable to store the input character
    unsigned char i = 0; // Index to track the position in the CLCD line
    unsigned char line_1[17]; // Array to store characters on LINE-1 of the CLCD
    unsigned char line_2[17] = "                "; // Array to store characters on LINE-2 of the CLCD

    while (1) {
        ch = getchar();
        putchar(ch); // Transmit the received character back to the laptop.

        if ((i < 16) && (flag == 1)) {
            // Display the character on LINE-1 of the CLCD at position 'i'.
            clcd_putch(ch, LINE1(i));
            i += 1; // Increment the index for the next character on LINE-1.

            if (i == 16) {
                i = 0; // Reset the index when LINE-1 is full.
                flag = 2; // Switch to LINE-2 for the next character.
            }
        } else if ((i < 16) && (flag == 2)) {
            line_1[i] = ch; // Store the character in LINE-2 in 'line_1'.
            clcd_putch(ch, LINE2(i)); // Display the character on LINE-2 at position 'i'.
            i += 1; // Increment the index for the next character on LINE-2.

            if (i == 16) {
                i = 0; // Reset the index when LINE-2 is full.
                clcd_print(line_1, LINE1(0)); // Shift characters from LINE-2 to LINE-1.
                clcd_print(line_2, LINE2(0)); // Clear LINE-2 for the next character.
            }
        }
    }
}