#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include <avr/io.h>
#include "../../Utilities/AVR_ATMega32.h"

#define F_CPU 8000000UL
#define BAUD_RATE(BAUD) (((F_CPU) / (BAUD * 16UL)) - 1)


/***
 * [Purpose] Initialize USART.
 *
 * Initializes the USART by: 
 *      [1] Clearing UDR (USART Data Register).
 *      [2] Enabling Double USART Transmission Speed by setting U2X pin in UCSRA.
 *      [3] Enabling UART Module by setting RXEN and TXEN pins in UCSRB.
 *      [4] Setting USART configuration
 *          1. Set character size
 *          2. Set parity mode
 *          3. Set the type of stop bit.
 *          4. Set synchronization mode.
 *          5. Set baud-rate.
 *
 * [Arguments] baud : could be 4800, 9600, 19200, 115200 etc.
 *             parity : could be NO_PARITY, EVEN_PARITY or ODD_PARITY
 *             stopBit : could be either ONE_STOP_BIT or TWO_STOP_BITS
 *             charSize : could be FIVE_BITS, SIX_BITS, SEVEN_BITS or EIGHT_BITS 
 *             sync : could be either SYNCHRONOUS or ASYNCHRONOUS
 * [Return Type] Void.
 *
 ***/
void USART_Init(int baud, int parity, int stopBit, int charSize, int sync);

/***
 * [Purpose] Transmit byte using USART serial communication.
 *
 * 1. Wait until the transmit buffer (UDR) is ready to receive new data [i.e. when the buffer is empty].
 * 2. Store the data in UDR (USART Data Register).
 *
 * [Arguments] data : data to be transmitted.
 * [Return Type] Void.
 *
 ***/
void USART_Transmit(U8 data);

/***
 * [Purpose] Receive byte using USART serial communication.
 *
 * 1. Wait until there are unread data in the receive buffer.
 * 2. Return the data stored in UDR (USART Data Register).
 *
 * [Arguments] None.
 * [Return Type] unsigned character.
 *
 ***/
U8 USART_Receive(void);

/***
 * [Purpose] Transmit string.
 *
 * This method takes a string and pass it character by character (byte by byte) to 
 *  USART_Transmit() to transmit it.
 *
 * [Arguments] str : string to be transmitted.
 * [Return Type] Void.
 *
 ***/
void USART_TransmitString(U8 *str);

/***
 * [Purpose] Receive string.
 *
 * This method reads a string character by character and store it in str.
 *
 * [Arguments] None.
 * [Return Type] Void.
 *
 ***/
void USART_ReceiveString(U8 *str);

#endif


