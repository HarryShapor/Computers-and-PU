#include <avr/io.h>
#include <util/delay.h>
#define FREQ1 1000
#define FREQ2 2000
#define FREQ3 3000
#define INTERVAL 250 // �������� � �������������
int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
    TCCR0A |= (1 << WGM01) | (1 << WGM00); // ��������� Fast PWM ������
    TCCR0A |= (1 << COM0A0); // ��������� ��� ������ �� ��� OC0A (pin 6 �� Atmega328P)
    TCCR0B |= (1 << CS01); // ��������� ������������ �� 8

    OCR0A = 127; // ������������� �������� ��� ��� ��������� �������������� ������� � ������������� 50%

    while (1)
    {
    // ��������� ������� ������� 1���
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // ���������� ������
    _delay_ms(INTERVAL);

    // ��������� ������� ������� 2���
    TCCR0B |= (1 << CS01); // ��������� ������������ �� 8
    _delay_ms(INTERVAL);

    // ��������� ������� ������� 3���
    TCCR0B |= (1 << CS02); // ��������� ������������ �� 64
    _delay_ms(INTERVAL);
    }

    return 0;
}

