#ifndef OPENWARP_MEMMAP_H
#define OPENWARP_MEMMAP_H

#define _REG(addr)   (*(volatile uint32_t *)(addr))
#define DR_REG_GPIO_BASE            0x3FF44000UL

// Output – pins 0-31 
#define GPIO_OUT_REG                _REG(DR_REG_GPIO_BASE + 0x004)
#define GPIO_OUT_W1TS_REG           _REG(DR_REG_GPIO_BASE + 0x008)
#define GPIO_OUT_W1TC_REG           _REG(DR_REG_GPIO_BASE + 0x00C)
// Output – pins 32-39
#define GPIO_OUT1_REG               _REG(DR_REG_GPIO_BASE + 0x010)
#define GPIO_OUT1_W1TS_REG          _REG(DR_REG_GPIO_BASE + 0x014)
#define GPIO_OUT1_W1TC_REG          _REG(DR_REG_GPIO_BASE + 0x018)
// Output-enable – pins 0-31
#define GPIO_ENABLE_REG             _REG(DR_REG_GPIO_BASE + 0x020)
#define GPIO_ENABLE_W1TS_REG        _REG(DR_REG_GPIO_BASE + 0x024)
#define GPIO_ENABLE_W1TC_REG        _REG(DR_REG_GPIO_BASE + 0x028)
// Output-enable – pins 32-39
#define GPIO_ENABLE1_REG            _REG(DR_REG_GPIO_BASE + 0x02C)
#define GPIO_ENABLE1_W1TS_REG       _REG(DR_REG_GPIO_BASE + 0x030)
#define GPIO_ENABLE1_W1TC_REG       _REG(DR_REG_GPIO_BASE + 0x034)
// Input – pins 0-31 / 32-39
#define GPIO_IN_REG                 _REG(DR_REG_GPIO_BASE + 0x03C)
#define GPIO_IN1_REG                _REG(DR_REG_GPIO_BASE + 0x040)

#define GPIO_FUNC_OUT_SEL_CFG_BASE  (DR_REG_GPIO_BASE + 0x530UL)
#define GPIO_FUNC_OUT_SEL_CFG(n)    _REG(GPIO_FUNC_OUT_SEL_CFG_BASE + (n)*4UL)
#define SIG_GPIO_OUT_IDX            256u

// Per-signal function-input-select registers (base + 0x130 + sig*4)

#define GPIO_FUNC_IN_SEL_CFG_BASE   (DR_REG_GPIO_BASE + 0x130UL)
#define GPIO_FUNC_IN_SEL_CFG(s)     _REG(GPIO_FUNC_IN_SEL_CFG_BASE + (s)*4UL)

#define DR_REG_IO_MUX_BASE          0x3FF49000UL

// Offsets for GPIO 0-39

static const uint8_t _iomux_off[40] = {
 /* 0     1     2     3     4     5     6     7     8     9  */
   0x44, 0x88, 0x40, 0x84, 0x48, 0x6C, 0x60, 0x64, 0x68, 0x54,
 /* 10    11    12    13    14    15    16    17    18    19 */
   0x58, 0x5C, 0x34, 0x38, 0x30, 0x3C, 0x4C, 0x50, 0x70, 0x74,
 /* 20    21    22    23    24    25    26    27    28    29 */
   0x78, 0x7C, 0x80, 0x8C, 0x90, 0x24, 0x28, 0x2C, 0x00, 0x00,
 /* 30    31    32    33    34    35    36    37    38    39 */
   0x00, 0x00, 0x1C, 0x20, 0x14, 0x18, 0x04, 0x08, 0x0C, 0x10,
};

#define IO_MUX_PAD(n)       _REG(DR_REG_IO_MUX_BASE + _iomux_off[n])
#define IO_MUX_MCU_SEL_S    12
#define IO_MUX_MCU_SEL_M    (0x7u << IO_MUX_MCU_SEL_S)
#define IO_MUX_FUN_WPU      (1u << 7)
#define IO_MUX_FUN_WPD      (1u << 8)
#define IO_MUX_FUN_IE       (1u << 9)
#define IO_MUX_FUNC_GPIO    2u

#define DR_REG_RTC_CNTL_BASE        0x3FF48000UL

#define RTC_CPU_FREQ_REG            _REG(DR_REG_RTC_CNTL_BASE + 0xB0)
#define RTC_APB_FREQ_REG            _REG(DR_REG_RTC_CNTL_BASE + 0xB4)

#define DR_REG_UART0_BASE           0x3FF40000UL
#define DR_REG_UART1_BASE           0x3FF50000UL
#define DR_REG_UART2_BASE           0x3FF6E000UL

// UART0 in use for standard serial debugging

#define UART_BASE                   DR_REG_UART0_BASE

#define UART_FIFO_REG               _REG(UART_BASE + 0x00)  /* TX/RX FIFO  */
#define UART_STATUS_REG             _REG(UART_BASE + 0x1C)  /* status      */
#define UART_CONF0_REG              _REG(UART_BASE + 0x20)  /* config 0    */
#define UART_CONF1_REG              _REG(UART_BASE + 0x24)  /* config 1    */
#define UART_CLKDIV_REG             _REG(UART_BASE + 0x14)  /* baud divisor*/

// UART_STATUS bits

#define UART_TXFIFO_CNT_S           16
#define UART_TXFIFO_CNT_M           (0xFFu << UART_TXFIFO_CNT_S)
#define UART_RXFIFO_CNT_S           0
#define UART_RXFIFO_CNT_M           (0xFFu << UART_RXFIFO_CNT_S)

// UART TX FIFO depth

#define UART_FIFO_LEN               128

#define DR_REG_DPORT_BASE           0x3FF00000UL
#define DPORT_PERIP_CLK_EN_REG      _REG(DR_REG_DPORT_BASE + 0x0C0)
#define DPORT_PERIP_RST_EN_REG      _REG(DR_REG_DPORT_BASE + 0x0C4)
#define DPORT_UART_CLK_EN           (1u << 2)
#define DPORT_UART_RST              (1u << 2)

#define SOC_IRAM_LOW    0x40080000UL
#define SOC_IRAM_HIGH   0x400A0000UL
#define SOC_DRAM_LOW    0x3FFB0000UL
#define SOC_DRAM_HIGH   0x3FFF0000UL
#define SOC_RTC_IRAM    0x400C0000UL
#define SOC_RTC_DRAM    0x3FF80000UL

// Watchdog Handling

#define RTC_CNTL_WDTCONFIG0_REG   0x3FF4808C
#define RTC_CNTL_WDTWPROTECT_REG  0x3FF480A4
#define RTC_CNTL_WDTFEED_REG      0x3FF480A0

#define TIMG0_WDTCONFIG0_REG      0x3FF5F048
#define TIMG0_WDTWPROTECT_REG     0x3FF5F064
#define TIMG0_WDTFEED_REG         0x3FF5F060

#define TIMG1_WDTCONFIG0_REG      0x3FF60048
#define TIMG1_WDTWPROTECT_REG     0x3FF60064

// WDT magic key

#define WDT_WKEY_VALUE            0x50D83AA1

#endif
