#include <Arduino.h>

#include "UART.h"
#include "TIMER2.h"

#define BTN_CLICK (1 << PB1)

void timer2_callback(char *message)
{
  UART_Transmit(message);
}

void setup_button_interrupts_PCINT0()
{
  PCICR |= (1 << PCIE0);                   // Habilitar interrupção no PCINT0
  PCMSK0 |= (1 << PCINT1) | (1 << PCINT2); // Habilitar interrupção nos pinos PB1 e PB2
}


int main(void)
{

  UART_Init(MYUBRR);
  TIMER2_setup(timer2_callback);

  sei();

  for (;;)
  {
    if (UART_StringReceived())
    {
      char *message = (char *)UART_GetString();
      if (strcmp(message, "on") == 0)
      {
        print("ligando\n");
        TIMER2_start();
      }

      if(strcmp(message, "of") == 0) {
        print("desligando\n");
        TIMER2_stop();
      }
      print(strcat(message, "\n"));
    }
  }

  return 0;
}