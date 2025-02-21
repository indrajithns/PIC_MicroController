/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indrajith
 *   File           : external_interrupt.c
 *   Title          : External Interrupt Configuration
 *   Description    : A configuration function to detect rising edge signal
 *-----------------------------------------------------------------------------------------------*/

#include <xc.h>
#include "main.h"

void init_ext_int(void) {
    /* Selecting Falling Edge Trigger */
    INTEDG = 0;
    /* Enable the External Interrupt */
    INTE = 1;
}
