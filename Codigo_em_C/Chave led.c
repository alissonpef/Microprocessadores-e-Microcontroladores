#include <xc.h>          
#include <pic16f877a.h>  
#include <stdio.h>       

#define _XTAL_FREQ 4000000 

__bit led;   
int valor;

void main(void) 
{
   TRISB = 0b00000000;    
   PORTB = 0;             
   TRISD = 0b11111111;    

   while (1)
   {
       led = PORTDbits.RD1;
       
       if (led == 0)
           PORTBbits.RB0 = 1;
       else
           PORTBbits.RB0 = 0;
   }
}
