int main(void)
{
    DDRB = 0b00000011;

    char estado = 0b1;

    // 01 -> 10 -> 00 -> 01
    while (1)
    {
        printf("estado: %d", estado);
        PORTB = estado;
        _delay_ms(1000);
        estado = (estado + 1) % 3;
    }
}