#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>

#pragma config WDTE = OFF
#pragma config FOSC = HS
#pragma config PWRTE = ON
#pragma config BOREN = ON

#define _XTAL_FREQ 4000000

#define ENTR_CONTA    PORTBbits.RB5
#define SEL_UNIDADE   PORTBbits.RB4
#define SEL_DEZENA    PORTBbits.RB3

int indice = 0;
int conta = 0;
int unidade = 0, dezena = 0;

unsigned char TABELA[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void __interrupt() TrataInt(void)
{
    if (TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        TMR1L = 0x8F;
        TMR1H = 0xFD;

        indice++;

        switch (indice)
        {
        case 1:
            SEL_DEZENA = 0;
            SEL_UNIDADE = 1;
            PORTD = TABELA[unidade];
            break;

        case 2:
            indice = 0;
            SEL_UNIDADE = 0;
            SEL_DEZENA = 1;
            PORTD = TABELA[dezena];
            break;
        }
    }
    return;
}

void main(void)
{
    TRISB = 0b00100000;
    TRISD = 0b00000000;
    OPTION_REGbits.nRBPU = 0;

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR1IE = 1;

    T1CONbits.TMR1ON = 0;
    T1CONbits.T1OSCEN = 1;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;

    TMR1L = 0x8F;
    TMR1H = 0xFD;

    T1CONbits.TMR1ON = 1;

    while (1)
    {
        conta = ENTR_CONTA;
        if (conta == 0)
        {
            __delay_ms(400);

            unidade++;
            if (unidade == 10)
            {
                unidade = 0;
                dezena++;
                if (dezena == 10)
                    dezena = 0;
            }
        }
    }
}
