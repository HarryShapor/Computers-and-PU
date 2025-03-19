#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
ISR(INT0_vect)
{
	wdt_reset();
	PORTC ^= (1 << PORTC3);
}
ISR(WDT_vect)
{
	PORTC = (1 << PORTC2);
}
int main(void)
{
    DDRC = 0x0F;
	PORTC = (0 << 3) | (0 << 2) | (0 << 1) | (1 << 0);
	//DDRD = 0x04;
	PORTD = 0x04;
	EICRA = 0x03;
	wdt_enable(WDTO_8S);
	WDTCSR = (1 << WDIE);
	PORTC = (0 << 0);
	
	sei();
    while (1) 
    {
		PORTC ^= (1 << PORTC1);
		
    }
}

