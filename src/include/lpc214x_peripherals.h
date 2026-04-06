#ifndef LPC214X_PERIPHERALS_H
#define LPC214X_PERIPHERALS_H

void UART0_Init(unsigned int baudrate);
void UART0_SendChar(char data);
void UART0_SendString(char *str);

void ADC_Init(void);
unsigned int ADC_Read(unsigned char channel);
float ADC_To_Temperature(unsigned int adc_value);

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Goto(unsigned char row, unsigned char col);
void LCD_Data(unsigned char data);
void LCD_Print(char *str);
void LCD_PrintNumber(int num);

void delay_ms(unsigned int ms);

#endif
