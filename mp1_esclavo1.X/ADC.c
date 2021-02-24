/* 
 * Author: mario
 * 
 * 
 * 
 * 
 */

#include "adc.h"
#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _XTAL_FREQ 8000000

void ADCen(void){
            
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    ADCON0bits.ADCS = 01;
    ADCON0bits.CHS = 0000;//Seleccion Canal AN0
    ADCON0bits.ADON = 1;
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0;
    
    
}