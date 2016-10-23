/*
 * File:   lcd8bit16f88C.c
 * Author: edwtron
 *
 * Created on October 20, 2016, 9:53 PM
 * Lcd_iniciar() : Inicializa el modulo LCD
    #define EN RA0
    #define RS RA1
    #define D0 RB0
    #define D1 RB1
    #define D2 RB2
    #define D3 RB3
    #define D4 RB4
    #define D5 RB5
    #define D6 RB6
    #define D7 RB7
 Estos serian los pines del micro a los que se conecta la pantalla

 */




#include <xc.h>

                                //definicion de pines
#define RS RA0
#define EN RA1
#define D0 RB0
#define D1 RB1
#define D2 RB2
#define D3 RB3
#define D4 RB4
#define D5 RB5
#define D6 RB6
#define D7 RB7

#define LED RA2
                                //Definición de comandos

#define INIT1   0b00111000      //8 bits, 2 lineas, 7x5
#define INIT2   0b00001111      //On LCD, On cursor, On intermitencia
#define CLEAR   0b00000001      //Borro pantalla
#define HOME    0b00000011      //Ir al inicio
#define IZQ     0b00010000      //mover cursor a la izquierda
#define DER     0b00010100      //mover cursor a la derecha
#define MOVER_PANTALLA_IZQ  0b00011000 //mover pantalla a la izquierda
#define MOVER_PANTALLA_DER  0b00011100 //mover pantalla a la derecha

#define _XTAL_FREQ 4000000      // Indicamos a que frecuencia de reloj esta funcionando el micro

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


                                //Prototipos
void escribirLetra(char);
void escribirCadena(char*);
void comando(char);
void irLinea2(void);
void irA(int);

void iniciarLCD(void);

                                //Funcion principal
void main() {
    
                                //configuraciones básicas
    ANSEL = 0b00000000;         //Pines Digitales
    TRISA = 0b00000000;         //Configuro puerto A como salidas
    TRISB = 0b00000000;         //Configuro puerto B como salidas
    OSCCON = 0b01101100;    //Configuro el Oscilador interno a 8MHz
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    
    __delay_ms(100);
    
    iniciarLCD();
    comando(CLEAR);
    escribirCadena("Electronica 2016");
    irA(40);
    escribirCadena("xorwf.blogspot.com");
    
    
    
    
    while(1){                   //Loop infinito
        
        LED = 1;
        __delay_ms(500);
        LED = 0;
        __delay_ms(500);
        
    }
    
}

void irLinea2(void){
    irA(40);
}

void iniciarLCD(void){
    
    comando(INIT1);
    __delay_ms(1);
    comando(INIT2);
    __delay_ms(1);
    
    
}

void escribirLetra(char dato){
    __delay_ms(1);
    RS = 0;
    EN = 0;
    PORTB = dato;
    RS = 1;
    EN = 1;
    __delay_ms(1);
    
    EN = 0;
    __delay_ms(1);
    
}

void irA(int posicion){
    comando(HOME);
    for(int i = 0; i < posicion; i++)
        comando(DER);
}

void escribirCadena(char *dato)
{
	int i;
	for(i=0;dato[i]!='\0';i++)
	   escribirLetra(dato[i]);
}

void comando(char command){
    __delay_ms(1);
    RS = 0;
    EN = 0;
    PORTB = command;
    RS = 0;
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(1);
    
}

