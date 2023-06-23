#include <Arduino.h>
#include "ADC.h"
#include "UART.h"
#include "TIMER2.h"

#define S_ENTRADA_VOLUME 0
#define S_ENTRADA_TEMPO 10
#define S_CALC_FLUXO 20
#define S_CALC_POTENCIA 30
#define S_ALTERAR_PARAMETROS 40
#define S_CALC_FLUXO_REAL 50
#define S_CALC_ERRO_PORCENTUAL 60

short int estado = S_ENTRADA_VOLUME;

unsigned int volume;           // ml
unsigned int tempo_em_minutos; // min
float fluxo_definido;          // ml/h
float fluxo_real;              // ml/h
float erro_porcentual;         // %

// Protótipos ----------------------------------------------
void entrada_volume();
void entrada_tempo();
void calcula_fluxo();
void calculo_potencia();
void alterar_parametros();
void calcula_fluxo_real();
void calcula_erro_porcentual();

// Callbacks -----------------------------------------------
void timer2_callback(char *message, unsigned int seconds)
{
  UART_Transmit(message);
}

// Main ----------------------------------------------------
int main(void)
{
  // Configurações iniciais ---------------------------------
  ADC_setup();
  UART_setup(MYUBRR);
  TIMER2_setup(timer2_callback);
  sei();

  // Variáveis ----------------------------------------------

  // Função principal ---------------------------------------

  for (;;)
  {

    switch (estado)
    {
    case S_ENTRADA_VOLUME:
      UART_print("Entre com o volume\n");
      entrada_volume();
      break;
    case S_ENTRADA_TEMPO:
      UART_print("Entre com o Tempo de Infusão em minutos\n");
      entrada_tempo();
      break;
    case S_CALC_FLUXO:
      UART_print("Calculando o fluxo\n");
      calcula_fluxo();
      break;
    case S_CALC_POTENCIA:
      UART_print("Calculando a potência\n");
      calculo_potencia();
      break;
    case S_ALTERAR_PARAMETROS:
      UART_print("Deseja alterar os parâmetros? (sim(s)/nao(n))\n");
      alterar_parametros();
      break;

    default:
      break;
    }

    // adc resultado = ADC_get_from_adc(ADC0D);
    // UART_print("ADC0D: ");
    // UART_print(resultado.voltage);
    // UART_print(" V\n");

    _delay_ms(1000);
  }

  return 0;
}

// Funções --------------------------------------------------
void entrada_volume()
{
  // Aguarda a leitura do volume
  while (!UART_StringReceived())
    ;

  char *message = (char *)UART_GetString();
  volume = atoi(message);
  UART_print("Volume: ");
  UART_print(message);
  UART_print("\n");
  estado = S_ENTRADA_TEMPO;
  // Limpa o conteúdo do buffer 'message'
  memset(message, 0, strlen(message));
}

void entrada_tempo()
{
  // Aguarda a leitura do tempo
  while (!UART_StringReceived())
    ;

  char *message = (char *)UART_GetString();
  tempo_em_minutos = atoi(message);
  UART_print("Tempo: ");
  UART_print(message);
  UART_print("\n");
  estado = S_CALC_FLUXO;
  // Limpa o conteúdo do buffer 'message'
  memset(message, 0, strlen(message));
}

void calcula_fluxo()
{
  /*
  O usuário necessita que seja injetado no paciente 300 ml de um determinado líquido
em um período de tempo de 3 horas. Com base nas informações inseridas, pode-se
perceber que é necessário que o motor opere de tal forma que seja injetado no
paciente um fluxo de 100 ml por hora do líquido.*/

  float tempo_em_horas = tempo_em_minutos / 60.0;
  fluxo_definido = volume / tempo_em_horas;
  UART_print("Fluxo: ");
  UART_print(fluxo_definido);
  UART_print(" ml/h\n");
  UART_print("\n");

  estado = S_CALC_POTENCIA;
}

void calculo_potencia()
{
  /*
  Como o motor, à 100% de potência, injeta 450 ml de líquido por hora, é necessário
que opere com uma potência de 22,22% para que seja injetado 100 ml por hora:*/

  float potencia = fluxo_definido * 100 / 450;
  UART_print("Potência: ");
  UART_print(potencia);
  UART_print("%\n");

  estado = S_ALTERAR_PARAMETROS;
}

void alterar_parametros()
{
  // Aguarda o usuario digitar sim ou nao
  while (!UART_StringReceived())
    ;

  char *message = (char *)UART_GetString();
  if (strcmp(message, "sim") == 0 || strcmp(message, "s") == 0)
  {
    estado = S_ENTRADA_VOLUME;
  }
  else if (strcmp(message, "nao") == 0 || strcmp(message, "n") == 0)
  {
    estado = S_CALC_FLUXO_REAL;
  }
}

void calcula_fluxo_real()
{
  // Precisa contar duas gotas (clicks no botão PD2) e dividir pelo tempo entre as gotas

}