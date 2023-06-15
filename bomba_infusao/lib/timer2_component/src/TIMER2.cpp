#include <Arduino.h>

#include "TIMER2.h"

TIMER2_Callback timer2_callback;

volatile unsigned int timer2_cont;
volatile unsigned int timer2_segundos;

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
    timer2_segundos = 0;
    timer2_cont = 0;
}

ISR(TIMER2_COMPA_vect) // Rotina de interrupção do Timer 2
{
    timer2_cont++;

    if (timer2_cont == 10000)
    {
        timer2_cont = 0;
        timer2_segundos++;
        
        char message[20];
        snprintf(message, 20, "Segundos: %d\n", timer2_segundos);
        timer2_callback(message);
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