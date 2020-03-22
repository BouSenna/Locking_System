#include "HMI.h"

int main(void){
	while (1){}
}

void initialize_Devices(void){
	int BaudRate = 9600;
	/// Initialize LCD.
	LCD_Init();
	/// Initialize Keypad.
	Keypad_init();
	/// Setting the configurations and initializing USART.
	USART_Init(BaudRate, NO_PARITY, ONE_STOP_BIT, EIGHT_BITS, ASYNCHRONOUS);
}