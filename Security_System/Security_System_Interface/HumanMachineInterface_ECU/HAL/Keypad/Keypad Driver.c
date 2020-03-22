#include "Keypad Driver.h"

int KeypadRows[] = {Row_0, Row_1, Row_2, Row_3};
int KeypadCols[] = {Col_0, Col_1, Col_2, Col_3};
char charMap[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'C', '0', '=', '+'}
};


void  Keypad_init(void) {
	int i;
	/// Set the direction of rows as input.
	for(i=0; i < 4 ;i++)
	keypadDDR &= ~(1 << KeypadRows[i]);
	
	/// Set the direction of columns (where the rows are connected) as output.
	for(int i = 0; i < 4 ;i++)
	keypadDDR |= (1 << KeypadCols[i]);
	
	keypadPORT = 0xFF;
}


U8 Keypad_keylisten(void){
	int i, j, k;
	for(i = 0; i < 4 ; i++){
		for(int j = 0; j < 4 ;j++)
		keypadPORT |= (1 << KeypadCols[j]);

		keypadPORT &= ~(1 << KeypadCols[i]);

		for(k = 0; k < 4; k++){
			if(!(keypadPIN & (1 << KeypadRows[k]))){
				while(!(keypadPIN & (1 << KeypadRows[k]))); /// Wait until the key is released.
				return charMap[k][i];
			}
		}
	}
	return ' ';
}
