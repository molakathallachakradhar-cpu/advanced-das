#include <LPC214x.h>
#include <stdio.h>
#include "lpc214x_peripherals.h"

void System_Init(void);
void PLL_Init(void);

int main(void) {
    unsigned int adc_value;
    float temperature;
    char temp_str[50];
    int temp_int, temp_frac;

    System_Init();
    PLL_Init();

    UART0_Init(9600);
    SPI0_Init();
    I2C0_Init();
    CAN1_Init();
    ADC_Init();
    LCD_Init();

    LCD_Clear();
    LCD_Goto(0, 0);
    LCD_Print("Temperature DAS");
    LCD_Goto(1, 0);
    LCD_Print("by Chakri");
    delay_ms(2000);

    LCD_Clear();
    LCD_Goto(0, 0);
    LCD_Print("Temp: ");

    while(1) {
        adc_value = ADC_Read(1);
        temperature = ADC_To_Temperature(adc_value);

        temp_int = (int)temperature;
        temp_frac = (int)((temperature - temp_int) * 10);

        LCD_Goto(0, 6);
        LCD_PrintNumber(temp_int);
        LCD_Data('.');
        LCD_PrintNumber(temp_frac);
        LCD_Print(" C ");

        LCD_Goto(1, 0);
        LCD_Print("ADC: ");
        LCD_PrintNumber(adc_value);

        sprintf(temp_str, "Temp: %d.%d C ADC:%d\r\n",
                temp_int, temp_frac, adc_value);
        UART0_SendString(temp_str);

        delay_ms(500);
    }
}

void System_Init(void) {
    IODIR0 = 0x0000FC00;
}

void PLL_Init(void) {
    PLL0CON = 0x01;
    PLL0CFG = 0x24;
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    while(!(PLL0STAT & 0x400));

    PLL0CON = 0x03;
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    VPBDIV = 0x01;
}
