/*------------------------------------------------------------------------------------------------- 
 *   Author         : Indrajith
 *   File           : main.c
 *   Title          : Implement a 8 field password access to screen. The user has to enter a key press
 *                    pattern to unlock the Easter egg. If the user succeeds in unlocking the screen, 
 *                    The will be able to read the message. On failure attempt the LED will blink faster for every attempt. 
 *                    The max attempt would be 5.
 *   Description    : As soon as the board is powered up or reset, CLCD display the title in the first line.
                      In second line, an ?_? (underscore) should blink at rate of 0.5Hz to display the password entry which is indicated as ?*? (star).
                      Combination of Key1 and Key2 has to be used as a password.
                      You should provide a max if 5 chances to unlock the system.
                      On every wrong entry an LED should blink constant rate
                      The rate of blink doubles on every failure attempt.
                      On the fifth failure attempt the LED should glow constant and a message has to be put on screen indicating failure.
                      You have to reset the board to retry.
                      On a successful attempt the Embedded message should be displayed on screen.
 *-----------------------------------------------------------------------------------------------*/


#include <xc.h>
#include "clcd.h"
#include "main.h"
#include "matrix_keypad.h"
#include "isr.h"
#include "timers.h"

#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)

extern unsigned short blink; //blink is aactually updated in the ISR function
unsigned int flag = 1;

void read_input(void) {
    char actual_password[] = "000000000"; //Actual Password.
    char user_password[9];
    static unsigned long delay;
    static unsigned char i;
    static unsigned char j; /*these i,j,k are used nowhere except in this file so used static*/
    static unsigned char k;
    static unsigned int matched = 1;
    static unsigned char attempts = 0; //To store the Number of Password Attempts.
    unsigned char key;
    unsigned char number_entered = 0;


    if (j < 9) //To read the 9-field Password from the User.
    {
        clcd_print(" Enter Password ", LINE1(0));

        key = read_matrix_keypad(STATE); //To read the Key Press.
        if (key != ALL_RELEASED) //If any of the Key is pressed.
        {
            if (key == SW1 || key == SW2) //If the SW1 or SW2 is pressed, read the Password as '0' or '1' based on the corresponding Key press.
            {
                if (key == SW2) //If the SW2 is pressed, read '1'.

                    number_entered = 1;
            }
            user_password[j] = number_entered + '0'; //Otherwise, read '1'.

            clcd_putch(0x2A, LINE2(j + 3)); //Display '*' to hide the Password while reading and print from the center
            j++;
            i++;
        }
        /*Code to validate the actual_password*/
        if (j == 9) //If the 9-field Password is read from the User.
        {
            if (attempts++ < 5) //If the Password Attempts are left
            {
                for (k = 0; k < 9; k++) //The loop shall run to check if the Password read is matching with the actual Password.
                {
                    if (user_password[k] != actual_password[k]) //If the Password doesn't matches, display the Error messages.
                    {
                        clcd_print("                    ", LINE2(0));
                        clcd_putch(attempts + '0', LINE2(1));
                        clcd_print("Attempts left", LINE2(3));
                        for (delay = 5000; delay--;);
                        clcd_print("                    ", LINE2(0));
                        matched = 0;
                        i = 0;
                        j = 0;
                        flag++;
                        break;
                    }
                }
                if (matched == 1) //If the Password matches, display the Successful message and turn OFF the LED.
                {
                    LED1 = 0;
                    CLEAR_DISP_SCREEN;
                    clcd_print("Successful! You", LINE1(0));
                    clcd_print("cracked the code", LINE2(0));
                }
            } else //If there are no more Attempts left, display the Error message.
            {
                CLEAR_DISP_SCREEN;
                clcd_print("Password Failed", LINE1(0));
                clcd_print("Reset the Board", LINE2(0));
            }
        }
    }
    /*code to blink the LED*/
    if (i < 9) {
        if (blink == 120) //If 'blink' reaches 120; reset the 'blink' to 0.
            blink = 0;
        else if (blink % 2 == 0) //If the 'blink' is an Even value, display the '_'.
        {
            clcd_putch(0x5F, LINE2(i + 3)); /*hexadecimal value for '_' */
        } else if (blink % 2 == 1) //If the 'blink' is an Odd value, display the space.
        {
            clcd_putch(0xFE, LINE2(i + 3)); /*hexadecimal value for space*/
        }
        if (flag >= 2) //If the 'flag' is greater than equal to 2; Toggle the LED based on the 'blink' value.
        {
            if (blink % 2 == 0) //If the 'blink' is an Even value, turn ON the LED.
                LED1 = 1;
            else //If the 'blink' is an Odd value, turn OFF the LED.
                LED1 = 0;
            if (flag == 6) //If the 'flag' is 6; turn ON the LED irrespective of the 'blink'.
                LED1 = 1;
        }
    }
}

/* Basic Configuration */
void init_config(void) {
    init_matrix_keypad();
    init_clcd();
    init_timer0();
    LED1 = 0;
    GIE = 1;
    PEIE = 1; //peripheral int enable bit 

}

void main(void) {
    init_config(); /*calling the initial declaration function*/

    while (1) {
        read_input(); /*call the function repeatedly*/
    }
}
