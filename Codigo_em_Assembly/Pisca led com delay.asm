;*******************************************************************************
; Pisca Led com delay
;*******************************************************************************

#include <P16F877A.INC> ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configuracao, desabilita e habilita algumas opcoes internas
__CONFIG _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** definicao de Variaveis *****************************
;cria variaveis para o programa

cblock 0x20
    tempo0
    tempo1 ; Variaveis usadas na rotina de delay.
    tempo2
    filtro
endc

;******** Vetor de Reset do uC**************
org 0x00 ; Vetor de reset do uC.
goto inicio ; Desvia para o inicio do programa.

;*************** Rotinas e Sub-Rotinas *****************************************
; Rotina de delay (De 1ms ate 256 ms)
delay_ms:
    movlw .4 ; vai carrega tempo2 com constante
    movwf tempo2 ; carrega tempo2
denovo2:
    movlw .250 ; vai carrega tempo1 com constante
    movwf tempo1 ; Carrega tempo1
denovo:
    movlw .250 ; vai carregar tempo0 com constante
    movwf tempo0 ; Carrega tempo0
volta:
    nop ; gasta 1 ciclo de maquina(1us para clock 4Mhz)
    decfsz tempo0,F ; Fim de tempo0 ? (gasta 2 us)
    goto volta ; Nao - Volta (gasta 1us)
    ; Sim - Passou-se 1ms. (4us x 250 = 1ms)
    decfsz tempo1,F ; Fim de tempo1?
    goto denovo ; Nao - Volta
    ; Sim. 250 x 1ms = 250ms
    decfsz tempo2,F ; Fim de tempo2?
    goto denovo2 ; Nao - Volta
    ; Sim. 4 x 250 = 1s
    return ; Retorna.

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
    bsf PORTB,0 ; Liga led
    call delay_ms ; Rotina gasta tempo
    bcf PORTB,0 ; Apaga
    call delay_ms ; Rotina gasta tempo
    goto loop ; Vai para loop. Deixa lendo as entradas

    end
