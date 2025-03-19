#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
int flag = 0;
ISR(TIMER1_COMPA_vect)
{
	PORTD ^= (1 << PORTD0);
	if (flag == 0)
	{
		TCCR2A = 0b10100011;
		TCCR2B = (1 << WGM22) | (1 << CS22) | (1 << CS21) | (0 << CS20);
		flag = 1;
	}
	else if (flag == 1)
	{
		TCCR2A = 0b10100011;
		TCCR2B = (1 << WGM22) | (1 << CS22) | (0 << CS21) | (1 << CS20);
		flag = 2;
	}
	else if (flag == 2)
	{
		TCCR2A = 0b10100011;
		TCCR2B = (1 << WGM22) | (1 << CS22) | (0 << CS21) | (0 << CS20);
		flag = 0;
	}
}

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	
	//TIMER1
	TCCR1A |= (1 << COM1A0) | (1 << COM1A1) | (0 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = 3906;
	
	// TIMER2
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
	//OCR2A = 61;  // 1 êÃö - 2 êÃö - 4 êÃö 
	OCR2A = 70;  // 0,9 êÃö - 1,7 êÃö - 3,5 êÃö 
	OCR2B = 35;
	
	sei();
    while (1) 
    {
    }
}