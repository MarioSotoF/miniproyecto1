/*
 * File:   main.c
 * Author: mario
 *
 * Created on 23 de febrero de 2021, 04:41 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
// Incluyo librerias creadas
#include <xc.h>
#include "SPI.h"
#include "adc.h"



void main(void) {
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.OSTS = 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00000001;
    ANSELbits.ANS0 = 1;
    PORTA = 0;
    TRISD=0;
    PORTD=0;
    TRISC = 0b00010000;
    TRISAbits.TRISA5 = 1;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

    while (1) {
        spiWrite(ADCV);
        ADCen();
        ADCON0bits.ADON = 1;
        __delay_ms(15);
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO);
        PORTD=ADCV;
    }

    return;
}

void __interrupt() ISR(void){
    if (PIR1bits.ADIF == 1) {
        ADCV = ADRESH;
        PIR1bits.ADIF = 0;
        return;
    }
    
//    if(SSPIF == 1){
//        spiRead(1);
//        spiWrite(ADCV);
//        SSPIF = 0;
//    }
}


   