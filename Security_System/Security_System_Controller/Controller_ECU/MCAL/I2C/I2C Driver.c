#include "I2C Driver.h"

void I2C_Init(int prescaler, U8 address, U8 Clock){
	/// Set the prescaler configuration.
	I2C_Prescaler(prescaler);
	/// Set the address of the slave.
	I2C_Set_Address(address);
	/// Set the value of TWBR.
	TWBR = TWBR_VALUE(Clock, prescaler);
	TWCR = (1 << TWEN);
}

void I2C_Prescaler(int prescaler){
	switch(prescaler){
		case 1:
			TWSR &= ~(1 << TWPS0);
			TWSR &= ~(1 << TWPS1);
			break;
		case 4:
			TWSR |= (1 << TWPS0);
			TWSR &= ~(1 << TWPS1);
			break;
		case 16:
			TWSR &= ~(1 << TWPS0);
			TWSR |= (1 << TWPS1);
			break;
		case 64:
			TWSR |= (1 << TWPS0);
			TWSR |= (1 << TWPS1);
			break;
	}
}

void I2C_Set_Address(U8 address){
	/// Setting the address of slave in the most significant seven bits.
	TWAR = (TWAR & 0x01) | (address << 1);
}

U8 I2C_Read(U8 ACK){
	/// Setting the TWEN and TWINT bits of the TWCR register to one to start receiving a byte.
	TWCR = (1 << TWINT) | (1 << TWEN);
	/// Setting the TWEA bit of the TWCR register to one to return acknowledgment.
	TWCR = (ACK << TWEA);
	
	/// Polling the TWINT flag in the TWCR register to make sure the byte has been received completely.
	while ((TWCR & 0x80) == 0);
	return TWDR;
}

void I2C_Write(U8 data){
	/// Copying the data byte to the TWDR.
	TWDR = data;
	/// Setting the TWEN and TWINT bits of the TWCR register to one to start sending the byte.
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	/// Polling the TWINT flag in the TWCR register to make sure the byte has been transmitted completely.
	while ((TWCR & 0x80) == 0);
}

void I2C_Start(void){
	/// Enable TWI module.
	TWCR = (1 << TWEN);
	/// Initiate start condition.
	TWCR = (1 << TWSTA);
	/// Clears the interrupt flag to initiate operation of the TWI module to transmit the start condition.
	TWCR = (1 << TWINT);
	
	/// Poll the TWINT flag in the TWCR register to make sure the start condition is transmitted completely.
	while ((TWCR & 0x80) == 0);
}

void I2C_Stop(void){
	/// Transmitting stop condition to stop data transfer.
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}




