// Declaração de bibliotecas
#include <Arduino.h>

// Declaração de constantes
#define BOTAO_A (1 << PB0)
#define BOTAO_B (1 << PB1)
#define BOTAO_C (1 << PB2)

#define MOTOR_1 (1 << PD5)
#define MOTOR_2 (1 << PD6)
#define MOTOR_3 (1 << PD2)

// Declaração de variáveis globais

// Declaração de funções
int main(void)
{
  // Direcionamento das Portas (DDRx) - Modificar só os pinos de saída
  DDRB = 0;
  DDRD |= MOTOR_1 + MOTOR_2 + MOTOR_3;

  while (1)
  {
    short int botaoA = (PINB & BOTAO_A);
    short int botaoB = (PINB & BOTAO_B);
    short int botaoC = (PINB & BOTAO_C);

    if (botaoC)
    {
      PORTD &= ~(MOTOR_1 + MOTOR_2);
      PORTD |= MOTOR_3;
    }

    if (botaoB)
    {
      PORTD &= ~(MOTOR_3);
      PORTD |= MOTOR_2;
    }

    if (botaoA)
    {
      PORTD &= ~(MOTOR_3);
      PORTD |= MOTOR_1;
    }
  }

  return 0;
}