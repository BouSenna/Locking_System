#include "HMI.h"

int main(void){
	startUp_HMI();
	while (1){}
}

void startUp_HMI(void){
	/// Initialize the devices that will be used. 
	initialize_Devices();
	/// Display message to user to inform him to press 0 key when he wishes to begin using the system.
	initial_LCDScrollText();
	/// Busy waiting till the end-user presses 0 key.
	while(Keypad_keylisten() != '0');
	/// Delay for pressing time.
	_delay_ms(500);
	/// Clear the LCD.
	LCD_WriteCommand(LCD_CLEAR_CMD);
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

void isFirstTime(void){
	U8 signal;
	USART_Transmit(IS_FIRST_TIME);
	signal = USART_Receive();
	if(signal == SAVED_PASSWORDS){
		normal_SystemOperations();
	}
	else if(signal == NO_SAVED_PASSWORDS){
		firstTime_SystemOperations();
	}
}

void normal_SystemOperations(void){
	
}


void firstTime_SystemOperations(void){
	U8 Password[PASSWORD_SIZE];
	U8 ConfPassword[PASSWORD_SIZE];
	
	/* This is a function to enter the password you want to set*/
	setPassword(Password, SETTING_PASSWORD);
	/* Re-enter the password for verification */
	setPassword(ConfPassword, CONFIRM_PASSWORD);
	
	if(passwordMatch(&Password, &ConfPassword)){
		LCD_WriteString(" Password Saved.");
		USART_Transmit(PASSWORD_MATCH);
		_delay_ms(10000);
	    normal_SystemOperations();
	}
	
	else {
		LCD_WriteCommand(LCD_CLEAR_CMD); 
		LCD_WriteString("Didn't Match");
		LCD_SetCursor(1,0);
		LCD_WriteString("Please try again");
		_delay_ms(10000);
		USART_Transmit(PASSWORD_MISMATCH);
		clearMemory(); 
		
		LCD_WriteCommand(LCD_CLEAR_CMD);
		firstTime_SystemOperations();
	}
	
	LCD_WriteCommand(LCD_CLEAR_CMD);
}

void setPassword(U8 *password, int action){
	int i;
	USART_Transmit(ENTER_PASSWORD);
	/// In case you are entering the password for the first time
	if (action == SETTING_PASSWORD){
		LCD_WriteCommand(LCD_CLEAR_CMD);
		LCD_WriteString("Enter password:");
		LCD_SetCursor(1,0);
		LCD_WriteCharacter(' ');
		for(i=0 ; i<PASSWORD_SIZE ; i++) {
			/// Send pressed key to Controller to store it.
			while((*(password + i) = Keypad_keylisten()) ==' ');
			USART_Transmit(*(password + i));
			LCD_WriteCharacter('*');
			_delay_ms(5000);
		}
	}
	
	/// Re-writing the password for confirmation.
	else if (action == CONFIRM_PASSWORD){
		LCD_WriteCommand(LCD_CLEAR_CMD);
		LCD_WriteString("Reenter password");
		LCD_SetCursor(1,0);
		LCD_WriteCharacter(' ');
		for(i=0 ; i<PASSWORD_SIZE ; i++) {
			/// Send pressed key to Controller to store it.
			while((*(password + i) = Keypad_keylisten()) ==' ');
			LCD_WriteCharacter('*');
			_delay_ms(5000);
		}
	}
	LCD_WriteCommand(LCD_CLEAR_CMD);
}

int passwordMatch(U8* pass1, U8* pass2){
	int counter;
	for(counter = 0; counter < PASSWORD_SIZE; counter++){
		if(*(pass1 + counter) != *(pass2 + counter))
			return 0;
	}
	return 1;
}

void clearMemory(){
	
}