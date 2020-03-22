#include "LCD Driver.h"
#include <util/delay.h>

void LCD_Init(void){
	/// Delay for 15ms for the LCD to power up. 
	_delay_ms(15);
	 
	LCD_RS_DDR |= (1 << LCD_RS_PIN);
	LCD_RW_DDR |= (1 << LCD_RW_PIN);
	LCD_EN_DDR |= (1 << LCD_EN_PIN);
	LCD_D7_DDR |= (1 << LCD_D7_PIN);
	LCD_D6_DDR |= (1 << LCD_D6_PIN);
	LCD_D5_DDR |= (1 << LCD_D5_PIN);
	LCD_D4_DDR |= (1 << LCD_D4_PIN);


	/* send the initialization values as in data sheet (as commands) */
	LCD_WriteCommand(0x33U);    /* Initialization */
	LCD_WriteCommand(0x32U);    /* Initialization */
	LCD_WriteCommand(0x28U);    /* Function Set: 4-bit, 2 Line, 5x7 Dots */
	LCD_WriteCommand(0x0cU);    /* Display on, cursor off */
	LCD_WriteCommand(0x01U);    /* Clear display, Cursor home */
}

void static LCD_Read(){
	LCD_EN_PORT |= (1 << LCD_EN_PIN);
	_delay_us(2U);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	_delay_ms(3U);
 }

void static LCD_Write(U8 value){
	/// 4-Bit Mode.
	// Write each bit of the high nibbles [4-7] to data bus.
	if (value & (1U << 7))
		LCD_D7_PORT |= (1U << LCD_D7_PIN);
	else 
		LCD_D7_PORT &= ~(1U << LCD_D7_PIN);
	if (value & (1U << 6))
		LCD_D6_PORT |= (1U << LCD_D6_PIN);
	else 
		LCD_D6_PORT &= ~(1U << LCD_D6_PIN);
	if (value & (1U << 5))
		LCD_D5_PORT |= (1U << LCD_D5_PIN);
	else 
		LCD_D5_PORT &= ~(1U << LCD_D5_PIN);
	if (value & (1U << 4))
		LCD_D4_PORT |= (1U << LCD_D4_PIN);
	else 
		LCD_D4_PORT &= ~(1U << LCD_D4_PIN);
	
	LCD_Read();
	
	// Write each bit of the low nibbles [0-3] to its place.
	if (value & (1U << 3))
		LCD_D7_PORT |= (1U << LCD_D7_PIN);
	else
		LCD_D7_PORT &= ~(1U << LCD_D7_PIN);
	if (value & (1U << 2))
		LCD_D6_PORT |= (1U << LCD_D6_PIN);
	else
		LCD_D6_PORT &= ~(1U << LCD_D6_PIN);
	if (value & (1U << 1))
		LCD_D5_PORT |= (1U << LCD_D5_PIN);
	else
		LCD_D5_PORT &= ~(1U << LCD_D5_PIN);
	if (value & (1U << 0))
		LCD_D4_PORT |= (1U << LCD_D4_PIN);
	else 
		LCD_D4_PORT &= ~(1U << LCD_D4_PIN);
	
	LCD_Read();
}
 
void LCD_WriteCommand(U8 command){
	LCD_RS_PORT &= ~(1U << LCD_RS_PIN);
	LCD_RW_PORT &= ~(1U << LCD_RW_PIN);

	/// Write command with 4-bit mode 
	LCD_Write(command);
}
 
void LCD_WriteCharacter(U8 character){
	LCD_RS_PORT |= (1U << LCD_RS_PIN);
	LCD_RW_PORT &= ~(1U << LCD_RW_PIN);

	 /// Write command with 4-bit mode
	 LCD_Write(character);
}

void LCD_WriteString(U8 *string){
	while(*string){
		LCD_WriteCharacter(*string++);
	}
}

void LCD_SetCursor(U8 row, U8 position){
	// send the position to the LCD 
	if (row == LCD_ROW_1){
		LCD_WriteCommand(position | 0x80);
	}
	
	else if(row == LCD_ROW_2){
		LCD_WriteCommand(0x80 | 0x40 | position); 	/// 192 + position.
	}
 }


