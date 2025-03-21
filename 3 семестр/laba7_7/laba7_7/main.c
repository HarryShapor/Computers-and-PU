#include <avr/io.h>			//���������� �����/������
#include <avr/interrupt.h>	//���������� ��������� ����������
ISR(ADC_vect)				//���������� ADC
{
	if (UDRE0 != 0  & TXC0 != 0)	//�������� ��������� �������� ������
	{
		UDR0 = ADCL/10;				//�������� �������� ����������� � ��������
	}
}
int main(void)
{
	UBRR0 = 103;			//�������� 9600���/c ��� ������� ���������� 16���
	UCSR0B |= (1 << TXEN0);	//���������� �������� ������ �� UART
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);//������ ������ 8���
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	
	//��������� ���, ��������� ��������������, ���������� ���������� ADC � //CLK/128
	ADMUX |= (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
	//���������� ��� 1.1 � � ��������� ������� �����������
	ACSR = 0b01001000;	//��������� ��� � ���������� ����������
	sei();				//���������� ���������� ����������
	while (1)			//����������� ����
	{
	}
}

