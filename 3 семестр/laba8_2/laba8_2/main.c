#include <avr/io.h>			//���������� � ����������� ������� ������ �����/������
#include <avr/interrupt.h>	//���������� ������ � ������������
ISR (TIMER1_COMPA_vect)		//���������� ���������� �� ������� ������������ Timer1
{
	PORTB ^= 0x20;	//����� ��������� ������ PORTB5 �� ��������������� (���������)
}
int main(void)				//������� ���������, ����� ����� � ���������
{
	DDRB = 0x20;			//��������� PORTB5 �� ����� ����������
	TCCR1A = 0xC0;			//������� ����� ��� ������������� ������� OC1A � OC1B
	TCCR1B = (1 << WGM12) | (1 << CS00) | (1 << CS02);	//������ �������, ������������ clk/64
	TIMSK1 = (1 << OCIE1A);
	OCR1AH = 0x3D;
	OCR1AL = 0x09;	//���������� ���������� �� ������������ �������� TC1
	sei();					//���������� ���������� ����������
	while (1)				//����������� ����
	{
	}
}

