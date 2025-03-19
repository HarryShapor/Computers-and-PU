#include <avr/io.h> //���������� � ����������� ������� ������
#include <avr/interrupt.h>	//���������� ����������
uint16_t old; //���������� ���������� ��� �������� ���������� �������� �������
ISR(TIMER1_CAPT_vect) //���������� ������� 1 �� �������
{
	uint16_t temp = ICR1; //������� �������� �������
	uint16_t delta = 0; //���������� ��� �������� �������
	if (PORTB0 == 1)	//���� �� ����� ECHO 1
	{
		TCCR1B = (0 << ICES1) | (1 << CS12) | (0 << CS11) | (0 << CS10);
		//������ ������� � �������� Fclk/256 � ��������� ����� �������� �������
		old = temp;	//���������� �������� ������� � ���������� ����������
		TIMSK0 = (0 << OCIE0A) | (0 << OCIE0B); //������ ���������� �� ���������� � A � B
	}
	if (PORTB0 == 0)	//���� �� ����� ECHO 0
	{
		TCCR1B = (1 << ICES1) | (1 << CS12) | (0 << CS11) | (0 << CS10);
		//������ ������� � �������� Fclk/256 � ����������� ����� �������� �������
		if (temp>old) //���� ������� ������ �����������
			delta = temp - old; //������� ����� - ������
		else //����� (������ ����� �������������)
			delta = 65535 - old + temp; //������� 65635 - ������ + �����
		if ((UCSR0A&(1<<UDRE0))!=0) //���� UART �� �����
			UDR0 = (343 * delta) / 2; //�������� �� UART
			TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B); //���������� ���������� �� ���������� � A � B
		old = temp; //���������� ������ ��������
	}
}
void timer0()		//������� ��� ������������� ������� 0
{
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0) | (1 << COM0B1) | (1 << COM0B0)| (1 << WGM00) | (0 << WGM01);
	//��������� TC0 � ������ ���, ����� ������ OC0A ��� ���������� � A � ��������� � 1 OC0B ��� ���������� � B
	TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00); //������ ������� � �������� Fclk/8
	TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B);		//���������� ���������� �� ���������� � A � B
	OCR0A = 255;	//��������� �������� � ������� ��������� A
	OCR0B = 234;	//��������� �������� � ������� ��������� B
}
void uartic()		//������� ������������� UART
{
	UBRR0 = 103;	//�������� 9600���/c ��� ������� ���������� 16���
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//������ ������ 8���
	UCSR0B |= (1 << TXEN0);	//���������� �������� ������
}
ISR(TIMER0_COMPA_vect) {	//���������� ������� 0 �� ���������� � ��������� ��������� A
	PORTB = (1 << PORTB1);	//��������� �������� 1 � PORTB1
}
ISR(TIMER0_COMPB_vect) {	//���������� ������� 0 �� ���������� � ��������� ��������� B
	PORTB = (0 << PORTB1);	//��������� �������� 0 � PORTB1
}
int main(void)		//������� ���������, ����� ����� � ���������
{
	DDRB = 0x02;	//������������� �� ����� ����� PB1
	TCCR1B = (1 << ICES1) | (1 << CS12) | (0 << CS11) | (0 << CS10);
	//������ ������� � �������� Fclk/256 � ����������� ����� �������� �������
	TIMSK1 = (1 << ICIE1);	//���������� ���������� ������� �����
	timer0();		//������������� Timer0
	uartic();		//������������� UART
	sei();			//���������� ����������
	while (1)		//����������� ����
	{
	}
	
}