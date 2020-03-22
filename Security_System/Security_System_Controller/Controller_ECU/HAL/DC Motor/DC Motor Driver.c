#include "DC Motor Driver.h"

void DCMotor_Init(void){
	DIO_PinDirection(B, MOTOR_ENABLE, OUTPUT);
	DIO_PinDirection(B, PIN_1, OUTPUT);
	DIO_PinDirection(B, PIN_2, OUTPUT);
}

void DCMotor_ClockwiseRotation(void){
	DIO_PinWrite(B, MOTOR_ENABLE, 1);
	DIO_PinWrite(B, PIN_1, 1);
	DIO_PinWrite(B, PIN_2, 0);
}

void DCMotor_AntiClockwiseRotation(void){
	DIO_PinWrite(B, MOTOR_ENABLE, 1);
	DIO_PinWrite(B, PIN_1, 0);
	DIO_PinWrite(B, PIN_2, 1);
}

void DCMotor_Stop(void){
	DIO_PinWrite(B, MOTOR_ENABLE, 0);
	DIO_PinWrite(B, PIN_1, 0);
	DIO_PinWrite(B, PIN_2, 0);
}