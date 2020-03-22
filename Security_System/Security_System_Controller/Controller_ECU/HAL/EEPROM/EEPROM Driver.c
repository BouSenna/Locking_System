#include "EEPROM Driver.h"

void EEPROM_Init(int prescaler, U8 address, U8 Clock){
	I2C_Init(prescaler, address, Clock);
}

void EEPROM_Read(int address, U8* data){
	/// Send start bit to initiate start condition.
	I2C_Start();
	/// Write the slave address and write operation bit. 
	I2C_Write(SLAVE_ADDRESS_W(address));
	/// Write the memory location.
	I2C_Write((U8)(address));
	
	/// Send another start bit to change write operation to read.
	I2C_Start();
	/// Write the slave address and read operation bit.
	I2C_Write(SLAVE_ADDRESS_R(address));
	/// Store the data in the memory.
	*data = I2C_Read(0);
	/// Send stop bit.
	I2C_Stop();
}

void EEPROM_Write(int address, U8 data){
	/// Send start bit to initiate start condition.
	I2C_Start();
	/// Write the slave address and write operation bit.
	I2C_Write(SLAVE_ADDRESS_W(address));
	/// Write the memory location.	
	I2C_Write((U8)(address));
	/// Write the data in memory.
	I2C_Write(data);
	/// Send stop bit.	
	I2C_Stop();
}
