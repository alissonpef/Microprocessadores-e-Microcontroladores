#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000
#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D3 PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

int valor = 0;

void clear_men() {
    PORTD = 0x00;
}

int digit1(int numero) {
    switch (numero) {
    case 1:
        D0 = 1;
        D1 = 0;
        D2 = 0;
        D3 = 0;
        break;
    case 2:
        D0 = 0;
        D1 = 1;
        D2 = 0;
        D3 = 0;
        break;
    case 3:
        D0 = 1;
        D1 = 1;
        D2 = 0;
        D3 = 0;
        break;
    case 4:
        D0 = 0;
        D1 = 0;
        D2 = 1;
        D3 = 0;
        break;
    case 5:
        D0 = 1;
        D1 = 0;
        D2 = 1;
        D3 = 0;
        break;
    case 6:
        D0 = 0;
        D1 = 1;
        D2 = 1;
        D3 = 0;
        break;
    case 7:
        D0 = 1;
        D1 = 1;
        D2 = 1;
        D3 = 0;
        break;
    case 8:
        D0 = 0;
        D1 = 0;
        D2 = 0;
        D3 = 1;
        break;
    case 9:
        D0 = 1;
        D1 = 0;
        D2 = 0;
        D3 = 1;
        break;
    default:
        D0 = 0;
        D1 = 0;
        D2 = 0;
        D3 = 0;
        break;
    }
}

int digit2(int numero) {
    switch (numero) {
    case 1:
        D4 = 1;
        D5 = 0;
        D6 = 0;
        D7 = 0;
        break;
    case 2:
        D4 = 0;
        D5 = 1;
        D6 = 0;
        D7 = 0;
        break;
    case 3:
        D4 = 1;
        D5 = 1;
        D6 = 0;
        D7 = 0;
        break;
    case 4:
        D4 = 0;
        D5 = 0;
        D6 = 1;
        D7 = 0;
        break;
    case 5:
        D4 = 1;
        D5 = 0;
        D6 = 1;
        D7 = 0;
        break;
    case 6:
        D4 = 0;
        D5 = 1;
        D6 = 1;
        D7 = 0;
        break;
    case 7:
        D4 = 1;
        D5 = 1;
        D6 = 1;
        D7 = 0;
        break;
    case 8:
        D4 = 0;
        D5 = 0;
        D6 = 0;
        D7 = 1;
        break;
    case 9:
        D4 = 1;
        D5 = 0;
        D6 = 0;
        D7 = 1;
        break;
    default:
        D4 = 0;
        D5 = 0;
        D6 = 0;
        D7 = 0;
        break;
    }
}

void main(void) {
    TRISA = 0b11111111;
    TRISD = 0b00000000;
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 0;
    ADCON1bits.ADFM = 1;
    ADRESL = 0x00;
    ADRESH = 0x00;
    ADCON0bits.ADON = 1;
    clear_men();

    while (1) {
        ADCON0bits.CHS0 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.GO = 1;
        __delay_us(100);
        valor = ((ADRESH << 8) + ADRESL);
        valor = valor / 2;
        digit1(valor % 10);
        digit2(valor / 10);
    }
    return;
}
