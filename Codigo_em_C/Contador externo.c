#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000
#define LED PORTAbits.RA5

#pragma config FOSC = HS

__bit inverte;

void __interrupt() TrataInt(void)
{
    if (TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        TMR0 = 251;

        inverte = ~inverte;
        LED = inverte;
    }
    return;
}

void main(void)
{
    TRISA = 0b00011111;
    OPTION_REGbits.nRBPU = 0;

    OPTION_REGbits.T0CS = 1;
    OPTION_REGbits.T0SE = 1;
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PSA = 1;

    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;

    TMR0 = 251;

    LED = 0;

    while (1)
    {
    }
}
