#include <avr/io.h>

#define LED_PIN PD5

volatile uint8_t tick_count = 0;

void setup() {
  // Configura o pino do LED como saída
  DDRD |= (1 << LED_PIN);

  // Configura o timer0 com prescaler de 1024 e modo de contagem normal
  TCCR0A = 0x00; // definir o modo de operação normal
  TCCR0B = 0x05; // definir o prescaler como 1024
  TCNT0 = 0x00; // reiniciar o contador
  TIMSK0 |= (1 << TOIE0); // habilitar a interrupção de overflow
  sei(); // habilitar interrupções globalmente
}


ISR(TIMER0_OVF_vect) {
  // A cada interrupção de overflow do timer0, incrementa o contador de ticks
  tick_count++;

  // Se o contador atingir o valor necessário para 150ms, inverte o estado do LED
  if (tick_count == 234) { // 150ms / 64us = 234
    tick_count = 0;
    PORTD ^= (1 << LED_PIN);
  }
}

int main() {
  setup();

  while (1) {
  }

  return 0;
}
