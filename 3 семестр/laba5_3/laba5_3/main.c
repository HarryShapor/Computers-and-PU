#include <avr/io.h>
#include <avr/interrupt.h>
char x,y, count;
ISR(PCINT0_vect)
{
	x = (count & 0x40) >> 1;
	PORTB = PORTB & 0xDF;
	PORTB = PORTB | x;
}
ISR(PCINT2_vect)
{
	y = (count & 0x40) >> 1;
	PORTB = PORTB & 0xDF;
	PORTB = PORTB | y;
}int main(void)
{
	x=0;
	sei();
	DDRC = 0xff;
	DDRB = 0x20;
	DDRD = 0x00;
	PCICR = 0x07;
	PCMSK0 |= (1 << PCINT3);
	PCMSK2 |= (1 << PCINT20);

	while (1)
	{
		PORTC = count;
		PORTD = PORTC >> 4;
		count++;
	}
}