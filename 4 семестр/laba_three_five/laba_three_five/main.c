#include <avr/io.h> //библиотека с логическими именами портов
#include <avr/interrupt.h>
uint16_t old; //глобальная переменная для хранения последнего значения захвата
ISR(TIMER1_CAPT_vect) //прерывание таймера 1 по захвату
{
	uint16_t temp = ICR1; //текущее значение захвата
	uint16_t delta = 0; //переменная для хранения разницы
	if (PORTB0 == 1)
	{
		TCCR1B |= (1 << WGM12) | (0 << ICES1) | (0 << CS02) | (1 << CS01) | (0 << CS00);
		old = temp;
		TIMSK0 = (0 << OCIE0A) | (0 << OCIE0B);
	}
	if (PORTB0 == 0)
	{
		TCCR1B |= (1 << WGM12) | (1 << ICES1) | (0 << CS02) | (1 << CS01) | (0 << CS00);
		if (temp>old) //если текущее больше предыдущего
			delta = temp - old; //разница новое - старое
		else //иначе (таймер успел переполниться)
			delta = 65535 - old + temp; //разница 65635 - старое + новое
		if ((UCSR0A&(1<<UDRE0))!=0) //если UART не занят
			UDR0 = (343 * delta) / 2; //отправка по UART
			TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B);
		old = temp; //сохранение нового значения
	}
}
void timer1()		//функция для инициализации таймера 0
{
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (0 << COM1B0)| (0 << WGM10) | (0 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << ICES1) | (0 << CS02) | (1 << CS01) | (0 << CS00); //запуск таймера с частотой Fclk/256
	TIMSK1 |= (1 << OCIE0A) | (1 << OCIE0B) | (1 << ICIE1);
	OCR1A = 255;	//установка регистра сравнения A (50% заполнения)
	OCR1B = 234;
}
void uartic()		//функция инициализации UART
{
	UBRR0 = 103;	//скорость 9600бит/c при частоте генератора 16МГц
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//размер пакета 8бит
	UCSR0B |= (1 << TXEN0);	//разрешение передачи данных
}
ISR(TIMER1_COMPA_vect) {
	PORTB = (1 << PORTB1);
}
ISR(TIMER1_COMPB_vect) {
	PORTB = (0 << PORTB1);
}
int main(void)		//главная процедура, точка входа в программу
{
	DDRB = 0x02;
	DDRC = 0xFF;
	timer1();
	uartic();
	sei();
	while (1)		//бесконечный цикл
	{
		PORTC = PORTB;
	}
	
}