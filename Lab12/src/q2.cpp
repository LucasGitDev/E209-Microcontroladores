#include <Arduino.h>

#define FOSC 16000000U // ClockSpeed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#define LED_VERDE (1 << PB0)    // Pino 8
#define LED_VERMELHO (1 << PB1) // Pino 9

char msg_tx[30];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 1;

ISR(USART_RX_vect)
{
    // Escreve o valor recebido pela UART na posição pos_msg_rx do buffer msg_rx
    msg_rx[pos_msg_rx++] = UDR0;
    if (pos_msg_rx == tamanho_msg_rx) // Se o tamanho da mensagem recebida for igual ao tamanho máximo
        pos_msg_rx = 0;               // Reinicia a posição do buffer
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

void UART_Init(unsigned int ubrr)
{
    // Configuraabaudrate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Habilita a recepcao, tranmissao e interrupcao na recepcao
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Configura o formato da mensagem: 8 bits de dados e 1bits de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void setup_leds()
{
    DDRB = 0;                             // Configura todos os pinos do PORTB como entrada
    DDRB |= LED_VERDE | LED_VERMELHO;     // Configura os pinos PB0 e PB1 como saída
    PORTB &= ~(LED_VERDE | LED_VERMELHO); // Desliga os LEDs
}

int main(void)
{
    UART_Init(MYUBRR);
    // setupInterrupt();
    sei();
    setup_leds();

    // Super-loop
    for (;;)
    {
        // se a mensagem recebida for '9' liga vermelho e desliga verde
        if (msg_rx[0] == '9')
        {
            PORTB |= LED_VERMELHO;
            PORTB &= ~LED_VERDE;
        }

        // se a mensagem recebida for '8' liga verde e desliga vermelho
        if (msg_rx[0] == '8')
        {
            PORTB |= LED_VERDE;
            PORTB &= ~LED_VERMELHO;
        }

        msg_rx[0] = '\0';

        _delay_ms(150);
    }
}
