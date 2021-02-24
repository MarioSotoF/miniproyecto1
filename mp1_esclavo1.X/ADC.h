/*
 * File:
 * Author: Mario Soto
 * Commets:
 * Revision history
 * 
 */

#ifndef ADC_H
#define ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _XTAL_FREQ 8000000

uint8_t ADCV=0;

void ADCen(void);
#endif 