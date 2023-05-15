#include <Arduino.h>

#define LED (1 << PD6)
#define BTN (1 << PB1)

char VALUE = 0;

void config_outputs()
{
    DDRD |= LED;
    PORTD &= ~LED;
}

void config_timer()
{
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
    TCCR0B = (1 << CS00);
    OCR0A = 0;
}

void config_interrupts()
{
    PCICR = (1 << PCIE0);
    PCMSK0 = BTN;
}

int main()
{

    config_outputs();
    config_timer();
    config_interrupts();

    sei();

    for (;;)
    {
    }
}

ISR(PCINT0_vect)
{
    VALUE += 10;
    if (VALUE >= 0 && VALUE < 100)
        OCR0A = (int)((VALUE / 100.0) * 255); //
    if (VALUE > 100)
        VALUE = 0;
    OCR0A = VALUE;
}
