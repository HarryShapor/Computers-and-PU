#include <avr/io.h> //библиотеки ввода/вывода
#include <avr/interrupt.h>
char x = 0x00;
char Msg[];
int i;
ISR (USART0_TX_vect)
{
	if (i <= strlen(Msg) & UDRE0 != 0 & TXC0 != 0)
	{
		UDR0 = Msg[i++];
	}
	if (i >= strlen(Msg))
		i = 0;
}

ISR (USART0_RX_vect)
{
	if (RXC0 != 1)
	{
		if (UDR0 == 0x4D)
		{
			Msg[i++] = UDR0;
			PORTB = 0x20;
		}
		x = 0x00;
	}
}
int main(void)
{
	char y;
	DDRB = 0x20;
	UBRR0 = 103; //скорость
	UCSR0B |= (1 << TXEN0) | (1<<RXEN0) | (1 << TXCIE0);	//разрешение отправки данных
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);	//размер пакета 8бит
	sei();	//глобальное разрешение прерываний
	//char Msg[];
	x = UDR0;
	if (x == 0x21){
		UCSR0B |= (1 << RXCIE0);
		while (1)	//бесконечный цикл
		{
			x = UDR0;
				//PORTB = 0x20;
				/*UCSR0B |= (1 << RXCIE0);
				y = Msg[0];
				Msg[0] = Msg[1];
				Msg[1] = y;
				y = Msg[2];
				Msg[2] = Msg[3];
				Msg[3] = y;
				x = 0x00;*/
		}
	}
	i =0x00;
	UDR0 = Msg[i++];
	while (1)
	{
		
	}
}
