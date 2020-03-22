#include "../../Utilities/AVR_ATMega32.h"

/// Port direction methods.
void DIO_PortDirection(U8 port, U8 direction){
	if(IS_PORT(port) && IS_DIR(direction)){
		DDR(port) = (direction = OUTPUT)? 0xFF : 0X00;
	}
}

void DIO_PinDirection(U8 port, U8 pin, U8 direction){
	if(IS_PORT(port) && IS_DIR(direction) && IS_PIN(pin)){
		(direction == OUTPUT)? SET_BIT(DDR(port), pin) : CLEAR_BIT(DDR(port), pin);
	}
}

void DIO_PortRangeDirection(U8 port, U8 stPin, U8 endPin, U8 direction){
	U8 temp;
	int i;
	if(IS_PORT(port) && IS_DIR(direction) && IS_PIN(stPin) && IS_PIN(endPin)){
		/// Ensures that the start pin is smaller than the end pin.
		if(stPin > endPin){
			temp = stPin;
			stPin = endPin;
			endPin = temp;
		}
		
		if(direction == OUTPUT)
		for(i = stPin; i<= endPin; i++ )
		SET_BIT(DDR(port), i);
		else
		for(i = stPin; i<= endPin; i++)
		CLEAR_BIT(DDR(port), i);
	}
}

void DIO_PortMaskDirection(U8 port, U8 direction, U8 mask){
	int i;
	if(IS_PORT(port) && IS_DIR(direction) && (mask > 0x00  && mask <= 0xFF)) {
		for(i = 0 ; i < 8 ; i++) {
			if(READ_BIT(mask, i)){
				if(READ_BIT(direction, i))
				SET_BIT(DDR(port), i);
				
				else if(!READ_BIT(direction, i))
				CLEAR_BIT(DDR(port), i) ;
			}
		}
	}
}


///  Writing to Port methods.
void DIO_PortWrite(U8 port, U8 value) {
	if(IS_PORT(port) && (value >= 0x00 && value <= 0xff)) {
		PORT(port) = value;
	}
}

void DIO_PinWrite(U8 port, U8 pin, U8 value) {
	if(IS_PORT(port) && IS_PIN(pin) && (value == 0x00 || value == 0x01)) {
		if(value == 1) {
			SET_BIT(PORT(port), pin);
			} else {
			CLEAR_BIT(PORT(port), pin);
		}
	}
}

void DIO_PortRangeWrite(U8 port, U8 stPin, U8 endPin, U8 value){
	U8 temp;
	int i;
	if(IS_PORT(port) && IS_PIN(stPin) && IS_PIN(endPin) && (value == 0x00 || value == 0x01)) {
		if(stPin > endPin){
			temp = stPin;
			stPin = endPin;
			endPin = temp;
		}
		if(value == 1)
		for(i = stPin; i<= endPin; i++ )
		SET_BIT(PORT(port), i);
		else
		for(i = stPin; i<= endPin; i++)
		CLEAR_BIT(PORT(port), i);
	}
}

void DIO_PortMaskWrite(U8 port, U8 value, U8 mask) {
	int i;
	if(IS_PORT(port) && (mask > 0x00  && mask <= 0xFF)) {
		for(i= 0 ; i< 8 ; i++) {
			if(READ_BIT(mask, i)){
				if(READ_BIT(value, i))
				SET_BIT(PORT(port), i);
				else if(!READ_BIT(value, i))
				CLEAR_BIT(PORT(port), i);
			}
		}
	}
}


/// Reading Port value
void DIO_PortRead(U8 port, U8 *value) {
	if(IS_PORT(port)) {
		*value = PIN(port) ;
	}
}

void DIO_PinRead(U8 port, U8 pin, U8 *pinValue) {
	if(IS_PORT(port) && IS_PIN(pin))
	*pinValue = READ_BIT(PIN(port), pin);
}

void DIO_PortRangeRead(U8 port, U8 stPin, U8 endPin, U8 *pinValue) {
	U8 temp;
	int i;
	if(IS_PORT(port) && IS_PIN(stPin) && IS_PIN(endPin)) {
		if(stPin > endPin){
			temp = stPin;
			stPin = endPin;
			endPin = temp;
		}
		*pinValue = 0x00;
		for(i= stPin; i<= endPin ; i++)
		*pinValue = READ_BIT(PIN(port), i);
	}
}

void DIO_PortMaskRead(U8 port, U8 mask, U8 *value) {
	U8 temp= 0x01;
	int i;
	if(IS_PORT(port) && (mask > 0x00  && mask <= 0xFF)) {
		*value = 0x00;
		for(i= 0 ; i< 8 ; i++) {
			if((mask & temp) >> i) {
				*value = READ_BIT(PIN(port), i);
				temp <<= 1;
			}
		}
	}
}


/// Toggle port value
void DIO_PortToggle(U8 port) {
	int i;
	if(IS_PORT(port)) {
		for(i= 0; i <= 8 ; i++)
		TOGGLE_BIT(PORT(port), i);
	}
}

void DIO_PinToggle(U8 port, U8 pin) {
	if(IS_PORT(port) && IS_PIN(pin))
	TOGGLE_BIT(PORT(port), pin);
}

void DIO_PortRangeToggle(U8 port, U8 stPin, U8 endPin) {
	U8 temp;
	int i;
	if(IS_PORT(port) && IS_PIN(stPin) && IS_PIN(endPin) ) {
		if(stPin > endPin){
			temp = stPin;
			stPin = endPin;
			endPin = temp;
		}
		for(i= stPin; i <= endPin ; i++)
		TOGGLE_BIT(PORT(port), i);
	}
}

void DIO_PortMaskToggle(U8 port, U8 mask) {
	U8 temp= 0x01;
	int i;
	if(IS_PORT(port) && (mask > 0x00  && mask <= 0xFF)) {
		for(i= 0 ; i < 8 ; i++){
			if((mask & temp) >> i){
				TOGGLE_BIT(PORT(port), i) ;
			}
			temp <<= 1;
		}
	}
}

