#include "Controller.h"

int main(void){
	startUp_Controller();
	isFirstTime();
	while (1){}
}

void startUp_Controller(void){
	initialize_Devices();
}


void initialize_Devices(void){
	int BaudRate = 9600;
	USART_Init(BaudRate, NO_PARITY, ONE_STOP_BIT, EIGHT_BITS, ASYNCHRONOUS);
	Buzzer_Init();
	DCMotor_Init();
	EEPROM_Init(1, 1, 400000);
}

void isFirstTime(void){
	U8 FisrtTimeCheckData;
	while(USART_Receive() != IS_FIRST_TIME);  // Busy waiting

	/*Read from the address that is used to tell whether there is saved passwords or not 
	and then store the data in FisrtTimeCheckData */
	EEPROM_Read(FIRST_TIME_CHECK_ADDRESS, &FisrtTimeCheckData);

	if(FisrtTimeCheckData == SAVED_PASSWORDS){
		USART_Transmit(SAVED_PASSWORDS);	
		normal_SystemOperations();
	}
	
	else if(FisrtTimeCheckData == NO_SAVED_PASSWORDS){
		USART_Transmit(NO_SAVED_PASSWORDS);
		firstTime_SystemOperations();
	}
}


void firstTime_SystemOperations(void){
	U8 signal;
	/// Busy wait until the HMI sends a signal to store new password.
	while(USART_Receive() != ENTER_PASSWORD);
	_delay_ms(100);
	setPassword();

	signal = USART_Receive();
	
	if(signal == PASSWORD_MISMATCH){
		firstTime_SystemOperations();
	}
	
	else if(signal == PASSWORD_MATCH){
		normal_SystemOperations();
    }

}

void setPassword(){
	int i;
	for(i = 0 ; i < PASSWORD_SIZE ; i++){
		EEPROM_Write(EEPROM_BASE_ADDRESS + i, USART_Receive());
		_delay_ms(100);
	}
	EEPROM_Write(FIRST_TIME_CHECK_ADDRESS, SAVED_PASSWORDS);
	_delay_ms(100);
}



void normal_SystemOperations(void){
	enterPassword();
	U8 operation = USART_Receive();
	
	if(operation == REQUEST_TO_OPEN_DOOR){
		openDoor();
	}
	else if(operation == REQUEST_TO_CHANGE_PASS){
		changePassword();
	}
}

void enterPassword(void){
	/*This variable counts the number of times the user enters incorrect passwords, 
	so that we can limit the number of times the user could enter incorrect 
	password before the system is locked.*/
	static int Mismatch_Counter = 0;  	
	
	/*This function returns 1 if the password the user entered and the
	one stored in the memory are identical. Otherwise, it returns 0*/
	int AthorizedUser = authorityChecking(); 
	
	if (AthorizedUser){
		/// Reseting the Mismatch_Counter.
		Mismatch_Counter = 0; 
		USART_Transmit(CORRECT_PASSWORD);
	}
	
	else if(!AthorizedUser){
		Mismatch_Counter++;
		if(Mismatch_Counter >= 3){
			USART_Transmit(REPEATEDLY_INCORRECT);
			Buzzer_TurnOn();
			_delay_ms(100000);
			USART_Transmit(SYSTEM_UNLOCKED);
			normal_SystemOperations();
		}
		
		else {
			USART_Transmit(INCORRECT_PASSWORD);
			enterPassword();
		}
	}
}

int authorityChecking(void){
	int Actual_Password[PASSWORD_SIZE], Expected_Password[PASSWORD_SIZE];
	int i;   /// Loop counter.
	int Mismatch_Flag = 1; 
	while(USART_Receive() != ENTER_PASSWORD);
	
	/// Store the password entered by the user in Actual_Password array.
	for(i = 0; i < PASSWORD_SIZE; i++){
		Expected_Password[i] = USART_Receive();
	}
	
	/// Store the password saved previously in the memory.
	for(i = 0; i < PASSWORD_SIZE; i++){
		EEPROM_Read(EEPROM_BASE_ADDRESS + i, Actual_Password[i]);
	}
	
	/// Compare both the entered password and the stored one.
	for(i = 0; i < PASSWORD_SIZE; i++){
		if(Actual_Password[i] != Expected_Password[i]){
			Mismatch_Flag = 0;
		}
	}
	
	return Mismatch_Flag;
}