#ifndef KEYPAD_DRIVER_H
#define KEYPAD_DRIVER_H

#include <avr/io.h>
#include "../../Utilities/AVR_ATMega32.h"

#define keypadPORT PORTC
#define keypadPIN PINC
#define keypadDDR DDRC

#define Row_0     0
#define Row_1     1
#define Row_2     2
#define Row_3     3

#define Col_0     4
#define Col_1     5
#define Col_2     6
#define Col_3     7

/***
 * [Purpose] Initialize Keypad.
 *
 * Initializes the keypad by: 
 *      [1] Setting the direction of the rows as input.
 *      [2] Setting the direction of the columns (where the rows are connected) as output.
 *      [3] Setting all the pins of the port that the keypad is connected to.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void Keypad_init(void);

/***
 * [Purpose] Read the pressed key and return its value.
 *  This method is based on the fact that the only time to get a connection
 *   between a row and a column is by pressing the key connected to both of them.
 * 
 *  1. Setting all the keypadCol pins of the port that the keypad is connected to (pins 4, 5, 6 and 7)
 *  2. Ground one column at a time.
 *  3. Check which row read  0. (This way we can know exactly which key it was that caused the zero)
 *  4. Return the value of the pressed key.
 * 
 * [Arguments] None.
 * [Return Type] Unsigned character.
 *
 ***/
U8 Keypad_keylisten(void);

#endif