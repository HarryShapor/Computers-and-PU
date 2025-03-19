#include <avr/io.h> //библиотеки ввода/вывода
#include <avr/interrupt.h>
#include <stdio.h>
char i = 0;
char USB = 0x65;
char x;
char len;
char Msg[23] = "Atmega328P:ReadyToWork\n";
char flag = 0x00;
ISR (USART0_TX_vect)
{	
	if (flag == 0x00 & x == 0x80)
		flag = 0x01;
	if (flag == 0x01 & UDRE0 != 0 & TXC0 != 0)
		{
			UDR0 = USB;
			flag = 0x02;
		}
	if (flag == 0x02 & TXC0 == 0 & UDR0 == 0x65)
		flag = 0x03;
	if (UDRE0 != 0 &TXC0 != 0 & flag == 0x03)
	{
		UDR0 = len = strlen(Msg);
		flag = 0x04;
	}
	if (flag == 0x04 & UDRE0 != 0 & TXC0 != 0)
		{
			if (i <= len)
				UDR0 = Msg[i++];
			else UDR0 = 0xF0;
		}
	if (TXC0 == 0 & UDR0 == 0xF0)
	{
		UCSR0B &= 0xBF;
		i = 0;
	}
}

int main(void)
{

	UBRR0 = 1; //скорость
	UCSR0B |= (1<<TXEN0) | (1 << TXCIE0);	//разрешение отправки данных
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);	//размер пакета 8бит
	sei();	//глобальное разрешение прерываний
	UDR0 = x = 0x80;
	while (1)	//бесконечный цикл
	{
	}
}