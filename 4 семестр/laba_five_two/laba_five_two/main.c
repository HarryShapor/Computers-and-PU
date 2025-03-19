#include <avr/io.h>		//библиотека с логическими именами портов
#include <util/delay.h>	//библиотека для временных задержек
#include <avr/interrupt.h>	//библиотека прерываний
#include <avr/eeprom.h>		//библиотека для работы с EEPROM
char x;					//вспомогательная переменная
int count;				//счётчик адреса eeprom
uint8_t mass[255];		//массив для значений из eeprom
ISR(USART0_RX_vect){	//прерываение по приёму данных по UART
	x = UDR0;			//Чтение значения по UART
	while(!(UCSR0A & (1 << UDRE0))); // Ждем пока буфер отправки не будет пустым
		count++;					//увеличение счётчика адреса eeprom
		eeprom_write_byte((uint8_t *) count, (uint8_t) x);	//запись значения в EEPROM[count]
		eeprom_write_byte((uint8_t *) 0, (uint8_t) count);	//запись count в EEPROM[0]
}
void uartic(){			//функция инициализации UART
	UBRR0 = 103;		//главная процедура, точка входа в программу
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//размер пакета 8бит
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);	//разрешение передачи и приёма данных
}

int main(void){		//главная процедура, точка входа в программу
	uartic();		//вызов функции инициализации UART
	sei();			//разрешение глобальных прерываний
	_delay_ms(150000);	//задержка 15 секунд
	count = eeprom_read_byte((uint8_t*) 0); //Чтение значение из EEPROM[0]
	eeprom_read_block(mass, 0, count);		//Чтение блока из EEPROM
	for (int i=0; i < count; i++){			//перебор значений массива
		while(!(UCSR0A & (1 << UDRE0))); // Ожидание пока буфер отправки не будет пустым
			UDR0 = mass[i]; // Отправка значения по UART
	}
	while (1)	//бесконечный цикл
	{
	}}

