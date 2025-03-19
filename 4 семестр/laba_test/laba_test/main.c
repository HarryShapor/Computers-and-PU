#include <avr/io.h>
#include <util/delay.h>
#define FREQ1 1000
#define FREQ2 2000
#define FREQ3 3000
#define INTERVAL 250 // интервал в миллисекундах
int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
    TCCR0A |= (1 << WGM01) | (1 << WGM00); // настройка Fast PWM режима
    TCCR0A |= (1 << COM0A0); // настройка для вывода на пин OC0A (pin 6 на Atmega328P)
    TCCR0B |= (1 << CS01); // настройка предделителя на 8

    OCR0A = 127; // устанавливаем значение ШИМ для генерации прямоугольного сигнала с длительностью 50%

    while (1)
    {
    // Генерация сигнала частоты 1КГц
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // Остановить таймер
    _delay_ms(INTERVAL);

    // Генерация сигнала частоты 2КГц
    TCCR0B |= (1 << CS01); // настройка предделителя на 8
    _delay_ms(INTERVAL);

    // Генерация сигнала частоты 3КГц
    TCCR0B |= (1 << CS02); // настройка предделителя на 64
    _delay_ms(INTERVAL);
    }

    return 0;
}

