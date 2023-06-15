#include <Arduino.h>
#include "UART.h"

volatile char buffer[MAX_BUFFER_SIZE];
volatile uint8_t bufferIndex = 0;
volatile bool stringReceived = false;

void UART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Habilita a recepcao, tranmissao e interrupcao na recepcao
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Configura o formato da mensagem: 8 bits de dados e 1bits de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    memset((void *)buffer, 0, sizeof(buffer)); // Limpa o buffer de recepção
}

void UART_Transmit(char *dados)
{
    // Envia todos os caracteres do buffer dados ate chegar um final de linha
    while (*dados != 0)
    {
        // Aguarda a transmissão acabar
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        // Escreve o caractere no registro de tranmissão
        UDR0 = *dados;
        // Passa para o próximo caractere do buffer dados
        dados++;
    }
}

ISR(USART_RX_vect)
{
    if (!stringReceived)
    {
        buffer[bufferIndex] = UDR0;
        if (buffer[bufferIndex] == '\n')
        {
            stringReceived = true;
            buffer[bufferIndex] = '\0';
            bufferIndex = 0;
        }
        else
        {
            bufferIndex++;
        }
    }
}

/*
 * GETTERS
 ****************************************************************************************
 */


bool UART_StringReceived()
{
    return stringReceived;
}

volatile char *UART_GetString()
{
    stringReceived = false; // Sinaliza que a string foi lida

    return buffer;
}
/*
 * EXAMPLES
 ****************************************************************************************
 */
int main_sample(void)
{

    UART_Init(MYUBRR);

    sei();

    for (;;)
    {
        if (UART_StringReceived())
        {
            char *message = (char *)UART_GetString();
            if (strcmp(message, "ligar") == 0)
            {
                print("ligando\n");
            }
            print(strcat(message, "\n"));
        }
    }

    return 0;
}