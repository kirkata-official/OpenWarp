#include "../../../../../include/OpenWarp.h"
#include "memory-map.h"

void kill_watchdogs(void) {
    // 1. Kill RTC Watchdog
    *((volatile uint32_t *)RTC_CNTL_WDTWPROTECT_REG) = WDT_WKEY_VALUE;
    *((volatile uint32_t *)RTC_CNTL_WDTCONFIG0_REG) = 0;
    *((volatile uint32_t *)RTC_CNTL_WDTWPROTECT_REG) = 0;

    // 2. Kill Timer Group 0 Watchdog
    *((volatile uint32_t *)TIMG0_WDTWPROTECT_REG) = WDT_WKEY_VALUE;
    *((volatile uint32_t *)TIMG0_WDTCONFIG0_REG) = 0;
    *((volatile uint32_t *)TIMG0_WDTWPROTECT_REG) = 0;

    // 3. Kill Timer Group 1 Watchdog
    *((volatile uint32_t *)TIMG1_WDTWPROTECT_REG) = WDT_WKEY_VALUE;
    *((volatile uint32_t *)TIMG1_WDTCONFIG0_REG) = 0;
    *((volatile uint32_t *)TIMG1_WDTWPROTECT_REG) = 0;
}

void ping_watchdogs(void) {
    // Ping the RTC Watchdog (The 600ms culprit)
    *((volatile uint32_t *)RTC_CNTL_WDTWPROTECT_REG) = WDT_WKEY_VALUE;
    *((volatile uint32_t *)RTC_CNTL_WDTFEED_REG) = 1;
    *((volatile uint32_t *)RTC_CNTL_WDTWPROTECT_REG) = 0;

    // Ping Timer Group 0 (The system watchdog)
    *((volatile uint32_t *)TIMG0_WDTWPROTECT_REG) = WDT_WKEY_VALUE;
    *((volatile uint32_t *)TIMG0_WDTFEED_REG) = 1;
    *((volatile uint32_t *)TIMG0_WDTWPROTECT_REG) = 0;
}