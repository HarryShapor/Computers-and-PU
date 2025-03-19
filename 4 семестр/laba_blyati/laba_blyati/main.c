#include <avr/io.h> //библиотека с логическими именами портов
#include <avr/interrupt.h>
uint16_t old; //глобальная переменная для хранения последнего значения захвата
ISR(TIMER1_CAPT_vect) //прерывание таймера 1 по захвату
{
	uint16_t temp = ICR1; //текущее значение захвата
	uint16_t delta = 0; //переменная для хранения разницы
	if (TCCR1B&(1 << ICES1) == 1)
	{
		TCCR1B |= (1 << WGM13) | (1 << WGM12) | (0 << ICES1) | (0 << CS12) | (1 << CS11) | (0 << CS10);
	}
	if (TCCR1B&(1 << ICES1) == 0)
	{
		TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << ICES1) | (0 << CS12) | (1 << CS11) | (0 << CS10);
		if (temp>old) //если текущее больше предыдущего
			delta = temp - old; //разница новое - старое
		else //иначе (таймер успел переполниться)
			delta = 65535 - old + temp;//разница 65635 - старое + новое
		if ((UCSR0A&(1<<UDRE0))!=0) //если UART не занят
			UDR0=delta; //отправка по UART
		old = temp; //сохранение нового значения
	}
};
ISR(TIMER0_COMPA_vect)
{
	PORTD ^= (1 << PORTD5);
}

// void timer0()		//функция для инициализации таймера 0
// {
// 	DDRD = 0x70;	//инициализация PORTD6 на вывод
// 	TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
// 	//Настройка TC0 в режиме ШИМ на выводе OC0A (не инверсный режим)
// 	TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00); //запуск таймера с частотой Fclk/8
// 	TIMSK0 |= (1 << OCIE0A);
// 	OCR0A = 1;	//установка регистра сравнения A (50% заполнения)
// }

void timer0()
{
	TCCR0A = 0b00000010; // Set Timer0 to CTC mode
	TCCR0B = 0b00000010; // Set prescaler to 64
	OCR0A = (16000000 / 8) * 10 / 2000000 + 10; // Calculate compare value for 10us pulse
	TIMSK0 |= (1 << OCIE0A); // Enable compare match interrupt
}
void uartic()		//функция инициализации UART
{
	UBRR0 = 103;	//скорость 9600бит/c при частоте генератора 16МГц
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//размер пакета 8бит
	UCSR0B |= (1 << TXEN0);	//разрешение передачи данных
}

void timer1()
{
	TCCR1A |=  (0 << WGM10) | (0 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << ICES1) | (0 << CS12) | (1 << CS11) | (0 << CS10);
	TIMSK1 = (1 << ICIE1);
	
}
int main(void)		//главная процедура, точка входа в программу
{
	timer0();		//вызов функции инициализации таймера 0
	timer1();
	uartic();		//вызов функции инициализации UART
	sei();
	while (1)		//бесконечный цикл
	{
		if (UDRE0 != 0)	//проверка на готовность приёма данных
		{
			UDR0 = PORTB0;	//вывод текущего значения Timer0 по UART
		}
	}
}

