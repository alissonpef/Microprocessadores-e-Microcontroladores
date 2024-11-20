;*******************************************************************************
; Programa Prensa, aciona com dois botoes simultaneamente, o pistao desce por 2s
; em seguida sobre por 2s. Um botao de emergencia sobe o pistao.
; 
; *******************************************************************************

#include <P16F877A.INC> ; Arquivo de include do uC usado, no caso PIC16F877A

; Palavra de configuracao, desabilita e habilita algumas opcoes internas
__CONFIG _CP_OFF & _CPD_OFF & _DEBUG_OFF & _LVP_OFF & _WRT_OFF & _BODEN_OFF & _PWRTE_OFF & _WDT_OFF & _XT_OSC

;***** definicao de Variaveis *****************************
;cria constantes para o programa

cblock 0x20
    tempo0
    tempo1 ; Variaveis usadas na rotina de delay.
    filtro
    temp ; Variavel temporaria.
    tempo2
endc 

cblock 0x70
    work_temp
    status_temp ; Variaveis usadas para salvar contexto no momento das interrupcoes.
    fsr_temp
    pclath_temp
endc

;********* variaveis de Entrada ************
#define BT_EMG PORTB,0 ; Esta ligada RB0 (Pino 33 do uC)
#define BT_1 PORTB,1 ; Esta ligada RB1 (Pino 34 do uC)
#define BT_2 PORTB,2 ; Esta ligada RB2 (Pino 35 do uC)

;********* variaveis de Saida ***************
#define SOBE PORTD,0 ; Saida ligada RD0 (Pino 19 do uC)
#define DESCE PORTD,1 ; Saida ligada RD1 (Pino 20 do uC)

;******** Vetor de Reset do uC**************
org 0x00 ; Vetor de reset do uC.
goto inicio ; Desvia para o inicio do programa.

;******** Vetor de Interrupcoes do uC **************
org 0x04 ; Vetor de interrupcoes do uC.

salva_contexto:
    movwf work_temp ; Salva o registrador de trabalho
    swapf STATUS,W ; Salva o registrador de status
    movwf status_temp
    movf FSR,W
    movwf fsr_temp ; Salva registrador FSR.
    movf PCLATH,W
    movwf pclath_temp ; Salva registrador PCLATH.
    clrf PCLATH ; Seleciona pagina de memoria 0.
    clrf STATUS ; Seleciona banco de memoria 0.

    btfss INTCON,INTF ; Foi interrupcao externa pino RB0?
    goto sai_int ; Nao - Sai da interrupcao.

; Tratamento da interrupcao de mudanca de estado no PortB

int_rb0:
    bcf DESCE ; Desce desliga
    bsf SOBE ; Sobe prensa

volta: btfss BT_EMG ; Continua apetardo INT? Entao fica aqui
       goto volta

sai_int_rb0:
    bcf INTCON,INTF ; Limpa flag da interrupcao de mudanca de estado no PortB .

sai_int
    movf pclath_temp,W
    movwf PCLATH ; Recupera registrador PCLATH.
    movf fsr_temp,W
    movwf FSR ; Recupera registrador FSR.
    swapf status_temp,W
    movwf STATUS ; Recupera registrador STATUS.
    swapf work_temp,F
    swapf work_temp,W ; Recupera registrador Work.
 retfie

;*************** Rotinas e Sub-Rotinas *****************************************

; Rotina de delay 
delay_ms:
    movwf tempo2
conta: movlw .255
    movwf tempo1 ; Carrega tempo1 (Unidade de ms).
    movlw .255
    movwf tempo0 ; Carrega tempo0 (Para contar 1ms).
    nop ; Perde tempo.
    decfsz tempo0,F ; Fim de tempo0 ?
    goto $-2 ; Nao - Volta duas instrucoes.
    ; Sim - Passou-se 1ms.
    decfsz tempo1,F ; Fim de tempo1 ?
    goto $-6 ; Nao - Volta seis instrucoes.
    
    decfsz tempo2, F
    goto conta
    ; Sim.
 return ; Retorna.

trata_entrada:
    
    bsf DESCE ; Desce prensa
    bcf SOBE ; Sobe prensa
    movlw .8
    call delay_ms ; Delay de 250 ms. Tempo para Acionar prensa
    
    bcf DESCE ; Desce desliga
    bsf SOBE ; Sobe prensa
    
return

;****************** Inicio do programa *****************************************

inicio:
    clrf PORTA ; Inicializa os Ports. Coloca todas pinos em 0.
    clrf PORTB
    clrf PORTC
    clrf PORTD
    clrf PORTE

    banksel TRISA ; Seleciona banco de memoria 1
    movlw 0x00
    movwf TRISA ; Configura PortA todas com saida
    movlw 0x07
    movwf TRISB ; Configura PortB como entrada (RB0, RB1, RB2)
    movlw 0x00
    movwf TRISC ; Configura PortC todas com saida
    movlw 0x00
    movwf TRISD ; Configura PortD todas com saida
    movlw 0x00
    movwf TRISE ; Configura PortE todas com saida

    movlw 0x00
    movwf OPTION_REG ; Configura Opcoes:
    ; Pull-Up habilitados.
    ; Interrupcao na borda de subida do sinal no pino RB0.
    ; Timer0 incrementado pelo oscilador interno.
    ; Prescaler WDT 1:1.
    ; Prescaler Timer0 1:2.

    movlw 0x90
    movwf INTCON ; Habilita interrupcao RB0.

    movlw 0x00
    movwf PIE1 ; Desabilita interrupcoes perifericas.

    movlw 0x00
    movwf PIE2 ; Desabilita interrupcoes perifericas.

    movlw 0x07
    movwf ADCON0 ; Desliga conversor A/D, PortA e PortE com I/O digital.

    movlw 0x07
    movwf CMCON ; Desliga comparadores internos.

    movlw 0x00
    movwf CVRCON ;
