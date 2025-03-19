#include <avr/io.h>			//библиотеки ввода/вывода
#include <avr/interrupt.h>	//библиотека обработки прерываний
ISR (ADC_vect)			//прерывания ADC
{
	if (ADCL >= 0x00 &  ADCL <= 0x14) 	//значение от 0 до 20
	{
		PORTB = 0x00;			//выключение L
		PORTD = 0x03;			//выключение RX, TX
	}
	if (ADCL >= 0x15 &  ADCL <= 0x64)	//значение от 21 до 100
	{
		PORTB = 0x20;			//включение L
		PORTD = 0x03;			//выключение RX, TX
	}
	if (ADCL >= 0x65 &  ADCL <= 0xB4)	//значение от 101 до 180
	{
		PORTB = 0x20;			//включение L
		PORTD = 0x02;			//включение RX
	}
	if (ADCL >= 0xB5 & ADCL <= 0xFF)	//значение от 181 до 255
	{
		PORTB = 0x20;			//включение L
		PORTD = 0x00;			//включение RX, TX
	}
}
int main(void)
{
	ADMUX |= (1 << REFS0);			//Vопорного = Vпитания
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) |
	(1 << ADPS1) | (1 << ADPS0);
	//включение АЦП, включение преобразования, разрешение прерывания ADC и //CLK/128
	DDRB = 0x20;	//на выход PORTB5
	DDRD = 0xff;		//на выход весь PORTD
	sei();			//глобальное разрешение прерываний
	while (1)		//бесконечный цикл
	{
	}
}
