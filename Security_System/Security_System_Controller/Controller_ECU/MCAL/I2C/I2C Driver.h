#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <avr/io.h>
#include "../../Utilities/AVR_ATMega32.h"

#define F_CPU 8000000UL
#define TWBR_VALUE(SCL_FREQ, PRESCALER)      ((((F_CPU) / (SCL_FREQ)) - 16) / ((PRESCALER) * 2))

/***
 * [Purpose] Initialize I2C.
 *
 * Initializes the I2C by: 
 *      [1] Invoking I2C_Prescaler() to set the prescaler configuration.
 *      [2] Invoking I2C_Set_Address() to set the address of the slave.
 *      [3] Setting the value of TWBR.
 *      [4] Enabling I2C module.
 *
 * [Arguments] prescaler : could be 1, 4, 16 or 64.
 *             address : slave address.
 *             Clock : SCL frequency.    
 * [Return Type] Void.
 *
 ***/
void I2C_Init(int prescaler, U8 address, U8 Clock);

/***
 * [Purpose] Set the prescaler configuration.
 *
 * This method sets or clears TWPS0 and TWPS1 pins in TWSR based on the prescaler value.
 *
 * [Arguments] prescaler : could be 1, 4, 16 or 64.       
 * [Return Type] Void.
 *
 ***/
void I2C_Prescaler(int prescaler);


/***
 * [Purpose] Set the address of the slave.
 *
 * Sets the address of the slave in the most significant 
 *  seven bits of TWAR.
 *
 * [Arguments] address : slave address.    
 * [Return Type] Void.
 *
 ***/
void I2C_Set_Address(U8 address);


/***
 * [Purpose] Receive a byte.
 *
 * 1. Setting the TWEN and TWINT bits of the TWCR register to one to start receiving a byte.
 * 2. Setting the TWEA bit of the TWCR register to one to return acknowledgment.
 * 3. Polling the TWINT flag in the TWCR register to make sure the byte has been received completely.
 * 4. Return the data stored in TWDR
 *
 * [Arguments] ACK : acknowledgment.
 * [Return Type] unsigned character.
 *
 ***/
U8 I2C_Read(U8 ACK);


/***
 * [Purpose] Transmit a byte.
 *
 * 1. Copying the data byte to the TWDR.
 * 2. Setting the TWEN and TWINT bits of the TWCR register to one to start sending the byte.
 * 3. Polling the TWINT flag in the TWCR register to make sure the byte has been transmitted completely.
 *
 *
 * [Arguments] data : data to be transmitted.
 * [Return Type] Void.
 *
 ***/
void I2C_Write(U8 data);


/***
 * [Purpose] Start condition.
 *
 * 1. Enable TWI module.
 * 2. Initiate start condition.
 * 3. Clear the interrupt flag to initiate operation of the TWI module to transmit the start condition.
 * 4. Poll the TWINT flag in the TWCR register to make sure the start condition is transmitted completely.
 *
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void I2C_Start(void);


/***
 * [Purpose] Stop condition.
 *
 * Transmits stop condition to stop data transfer.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void I2C_Stop(void);


#endif
