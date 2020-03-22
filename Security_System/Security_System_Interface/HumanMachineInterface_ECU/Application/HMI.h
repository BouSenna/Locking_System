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

/***
 * [Purpose] Display message to the user to inform him that he should press 0 key to begin using the system. 
 * [NOTE] The message is displayed as circularly scrolling text on the first row since I'm using 16x2 alphanumeric
 *        LCD and the message length is 30 character. 
 * 
 * Store the message in character array.
 * Loop with the array size and do the following instructions each iteration:
 *       [1] Display the message stored in the array on the LCD. 
 *           (Note that only the first 16 characters will be displayed to the user)
 *       [2] Store the first character in a temporary variable.
 *       [3] Shift all the other characters one place to the left.
 *       [4] Add the value stored in the temporary variable at the end of the array 
 *           then add the string terminator at the last index of the array.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void initial_LCDScrollText(void);