;*******************************************************************************
; Se apertar botao, pisca led
;
;*******************************************************************************

#include <P16F877A.INC> ; Arquivo de include do uC usado, no caso PIC16F877A

;Palavra de configuracao, desabilita e habilita algumas opcoes internas
__CONFIG _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** definicao de Variaveis *****************************
;cria constantes para o programa

cblock 0x20
    tempo
    tempo1 ; Variaveis usadas na rotina de delay.
endc

;******** Vetor de Reset do uC**************

org 0x00 ; Vetor de reset do uC.
goto inicio ; Desvia para o inicio do programa.

;***************** criacao de subrotinas******************************************
Delay:
    movlw 0xFF ; Carrega 255 em W
    movwf tempo ; Passa o 255 de W para a variavel tempo

denovo:
    movlw 0xFF ;carrega 255 em W
    movwf tempo1 ;Passa o 255 de W para a variavel tempo1
    decfsz tempo,F ;dec 1 unidade tempo e pula se zero
    goto repete
    goto sai

repete:
    decfsz tempo1,F
    goto repete
    goto denovo
sai:
    Return
;****************** Inicio do programa *****************************************

inicio:
    clrf PORTA ; Inicializa os Port's. Coloca todas pinos em 0.
    clrf PORTB
    clrf PORTC
    clrf PORTD
    clrf PORTE

    banksel TRISA ; Seleciona banco de memoria 1
    movlw 0x1f
    movwf TRISA ; Configura PortA (A0,A1,A2,A3,A4 = Entradas, A5 = Saida).
    movlw 0xff ; 1111 1111   1 = Input   0 = Output
    movwf TRISB ; Configura PortB como entrada.
    movlw 0x6f
    movwf TRISC ; Configura PortC (C4,C7 = Saida, C0,C1,C2,C3,C5,C6 = Entradas).
    movlw 0x00
    movwf TRISD ; Configura PortD como saida.
    movlw 0x07
    movwf TRISE ; Configura PortE como entrada e desliga Posta Paralela.

    movlw 0x00
    movwf OPTION_REG ; Configura Opcoes:
    ; Pull-Up habilitados.
    ; Interrupcao na borda de subida do sinal no pino B0.
    ; Timer0 incrementado pelo oscilador interno.
    ; Prescaler WDT 1:1.
    ; Prescaler Timer0 1:2.

    banksel PORTA ; Seleciona banco de memoria 0.

;*********************** Loop principal ****************************************
loop:
    movf PORTB,W ;Le o PortB.
    btfss PORTB,1 ;RB1 foi para 0, ou seja, foi acionada?
    goto lig ;Mantem piscando
    bcf PORTD,7 ;se RB1 em 1, desliga led
    goto loop ;Vai para loop. Deixa lendo as entradas

lig:
    bsf PORTD,7 ;liga led
    call Delay ;chama gasta tempo
    call Delay ;chama gasta tempo
    bcf PORTD,7 ;desliga led
    call Delay ;chama gasta tempo
    call Delay ;chama gasta tempo
    goto loop ;Vai para loop. Deixa lendo as entradas

    end ; Fim do Programa.
