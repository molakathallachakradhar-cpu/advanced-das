#include <LPC214x.h>

void ADC_Init(void) {
    PCONP |= (1 << 12);
    PINSEL1 |= 0x01000000;
    AD0CR = 0x00200400;
}

unsigned int ADC_Read(unsigned char channel) {
    AD0CR &= 0xFFFFFF00;
    AD0CR |= (1 << channel);
    AD0CR |= (1 << 24);

    while(!(AD0GDR & 0x80000000));

    return (AD0GDR >> 6) & 0x3FF;
}

float ADC_To_Temperature(unsigned int adc_value) {
    float voltage = (adc_value * 3.3) / 1024.0;
    return voltage * 100.0;
}
