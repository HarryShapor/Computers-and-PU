#include <avr/io.h> //библиотека с логическими именами портов
#include <avr/interrupt.h>
void timer0()		//функци€ дл€ инициализации таймера 0
{
	DDRD = 0x60;	//инициализаци€ PORTD6 на вывод
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0) | (1 << COM0B1) | (0 << COM0B0) | (1 << WGM00) | (1 << WGM01);
	TCCR0B |= (1 << WGM02) | (0 << CS02) | (1 << CS01) | (1 << CS00);
	OCR0A = 100;
	OCR0B = 5;
}
void uartic()		//функци€ инициализации UART
{
	UBRR0 = 103;	//скорость 9600бит/c при частоте генератора 16ћ√ц
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//размер пакета 8бит
	UCSR0B |= (1 << TXEN0);	//разрешение передачи данных
}
void adc(){
	DDRC = 0x01;
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	ADCSRA |= (1 << ADATE) | (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
}
void timer1(){
	TCCR1A |= (1 << );
	TCCR1B |= (1 << );
	
}
int main(void)		//главна€ процедура, точка входа в программу
{
	timer0();		//вызов функции инициализации таймера 0
	uartic();		//вызов функции инициализации UART
	adc();
	sei();
	while (1)		//бесконечный цикл
	{
		OCR0A = ADCH;
		ADCSRA |= 1<< ADSC;
		if (UDRE0 != 0)	//проверка на готовность приЄма данных
		{
			UDR0 = ADCH;	//вывод текущего значени€ Timer0 по UART
		}
	}
}

