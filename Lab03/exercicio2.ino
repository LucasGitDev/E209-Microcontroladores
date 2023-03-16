int main(void)
{
    DDRB = 0b00000011;

    char estado = 0b00;

    // 00 -> 01 -> 10 -> 11 -> 00
    while (1)
    {
        printf("estado: %d", estado);
        PORTB = estado;
        _delay_ms(1000);
        estado = (estado + 1) % 4;
    }
}