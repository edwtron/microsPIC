; TODO INSERT CONFIG CODE HERE USING CONFIG BITS GENERATOR

    
    #include "p16f88.inc"

; CONFIG1
; __config 0xFF50
    __CONFIG _CONFIG1, _FOSC_INTOSCIO & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _BOREN_ON & _LVP_OFF & _CPD_OFF & _WRT_OFF & _CCPMX_RB0 & _CP_OFF
; CONFIG2
; __config 0xFFFC
    __CONFIG _CONFIG2, _FCMEN_OFF & _IESO_OFF
    
    cblock  0X20
	d1
	d2
	d3
	endc
    
RES_VECT  CODE    0x0000            ; processor reset vector
  
    GOTO    CONFIGURA                   ; go to beginning of program

; TODO ADD INTERRUPTS HERE IF USED

MAIN_PROG CODE                      ; let linker place main program
 
 
RET_1S			;999997 cycles
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
	
	
RET_10MS NOP		;9998 cycles
	movlw	0xCF
	movwf	d1
	movlw	0x08
	movwf	d2
Delay_01
	decfsz	d1, f
	goto	$+2
	decfsz	d2, f
	goto	Delay_01

			;2 cycles
	goto	$+1
	RETURN
	
RET_1MS NOP		;998 cycles
	movlw	0xC7
	movwf	d1
	movlw	0x01
	movwf	d2
Delay_02
	decfsz	d1, f
	goto	$+2
	decfsz	d2, f
	goto	Delay_02

			;2 cycles
	goto	$+1
	
	RETURN
	

CONFIGURA	NOP
    BANKSEL    ADCON1
    CLRF           ANSEL
    MOVLW B'01101100'
    MOVWF OSCCON
    CLRF          TRISA
    CLRF          TRISB
 
    BANKSEL    PORTB
    CLRF           PORTA
    CLRF           PORTB   
 
    CALL        RET_1MS
    BCF          PORTA,0    ;RS = 0
    BCF          PORTA,1    ;E = 0
    MOVLW    B'00111000'    ;8 BITS 2 LINEAS 7X5
    MOVWF    PORTB   
    BCF           PORTA,0    ;RS=0
    BSF           PORTA,1    ;E=1 HABILITO ESCRITURA
    CALL         RET_1MS
    BCF          PORTA,1    ;E = 0
    CALL        RET_1MS
   
    MOVLW    B'00001111'    ;ON LCD, ON CURSOR, ON INTER   
    MOVWF    PORTB   
    BCF           PORTA,0    ;RS=0
    BSF           PORTA,1    ;E=1 HABILITO ESCRITURA
    CALL         RET_1MS
    BCF           PORTA,1    ;E = 0
    CALL        RET_1MS

   

    MOVLW    A'E'    ; Cargo el ASCII de la E
    MOVWF    PORTB    ;Envio la E al puerto
    BSF           PORTA,0
    BSF           PORTA,1
    CALL        RET_10MS
    BCF          PORTA,1
    CALL       RET_10MS
    
    MOVLW    A'd'    ; Cargo el ASCII de la E
    MOVWF    PORTB    ;Envio la E al puerto
    BSF           PORTA,0
    BSF           PORTA,1
    CALL        RET_10MS
    BCF          PORTA,1
    CALL       RET_10MS
    
    MOVLW    A'w'    ; Cargo el ASCII de la E
    MOVWF    PORTB    ;Envio la E al puerto
    BSF           PORTA,0
    BSF           PORTA,1
    CALL        RET_10MS
    BCF          PORTA,1
    CALL       RET_10MS
    
    MOVLW    A'i'    ; Cargo el ASCII de la E
    MOVWF    PORTB    ;Envio la E al puerto
    BSF           PORTA,0
    BSF           PORTA,1
    CALL        RET_10MS
    BCF          PORTA,1
    CALL       RET_10MS
    
    MOVLW    A'n'    ; Cargo el ASCII de la E
    MOVWF    PORTB    ;Envio la E al puerto
    BSF           PORTA,0
    BSF           PORTA,1
    CALL        RET_10MS
    BCF          PORTA,1
    CALL       RET_10MS

INICIO        NOP
    
    GOTO     INICIO   

   
    END