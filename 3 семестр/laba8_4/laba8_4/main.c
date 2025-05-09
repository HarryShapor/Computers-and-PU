#include <avr/io.h>			//���������� � ����������� ������� ������ �����/������
#include <avr/interrupt.h>	//���������� ������ � ������������
char flag_2 = 0x00;			//���� �������� ��� ���������� TIMER2 COMPA
char flag_0 = 0x00;			//���� �������� ��� ���������� TIMER0 COMPA
ISR (TIMER0_OVF_vect)		//���������� ���������� �� ������� ������������ Timer0
{
	flag_0 += 0x01;			//����������������� ���������� flag_0
}
ISR (TIMER1_COMPA_vect)		//���������� ���������� �� ������� ���������� Timer1 c A
{
	PORTB ^= 0x20;			//����� ��������� L �� ���������������
}
ISR (TIMER0_COMPA_vect)		//���������� ���������� �� ������� ���������� Timer0 c A
{	
	if (flag_0 == 0x5C)		//��������� �������� flag_0 � ���������� 0x5C
	{
		PORTD ^= 0x01;		//����� ��������� RX �� ���������������
		flag_0 = 0x00;		//��������� flag_0
	}
}
ISR (TIMER2_OVF_vect)		//���������� ���������� �� ������� ������������ Timer2
{
	flag_2 += 0x01;			//����������������� ���������� flag_2
}
ISR (TIMER2_COMPA_vect)		//���������� ���������� �� ������� ���������� Timer2 c A
{
	if (flag_2 == 0x25)		//��������� �������� flag_2 � ���������� 0x25
	{
		PORTD ^= 0x02;		//����� ��������� TX �� ���������������
		flag_2 = 0x00;		//��������� flag_2
	}
}
int main(void)				//������� ���������, ����� ����� � ���������
{
	DDRB = 0x20;			//��������� PORTB5 �� ����� ����������
	DDRD = 0x03;			//��������� PORTD �� ����� ����������
	TCCR1A = (1 << COM1A0) | (1 << COM1A1);			//��������� ������ OC0A � 1 ��� ���������� � A
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);	//����� ����� ��������� (OCR1A) (����� ��� ����������), ������������ clk/1024
	TIMSK1 = (1 << OCIE1A);		//���������� ���������� TIMER1 COMPA
	OCR1AH = 0x7A;			//������� ����� �������� A Timer1
	OCR1AL = 0x12;			//������� ����� �������� A Timer1
	TCCR0A = (1 << COM0A0) | (1 << COM0A1) | (1 << WGM01);	//����� ���, ��������� ������ OC0A � 1 ��� ���������� � A
	TCCR0B = (1 << CS00) | (1 << CS02);	//������ �������, ������������ clk/1024
	TIMSK0 = (1 << OCIE0A) | (1 << TOIE0);	//���������� ���������� TIMER0 COMPA � �� ������������ ��������
	OCR0A = 0xFF;			//�������� A Timer0
	TCCR2A = (1 << COM2A0) | (1 << COM2A1) | (1 << WGM21);	//����� ���, ��������� ������ OC0A � 1 ��� ���������� � A
	TCCR2B = (1 << CS20) | (1 << CS21) | (1 << CS22);	//������ �������, ������������ clk/1024
	TIMSK2 = (1 << OCIE2A) | (1 << TOIE0); //���������� ���������� TIMER2 COMPA � �� ������������ ��������
	OCR2A = 0xFF;			//�������� A Timer2
	sei();					//���������� ���������� ����������
	while (1)				//����������� ����
	{
	}
}

