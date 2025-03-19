#include <avr/io.h>
int main(void)
{
  int x;
	DDRD = 0xFF;
	while (1)
	{
		PORTD = x;
		x++;
	}
}

