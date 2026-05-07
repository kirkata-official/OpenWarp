#include "../../../../../include/OpenWarp.h"
#include "memory-map.h"

void pinMode(uint8_t pin, uint8_t mode)
{
    if (pin >= 40) return;
    if (_iomux_off[pin]) {
        volatile uint32_t *mux =
            (volatile uint32_t *)(DR_REG_IO_MUX_BASE + _iomux_off[pin]);
        uint32_t r = *mux;
        r &= ~IO_MUX_MCU_SEL_M;
        r |=  (IO_MUX_FUNC_GPIO << IO_MUX_MCU_SEL_S);
        *mux = r;
    }

    if (mode == OUTPUT) {
        GPIO_FUNC_OUT_SEL_CFG(pin) = SIG_GPIO_OUT_IDX;
        if (pin < 32)
            GPIO_ENABLE_W1TS_REG = (1u << pin);
        else
            GPIO_ENABLE1_W1TS_REG = (1u << (pin - 32));
        if (_iomux_off[pin]) {
            volatile uint32_t *mux =
                (volatile uint32_t *)(DR_REG_IO_MUX_BASE + _iomux_off[pin]);
            *mux &= ~IO_MUX_FUN_IE;
        }

    } else {
        if (pin < 32)
            GPIO_ENABLE_W1TC_REG = (1u << pin);
        else
            GPIO_ENABLE1_W1TC_REG = (1u << (pin - 32));

        if (_iomux_off[pin]) {
            volatile uint32_t *mux =
                (volatile uint32_t *)(DR_REG_IO_MUX_BASE + _iomux_off[pin]);
            uint32_t r = *mux;

            r |= IO_MUX_FUN_IE;
            r &= ~(IO_MUX_FUN_WPU | IO_MUX_FUN_WPD);

            if (mode == INPUT_PULLUP)   r |= IO_MUX_FUN_WPU;
            if (mode == INPUT_PULLDOWN) r |= IO_MUX_FUN_WPD;

            *mux = r;
        }
    }
}

void pinWrite(uint8_t pin, uint8_t val)
{
    if (pin >= 34) return;

    if (pin < 32) {
        if (val) GPIO_OUT_W1TS_REG = (1u << pin);
        else     GPIO_OUT_W1TC_REG = (1u << pin);
    } else {
        if (val) GPIO_OUT1_W1TS_REG = (1u << (pin - 32));
        else     GPIO_OUT1_W1TC_REG = (1u << (pin - 32));
    }
}

int pinRead(uint8_t pin)
{
    if (pin >= 40) return 0;

    if (pin < 32)
        return (int)((GPIO_IN_REG  >>  pin)        & 1u);
    else
        return (int)((GPIO_IN1_REG >> (pin - 32))  & 1u);
}

void pinToggle(uint8_t pin)
{
    if (pin >= 34) return;

    if (pin < 32) {
        uint32_t mask = (1u << pin);
        if (GPIO_IN_REG & mask) GPIO_OUT_W1TC_REG = mask;
        else                    GPIO_OUT_W1TS_REG = mask;
    } else {
        uint32_t mask = (1u << (pin - 32));
        if (GPIO_IN1_REG & mask) GPIO_OUT1_W1TC_REG = mask;
        else                     GPIO_OUT1_W1TS_REG = mask;
    }
}
