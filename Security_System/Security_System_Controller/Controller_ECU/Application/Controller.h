#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/USART/USART_Config.h"
#include "../MCAL/USART/USART Driver.h"
#include "../Utilities/Basic_Datatypes.h"
#include "../HAL/DC Motor/DC Motor Driver.h"
#include "../HAL/Buzzer/Buzzer Driver.h"
#include "../HAL/EEPROM/EEPROM Driver.h"


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
