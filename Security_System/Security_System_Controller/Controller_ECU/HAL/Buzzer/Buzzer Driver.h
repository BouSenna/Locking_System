#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

#include <avr/io.h>
#include "../../Utilities/AVR_ATMega32.h"
#include "../../Utilities/Basic_Macros.h"

#define BUZZER    PB7


/***
 * [Purpose] Initialize Buzzer.
 *
 * Initializes the buzzer by setting the direction of  
 *  the buzzer as output.
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void Buzzer_Init(void);


/***
 * [Purpose] Fire the buzzer.
 *
 * Sets the buzzer bit to turn the buzzer on.
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void Buzzer_TurnOn(void);


/***
 * [Purpose] Turn off the buzzer.
 *
 * Clears the buzzer bit to stop the buzzer.
 *
 * [Arguments] None.   
 * [Return Type] Void.
 *
 ***/
void Buzzer_TurnOff(void);


#endif