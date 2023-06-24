#ifndef __PCINT_C_COMPONENT__
#define __PCINT_C_COMPONENT__

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * DECLARATIONS
 ****************************************************************************************
 */

typedef void (*PCINT_C_Callback)(void);

void PCINT_C_setup_PCINT0(uint8_t pinNumber, PCINT_C_Callback callback);
void PCINT_C_setup_PCINT1(uint8_t pinNumber, PCINT_C_Callback callback);
void PCINT_C_setup_PCINT2(uint8_t pinNumber, PCINT_C_Callback callback);

/*
 * GETTERS
 ****************************************************************************************
 */

#endif