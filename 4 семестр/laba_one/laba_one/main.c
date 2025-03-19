#include <avr/io.h>
#include <avr/wdt.h>

int main(void)
{
    DDRC = 0x03;
	PORTC = (0 << 1) & (1 << 0);
	wdt_enable(WDTO_8S);
	PORTC = (1 << 1);
    while (1) 
    {
		PORTC ^= (1 << PORTC1);
    }
}

