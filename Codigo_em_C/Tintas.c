#include <xc.h>          
#include <pic16f877a.h>  
#include <stdio.h>       

#define _XTAL_FREQ 4000000 

__bit Start;   
__bit SN;   

#define Y1 PORTBbits.RB3   
#define Y2 PORTBbits.RB4   
#define M1 PORTBbits.RB6   
#define Y3 PORTBbits.RB7   

void main(void) 
{  
   int aux;               

   TRISB = 0b00000011;      
   OPTION_REG = 0b01111111; 

   Y1 = 0; 
   Y2 = 0; 
   M1 = 0; 
   Y3 = 1; 
   
   while (1)  
   {
      aux = 0;
      while (aux == 0)
      {
         Start = PORTBbits.RB0;
         __delay_ms(400);
         if  (Start == 0 )
         {
            Y3 = 0;  
            aux = 1;
         }
      }

      Y1 = 1;              
      Y2 = 1;   

      aux = 0;
      while (aux == 0)
      {
         SN = PORTBbits.RB1;
         if  (SN == 0 )
            aux = 1;
      }

      Y1 = 0;              
      Y2 = 0;   

      M1 = 1;   
      __delay_ms(5000);    
      M1 = 0;   
      Y3 = 1;   
   }
}
