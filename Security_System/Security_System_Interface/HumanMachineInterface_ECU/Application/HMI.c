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

void initial_LCDScrollText(void){
	int i, j, str_size = 30;
	char temp;
	char str[30] = "Please press 0 to continue.   ";
	_delay_ms(1000);
	for (i = 0; i < str_size - 1; i++) {
		LCD_SetCursor(0, 0);
		LCD_WriteString(str);

		/// Storing the value of the first index of the array in temp variable.
		temp = str[0]; 
		/// Shift all the characters one place to the left.
		for (j = 0; j < str_size - 1; j++) {
			str[j] = str[j + 1];
		}
		/// Add the value of the temp variable at the end of the array.
		str[str_size - 2] = temp;
		str[str_size - 1] = 0;   // Terminator.
		_delay_ms(1000);
	}
} 