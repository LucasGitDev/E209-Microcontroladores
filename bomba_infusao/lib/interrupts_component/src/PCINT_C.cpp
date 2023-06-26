#include "Arduino.h"
#include "PCINT_C.h"

PCINT_C_Callback PCINT_C_callbacks[1];

void PCINT_C_setup_PCINT0(uint8_t pinNumber, PCINT_C_Callback callback)
{
    DDRB &= ~(1 << pinNumber); // Configura o pino PBx como entrada
    PORTB |= (1 << pinNumber); // Habilita o pull-up interno do pino PBx

    PCICR |= (1 << PCIE0);                                                                                                   // Habilita interrupção no PCINT0 (PCINT7:0)
    PCMSK0 |= (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4) | (1 << PCINT5) | (1 << PCINT6) | (1 << PCINT7); // PCINT0

    PCINT_C_callbacks[0] = callback; // callback é um ponteiro para função
}

ISR(PCINT0_vect)
{
    if (PCINT_C_callbacks[0] != NULL)
    {
        PCINT_C_callbacks[0]();
    }
}
