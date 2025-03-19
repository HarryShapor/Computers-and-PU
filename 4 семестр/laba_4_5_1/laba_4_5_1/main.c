#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char OVF_counter, zamer_1, zamer_T, zamer_t, duty;
unsigned long t, T, f;
unsigned int rising_1, rising_2, falling;

uint16_t old; //глобальная переменная для хранения последнего значения захвата
ISR(TIMER1_OVF_vect)
{
	OVF_counter++; // Увеличиваем счетчик переполнений
}
ISR(TIMER1_CAPT_vect) //прерывание таймера 1 по захвату
{
// 	if (UDRE0 != 0)
// 	{
// 		UDR0 = TCNT1/100;
// 		TCNT1 = 0;
// 	}
	switch(zamer_1)
  {
    case 0: // Вычисляем период импульса
      switch(zamer_T)  
      {
      case 0:
      rising_1 = ICR1; // Запоминаем значение счётчика
      OVF_counter = 0; // Обнуляем количество переполнений счётчика
      zamer_T = 1; // Переходим к следующему вычислению
      break;
   
      case 1: 
      rising_2 = ICR1; // Запоминаем значение счётчика
		// Приводим все переменные к одному типу и вычисляем период импульса
      T = (unsigned long)rising_2 - (unsigned long)rising_1 + ((unsigned long)OVF_counter * 65536);
      zamer_T = 0;
      zamer_1 = 1; // Переходим к следующему вычислению
      break;
      }
	break;
	  case 1:                   
	  f = (16000000/1)/T; // Вычисляем частоту сигнала в Гц
	  zamer_1 = 0; // Переходим к следующему вычислению
	  if (UDRE0 != 0)
		{
			UDR0 = f/1000;
		}
	  break;
  }
};
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
	TCCR1B |= (1 << ICES1) | (0 << CS12) | (0 << CS11) | (1 << CS10);
	TIMSK1 |= (1 << TOIE1) |(1 << ICIE1);	//разрешение прерывания захвата входа

}
int main(void)
{
	//DDRB = 0x01;
	timer0();
	uartic();
	adc();
	timer1();
	sei();
	while (1)
	{
// 		if (UDRE0 != 0)
// 		{
// 			UDR0 = f;
// 		}
	}
}

