#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "LCD_Config.h"
#include "../../Utilities/AVR_ATMega32.h"
#include <stdlib.h>

/// LCD Instructions.
#define  LCD_CLEAR_CMD                  0x01U
#define  LCD_RETURN_HOME_CMD            0x80U
#define  LCD_CURSOR_OFF_CMD             0x0CU
#define  LCD_UNDERLINE_ON_CMD           0x0EU
#define  LCD_BLINK_CURSOR_ON_CMD        0x0FU
#define  LCD_TURN_ON_CMD                0x0CU
#define  LCD_TURN_OFF_CMD               0x08U
#define  LCD_SHIFT_LEFT_CMD             0x18U
#define  LCD_SHIFT_RIGHT_CMD            0x1CU
#define  LCD_CURSOR_SHIFT_LIFT_CMD      0x10U
#define  LCD_CURSOR_SHIFT_RIGHT_CMD     0x14U

#define  LCD_ROW_1                      0U
#define  LCD_ROW_2                      1U

#define  LCD_POSITION_1                 0U
#define  LCD_POSITION_2                 1U
#define  LCD_POSITION_3                 2U
#define  LCD_POSITION_4                 3U
#define  LCD_POSITION_5                 4U
#define  LCD_POSITION_6                 5U
#define  LCD_POSITION_7                 6U
#define  LCD_POSITION_8                 7U
#define  LCD_POSITION_9                 8U
#define  LCD_POSITION_10                9U
#define  LCD_POSITION_11                10U
#define  LCD_POSITION_12                11U
#define  LCD_POSITION_13                12U
#define  LCD_POSITION_14                13U
#define  LCD_POSITION_15                14U
#define  LCD_POSITION_16                15U

/***
 * [Purpose] Initialize LCD.
 *
 * Initializes the LCD by: 
 *      [1] Waiting for the LCD to power up. 
 *      [2] Setting the direction of the LCD port as output.
 *      [3] Sending the initialization values of 16x2 LCD as commands 
 *          1. Send command to initialize LCD in 4-bit mode
 *          2. Configure LCD in 2-line, 4-bit mode, 5x8 dots.
 *          3. Send Display on cursor off command
 *          4. Send Increment cursor command
 *      [4] Clear the LCD display screen 
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void LCD_Init(void);

/***
 * [Purpose] Give high to low pulse at enable.
 * 
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/	
void static LCD_Read(void);
	
/***
 * [Purpose] Write command with 4-bit mode.
 *
 * 1. Writes each bit of the high nibbles [4-7] to data bus.
 * 2. Invokes LCD_Read() method : gives high to low pulsa at enable.
 * 3. Write each bit of the low nibbles [0-3] to data bus.
 * 4. Invokes LCD_Read() method : gives high to low pulsa at enable.
 *
 * [Arguments] value : could be either command or character.
 * [Return Type] Void.
 *
 ***/	
void static LCD_Write(U8 value);

/***
 * [Purpose] Write command.
 *
 * 1. Clears RS pin (command register)
 * 2. Clears RW pin (Write operation)
 * 3. Invokes LCD_Write()
 *
 * [Arguments] cmd : command.
 * [Return Type] Void.
 *
 ***/	
void LCD_WriteCommand(U8 cmd);

/***
 * [Purpose] Write character.
 *
 * 1. Clears RS pin (command register)
 * 2. Clears RW pin (Write operation)
 * 3. Invokes LCD_Write()
 *
 * [Arguments] character : the character required to be written on the LCD.
 * [Return Type] Void.
 *
 ***/	
void LCD_WriteCharacter(U8 character);

/***
 * [Purpose] Write string.
 *
 * This method takes a string and pass it character by character to 
 *  LCD_WriteCharacter() method to be written.
 *
 * [Arguments] str : the string required to be written on the LCD.
 * [Return Type] Void.
 ***/	
void LCD_WriteString(U8* str);

/***
 * [Purpose] Set the cursor to a specific position.
 *
 * [Arguments] row : could be either 0 or 1.
 *             position : could be any value ranging between 0-15
 * [Return Type] Void.
 ***/	
void LCD_SetCursor(U8 row, U8 position);


#endif 