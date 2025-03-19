#include <avr/io.h>
int main(void)
{
	DDRB =0x20;
	PORTB |= 0x01;
	while (1)
	{
		if(PIND&0x01)!=0x00)
		PORTD ^= ~0x04;
		if(PIND&0x02) != 0x00)
		PORTD ^= ~0x08;
		if(PINB&0x05) != 0x00)
		PORTD = ~0x10;
	}
}