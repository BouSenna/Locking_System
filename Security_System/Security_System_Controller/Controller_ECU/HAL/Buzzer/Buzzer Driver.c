#include "Buzzer Driver.h"

void Buzzer_Init(void){
	/// Set the direction of the buzzer to output.
	DIO_PinDirection(B, BUZZER, OUTPUT);
}

void Buzzer_TurnOn(void){
	/// Set the buzzer bit to turn the buzzer on.
	DIO_PinWrite(B, BUZZER, 1);
}

void Buzzer_TurnOff(void){
	/// Clear the buzzer bit to stop the buzzer.
	DIO_PinWrite(B, BUZZER, 0);
}