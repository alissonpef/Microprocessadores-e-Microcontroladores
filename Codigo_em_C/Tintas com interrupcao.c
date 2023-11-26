#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000
#define Y1 PORTBbits.RB3

int flag;

void __interrupt() TrataInt(void) {
    if (INTF) {
        INTCONbits.INTF = 0;
        PORTBbits.RB3 = 0;
        PORTBbits.RB4 = 0;
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 1;
        flag = 1;
    }
    return;
}

__bit Start;
__bit SN;

void main(void) {
    int aux;
    TRISB = 0b00000111;
    OPTION_REG = 0b01111111;

    OPTION_REGbits.INTEDG = 1;
    INTCON = 0b10010000;
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;

    Y1 = 0;
    PORTBbits.RB4 = 0;
    PORTBbits.RB7 = 1;
    PORTBbits.RB6 = 0;

    while (1) {
        aux = 0;
        flag = 0;
        while ((aux == 0) && (flag == 0)) {
            Start = PORTBbits.RB1;
            __delay_ms(500);
            if ((Start == 0) && (flag == 0)) {
                PORTBbits.RB7 = 0;
                aux = 1;
            }
        }
        if (flag == 0) {
            PORTBbits.RB3 = 1;
            PORTBbits.RB4 = 1;
        }
        aux = 0;
        while ((aux == 0) && (flag == 0)) {
            __delay_ms(1000);
            SN = PORTBbits.RB2;
            if ((SN == 0) && (flag == 0))
                aux = 1;
        }

        if (flag == 0) {
            PORTBbits.RB3 = 0;
            PORTBbits.RB4 = 0;
            PORTBbits.RB6 = 1;
            __delay_ms(2000);
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 1;
        }
    }
}
