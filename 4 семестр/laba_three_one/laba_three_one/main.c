#include <avr/io.h> //���������� � ����������� ������� ������ 
void timer0()		//������� ��� ������������� ������� 0
{
	DDRD = 0x40;	//������������� PORTD6 �� �����
	TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	//��������� TC0 � ������ ��� �� ������ OC0A (�� ��������� �����)
	TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);	//������ ������� � �������� Fclk/256
	OCR0A = 127;	//��������� �������� ��������� A (50% ����������)
}
int main(void)		//������� ���������, ����� ����� � ���������
{
	timer0();		//����� ������� ������������� ������� 0
    while (1)		//����������� ����
    {
    }
}

