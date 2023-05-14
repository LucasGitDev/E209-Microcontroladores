#include "Arduino.h"

#define INTERVALO 199 // Valor do comparador A para gerar uma interrupção a cada 100 us
#define ON_TIME 8     // Quantidade de segundos que o motor ficará ligado

#define MOTOR (1 << PD6)      // Pino 6 do Arduino
#define ON_BUTTON (1 << PB1)  // Pino 9 do Arduino
#define OFF_BUTTON (1 << PB2) // Pino 10 do Arduino

typedef struct _timer
{
    unsigned int cont;
    unsigned int segundos;
    unsigned int tempo_inicial;
    bool motor_ligado;
} timer;

timer self = {
    .cont = 0,             // Contador de interrupções do Timer 2
    .segundos = 0,         // Contador de segundos - máximo de 65535 segundos
    .tempo_inicial = 0,    // Tempo inicial da contagem a partir do momento que o motor é ligado
    .motor_ligado = false, // Variável que indica se o motor está ligado ou não
};

void setup_timer_2()
{

    TCCR2A = (1 << WGM21);  // Configuração do modo de funcionamento para Comparador
    TCCR2B = (1 << CS21);   // Pre-scaler de 8 (Frequência de 2MHz - Período de 500 ns em cada contagem)
    OCR2A = 199;            // 200 contagens de 500 ns, o que gera uma interrupção a cada 100 us
    TIMSK2 = (1 << OCIE2A); // Gerar uma interrupção no estouro do comparador A
}

void setup_button_interrupts_PCINT0()
{
    PCICR |= (1 << PCIE0);                   // Habilitar interrupção no PCINT0
    PCMSK0 |= (1 << PCINT1) | (1 << PCINT2); // Habilitar interrupção nos pinos PB1 e PB2
}

void setup_outputs()
{
    DDRD |= MOTOR;   // Configurar pino de saída
    PORTD &= ~MOTOR; // Iniciar com o pino em nível baixo
}

void setup_PWM()
{
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1); // Modo 7
    TCCR0B |= (1 << CS00);                                 // Seleciona opção para frequência
    OCR0A = 0;                                             // Inicia com 0% de duty cycle
}

void start_motor()
{

    if ((int)OCR0A == 0)  // Se o motor estiver desligado
        OCR0A += 255 / 8; // Ligar o motor com 12,5% de duty cycle

    self.tempo_inicial = self.segundos; // Guardar o tempo inicial da contagem
    self.motor_ligado = true;           // Indicar que o motor está ligado

    Serial.println("Motor ligado");
}

void stop_motor()
{

    Serial.print("Velocidade final: ");
    Serial.println(OCR0A);

    OCR0A = 0;                 // Desligar o motor
    self.motor_ligado = false; // Indicar que o motor está desligado
    self.tempo_inicial = 0;    // Zerar o tempo inicial da contagem

    Serial.println("Motor desligado");
}

void increase_speed()
{
    Serial.print("Velocidade: ");
    Serial.println(OCR0A);
    int aux = (int)OCR0A; // Conversão para inteiro para evitar erros de arredondamento
    if ((int)OCR0A < 255) // Se a velocidade for menor que 100%
        aux += 255 / 8;   // Aumentar a velocidade em 12,5%

    if (aux > 255) // Se a velocidade for maior que 100%
        aux = 255; // Ajustar para 100%

    OCR0A = aux; // Atribuir o novo valor de velocidade
}

ISR(PCINT0_vect)
{
    if ((PINB & ON_BUTTON) == ON_BUTTON)
    {
        Serial.println("Botão ON pressionado");
        start_motor();
    }

    if ((PINB & OFF_BUTTON) == OFF_BUTTON)
    {
        Serial.println("Botão OFF pressionado");
        stop_motor();
    }
}

ISR(TIMER2_COMPA_vect) // Rotina de interrupção do Timer 2
{
    self.cont++;

    if (self.cont == 10000)
    {
        self.cont = 0;
        self.segundos++;

        Serial.print("Segundos: ");
        Serial.println(self.segundos);

        if (self.motor_ligado && self.segundos - self.tempo_inicial < ON_TIME) // Se o motor estiver ligado e o tempo de 8 segundos não tiver sido atingido
        {
            increase_speed();
        }
    }
}
int main(void)
{
    Serial.begin(115200);
    Serial.println("Iniciando...");

    setup_outputs();
    setup_timer_2();
    setup_button_interrupts_PCINT0();
    setup_PWM();

    Serial.println("Configurado...");
    sei();

    for (;;)
    {
        if (self.motor_ligado)
        {

            if (self.segundos - self.tempo_inicial >= ON_TIME)
            {
                stop_motor();
            }
        }
        _delay_ms(100);
    }

    return 0;
}
