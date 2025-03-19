#include <avr/io.h>			//���������� �����/������
#include <avr/interrupt.h>	//���������� ��������� ����������
ISR (ADC_vect)			//���������� ADC
{
	if (ADCL >= 0x00 &  ADCL <= 0x14) 	//�������� �� 0 �� 20
	{
		PORTB = 0x00;			//���������� L
		PORTD = 0x03;			//���������� RX, TX
	}
	if (ADCL >= 0x15 &  ADCL <= 0x64)	//�������� �� 21 �� 100
	{
		PORTB = 0x20;			//��������� L
		PORTD = 0x03;			//���������� RX, TX
	}
	if (ADCL >= 0x65 &  ADCL <= 0xB4)	//�������� �� 101 �� 180
	{
		PORTB = 0x20;			//��������� L
		PORTD = 0x02;			//��������� RX
	}
	if (ADCL >= 0xB5 & ADCL <= 0xFF)	//�������� �� 181 �� 255
	{
		PORTB = 0x20;			//��������� L
		PORTD = 0x00;			//��������� RX, TX
	}
}
int main(void)
{
	ADMUX |= (1 << REFS0);			//V�������� = V�������
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) |
	(1 << ADPS1) | (1 << ADPS0);
	//��������� ���, ��������� ��������������, ���������� ���������� ADC � //CLK/128
	DDRB = 0x20;	//�� ����� PORTB5
	DDRD = 0xff;		//�� ����� ���� PORTD
	sei();			//���������� ���������� ����������
	while (1)		//����������� ����
	{
	}
}
