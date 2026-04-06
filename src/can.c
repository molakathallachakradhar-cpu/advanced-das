#include <LPC214x.h>

void CAN1_Init(void) {
    PINSEL1 |= 0x00014000;
    PCONP |= (1 << 13);

    C1MOD = 0x01;
    C1BTR = 0x001C0009;
    C1MOD = 0x00;
}
