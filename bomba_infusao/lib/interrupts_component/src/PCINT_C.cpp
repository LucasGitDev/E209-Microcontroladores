#include "Arduino.h"
#include "PCINT_C.h"

PCINT_C_Callback PCINT_C_callbacks[3];

void PCINT_C_setup_PCINT0(uint8_t pinNumber, PCINT_C_Callback callback)
{
    // Configurar o pino como entrada
    DDRD &= ~(1 << pinNumber);

    // Habilitar a resistência de pull-up no pino
    PORTD |= (1 << pinNumber);

    // Habilitar o pino para PCINT
    PCMSK2 |= (1 << PCINT16); // PCINT0

    // Habilitar interrupções de PCINT no grupo PCIE2
    PCICR |= (1 << PCIE2);

    PCINT_C_callbacks[0] = callback;
}

void PCINT_C_setup_PCINT1(uint8_t pinNumber, PCINT_C_Callback callback)
{
    // Configurar o pino como entrada
    DDRD &= ~(1 << pinNumber);

    // Habilitar a resistência de pull-up no pino
    PORTD |= (1 << pinNumber);

    // Habilitar o pino para PCINT
    PCMSK2 |= (1 << PCINT17); // PCINT1

    // Habilitar interrupções de PCINT no grupo PCIE2
    PCICR |= (1 << PCIE2);

    PCINT_C_callbacks[1] = callback;
}

void PCINT_C_setup_PCINT2(uint8_t pinNumber, PCINT_C_Callback callback)
{
    // Configurar o pino como entrada
    DDRD &= ~(1 << pinNumber);

    // Habilitar a resistência de pull-up no pino
    PORTD |= (1 << pinNumber);

    // Habilitar o pino para PCINT
    PCMSK2 |= (1 << PCINT18); // PCINT2

    // Habilitar interrupções de PCINT no grupo PCIE2
    PCICR |= (1 << PCIE2);

    PCINT_C_callbacks[2] = callback;
}

ISR(PCINT0_vect)
{
    if (PCINT_C_callbacks[0] != NULL)
    {
        PCINT_C_callbacks[0]();
    }
}

ISR(PCINT1_vect)
{
    if (PCINT_C_callbacks[1] != NULL)
    {
        PCINT_C_callbacks[1]();
    }
}

ISR(PCINT2_vect)
{
    if (PCINT_C_callbacks[2] != NULL)
    {
        PCINT_C_callbacks[2]();
    }
}