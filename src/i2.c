#include <LPC214x.h>

void I2C0_Init(void) {
    PINSEL0 |= 0x00000050;
    I2C0SCLH = 150;
    I2C0SCLL = 150;
    I2C0CONSET = 0x40;
}
