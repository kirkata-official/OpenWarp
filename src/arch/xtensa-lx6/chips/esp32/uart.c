#include "../../../../../include/OpenWarp.h"
#include "memory-map.h"

static uint32_t _apb_hz(void)
{
    uint32_t raw = RTC_APB_FREQ_REG & 0x00FFFFFFul;
    if (raw == 0)
        return 80000000ul;
    return raw << 12;
}

static inline uint32_t _tx_fifo_count(void)
{
    return (UART_STATUS_REG >> UART_TXFIFO_CNT_S) & 0xFFu;
}

static inline uint32_t _rx_fifo_count(void)
{
    return (UART_STATUS_REG >> UART_RXFIFO_CNT_S) & 0xFFu;
}

void serialBegin(uint32_t baud)
{
    DPORT_PERIP_CLK_EN_REG |= DPORT_UART_CLK_EN;
    DPORT_PERIP_RST_EN_REG |=  DPORT_UART_RST;
    DPORT_PERIP_RST_EN_REG &= ~DPORT_UART_RST;
    UART_CLKDIV_REG = 80000000ul / baud;
    volatile uint32_t *tx_mux = (volatile uint32_t *)(DR_REG_IO_MUX_BASE + _iomux_off[1]);
    volatile uint32_t *rx_mux = (volatile uint32_t *)(DR_REG_IO_MUX_BASE + _iomux_off[3]);
    *tx_mux = (0u << IO_MUX_MCU_SEL_S);
    *rx_mux = (0u << IO_MUX_MCU_SEL_S) | IO_MUX_FUN_IE | IO_MUX_FUN_WPU;
}

void serialWrite(uint8_t byte)
{
    while (_tx_fifo_count() >= UART_FIFO_LEN)
        ;
    UART_FIFO_REG = (uint32_t)byte;
}

void serialPrint(const char *s)
{
    while (*s)
        serialWrite((uint8_t)*s++);
}

void serialPrintln(const char *s)
{
    serialPrint(s);
    serialWrite('\r');
    serialWrite('\n');
}

void serialPrintInt(int32_t n)
{
    char buf[12];
    char *p = buf + sizeof(buf) - 1;
    uint32_t u;
    int neg = 0;

    *p = '\0';

    if (n < 0) {
        neg = 1;
        u   = (uint32_t)(-(n + 1)) + 1u;   /* avoids UB on INT32_MIN */
    } else {
        u = (uint32_t)n;
    }

    if (u == 0) {
        *--p = '0';
    } else {
        while (u) {
            *--p = '0' + (char)(u % 10u);
            u /= 10u;
        }
    }

    if (neg) *--p = '-';

    serialPrint(p);
}

void serialPrintHex(uint32_t n)
{
    static const char hex[] = "0123456789ABCDEF";
    char buf[11];
    buf[0]  = '0';
    buf[1]  = 'x';
    buf[10] = '\0';
    for (int i = 9; i >= 2; i--) {
        buf[i] = hex[n & 0xFu];
        n >>= 4;
    }
    serialPrint(buf);
}

int serialAvailable(void)
{
    return (int)_rx_fifo_count();
}

int serialRead(void)
{
    if (_rx_fifo_count() == 0)
        return -1;
    return (int)(UART_FIFO_REG & 0xFFu);
}

void serialFlush(void)
{
    while (_tx_fifo_count() > 0)
        ;
}
