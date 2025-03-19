#include <avr/io.h> //���������� �����/������
#include <avr/interrupt.h>
#include <stdio.h>
char i = 0;
char Msg[23] = "Atmega328P:ReadyToWork\n";
ISR (USART0_TX_vect)
{	
	if (i <= strlen(Msg) & UDRE0 != 0 & TXC0 != 0)
	{
		UDR0 = Msg[i++];
	}
	if (i >= strlen(Msg))
		i = 0;
}

int main(void)
{

	UBRR0 = 103; //��������
	UCSR0B |= (1<<TXEN0) | (1 << TXCIE0);	//���������� �������� ������
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);	//������ ������ 8���
	sei();	//���������� ���������� ����������
	UDR0 = 0x00;
	while (1)	//����������� ����
	{	
	}
}