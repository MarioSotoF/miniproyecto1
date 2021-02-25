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
#define _XTAL_FREQ (8000000)



// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
// Incluyo librerias creadas
#include <xc.h>
#include "SPI.h"
#include <stdint.h>
//#include "adc.h"
uint8_t potenciometro = 0;
uint8_t contador = 0;
uint8_t semaforo = 0;


void main(void) {
//    OSCCONbits.IRCF = 0b111;
//    OSCCONbits.OSTS = 0;
//    OSCCONbits.HTS = 0;
//    OSCCONbits.LTS = 0;
//    OSCCONbits.SCS = 1;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00000000;
    TRISC = 0b00000000;
    TRISCbits.TRISC4 = 1;
    PORTA = 0;
    TRISD=0;
    PORTD=0;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) {
        PORTCbits.RC0 = 0; //Slave Select
        __delay_ms(1);

        spiWrite(1);
        potenciometro = spiRead();

        __delay_ms(1);
        PORTCbits.RC0 = 1; //Slave Deselect 

        __delay_ms(250);

        PORTCbits.RC1 = 0; //Slave Select
        __delay_ms(1);

        spiWrite(1);
        contador = spiRead();

        __delay_ms(1);
        PORTCbits.RC1 = 1; //Slave Deselect 

        __delay_ms(250);

        PORTCbits.RC2 = 0; //Slave Select
        __delay_ms(1);

        spiWrite(1);
        semaforo = spiRead();

        __delay_ms(1);
        PORTCbits.RC2 = 1; //Slave Deselect 

        __delay_ms(250);


        
        
        
//        ADCen();
//        ADCON0bits.ADON = 1;
//        ADCON0bits.GO = 1;
//        while (ADCON0bits.GO);
//        PORTD=ADCV;
    }

    return;
}

