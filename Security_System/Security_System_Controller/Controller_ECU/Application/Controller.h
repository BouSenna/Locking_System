#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/USART/USART_Config.h"
#include "../MCAL/USART/USART Driver.h"
#include "../Utilities/Basic_Datatypes.h"
#include "../HAL/DC Motor/DC Motor Driver.h"
#include "../HAL/Buzzer/Buzzer Driver.h"
#include "../HAL/EEPROM/EEPROM Driver.h"


#define EEPROM_BASE_ADDRESS        0x0000 	/// TODO: Check the data sheet
#define FIRST_TIME_CHECK_ADDRESS   0xffff	/// TODO: Check the data sheet
#define PASSWORD_SIZE              4

#define ENTER_PASSWORD             0x10

#define IS_FIRST_TIME              0x11
#define SAVED_PASSWORDS            0x12
#define NO_SAVED_PASSWORDS         0x13


#define PASSWORD_MATCH             0x14
#define PASSWORD_MISMATCH          0x15


/***
 * [Purpose] Starting and setting up the controller micro-controller.
 *
 * Invokes initialize_Devices : Initializes set of devices that will be used.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void startUp_Controller(void);


/***
 * [Purpose] Initialize the devices that controller micro-controller interfaces with.
 * 
 * [1] Initializes USART by setting the baud-rate, parity mode, type of stop-bit, character size and synchronization mode as following:
 *      - Baud Rate : 9600.
 *      - Parity Mode : No Parity.
 *      - Stop Bit Type : One Stop Bit.
 *      - Character Size : 8-Bits.
 *      - Synchronization Mode : Asynchronous.
 * [2] Initializes Buzzer.
 * [3] Initializes DC-Motor.
 * [4] Initialized EEPROM and set the prescaler, slave address and bit rate as following:
 *      - Prescaler : 1
 *      - Slave Address : 1.
 *      - Bit Rate : 400 KBPS.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void initialize_Devices(void);



/***
 * [Purpose] Start communication with the HMI to inform it whether it is the first time to use the system or not. 
 * 
 * Wait for IS_FIRST_TIME signal to be transmitted from the HMI micro-controller.
 * Read the date stored in FisrtTimeCheckAddress that acts as a flag to know whether there is saved password or not.
 * Stores the value found in FisrtTimeCheckData variable.
 * - If the data stored in FisrtTimeCheckData equals SAVED_PASSWORDS, SAVED_PASSWORDS signal is transmitted to the HMI.
 * - If the data stored in FisrtTimeCheckData equals NO_SAVED_PASSWORDS, NO_SAVED_PASSWORDS signal is transmitted to the HMI
 *   and storePassword function is invoked.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void isFirstTime(void);



/***
 * [Purpose] Define the system control flow if the system is being used for the first time.
 * 
 * Wait until ENTER_PASSWORD signal is received.
 * Invoke setPassword function : receives the password from the HMI micro-controller and store it in memory
 * Receive a signal from the HMI micro-controller, it could either be PASSWORD_MATCH or PASSWORD_MISMATCH
 * - In case the signal is PASSWORD_MATCH, normal_SystemOperations is invoked.
 * - In case the signal is PASSWORD_MISMATCH, firstTime_SystemOperations is invoked to repeat the process again.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void firstTime_SystemOperations(void);



/***
 * [Purpose] Receive the password from the HMI micro-controller and store it in memory.
 * 
 * Store the password transmitted by the HMI and store it in the memory.
 * Write SAVED_PASSWORDS in FisrtTimeCheckAddress which acts as a flag to know whether there is a saved password in the  
 * system or not.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void setPassword(void);

