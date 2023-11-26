#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000
#define LED PORTCbits.RC0

#pragma config WDTE = ON
#pragma config FOSC = HS
#pragma config PWRTE = ON
#pragma config BOREN = ON

int valor;

void __interrupt() TrataInt(void)
{
    if (ADIF)
    {
        PIR1bits.ADIF = 0;

        valor = ADRESH;
        PORTB = valor;

        if (valor == 127)
            LED = 1;
        else
            LED = 0;
    }
    return;
}

void main(void)
{
    TRISB = 0b00000000;
    TRISC = 0b00000000;
    TRISA = 0b11111111;
    OPTION_REGbits.nRBPU = 0;

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;

    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 0;

    ADCON1bits.ADFM = 0;

    ADRESL = 0x00;
    ADRESH = 0x00;

    ADCON0bits.ADON = 1;

    LED = 0;
    PORTB = 0;

    OPTION_REGbits.PSA = 1;

    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 0;

    CLRWDT();

    PORTCbits.RC1 = 1;

    while (1)
    {
        if (PORTAbits.RA1 == 0)
        {
            PORTCbits.RC1 = 0;
            CLRWDT();
        }

        ADCON0bits.CHS0 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS2 = 0;

        ADCON0bits.GO = 1;
        __delay_us(10);
        valor = ADRESH;

        PORTB = valor;

        if (valor == 127)
            LED = 1;
        else
            LED = 0;
    }
}
