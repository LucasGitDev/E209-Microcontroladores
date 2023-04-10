// Includes
#include <Arduino.h>

// Link Tinkercad: https://www.tinkercad.com/things/kAMfnpXBAKi-cool-gaaris-densor/editel?sharecode=H04Lr7_IrkdeIkrGYRinn0rIMdvQzCtiofyQF6Eo6IE

// Defines

#define SENSOR_MIN (1 << PD2)
#define SENSOR_MAX (1 << PD3)
#define CHEIO (1 << PD4)
#define ENCHENDO (1 << PD5)
#define VALVULA (1 << PD6)

int main(void)
{
    Serial.begin(9600);

    DDRD = CHEIO | ENCHENDO | VALVULA;
    PORTD &= ~(CHEIO | ENCHENDO | VALVULA);

    // SENSOR_MIN é NORMALMENTE FECHADO, habilita pull-up
    PORTD |= SENSOR_MIN;


    // Só para de encher quando o sensor de nível máximo estiver fechado (HIGH)
    while (1)
    {

        if ((PIND & SENSOR_MIN) && !(PIND & SENSOR_MAX))
        {
            PORTD |= ENCHENDO;
            PORTD &= ~CHEIO;
            PORTD |= VALVULA;
        }
        else if ((PIND & SENSOR_MIN) && (PIND & SENSOR_MAX))
        {
            PORTD &= ~ENCHENDO;
            PORTD |= CHEIO;
            PORTD &= ~VALVULA;
        }
        else if (!(PIND & SENSOR_MIN) && (PIND & SENSOR_MAX))
        {
            PORTD &= ~ENCHENDO;
            PORTD &= ~VALVULA;
            PORTD |= CHEIO;
        }
        else
        {
            PORTD &= ~ENCHENDO;
            PORTD |= ENCHENDO + VALVULA;
        }
    }
    return 0;
}