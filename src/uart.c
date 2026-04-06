#include <LPC214x.h>

void UART0_Init(unsigned int baudrate) {
    unsigned int pclk = 60000000;
    unsigned int divisor;

    PINSEL0 |= 0x00000005;

    U0LCR = 0x83;
    divisor = pclk / (16 * baudrate);
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8) & 0xFF;

    U0LCR = 0x03;
    U0FCR = 0x07;
}

void UART0_SendChar(char data) {
    while(!(U0LSR & 0x20));
    U0THR = data;
}

void UART0_SendString(char *str) {
    while(*str) {
        UART0_SendChar(*str++);
    }
}
