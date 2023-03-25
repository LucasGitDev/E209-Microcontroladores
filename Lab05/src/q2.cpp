// Declaração de bibliotecas
#include <Arduino.h>

// Declaração de constantes
#define BOTAO_A (1 << PB0)
#define BOTAO_B (1 << PB1)
#define BOTAO_C (1 << PB3)

#define MOTOR_1 (1 << PD6)
#define MOTOR_2 (1 << PD2)
#define MOTOR_3 (1 << PD7)

#define BOTAO_A_PRESSED !(PINB & BOTAO_A)
#define BOTAO_B_PRESSED !(PINB & BOTAO_B)
#define BOTAO_C_PRESSED !(PINB & BOTAO_C)

// Link para testar no TinkerCad: https://www.tinkercad.com/things/car8zXYx93I?sharecode=Zouxd9nRDiuOjUH4fUxEZKzrCo382AnXi5d5piCjcaE

// Declaração de variáveis globais

// Declaração de funções
int main(void)
{
  // Direcionamento das Portas (DDRx) - Modificar só os pinos de saída
  DDRD |= MOTOR_1 + MOTOR_2 + MOTOR_3;

  PORTD &= ~(MOTOR_1 + MOTOR_2 + MOTOR_3); // Desligar motores

  short int motores[] = {0, 0, 0};

  while (1)
  {

    if (BOTAO_C_PRESSED)
    {
      if (motores[2] == 1)
      {
        PORTD &= ~(MOTOR_3);
        motores[2] = 0;
      }
      else
      {
        PORTD &= ~(MOTOR_1 + MOTOR_2);
        PORTD |= MOTOR_3;
        motores[2] = 1;
      }
      _delay_ms(100);
    }

    if (BOTAO_B_PRESSED)
    {
      if (motores[1] == 1)
      {
        PORTD &= ~(MOTOR_2);
        motores[1] = 0;
      }
      else if (motores[2] != 1)
      {
        PORTD &= ~(MOTOR_3); // Desligar o motor
        PORTD |= MOTOR_2;    // Ligar o motor
        motores[2] = 0;
        motores[1] = 1;
      }
      _delay_ms(100);
    }

    if (BOTAO_A_PRESSED)
    {
      if (motores[0] == 1)
      {
        PORTD &= ~(MOTOR_1);
        motores[0] = 0;
      }
      else if (motores[2] != 1)
      {
        PORTD &= ~(MOTOR_3);
        PORTD |= MOTOR_1;
        motores[2] = 0;
        motores[0] = 1;
      }
      _delay_ms(100);
    }
  }

  return 0;
}