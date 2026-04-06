#include <LPC214x.h>
#include "lpc214x_peripherals.h"

// LCD pin definitions
#define LCD_RS (1 << 10)
#define LCD_EN (1 << 11)
#define LCD_D4 (1 << 12)
#define LCD_D5 (1 << 13)
#define LCD_D6 (1 << 14)
#define LCD_D7 (1 << 15)

#define LCD_DATA (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 6000; j++);
}

void LCD_Enable(void) {
    IOSET0 = LCD_EN;
    delay_ms(1);
    IOCLR0 = LCD_EN;
}

void LCD_Send4Bit(unsigned char data) {
    IOCLR0 = LCD_DATA;

    if(data & 0x01) IOSET0 = LCD_D4;
    if(data & 0x02) IOSET0 = LCD_D5;
    if(data & 0x04) IOSET0 = LCD_D6;
    if(data & 0x08) IOSET0 = LCD_D7;

    LCD_Enable();
}

void LCD_Command(unsigned char cmd) {
    IOCLR0 = LCD_RS;
    LCD_Send4Bit(cmd >> 4);
    LCD_Send4Bit(cmd & 0x0F);
    delay_ms(2);
}

void LCD_Data(unsigned char data) {
    IOSET0 = LCD_RS;
    LCD_Send4Bit(data >> 4);
    LCD_Send4Bit(data & 0x0F);
    delay_ms(2);
}

void LCD_Init(void) {
    IODIR0 |= (LCD_RS | LCD_EN | LCD_DATA);

    delay_ms(20);

    LCD_Send4Bit(0x03);
    delay_ms(5);
    LCD_Send4Bit(0x03);
    delay_ms(5);
    LCD_Send4Bit(0x03);
    delay_ms(5);
    LCD_Send4Bit(0x02);

    LCD_Command(0x28); // 4-bit, 2-line
    LCD_Command(0x0C); // Display ON
    LCD_Command(0x01); // Clear
    LCD_Command(0x06); // Entry mode
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    delay_ms(2);
}

void LCD_Goto(unsigned char row, unsigned char col) {
    if(row == 0)
        LCD_Command(0x80 + col);
    else
        LCD_Command(0xC0 + col);
}

void LCD_Print(char *str) {
    while(*str) {
        LCD_Data(*str++);
    }
}

void LCD_PrintNumber(int num) {
    char buf[10];
    int i = 0;

    if(num == 0) {
        LCD_Data('0');
        return;
    }

    while(num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i--) {
        LCD_Data(buf[i]);
    }
}
