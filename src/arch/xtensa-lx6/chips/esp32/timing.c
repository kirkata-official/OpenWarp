#include "../../../../../include/OpenWarp.h"
#include "memory-map.h"

static inline uint32_t _ccount(void)
{
    uint32_t v;
    __asm__ volatile ("rsr %0, ccount" : "=r"(v));
    return v;
}

static uint32_t _cpu_hz(void)
{
    uint32_t raw = RTC_CPU_FREQ_REG & 0x00FFFFFFul;
    if (raw == 0)
        return 240000000ul;
    return raw << 12;
}

uint32_t micros(void)
{
    return (uint32_t)((uint32_t)_ccount() * 1000000ull / _cpu_hz());
}

uint32_t millis(void)
{
    return (uint32_t)((uint32_t)_ccount() * 1000ull / _cpu_hz());
}

void waitMicroseconds(uint32_t us)
{
    if (us == 0) return;
    uint32_t cycles = (uint32_t)((uint32_t)us * _cpu_hz() / 1000000ull);
    uint32_t start  = _ccount();
    while ((_ccount() - start) < cycles)
        ;
}

void wait(uint32_t ms)
{
    while (ms--)
        waitMicroseconds(1000);
}
