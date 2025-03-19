#include <avr/io.h> //���������� �����/������
#include <avr/interrupt.h>
char x = 0x00;
ISR (USART0_RX_vect)
{	
	if (RXC0 != 1)
	{
		PORTB = 0x00;
		if (UDR0 == 0x4D)
		{
			PORTB = 0x20;
		}
		x = 0x00;
	}

}
int main(void)
{
	DDRB = 0x20;
	UBRR0 = 103; //��������
	UCSR0B |= (1<<RXEN0) | (1 << RXCIE0);	//���������� �������� ������
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);	//������ ������ 8���
	sei();	//���������� ���������� ����������
	while (1)	//����������� ����
	{
		x = UDR0;
		if (x == 0x)
	}
}
