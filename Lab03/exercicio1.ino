int main(void)
{
    DDRD = 0b00001110;
    DDRB = 0b10001110;

    while (1)
    {
        PORTB = 0b00001110;
        _delay_ms(1000);
        PORTB = 0b00000110;
        _delay_ms(1000);
        PORTB = 0b10000110;
        _delay_ms(1000);
    }
}