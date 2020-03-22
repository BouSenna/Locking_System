#include <avr/io.h>
#include "../../Utilities/AVR_ATMega32.h"
#include "../../MCAL/DIO/DIO Driver.h"

#ifndef DC_MOTOR_DRIVER_H
#define DC_MOTOR_DRIVER_H

#define MOTOR_ENABLE          PB2
#define PIN_1                 PB0 
#define PIN_2                 PB1


/***
 * [Purpose] Initialize DC Motor.
 *
 * Initializes the DC Motor by setting the direction of the pin_1, 
 *  pin_2 and the enable pins as output. 
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void DCMotor_Init(void);


/***
 * [Purpose] Clockwise rotation.
 *
 * 1. Set the enable pin  
 * 2. Set pin_1 of the port in which the motor is connected to.
 * 3. Clear pin_2 of the port in which the motor is connected to.
 *
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void DCMotor_ClockwiseRotation(void);


/***
 * [Purpose] Anti-Clockwise rotation.
 *
 * 1. Set the enable pin  
 * 2. Clear pin_1 of the port in which the motor is connected to.
 * 3. Set pin_2 of the port in which the motor is connected to.
 *
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void DCMotor_AntiClockwiseRotation(void);


/***
 * [Purpose] Stop the motor
 *
 * Clear Pin_1, Pin_2 and the enable pins.
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void DCMotor_Stop(void);

#endif