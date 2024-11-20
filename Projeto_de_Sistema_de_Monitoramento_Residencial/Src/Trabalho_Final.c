// Configuração do LCD
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

sbit GAS_PIN at RC3_bit; // Pino de leitura do sensor de gás
sbit LED at RC2_bit;    // LED conectado à porta RC2

// Variáveis
float temperature;
float DisplayTemp;
char temp[4];
int currentGasValue;
float currentTempValue;

// Função para limpar uma linha no LCD
void ClearLine(int line, int column)
{
    Lcd_Out(line, column, "                ");
}

int initial()
{
    if (GAS_PIN == 0)
    {
        LED = 0; // Liga o LED
        lcd_out(3, -3, "NO GAS DETECT");
    }
    if (GAS_PIN != 0)
    {
        LED = 1; // Desliga o LED
        lcd_out(3, -3, "GAS DETECT  ");
    }

    return GAS_PIN;
}

// Função principal
void main()
{
    LED = 0;

    // Configuração dos pinos
    TRISB = 0X00;      // Configura PORTB como saída
    TRISA = 0X0F;      // Configura PORTA como entrada
    TRISC = 0X00;      // Configura PORTC como saída
    TRISC3_bit = 1;    // Configura o pino de leitura do sensor de gás como entrada

    // Inicializa LCD e ADC
    Lcd_Init();
    ADC_Init();

    // Mensagens iniciais no LCD
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1, 1, "Ambient");
    Lcd_Out(2, 1, "Monitoring Syst.");
    Lcd_Out(3, -3, "Authors:");
    Lcd_Out(4, -3, "Dennis & Alisson");
    delay_ms(1500);

    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    currentGasValue = initial();

    while (1)
    {
        Lcd_Cmd(_LCD_CURSOR_OFF);
        temperature = ADC_Read(RA0);
        floattostr(DisplayTemp, temp);
        Lcd_Out(1, 1, "Temperature:");

        DisplayTemp = temperature * 50 * 10 / 1023; // Calculo da temperatura
        Lcd_Out(2, 12, Ltrim(temp));                // Mostra a temperatura no LCD
        Lcd_Out(2, 16, "C");
        delay_ms(500);

        // Lógica de controle de temperatura
        if (DisplayTemp < 22)
        {
            PORTC.F0 = 1;
            PORTC.F1 = 0;
        }
        else if (DisplayTemp >= 22 && DisplayTemp <= 25)
        {
            PORTC.F0 = 0;
            PORTC.F1 = 0;
        }
        else if (DisplayTemp > 25)
        {
            PORTC.F0 = 0;
            PORTC.F1 = 1;
        }

        // Verifica se houve alteração no sensor de gás
        if (currentGasValue != GAS_PIN)
        {
            ClearLine(3, -3);
            delay_ms(500);

            if (GAS_PIN == 0)
            {
                LED = 0; // Liga o LED
                lcd_out(3, -3, "NO GAS DETECT");
            }
            if (GAS_PIN != 0)
            {
                LED = 1; // Desliga o LED
                lcd_out(3, -3, "GAS DETECT  ");
            }
            currentGasValue = GAS_PIN;
        }
    }
}