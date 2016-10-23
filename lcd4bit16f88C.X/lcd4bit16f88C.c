/*
 * File:   lcd4bit16f88C.c
 * Author: edwtron
 *
 * Created on October 21, 2016, 10:14 PM

 */




#include <xc.h>

                                //definicion de pines
#define RS RB1
#define EN RB0

#define D4 RA0
#define D5 RA1
#define D6 RA2
#define D7 RA3

#define LED RB7
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

void comando4(char);
void lcdPines4(char);
void Clear4(void);
void iniciarLCD4(void);
void escribirLetra4(char);
void escribirCadena4(char*);
void moverDerecha(void);
void moverIzquierda(void);

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
    iniciarLCD4();
    
    escribirCadena4("Electronica 2016");
    
    while(1){                   //Loop infinito
        
        LED = 1;
        __delay_ms(500);
        LED = 0;
        __delay_ms(500);
        
    }
    
}


//Activa los pines correspondientes del LCD
void lcdPines4(char valor)
{
	if(valor & 1)
		D4 = 1;
	else
		D4 = 0;

	if(valor & 2)
		D5 = 1;
	else
		D5 = 0;

	if(valor & 4)
		D6 = 1;
	else
		D6 = 0;

	if(valor & 8)
		D7 = 1;
	else
		D7 = 0;
}

void comando4(char command)
{
    __delay_ms(1);
	RS = 0;             
	lcdPines4(command);
	EN  = 1;            
    __delay_ms(1);
    EN  = 0;       
    __delay_ms(1);
}

void Clear4(void)
{
	lcdPines4(0);
	lcdPines4(1);
}

void iniciarLCD4(void)
{
    lcdPines4(0x00);
    __delay_ms(20);
    comando4(0x03);
      __delay_ms(5);
    comando4(0x03);
      __delay_ms(11);
    comando4(0x03); 
    comando4(0x02);

    comando4(0x02);
    comando4(0x08);

    comando4(0x00);
    comando4(0x0C);
  
    comando4(0x00);
    comando4(0x06);

}

void escribirLetra4(char dato)
{
   char temp,y;
   temp = dato & 0x0F;
   y = dato & 0xF0;
   RS = 1;             
   lcdPines4(y>>4);     
   EN = 1;
   __delay_us(40);
   EN = 0;
   lcdPines4(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void escribirCadena4(char *valor)
{
	int i;
	for(i=0;valor[i]!='\0';i++)
	   escribirLetra4(valor[i]);
}

void moverDerecha(void)
{
	lcdPines4(0x01);
	lcdPines4(0x0C);
}

void moverIzquierda(void)
{
	lcdPines4(0x01);
	lcdPines4(0x08);
}
