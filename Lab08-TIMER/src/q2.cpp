#include <avr/io.h>
#include <avr/interrupt.h>

#define RED_LED_PIN PD6
#define GREEN_LED_PIN PD7

int main() {
  // Configura os pinos do LED como saída
  DDRD |= (1 << RED_LED_PIN) | (1 << GREEN_LED_PIN);

  // Configura o timer0 com prescaler de 1024 e modo de contagem normal
  TCCR0A = 0x00; // definir o modo de operação normal
  TCCR0B = 0x05; // definir o prescaler como 1024
  TCNT0 = 0x00; // reiniciar o contador
  TIMSK0 |= (1 << TOIE0); // habilitar a interrupção de overflow
  sei(); // habilitar interrupções globalmente

  int red_led_state = 0;
  int green_led_state = 0;
  int tick_count = 0;

  while (1) {
    // loop infinito, a execução do programa ocorre dentro da rotina de interrupção
  }
}

ISR(TIMER0_OVF_vect) {
  // A cada interrupção de overflow do timer0, incrementa o contador de ticks
  static int tick_count = 0;
  tick_count++;

  // Verifica se passou um segundo (1000ms)
  if (tick_count == 15625) { // 1000ms / 64us = 15625
    tick_count = 0;

    // Inverte o estado do LED vermelho
    static int red_led_state = 0;
    red_led_state ^= 1;
    if (red_led_state) {
      PORTD |= (1 << RED_LED_PIN); // acende o LED vermelho
    } else {
      PORTD &= ~(1 << RED_LED_PIN); // apaga o LED vermelho
    }

    // Incrementa o estado do LED verde e verifica se passou um minuto (60000ms)
    static int green_led_state = 0;
    green_led_state++;
    if (green_led_state == 600) { // 60000ms / 100ms = 600
      green_led_state = 0;
    }
    if (green_led_state < 6) {
      PORTD |= (1 << GREEN_LED_PIN); // acende o LED verde
    } else {
      PORTD &= ~(1 << GREEN_LED_PIN); // apaga o LED verde
    }
  }
}
