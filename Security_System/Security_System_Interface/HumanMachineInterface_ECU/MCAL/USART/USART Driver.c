#include "USART Driver.h"

void USART_Init(int baud, int parity, int stopBit, int charSize, int sync){
	/// Clear USART Data register
	UDR = 0x00;
	
	/// Enable Double USART Transmission Speed
	UCSRA |= (1 << U2X);
	/// Enable UART Module. 
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	
	UCSRC |= (1 << URSEL);
	// Set character size.
	UCSRC = (UCSRC & 0xF9) | (charSize << UCSZ0);
	// Set parity mode.
	UCSRC= (UCSRC & 0xCF) | (parity << UPM0);
	// Set the type of stop bit.
	UCSRC= (UCSRC & 0xF7) | (stopBit << USBS);
	// Set synchronization mode.
	UCSRC= (UCSRC & 0xBF) | (sync << UMSEL);

	// Set baud-rate.
	UBRRH = (BAUD_RATE(baud) >> 8);
	UBRRL = BAUD_RATE(baud);
}

void USART_Transmit(U8 data){
	// Wait until the transmit buffer (UDR) is ready to receive new data [i.e. when the buffer is empty].
	while (( UCSRA & (1 << UDRE)) == 0);
	UDR = data;
}

U8 USART_Receive(void){
	/// Wait until there are unread data in the receive buffer.
	while(((UCSRA) & (1 << RXC)) == 0);
	return UDR;
}

void USART_TransmitString(U8 *str){
	while(*str != '\0'){
		USART_Transmit(*str);
		str++;
	}
}

void USART_ReceiveString(U8 *str){
	int i = 0;
	str[i] = USART_Receive();
	
	while(str[i] != '#'){
		i++;
		str[i] = USART_Receive();
	}
	str[i] = '\0';
}
