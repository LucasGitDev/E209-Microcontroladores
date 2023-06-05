#include <Arduino.h>

#define botao (1 << PD2)
#define FOSC 16000000U // ClockSpeed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

char msg_tx[30];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 5;

int quantidadeClicks = 0;

// Prototipos das funcoes
// void UART_Init(unsignedintubrr);
// voidUART_Transmit(char*dados);

ISR(USART_RX_vect)
{
  // Escreve o valor recebido pela UART na posição pos_msg_rx do buffer msg_rx
  msg_rx[pos_msg_rx++] = UDR0;
  if (pos_msg_rx == tamanho_msg_rx) // Se o tamanho da mensagem recebida for igual ao tamanho máximo
    pos_msg_rx = 0;                 // Reinicia a posição do buffer
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

void setupInterrupt()
{
  // Configura o pino PD4 como entrada
  DDRD &= ~botao;
  // Habilita o resistor de pull-up
  PORTD |= botao;
  // Configura a interrupcao externa INT0 para borda de descida
  EICRA = (1 << ISC01) + (1 << ISC00) + (1 << ISC10) + (1 << ISC11); // Configurar a INT0 para gerar interrupção quando o botão for pressionado

  // Habilitar a INT0
  EIMSK = (1 << INT0);
}

ISR(INT0_vect)
{
  quantidadeClicks++;

  // clear msg_tx
  msg_tx[0] = '\0';

  strcat(msg_tx, "Quantidade de clicks: ");

  itoa(quantidadeClicks, msg_tx + strlen(msg_tx), 10);

  strcat(msg_tx, "\n");

  UART_Transmit(msg_tx);
  msg_tx[0] = '\0';
}

int main(void)
{
  UART_Init(MYUBRR);
  setupInterrupt();
  sei();

  UART_Transmit("Iniciando contagem\n");

  // Super-loop
  for (;;)
  {
    // se digitar 'zerar' no terminal, zera a quantidade de clicks
    // UART_Transmit(msg_rx);
    if (strcmp(msg_rx, "zerar") == 0)
    {
      UART_Transmit("Zerando...\n");
      // itoa(quantidadeClicks, msg_tx, 10);
      // strcat(msg_tx, "\n");
      // UART_Transmit(msg_tx);
      quantidadeClicks = 0;
      msg_tx[0] = '\0';
      msg_rx[0] = '\0';
    }

    msg_rx[0] = '\0';
    // UDR0 = '\0';
    _delay_ms(150);
  }
}
