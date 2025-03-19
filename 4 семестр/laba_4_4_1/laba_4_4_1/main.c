#include <avr/io.h>
#include <avr/interrupt.h>
ISR(ADC_vect){
	OCR0A = ADCH;
}
void timer0()
{
	DDRD = 0x40;
	TCCR0A |= (0 << COM0A1) | (1 << COM0A0) | (0 << COM0B1) | (0 << COM0B0) | (1 << WGM00) | (1 << WGM01);
	TCCR0B |= (1 << WGM02) | (0 << CS02) | (1 << CS01) | (1 << CS00);
	OCR0A = 0;
}
void uartic()
{
	UBRR0 = 103;
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B |= (1 << TXEN0);
}
void adc(){
	ADMUX = (0<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	//вкл. ацп, реж. непрерывн. преобр., разр. прерывания, частота преобр. = FCPU/128
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
void timer1(){
	TCCR1A |= 
	TCCR1B |= 
	TIMSK1 |= 
}
void timer2(){
	TCCR2B |= (1 << CS21) | (1 << CS20);
	TIMSK2 = (1 << TOIE2);
}
int main(void)
{
	timer0();
	uartic();
	adc();
	timer1();
	timer2();
	sei();
	while (1)
	{
		if (UDRE0 != 0)
		{
			UDR0 = TCNT1;
		}
		
	}
}

