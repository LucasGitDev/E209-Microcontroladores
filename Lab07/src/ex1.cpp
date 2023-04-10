// Includes
#include <Arduino.h>

// Link para Tinkercad: https://www.tinkercad.com/things/aLk0CDT5QpW-frantic-jaagub-waasa/editel?sharecode=iv9I1MZuMa0Q3DCBoAp0XXE_5mh1606x8oOlZk6DqEU

// Definições
#define BOTAO (1 << PD2)          // Botão de controle do motor (INT0)
#define MOTOR_ABRINDO (1 << PD5)  // LED indicador de motor abrindo
#define MOTOR_FECHANDO (1 << PD4) // LED indicador de motor fechando

#define DELAY 1000 // Delay entre cada passo do motor

static short int path = 10;   // 0 = aberto, 10 = fechado
static short int step = 2;    // iniciar -> 0 = abertura, 1 = fechamento e 2 = parado
static short int pressed = 0; // Contador de botões pressionados

int main(void)
{
  Serial.begin(9600);
  Serial.println("| Aberto");
  Serial.println("  Fechado |");
  Serial.println("==========>");

  DDRD = MOTOR_ABRINDO | MOTOR_FECHANDO; // Configura os pinos como saída

  PORTD &= ~(MOTOR_ABRINDO | MOTOR_FECHANDO); // Desliga os LEDs

  EICRA = (1 << ISC01) | (1 << ISC00); // Configura a interrupção externa para borda de subida
  EIMSK = (1 << INT0);                 // Habilita a interrupção externa
  sei();                               // Habilita as interrupções

  short int ultimaDirecao = -1; // 0 = fechando, 1 = abrindo

  while (1)
  {
    // Serial.print("Step: ");
    // Serial.println(step);

    // Serial.print("Path: ");
    // Serial.println(path);
    printPortao();

    switch (step)
    {
    case 0:
      // Abre o portão
      if (path < 10)
      {
        path++;
        PORTD |= MOTOR_ABRINDO;
        PORTD &= ~MOTOR_FECHANDO;
        ultimaDirecao = 1;
      }
      else
      {
        step = 2;
      }
      break;

    case 1:
      // Fecha o portão
      if (path > 0)
      {
        path--;
        PORTD |= MOTOR_FECHANDO;
        PORTD &= ~MOTOR_ABRINDO;
        ultimaDirecao = 0;
      }
      else
      {
        step = 2;
      }
      break;

    default:
      // Para o portão
      PORTD &= ~(MOTOR_ABRINDO | MOTOR_FECHANDO);
      if (pressed > 1)
      {
        pressed = 0;
        step = ultimaDirecao;
      }

      break;
    }

    _delay_ms(DELAY);
  }

  return 0;
}

// Interrupção externa
ISR(INT0_vect)
{
  switch (path)
  {
  case 0:
    // caso o portão esteja aberto, inicia o fechamento
    step = 0;
    break;

  case 10:
    // caso o portão esteja fechado, inicia o abertura
    step = 1;
    break;

  default:
    // caso o portão esteja em movimento, para o mesmo
    step = 2;
    pressed++;
    break;
  }
}

void printPortao()
{
  // printa '=' para cada passo do portão
  for (int i = 0; i < path; i++)
  {
    Serial.print("=");
  }
  Serial.println(">");
}