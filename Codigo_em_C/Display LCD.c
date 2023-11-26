#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>

#pragma config WDTE = OFF
#pragma config FOSC = HS
#pragma config PWRTE = ON
#pragma config BOREN = ON

#define _XTAL_FREQ 4000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include "lcd.h"

int main()
{
    unsigned int a;
    float f = 1.414;
    char buffer[20];

    TRISD = 0x00;

    Lcd_Init();

    while (1)
    {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("OLA MUNDO");
        __delay_ms(1000);

        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String("MUNDO DOIDO");
        __delay_ms(2000);

        for (a = 0; a < 15; a++)
        {
            __delay_ms(300);
            Lcd_Shift_Left();
        }

        for (a = 0; a < 15; a++)
        {
            __delay_ms(300);
            Lcd_Shift_Right();
        }
        __delay_ms(2000);

        Lcd_Clear();
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Char('O');
        Lcd_Write_Char('I');
        __delay_ms(2000);

        Lcd_Clear();
        sprintf(buffer, "Float = %0.2f", f);
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String(buffer);
        __delay_ms(2000);

        sprintf(buffer, "Integer = %d", a);
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(buffer);
        __delay_ms(2000);
    }
    return 0;
}
