#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/LCD/LCD Driver.h"
#include "../HAL/Keypad/Keypad Driver.h"
#include "../MCAL/USART/USART_Config.h"
#include "../MCAL/USART/USART Driver.h"

/***
 * [Purpose] Initialize the devices that HMI micro-controller interfaces with.
 *
 * [1] Initializes LCD. 
 * [2] Initializes Keypad. 
 * [3] Initializes USART by setting the baud-rate, parity mode, type of stop-bit, character size and synchronization mode as following:
 *      - Baud Rate : 9600.
 *      - Parity Mode : No Parity.
 *      - Stop Bit Type : One Stop Bit.
 *      - Character Size : 8-Bits.
 *      - Synchronization Mode : Asynchronous.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void initialize_Devices(void);