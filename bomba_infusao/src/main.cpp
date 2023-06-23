#include <Arduino.h>
#include "ADC.h"
#include "UART.h"

int main(void)
{
  ADC_setup();
  UART_setup(MYUBRR);
  sei();

  for (;;)
  {
  }

  return 0;
}