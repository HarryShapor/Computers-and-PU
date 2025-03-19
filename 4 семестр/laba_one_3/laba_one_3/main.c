#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
ISR(WDT_vect)
{
	PORTC = (1 << 2);
	wdt_reset(); 
}
int main(void)
{
    DDRC = (1 << DDRC2) | (1 << DDRC1) | (1 << DDRC0);
	PORTC = (0 << 2) | (0 << 1) | (1 << 0);
	wdt_enable(WDTO_1S);
	WDTCSR = (1 << WDIE);
	PORTC = (0 << PORTC0);
	sei();
    while (1) 
    {
		PORTC ^= 0x02;
		//wdt_reset();
    }
}

