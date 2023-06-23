#include "Arduino.h"
#include "INT_C.h"

uint8_t intNumber;
uint8_t pinNumber;

void INT_C_setup(uint8_t intNumber, uint8_t pinNumber)
{
    // Configura o pino como entrada
    DDRD &= ~(1 << pinNumber);

    // Configura o pull-up interno para o pino
    PORTD |= (1 << pinNumber);

    // Configura a interrupção externa
    EICRA |= (intNumber % 2 == 0) ? (1 << ISC00) : (1 << ISC10);
    EIMSK |= (1 << intNumber);
}

ISR(INT0_vect)
{
}

ISR(INT1_vect)
{
}

ISR(INT2_vect)
{
}
