// Declaração de bibliotecas
#include <Arduino.h>

#define LED_LOOP (1 << PD5)
#define LED_INT (1 << PD4)

int main()
{

  DDRD = LED_INT + LED_LOOP; // Declarar LED_INT e LED_LOOP como saída

  // Desligar os LEDs
  PORTD &= ~LED_INT;
  PORTD &= ~LED_LOOP;

  // Configurar o funcionamento da INT0 (Botão Liga no PD2)
  EICRA = (1 << ISC01) + (1 << ISC00) + (1 << ISC10) + (1 << ISC11); // Configurar a INT0 para gerar interrupção quando o botão for pressionado

  // Habilitar a INT0
  EIMSK = (1 << INT0) + (1 << INT1);

  // Eu estou utilizando interrupção, se sim, DECLARA O "sei();"
  sei();

  for (;;)
  {
    // Inverte o estado do LED_LOOP
    PORTD ^= LED_LOOP;
    _delay_ms(500);
  }
}

// O que acontece se a interrupção INT0 for gerada?
ISR(INT0_vect)
{
  // Liga o LED_INT
  PORTD |= LED_INT;
  // Aguarda 1 segundo
  _delay_ms(1000);
  // Desliga o LED_INT
  PORTD &= ~LED_INT;
}

ISR(INT1_vect)
{

  if (EIMSK & (1 << INT0))
  {
    EIMSK &= ~(1 << INT0);
  }
  else
  {
    EIMSK |= (1 << INT0);
  }
  sei();
}
