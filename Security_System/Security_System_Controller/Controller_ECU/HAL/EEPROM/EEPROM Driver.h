#ifndef EEPROM_DRIVER_H
#define EEPROM_DRIVER_H

#include <avr/io.h>
#include "../../Utilities/AVR_ATMega32.h"
#include "../../MCAL/I2C/I2C Driver.h"

#define SLAVE_ADDRESS_W(Address)       (U8)(0xA0 | ((Address & 0x700) >> 7))
#define SLAVE_ADDRESS_R(Address)       (U8)(0x01 | (0xA0 | ((Address & 0x700) >> 7)))


/***
 * [Purpose] Initialize External EEPROM.
 *
 * Initializes the EEPROM by initializing I2C.
 *
 *
 * [Arguments] prescaler : could be 1, 4, 16 or 64.
 *             address : slave address.
 *             Clock : SCL frequency.   
 * [Return Type] Void.
 *
 ***/
void EEPROM_Init(int prescaler, U8 address, U8 Clock);


/***
 * [Purpose] Read data from memory.
 *
 * 1. Send start bit to initiate start condition.
 * 2. Write the slave address and write operation bit. 
 * 3. Write the memory location.
 * 4. Send another start bit to change write operation to read.
 * 5. Write the slave address and read operation bit.
 * 6. Store the data in the memory.
 * 7. Send stop bit.
 *
 *
 * [Arguments] address : slave address.
 *             data : variable to store the data in.
 * [Return Type] Void.
 *
 ***/
void EEPROM_Read(int address, U8* data);


/***
 * [Purpose] Write data in memory.
 *
 * 1. Send start bit to initiate start condition.
 * 2. Write the slave address and write operation bit. 
 * 3. Write the memory location.
 * 4. Write the data in memory.
 * 5. Send stop bit.
 *
 *
 * [Arguments] address : slave address.
 *             data : data to be stored.
 * [Return Type] Void.
 *
 ***/
void EEPROM_Write(int address, U8 data);

#endif
