#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>

#define _XTAL_FREQ 20000000
#define LED PORTBbits.RB0

#pragma config FOSC = HS

__bit inverte;
int conta = 0;

void __interrupt() TrataInt(void)
{
    if (TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        TMR1L = 0xDC;
        TMR1H = 0x0B;

        conta++;
        if (conta == 10)
        {
            inverte = ~inverte;
            LED = inverte;
            conta = 0;
        }
    }
    return;
}

void main(void)
{
    TRISB = 0b00000000;
    OPTION_REGbits.nRBPU = 0;

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR1IE = 1;

    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;

    TMR1L = 0xDC;
    TMR1H = 0x0B;

    T1CONbits.TMR1ON = 1;

    LED = 0;

    while (1)
    {
    }
}
