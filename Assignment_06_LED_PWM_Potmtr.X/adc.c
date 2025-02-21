/*------------------------------------------------------------------------------------------------- 			    
 *   Author         : Indra
 *   File           : adc.c
 *   Title          : ADC Driver
 *   Description    : Module to scan analog channel 
 *-----------------------------------------------------------------------------------------------*/
#include<xc.h>
void init_adc(void)
{
	/*starting the adc module*/ 
	ADON = 1;   

	/*selecting right justification*/
	ADFM = 1;
}

unsigned short read_adc(unsigned char channel)
{
    unsigned short adc_reg_val;
    
    /* Selecting the required channel */
    //first clear whatever is there in 3rd 4th and 5th positions
    //bringing channel value to 3 4 5th position
    ADCON0 = (ADCON0 & 0xC7) | (channel << 3);
    
    /* Start the ADC conversion */
    GO = 1;
    /* Wait for the conversion to complete */
    while (nDONE);
    
    adc_reg_val = (ADRESH << 8) | ADRESL; // 10bits
    
    return adc_reg_val;         //return the value as per the position of POT(10 bit res) b/w 0-1023
}
