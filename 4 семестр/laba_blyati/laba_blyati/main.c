#include <avr/io.h> //���������� � ����������� ������� ������
#include <avr/interrupt.h>
uint16_t old; //���������� ���������� ��� �������� ���������� �������� �������
ISR(TIMER1_CAPT_vect) //���������� ������� 1 �� �������
{
	uint16_t temp = ICR1; //������� �������� �������
	uint16_t delta = 0; //���������� ��� �������� �������
	if (TCCR1B&(1 << ICES1) == 1)
	{
		TCCR1B |= (1 << WGM13) | (1 << WGM12) | (0 << ICES1) | (0 << CS12) | (1 << CS11) | (0 << CS10);
	}
	if (TCCR1B&(1 << ICES1) == 0)
	{
		TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << ICES1) | (0 << CS12) | (1 << CS11) | (0 << CS10);
		if (temp>old) //���� ������� ������ �����������
			delta = temp - old; //������� ����� - ������
		else //����� (������ ����� �������������)
			delta = 65535 - old + temp;//������� 65635 - ������ + �����
		if ((UCSR0A&(1<<UDRE0))!=0) //���� UART �� �����
			UDR0=delta; //�������� �� UART
		old = temp; //���������� ������ ��������
	}
};
ISR(TIMER0_COMPA_vect)
{
	PORTD ^= (1 << PORTD5);
}

// void timer0()		//������� ��� ������������� ������� 0
// {
// 	DDRD = 0x70;	//������������� PORTD6 �� �����
// 	TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
// 	//��������� TC0 � ������ ��� �� ������ OC0A (�� ��������� �����)
// 	TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00); //������ ������� � �������� Fclk/8
// 	TIMSK0 |= (1 << OCIE0A);
// 	OCR0A = 1;	//��������� �������� ��������� A (50% ����������)
// }

void timer0()
{
	TCCR0A = 0b00000010; // Set Timer0 to CTC mode
	TCCR0B = 0b00000010; // Set prescaler to 64
	OCR0A = (16000000 / 8) * 10 / 2000000 + 10; // Calculate compare value for 10us pulse
	TIMSK0 |= (1 << OCIE0A); // Enable compare match interrupt
}
void uartic()		//������� ������������� UART
{
	UBRR0 = 103;	//�������� 9600���/c ��� ������� ���������� 16���
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//������ ������ 8���
	UCSR0B |= (1 << TXEN0);	//���������� �������� ������
}

void timer1()
{
	TCCR1A |=  (0 << WGM10) | (0 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << ICES1) | (0 << CS12) | (1 << CS11) | (0 << CS10);
	TIMSK1 = (1 << ICIE1);
	
}
int main(void)		//������� ���������, ����� ����� � ���������
{
	timer0();		//����� ������� ������������� ������� 0
	timer1();
	uartic();		//����� ������� ������������� UART
	sei();
	while (1)		//����������� ����
	{
		if (UDRE0 != 0)	//�������� �� ���������� ����� ������
		{
			UDR0 = PORTB0;	//����� �������� �������� Timer0 �� UART
		}
	}
}

