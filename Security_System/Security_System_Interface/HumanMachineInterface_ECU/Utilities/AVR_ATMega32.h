#ifndef AVRATMEGA32_H
#define AVRATMEGA32_H

#include "Basic_Datatypes.h"
#include "Basic_Macros.h"

/// ATMega32 Ports.
#define A 0x39
#define B 0x36
#define C 0x33
#define D 0x30

/// ATMega32 Pins.
/******** 0 ********/
#define PIN_RXD     0
#define PIN_SCL     0
#define PIN_XCK     0
#define PIN_T0      0
#define PIN_ADC0    0
/******** 1 ********/
#define PIN_TXD     1
#define PIN_SDA     1
#define PIN_T1      1
#define PIN_ADC1    1
/******** 2 ********/
#define PIN_INT0    2
#define PIN_TCK     2
#define PIN_AIN0    2
#define PIN_T2      2
#define PIN_ADC2    2
/******** 3 ********/
#define PIN_INT1    3
#define PIN_TMS     3
#define PIN_AIN1    3
#define PIN_OC0     3
#define PIN_ADC3    3
/******** 4 ********/
#define PIN_ADC4    4
#define PIN_TDO     4
#define PIN_OC1B    4
#define PIN_SS      4
/******** 5 ********/
#define PIN_MOSI    5
#define PIN_TDI     5
#define PIN_ADC5    5
#define PIN_OC1A    5
/******** 6 ********/
#define PIN_MISO    6
#define PIN_ADC6    6
#define PIN_TOSC1   6
#define PIN_ICP1    6
/******** 7 ********/
#define PIN_OC2     7
#define PIN_SCK     7
#define PIN_ADC7    7
#define PIN_TOSC2   7

/// ATMega32 directions.
#define INPUT	0x00
#define OUTPUT	0x01

/// Checking the validity of input.
#define IS_PORT(port)         (port == A || port == B || port == C || port == D)
#define IS_PIN(pin)           (pin >= 0 && pin <=7)
#define IS_DIR(direction)     (direction == 0x00 || direction == 0x01)

/// ATMega32 port's registers.
#define DDR(port)   (*((volatile U8 *const)(port + 0x01)))
#define PORT(port)  (*((volatile U8 *const)(port + 0x02)))
#define PIN(port)   (*((volatile U8 *const)(port + 0x00)))

#endif
