
#ifndef __UART_COMPONENT__
#define __UART_COMPONENT__

/*
 * DEFINES
 ****************************************************************************************
 */

#define FOSC 16000000U // ClockSpeed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define MAX_BUFFER_SIZE 32

#define print(x) UART_Transmit((char *)x)

/*
 * DECLARATIONS
 ****************************************************************************************
 */

void UART_setup(unsigned int ubrr);
void UART_Transmit(char *dados);
char *toString(void *dado, const char *formato);

void UART_print(double valor);
void UART_print(int valor);
void UART_print(uint16_t valor);
void UART_print(char caractere);
void UART_print(const char *string);

/*
 * GETTERS
 ****************************************************************************************
 */

bool UART_StringReceived();
volatile char *UART_GetString();

#endif