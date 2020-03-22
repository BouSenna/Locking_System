#ifndef BASIC_MACROS_H
#define BASIC_MACROS_H

#define SET_BIT(REG, Pin)        (REG |= (1 << Pin))
#define CLEAR_BIT(REG, Pin)      (REG &= ~ (1 << Pin))
#define TOGGLE_BIT(REG, Pin)     (REG ^= (1 << Pin))

#define READ_BIT(REG, Pin)                  ((REG & (1 << Pin)) >> Pin)
#define WRITE_REGISTER(REG, Data, Mask)     REG &= (~(Mask));	REG |= ((Data) & (Mask))

#endif