#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/LCD/LCD Driver.h"
#include "../HAL/Keypad/Keypad Driver.h"
#include "../MCAL/USART/USART_Config.h"
#include "../MCAL/USART/USART Driver.h"

#define PASSWORD_SIZE              4

#define SETTING_PASSWORD           0
#define CONFIRM_PASSWORD           1

#define IS_FIRST_TIME              0x10
#define SAVED_PASSWORDS            0x11
#define NO_SAVED_PASSWORDS         0x12

#define PASSWORD_MATCH             0x13
#define PASSWORD_MISMATCH          0x14

/***
 * [Purpose] Starting and setting up the HMI micro-controller.
 *
 * Invoke set of functions: 
 *      [1] initialize_Devices : Initializes set of devices that will be used.
 *      [2] initial_LCDScrollText : Displays to the user a message to press 0 if he wishes to start using with the system.
 * Wait until the user presses on the 0 key.
 * Clear the screen. 
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void startUp_HMI(void);


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



/***
 * [Purpose] Start communication with the controller to know whether it is the first time to use the system or not. 
 * 
 * Transmit IS_FIRST_TIME signal to the controller.
 * The controller is expected to either send back SAVED_PASSWORDS signal or NO_SAVED_PASSWORDS signal.
 * - In case the received signal is SAVED_PASSWORDS, normal_SystemOperations function is invoked.
 * - In case the received signal is NO_SAVED_PASSWORDS, firstTime_SystemOperations functions is invoked.
 * 
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void isFirstTime(void);



/***
 * [Purpose] Define the system control flow if the system is being used for the first time.
 * 
 * Declare two arrays with the PASSWORD_SIZE
 *       [1] Password : to store the password in it.
 *       [2] ConfPassword : used for confirmation.
 * Invoke setPassword function two times 
 *       [1] Allow the users to enter the password and store it in Password array.
 *       [2] Allow the users to re-enter the password and store it in ConfPassword array.
 * Compare the value in both of the arrays 
 * - In case the values were identical,
 *       [1] A message is displayed to the user confirming that the password is saved successfully.
 *       [2] PASSWORD_MATCH signal is transmitted to the controller.
 *       [3] normal_SystemOperations is invoked.
 * - In case the values were different,
 *       [1] A message is displayed to the user to inform him that the passwords mismatch.
 *       [2] PASSWORD_MISMATCH signal is transmitted to the controller.
 *       [3] clearMemory is invoked to remove the password the user entered from the memory. 
 *       [4] The whole process is repeated again.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void firstTime_SystemOperations(void);