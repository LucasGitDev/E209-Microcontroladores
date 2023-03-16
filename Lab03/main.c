#include <stdio.h>

int main(void)
{

    char estado = 0b00;

    // 00 -> 01 -> 10 -> 11 -> 00
    while (1)
    {
        estado = (estado + 1) % 4;
        printf("Estado: %d\n", estado);
        // _delay_ms(500);
        estado = (estado + 1) % 4;
        printf("Estado: %d\n", estado);
        // _delay_ms(500);
        estado = (estado + 1) % 4;
        printf("Estado: %d\n", estado);
        // _delay_ms(500);
        estado = (estado + 1) % 4;
        printf("Estado: %d\n", estado);
        // _delay_ms(500);
    }
}