#include <avr/io.h>	//��������� �������� � ������� ��������� B
#include <avr/interrupt.h>	//���������� ����������
int flag = 0;	//���������� ����� ��� �������� �������
ISR(TIMER1_COMPA_vect)	//���������� ������� 1 �� ���������� � A
{
	PORTD ^= (1 << PORTD0);	//�������� PORTD0
	if (flag == 0)	//�������� flag �� �������� 0
	{
		OCR2B = 254;	//��������� �������� � ������� ��������� B
		flag = 1;	//��������� ���������� flag � 1
	}
	else if (flag == 1)	//�������� flag �� �������� 1
	{
		OCR2B = 16;	//��������� �������� � ������� ��������� B
		flag = 2;	//��������� ���������� flag � 2
	}
	else if (flag == 2)	//�������� flag �� �������� 2
	{
		OCR2B = 24;	//��������� �������� � ������� ��������� B
		flag = 3;	//��������� ���������� flag � 3
	}
	else if (flag == 3)	//�������� flag �� �������� 3
	{
		OCR2B = 32;	//��������� �������� � ������� ��������� B
		flag = 0;	//��������� ���������� flag � 0
	}
}

int main(void)	//������� ���������, ����� ����� � ���������
{
	DDRD = 0xff;	//��������� �� ����� ����� D
	TCCR1A |= (1 << COM1A0) | (1 << COM1A1);
	//��������� ����� ������ OC1A ��� ����������
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (0 << CS11) |(1 << CS10);
	//���������� ������� ������ OC1A � OC1B � ��������� ������������ 1024
	TIMSK1 |= (1 << OCIE1A);	//���������� ���������� ������� 1
	OCR1A = 11000;	//��������� �������� � ������� ��������� A
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
	//��������� ����� ������ OC2A � OC2B ��� ���������� � ����� ���
	TCCR2B = (1 << WGM22) | (1 << CS22) | (1 << CS21) | (1 << CS20);
	//���������� ������� ������ OC2A � OC2B � ��������� ������������ 1024
	OCR2A = 255; //��������� �������� � ������� ��������� A
	sei();		//���������� ����������
    while (1) //����������� ����
    {
    }
}

