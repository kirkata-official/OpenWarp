#include "../../OpenWarp.h"
#include "memory-map.h"

void initPin(u8 pin, pinMode mode) {
    if (mode == 1) { // 1 = OUTPUT
        DDRB |= (1 << pin);
    }
}

void write(u8 pin, pinState state) {
    if (state == 1) {
        PORTB |= (1 << pin);
    } else {
        PORTB &= ~(1 << pin);
    }
}

void wait(u32 count) {
    u32 millisecconds = count * 100;
    while(count--);
}