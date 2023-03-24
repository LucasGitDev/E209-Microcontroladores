// Declaração de bibliotecas
#include <Arduino.h>

// Declaração de constantes
#define LIGA (1 << PB0)
#define DESLIGA (1 << PB1)
#define SENSOR (1 << PB3)
#define ALARME (1 << PD6)
#define MOTOR (1 << PD2)

// Declaração de variáveis globais

// Declaração de funções

// Diagrama de pinagens
// Fluxograma
// Código

int main()
{
    // Direcionamento das Portas (DDRx) - Modificar só os pinos de saída
    DDRB = 0;              // Todos os pinos do portal são entradas
    DDRD = ALARME | MOTOR; // PD6 como saída (Alarme) e PD2 como saída (Motor)

    // Definir como Pull-Up
    PORTB |= DESLIGA + LIGA + SENSOR;
    
    // Loop infinito
    while (1)
    {
        // Leitura do sensor (PB3)
        short int sensor;
        sensor = PINB & SENSOR;

        // Leitura do botão LIGA (PB0)
        short int liga;
        liga = PINB & LIGA;

        // Leitura do botão DESLIGA (PB1)
        short int desliga;
        desliga = PINB & DESLIGA;

        // se sensor estiver acionado desligar o motor
        if (sensor == SENSOR)
        {
            PORTD &= ~MOTOR;
            PORTD |= ALARME;
        }

        // se liga estiver pressionado ligar e sensor desligado
        if ((liga == LIGA) && (sensor != SENSOR))
        {
            PORTD |= MOTOR;   // Ligar o motor
            PORTD &= ~ALARME; // Desligar o alarme
        }

        // se desliga estiver pressionado desligar o motor
        if (desliga == DESLIGA)
        {
            PORTD &= ~MOTOR;  // Desligar o motor
            PORTD &= ~ALARME; // Desligar o alarme
        }
    }
    return 0;
}