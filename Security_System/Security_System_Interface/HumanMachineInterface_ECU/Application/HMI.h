#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/LCD/LCD Driver.h"
#include "../HAL/Keypad/Keypad Driver.h"
#include "../MCAL/USART/USART_Config.h"
#include "../MCAL/USART/USART Driver.h"

#define PASSWORD_SIZE              4

#define SETTING_PASSWORD           0
#define CONFIRM_PASSWORD           1

#define ENTER_PASSWORD             0x10

#define IS_FIRST_TIME              0x11
#define SAVED_PASSWORDS            0x12
#define NO_SAVED_PASSWORDS         0x13

#define PASSWORD_MATCH             0x14
#define PASSWORD_MISMATCH          0x15

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



/***
 * [Purpose] Read the password entered by the user, store it in the array passed to the function and transmit it to the controller to be stored in memory.  
 * 
 * Transmit ENTER_PASSWORD signal to the controller.
 * - In case the action passed to the function is SETTING_PASSWORD,
 *       [1] Display a message asking the user to enter the password. 
 *       [2] Read the input from the user, store it in the array passed to the function and display it on the LCD screen.  
 *       [3] Transmit the password to the controller to store it in the memory.
 * - In case the action passed to the function is CONFIRM_PASSWORD,
 *       [1] Display a message asking the user to re-enter the password.
 *       [2] Read the input from the user, store it in the array passed to the function and display it on the LCD screen.
 *
 * [Arguments]
 *  [1] *password : a pointer to the address of the array we want to store the password in.
 *  [2] action : integer variable holding the action we want to perform, it could either be SETTING_PASSWORD (0) or CONFIRM_PASSWORD (1).
 *
 * [Return Type] Void.
 *
 ***/
void setPassword(U8 *password, int action);



/***
 * [Purpose] Take two arrays and checks whether the value of both of them matches or not.
 * 
 * Loop with the PASSWORD_SIZE and compare the values of the two passwords
 * If the two passwords are identical, it will return 1. 
 * If the two passwords are different, it will return 0.
 *
 * [Arguments]
 *  [1] *pass1 : a pointer to the address of the array that represents the first password.
 *  [2] *pass2 : a pointer to the address of the array that represents the second password.
 *
 * [Return Type] int.
 *
 ***/
int passwordMatch(U8* pass1, U8* pass2);



/***
 * [Purpose] Define the system control flow if the system is previously used and there is saved password. 
 * 
 * Invokes enterPassword function : ensures that the user is authorized to use the system.
 * Display the available operations for the user to choose from
 *     [1] "New Password" message in the first row.
 *     [2] "Open the Door" message in the second row.
 * - In case the user pressed 0 key (chose to change the password),
 *   changePassword function is invoked.
 * - In case the user pressed 1 key (chose to open the door),
 *   openDoor function is invoked.
 *
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void normal_SystemOperations(void);



/***
 * [Purpose] Allows the user to enter the password and send it to the controller to check whether it's correct or not.
 * 
 * Display message asking the user to enter the password.
 * Transmit ENTER_PASSWORD signal to the controller.
 * Let the user enter the password, send it to the controller to check its validity and wait for the controller to respond.
 * The controller is expected to either send back CORRECT_PASSWORD signal or INCORRECT_PASSWORD signal or REPEATEDLY_INCORRECT.
 * - In case the received signal is CORRECT_PASSWORD, display message that welcomes the user and return back to normal_SystemOperations function.
 * - In case the received signal is INCORRECT_PASSWORD, display message informing the user that the password is incorrect and repeat the process.
 * - In case the received signal is REPEATEDLY_INCORRECT, display message informing the user that the system us locked the restart the system after receiving signal to unlock the system.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void enterPassword(void);



/***
 * [Purpose] Wait for opening and closing signals from the controller and notifying the user with the updates.
 * 
 * Send REQUEST_TO_OPEN_DOOR signal to the Controller
 * Wait until OPENING_DOOR signal is received from the controller. When received, 
 * display a message to the user informing him that the door is unlocked. 
 *
 * Wait until CLOSING_DOOR signal is received from the controller. When received,
 * display a message to the user informing him that the door is locked again.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void openDoor();



/***
 * [Purpose] Handle the user's request to change the password.
 * 
 * Send REQUEST_TO_CHANGE_PASS signal to the Controller
 * Invoke firstTime_SystemOperations to enter the new password.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void changePassword(void);