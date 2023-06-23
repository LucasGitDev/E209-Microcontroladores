#include <Arduino.h>

#include "TIMER2.h"

TIMER2_Callback timer2_callback;

volatile unsigned int timer2_cont;
volatile unsigned int timer2_segundos;
unsigned int timer2_last_segundos;

void TIMER2_setup(TIMER2_Callback callback)
{

    timer2_callback = callback;

    TCCR2A = (1 << WGM21); // Configuração do modo de funcionamento para Comparador
    TCCR2B = (1 << CS21);  // Pre-scaler de 8 (Frequência de 2MHz - Período de 500 ns em cada contagem)
    OCR2A = 199;           // 200 contagens de 500 ns, o que gera uma interrupção a cada 100 us
}

void TIMER2_start()
{
    TIMSK2 = (1 << OCIE2A); // Gerar uma interrupção no estouro do comparador A
}

void TIMER2_stop()
{
    TIMSK2 = (0 << OCIE2A); // Fazer com que o Timer 2 não gere mais interrupções
    timer2_last_segundos = timer2_segundos;
    timer2_segundos = 0;
    timer2_cont = 0;
}

int calc_cont(int milisegundos)
{
    return milisegundos * 10;
    // milisegundos == 1000 -> 1000 * 10 = 10000
    // milisegundos == 250 -> 250 * 10 = 2500
    // milisegundos == 500 -> 500 * 10 = 5000
    // milisegundos == 750 -> 750 * 10 = 7500
}

ISR(TIMER2_COMPA_vect) // Rotina de interrupção do Timer 2
{
    timer2_cont++;

    if (timer2_cont == calc_cont(1000)) // Quero entrar nesse if a cada 1 segundo
    {
        timer2_cont = 0;
        timer2_segundos++;

        char message[20];
        snprintf(message, 20, "Segundos: %d\n", timer2_segundos);
        timer2_callback(message, timer2_segundos);
    }
}

/*
 * GETTERS
 ****************************************************************************************
 */

unsigned int TIMER2_get_segundos()
{
    return timer2_segundos;
}

unsigned int TIMER2_get_cont()
{
    return timer2_cont;
}