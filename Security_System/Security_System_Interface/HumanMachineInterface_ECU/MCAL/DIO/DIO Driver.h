#ifndef DIO_Driver_H
#define DIO_Driver_H

#include "../../Utilities/AVR_ATMega32.h"

/// Port direction methods.
void DIO_PortDirection(U8, U8);
void DIO_PinDirection(U8, U8, U8);
void DIO_PortRangeDirection(U8, U8, U8, U8);
void DIO_PortMaskDirection(U8, U8, U8);


/// Writing to Port
void DIO_PortWrite(U8, U8);
void DIO_PinWrite(U8, U8, U8);
void DIO_PortRangeWrite(U8, U8, U8, U8);
void DIO_PortMaskWrite(U8, U8, U8);


/// Reading value from port
void DIO_PortRead(U8, U8 *);
void DIO_PinRead(U8, U8, U8 *);
void DIO_PortRangeRead(U8, U8, U8, U8 *);
void DIO_PortMaskRead(U8, U8, U8 *);


/// Toggle port value
void DIO_PortToggle(U8);
void DIO_PinToggle(U8, U8);
void DIO_PortRangeToggle(U8, U8, U8);
void DIO_PortMaskToggle(U8, U8);

#endif