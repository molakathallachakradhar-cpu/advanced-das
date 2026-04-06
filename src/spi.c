#include <LPC214x.h>

void SPI0_Init(void) {
    PINSEL0 |= 0x00001500;
    S0SPCR = 0x20;
    S0SPCCR = 8;
}

unsigned char SPI0_Transfer(unsigned char data) {
    S0SPDR = data;
    while(!(S0SPSR & 0x80));
    return S0SPDR;
}
