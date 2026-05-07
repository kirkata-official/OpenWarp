#pragma once

#ifndef OPENWARP_H
#define OPENWARP_H

#include "source/master.h"

// Core info

#define VERSION 1.0

// Math

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

// Functions

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define labs(x) ((x)<0?-(x):(x))
#define clamp(v, lo, hi)  min(max((v), (lo)), (hi))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

// flags

#define NONE -1

// Logic Levels

#define HIGH    1
#define LOW     0

// Pin Status

#define OUTPUT  1
#define INPUT   0
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3

// SPI Modes

#define SPI_MODE0       0
#define SPI_MODE1       1
#define SPI_MODE2       2
#define SPI_MODE3       3

// Roles

#define MASTER      0
#define SLAVE       1

// GPIO

void pinMode(uint8_t pin, uint8_t mode);
void pinWrite(uint8_t pin, uint8_t val);
int pinRead(uint8_t pin);
void pinToggle(uint8_t pin); 

// Timing

uint32_t millis(void);
uint32_t micros(void);
void wait(uint32_t ms);
void waitMicroseconds(uint32_t us);

// UART

void serialBegin(uint32_t baud);
void serialWrite(uint8_t byte);
void serialPrint(const char *s);
void serialPrintln(const char *s);
void serialPrintInt(int32_t n);
void serialPrintHex(uint32_t n);
int  serialAvailable(void);
int  serialRead(void);
void serialFlush(void);

// SPI

void     spiBegin(uint8_t bus, uint8_t role, uint8_t mode, uint32_t freq_hz);
uint8_t  spiTransfer(uint8_t bus, uint8_t byte);
void     spiTransferBuf(uint8_t bus, const uint8_t *tx, uint8_t *rx, uint32_t len);
int      spiAvailable(uint8_t bus);
void     spiOnReceive(uint8_t bus, void (*fn)(uint8_t byte));
void     spiEnd(uint8_t bus);

// I2C

void     i2cBegin(uint8_t bus, uint8_t role, uint8_t sda, uint8_t scl, uint32_t freq_hz, uint8_t addr);
int      i2cWrite(uint8_t bus, uint8_t addr, const uint8_t *buf, uint32_t len, uint8_t stop);
int      i2cRead(uint8_t bus, uint8_t addr, uint8_t *buf, uint32_t len, uint8_t stop);
void     i2cWriteByte(uint8_t bus, uint8_t byte);
int      i2cAvailable(uint8_t bus);
int      i2cReadByte(uint8_t bus);
void     i2cOnReceive(uint8_t bus, void (*fn)(uint32_t num_bytes));
void     i2cOnRequest(uint8_t bus, void (*fn)(void));
void     i2cPoll(uint8_t bus);
void     i2cEnd(uint8_t bus);

// WDT

void kill_watchdogs(void);
void feed_watchdogs(void);

#endif