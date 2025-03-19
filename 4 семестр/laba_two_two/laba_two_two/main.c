#include <avr/io.h>


int main(void)
{
	DDRD = 0x40;
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0) | (0 << WGM01) | (1 << WGM00);
	OCR0A = 0x0A;
	TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
	while (1)
	{
	}
}

