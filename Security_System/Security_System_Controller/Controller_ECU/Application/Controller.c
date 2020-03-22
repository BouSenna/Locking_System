#include "Controller.h"

int main(void){
	while (1){}
}

void initialize_Devices(void){
	int BaudRate = 9600;
	USART_Init(BaudRate, NO_PARITY, ONE_STOP_BIT, EIGHT_BITS, ASYNCHRONOUS);
	Buzzer_Init();
	DCMotor_Init();
	EEPROM_Init(1, 1, 400000);
}
 