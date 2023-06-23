#include <Arduino.h>

#include "PWM.h"

// Inicializa o PWM na porta digital 6 (PD6)
void PWM_setup()
{
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1); // Modo 7
    TCCR0B |= (1 << CS00);                                 // Seleciona opção para frequência
    OCR0A = 0;                                             // Inicia com 0% de duty cycle
}

void PWM_stop()
{
    TCCR0A &= ~(1 << COM0A1); // Desliga o PWM
}

void PWM_set_duty_cycle(float duty_cycle)
{
    if (duty_cycle < 0 || duty_cycle > 100)
        return;

    OCR0A = (int)(duty_cycle * 255) / 100;
}

float PWM_get_duty_cycle()
{
    return (OCR0A * 100.0) / 255.0;
}