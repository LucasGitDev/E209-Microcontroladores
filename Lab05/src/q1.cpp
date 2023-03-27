// Declaração de bibliotecas
#include <Arduino.h>

// Declaração de constantes
#define LIGA (1 << PB0)
#define DESLIGA (1 << PB1)
#define SENSOR (1 << PB3)
#define ALARME (1 << PD6)
#define MOTOR (1 << PD2)

#define LIGA_PRESSED !(PINB & LIGA)
#define DESLIGA_PRESSED !(PINB & DESLIGA)
#define SENSOR_PRESSED !(PINB & SENSOR)

// Link para testar no TinkerCad: https://www.tinkercad.com/things/car8zXYx93I?sharecode=Zouxd9nRDiuOjUH4fUxEZKzrCo382AnXi5d5piCjcaE

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

    PORTD &= ~(MOTOR | ALARME); // Desligar o motor e o alarme

    // Loop infinito
    while (1)
    {
        // se liga estiver pressionado ligar e sensor desligado
        if (LIGA_PRESSED && !SENSOR_PRESSED)
        {
            PORTD &= ~ALARME; // Desligar o alarme
            PORTD |= MOTOR;   // Ligar o motor
        }

        // se desliga estiver pressionado desligar o motor
        if (DESLIGA_PRESSED)
        {
            PORTD &= ~MOTOR; // Desligar o motor
        }

        // se sensor estiver acionado desligar o motor
        if (SENSOR_PRESSED)
        {
            PORTD &= ~MOTOR;
            PORTD |= ALARME;
        }
    }
    return 0;
}