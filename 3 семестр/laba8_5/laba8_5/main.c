#include <avr/io.h>			//���������� � ����������� ������� ������ �����/������
#include <avr/interrupt.h>	//���������� ������ � ������������
char flag_2 = 0x00;			//���� �������� ��� ���������� L
char flag_1 = 0x00;			//���� �������� ��� ���������� TX
char flag_0 = 0x00;			//���� �������� ��� ���������� RX
ISR (TIMER1_COMPA_vect)		//���������� ���������� �� ������� ���������� Timer1 c A
{
	flag_0 += 0x01;			//����������������� ���������� flag_0
	flag_1 += 0x01;			//����������������� ���������� flag_1
	flag_2 += 0x01;			//����������������� ���������� flag_2
	if (flag_0 == 0x0F)		//��������� �������� flag_0 � ���������� 0x0F
	{
		PORTD ^= 0x01;		//����� ��������� RX �� ���������������
		flag_0 = 0x00;		//��������� flag_0
	}
	if (flag_1 == 0x06)		//��������� �������� flag_1 � ���������� 0x06
	{
		PORTD ^= 0x02;		//����� ��������� TX �� ���������������
		flag_1 = 0x00;		//��������� flag_1
	}
	if (flag_2 == 0x14)		//��������� �������� flag_2 � ���������� 0x14
		{
			PORTB ^= 0x20;	//����� ��������� L �� ���������������
			flag_2 = 0x00;	//��������� flag_2
		}
	
}
int main(void)				//������� ���������, ����� ����� � ���������
{
	DDRB = 0x20;			//��������� PORTB5 �� ����� ����������
	DDRD = 0x03;			//��������� PORTD �� ����� ����������
	TCCR1A = (1 << COM1A0) | (1 << COM1A1);		//��������� ������ OC0A � 1 ��� ���������� � A
	TCCR1B = (1 << WGM12) | (1 << CS12);		//����� ���, ������������ clk/256
	TIMSK1 = (1 << OCIE1A);		//���������� ���������� TIMER1 COMPA
	OCR1AH = 0x18;				//������� ����� �������� A Timer1
	OCR1AL = 0x6A;				//������� ����� �������� A Timer1
	sei();					//���������� ���������� ����������
	while (1)				//����������� ����
	{
	}
}

