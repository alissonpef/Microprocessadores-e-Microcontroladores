#include <xc.h>          // Inclusão da biblioteca do compilador
#include <pic16f877a.h>  // Inclusão da biblioteca do chip específico
#include <stdio.h>       // Inclusão da biblioteca padrão "C"

#define _XTAL_FREQ 4000000 // Define a frequência do clock, 4MHz neste caso

void main(void) 
{
    TRISB = 0;            // Configura o Port B como saída
    
    while (1)
    {
        PORTBbits.RB0 = 1;  // Coloca pino RB0 em 1
        __delay_ms(1000);

        PORTBbits.RB0 = 0;  // Zera pino RB0
        __delay_ms(1000);         
    }
}
