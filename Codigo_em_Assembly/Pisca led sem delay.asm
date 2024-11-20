;*******************************************************************************
; Pisca Led sem delay
;*******************************************************************************

#include <P16F877A.INC> ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configuracao, desabilita e habilita algumas opcoes internas
__CONFIG _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;******** Vetor de Reset do uC**************
org 0x00 ; Vetor de reset do uC.
goto inicio ; Desvia para o inicio do programa.

;****************** Inicio do programa *****************************************
inicio:
    clrf PORTB ; Inicializa o Port B com zero

    banksel TRISA ; Seleciona banco de memoria 1

    movlw 0x00
    movwf TRISB ; Configura PortB como saida

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
    bsf PORTB, 0 ; Liga led

    bcf PORTB, 0 ; Apaga

    goto loop ; Vai para loop. Deixa lendo as entradas

    end
