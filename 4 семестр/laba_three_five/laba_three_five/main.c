#include <avr/io.h> //���������� � ����������� ������� ������
#include <avr/interrupt.h>
uint16_t old; //���������� ���������� ��� �������� ���������� �������� �������
ISR(TIMER1_CAPT_vect) //���������� ������� 1 �� �������
{
	uint16_t temp = ICR1; //������� �������� �������
	uint16_t delta = 0; //���������� ��� �������� �������
	if (PORTB0 == 1)
	{
		TCCR1B |= (1 << WGM12) | (0 << ICES1) | (0 << CS02) | (1 << CS01) | (0 << CS00);
		old = temp;
		TIMSK0 = (0 << OCIE0A) | (0 << OCIE0B);
	}
	if (PORTB0 == 0)
	{
		TCCR1B |= (1 << WGM12) | (1 << ICES1) | (0 << CS02) | (1 << CS01) | (0 << CS00);
		if (temp>old) //���� ������� ������ �����������
			delta = temp - old; //������� ����� - ������
		else //����� (������ ����� �������������)
			delta = 65535 - old + temp; //������� 65635 - ������ + �����
		if ((UCSR0A&(1<<UDRE0))!=0) //���� UART �� �����
			UDR0 = (343 * delta) / 2; //�������� �� UART
			TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B);
		old = temp; //���������� ������ ��������
	}
}
void timer1()		//������� ��� ������������� ������� 0
{
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (0 << COM1B0)| (0 << WGM10) | (0 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << ICES1) | (0 << CS02) | (1 << CS01) | (0 << CS00); //������ ������� � �������� Fclk/256
	TIMSK1 |= (1 << OCIE0A) | (1 << OCIE0B) | (1 << ICIE1);
	OCR1A = 255;	//��������� �������� ��������� A (50% ����������)
	OCR1B = 234;
}
void uartic()		//������� ������������� UART
{
	UBRR0 = 103;	//�������� 9600���/c ��� ������� ���������� 16���
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//������ ������ 8���
	UCSR0B |= (1 << TXEN0);	//���������� �������� ������
}
ISR(TIMER1_COMPA_vect) {
	PORTB = (1 << PORTB1);
}
ISR(TIMER1_COMPB_vect) {
	PORTB = (0 << PORTB1);
}
int main(void)		//������� ���������, ����� ����� � ���������
{
	DDRB = 0x02;
	DDRC = 0xFF;
	timer1();
	uartic();
	sei();
	while (1)		//����������� ����
	{
		PORTC = PORTB;
	}
	
}