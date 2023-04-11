#include <Arduino.h>

// Tinkercad: https://www.tinkercad.com/things/bXpN7iKAkUY-copy-of-projetinho-jao-gular/editel?sharecode=4A1vMZ0PL9Rs-whseg43lfbQfp7sQiY6JkKtvxrxNcg

#define LED00 (1 << PD5)
#define LED01 (1 << PD6)
#define LED02 (1 << PD7)
#define LED03 (1 << PB1)

#define BOTAO02 (1 << PB0) // PCINT0
#define BOTAO01 (1 << PB2) // PCINT2
#define BOTAO03 (1 << PD4) // PCINT20

int main()
{

  DDRD |= LED00 | LED01 | LED02;
  DDRB |= LED03;

  // Desligar todos os LEDs
  PORTD &= ~(LED00 | LED01 | LED02);
  PORTB &= ~LED03;

  PCICR |= (1 << PCIE0) | (1 << PCIE2);
  PCMSK0 |= BOTAO02 | BOTAO01;
  PCMSK2 |= BOTAO03;

  sei();

  while (1)
  {
    // Piscar LED00 a cada 1 segundo
    PORTD ^= LED00;
    _delay_ms(250);
  }

  return 0;
}

ISR(PCINT0_vect)
{
  // Piscar Led02 se o botão 02 for pressionado
  if (PINB & BOTAO02)
  {
    PORTD ^= LED02;
    _delay_ms(1000);
    PORTD ^= LED02;
  }

  // Piscar Led01 se o botão 01 for pressionado
  if (PINB & BOTAO01)
  {
    PORTD ^= LED01;
    _delay_ms(500);
    PORTD ^= LED01;
  }
}

ISR(PCINT2_vect)
{
  // Piscar LED03 a cada 1 segundo
  PORTB ^= LED03;
  _delay_ms(500);
  PORTB ^= LED03;
}
