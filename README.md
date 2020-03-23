# Locking System
This is a password-based door locking system based on two ATMega32 Microcontrollers.<br/>
The **HMI** is the first ECU interfacing with LCD and Keypad for the end user to enter the password. The other one is the **Controller** used to store the data in an external EEPROM, control the DC motor to open the door and the buzzer used to fire the alarm if unauthorized user trys to open the door.

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
