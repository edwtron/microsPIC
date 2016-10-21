/*
 * File:   onOff16f88C.c
 * Author: edwtron
 *
 * Created on October 19, 2016, 9:59 PM
 */
#define _XTAL_FREQ 8000000      // Indicamos a que frecuencia de reloj esta funcionando el micro


#include <xc.h>


// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)





void main() {
    
    
    TRISA = 0b00000000;         // Configuro puerto A como salidas
    OSCCONbits.IRCF = 0b111;    //Configuro el Oscilador interno a 8MHz
    
    while(1){                   //Loop infinito
        RA2 = 1;                //Enciendo el Bit 2 del puerto A
        __delay_ms(1000);       //Retardo de 1 segundo
        RA2 = 0;                //Apago el Bit 2 del puerto A
        __delay_ms(1000);
    }
    
}
