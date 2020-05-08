# Locking System
This is a password-based door locking system based on two ATMega32 Microcontrollers.<br/>
The **HMI** is the first ECU interfacing with LCD and Keypad for the end user to enter the password. The other one is the **Controller** used to store the data in an external EEPROM, control the DC motor to open the door and the buzzer used to fire the alarm if unauthorized user tries to open the door.

## System Control Flow
### First Use Mode
The user will be prompted to enter a password and confirm it using the keypad.<br/>
If the passwords match, the password will be transmitted to the controller ECU to be saved in the external EEPROM and a friendly message will be displayed on the LCD to confirm that the password is successfully saved. Otherwise, a message will be displayed to inform the user that the passwords mismatch and the whole process will be repeated again.

### Normal Mode 
The user will be prompted to enter his password using the keypad.<br/>
If the password is correct, the supported operations menu will be displayed to the user on the LCD to choose the action he wants to perform, he could either request to open the door or change the password.<br/>
However, if the password is incorrect the user can enter the password maximum of 3 times then the system will freeze and trigger the alarm.
##### Request to Open Door
If the controller ECU (actuator) receives a signal to open the door, it will rotate the motor in clockwise direction opening the door, wait for few minutes then close the door again.
##### Request to Change Password
If the user chooses to change the password, he will be prompted to enter a password and confirm it using the keypad. then it will be sent to the controller to store it instead of the old one. 


## Human Machine Interface ECU Modules
#### Hardware Abstraction Layer Drivers
- [x] LCD
- [x] Keypad

#### Microcontroller Abstraction Layer Drivers
- [x] DIO
- [x] UART

## Controller ECU Modules
#### Hardware Abstraction Layer Drivers
- [x] DC Motor
- [x] External EEPROM
- [x] Buzzer

#### Microcontroller Abstraction Layer Drivers
- [x] DIO
- [x] I2C
- [x] UART
- [ ] Timer1



## TBC
