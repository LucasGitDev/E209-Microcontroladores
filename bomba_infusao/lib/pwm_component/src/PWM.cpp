#include <Arduino.h>

#include "PWM.h"

// Inicializa o PWM na porta digital 6 (PD6)
void PWM_setup()
{
    DDRD |= (1 << PD6);   // Configura o pino como saída
    PORTD &= ~(1 << PD6); // Iniciar com o pino em nível baixo

    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1); // Modo 7
    TCCR0B |= (1 << CS00);                                 // Seleciona opção para frequência
    OCR0A = 0;                                             // Inicia com 0% de duty cycle
}

void PWM_stop()
{
    OCR0A = 0;
    TCCR0A &= ~(1 << COM0A1); // Desliga o PWM
}

void PWM_active()
{
    TCCR0A |= (1 << COM0A1); // Liga o PWM
}

void PWM_set_duty_cycle(float duty_cycle)
{
    if (duty_cycle < 0)
        duty_cycle = 0;
    else if (duty_cycle > 100)
        duty_cycle = 100;

    OCR0A = (int)(duty_cycle * 255) / 100;
}

float PWM_get_duty_cycle()
{
    return (OCR0A * 100.0) / 255.0;
}