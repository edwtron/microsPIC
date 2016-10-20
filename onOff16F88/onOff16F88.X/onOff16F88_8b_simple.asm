    ; onOff16F88
    ;
    ;Programa que muestra la configuracion basica para un microcontrolador 16f88
    ;en lenguaje Ensamblador y como ejemplo se enciende y apaga un LED con intervalo
    ;de 1 segundo.
    
    ;Hardware usado
    
    ;	1 PIC 16F88
    ;	1 LED
    ;	1 Resistencia de 1K
    ;	1 Protoboard
    ;	
    
    ; CIRCUITO
    
    ; LED Anodo: Conectado al PIN RA2 del microcontrolador
    ; LED Catodo: Conectado a VSS (GND) a travez de una resistencia de 1K
    
    ;	Para ver conexion del microcontrolador ir al manual que entrega Microchip
    
    
    
	    #include "p16f88.inc"
	    
    ;Estos son los Fusibles de configuracion del PIC(cada PIC tiene sus propios Fusibles(Bits)
    ; CONFIG1
    ; __config 0xFF50
	    __CONFIG _CONFIG1, _FOSC_INTOSCIO & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _BOREN_ON & _LVP_OFF & _CPD_OFF & _WRT_OFF & _CCPMX_RB0 & _CP_OFF

    ; CONFIG2
    ; __config 0xFFFC
	    __CONFIG _CONFIG2, _FCMEN_OFF & _IESO_OFF
    
    ;Asignamos memoria de usuario para las variables que son usadas en el programa
	    cblock  0X20		;En esta direccion inicia la memoria del usuario, 
					;tambien llamados Regitros de Proposito General
		    d1			;d1, d2 y d3 son Variables usadas por el retardo
		    d2
		    d3
	    endc			;Fin de la asignacion de GPRs
    
RES_VECT    CODE    0x0000		; Vector de Reset, aqui llega cuando se reinicia el micro
  
	    GOTO    CONFIGURA           ;Vamos al inicio del programa, a la parte de configuracion



MAIN_PROG   CODE			; Incia codigo del programa
 
    ;Bloque de Subrutinas
 
    ;Subrutina de Retardo de 1 segundo, para que se pueda ver el encendido y apaagado del LED 
RET_1S					;999997 cycles
	    movlw	0x08
	    movwf	d1
	    movlw	0x2F
	    movwf	d2
	    movlw	0x03
	    movwf	d3
Delay_0
	    decfsz	d1, f
	    goto	$+2
	    decfsz	d2, f
	    goto	$+2
	    decfsz	d3, f
	    goto	Delay_0

					;3 cycles
	    goto	$+1
	    nop

	    RETURN
	
	
    ;Bloque de configuracion del PIC, solo se hace cada vez que iniciamos el micro
    ;o hay un reset por algun motivo
CONFIGURA   NOP
	    BANKSEL    ADCON1		;Cambiamos de Banco de memoria
	    CLRF       ANSEL		;Configuramos Pines Digitales
	    MOVLW	B'01101100'	;Configuramos 0scilador interno del PIC
	    MOVWF	OSCCON		;0110 oscilador a 4 Mhz <6, 5, 4>, 1100 OSTS<3>, IOFS<2>, SCS<1,0>
	    CLRF        TRISA		;Configuramos los pines del puerto A como Salidas
	    CLRF        TRISB		;Configuramos los pines del puerto B como Salidas

	    BANKSEL     PORTB
	    CLRF	PORTA		;Nos aseguramos que todos los pines esten a 0 vdc
	    CLRF        PORTB   
 
  
    ;Bloque del programa principal
INICIO      NOP
	    BSF		PORTA,2		;Activa el Pin RA2(Envia 5 vdc a este Pin) del puerto A, lo que hace encender el LED
	    CALL	RET_1S		;LLama subrutina que tarda 1 segundo
	    BCF		PORTA,2		;Desactiva RA2 (envia 0 vdc) lo que apaga el LED
	    CALL	RET_1S

	    GOTO	INICIO		;Volvemos al inicio y quedamos en un LOOP

   
	    END				;Fin del programa, a este punto el microcontrolador nunca llega