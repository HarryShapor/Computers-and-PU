#include <avr/io.h>		//библиотека с логическими именами портов
#include <util/delay.h>	//библиотека для временных задержек
#include <avr/interrupt.h>	//библиотека прерываний
char x;					//вспомогательная переменная
int count;				//счётчик адреса eeprom
	//массив для значений из eeprom
void EEPROM_write(unsigned int uiAddress, unsigned char ucData){
	/* ожидание завершения предыдущей операции */
	while(EECR & (1<<EEPE)); //не продолжать пока бит (EEPE==1)
	/* установка значений регистров адреса и данных */
	EEAR = uiAddress;
	EEDR = ucData;
	/* чтение значения EECR и подготовка констант */
	uint8_t EEMPEmask = EECR|(1<<EEMPE);
	uint8_t EEPEmask = EEMPEmask|(1<<EEPE);
	/* выключение системы прерываний */
	cli();
	/* установка 1 в EEMPE */
	EECR = EEMPEmask;
	/* запись значения в EEPROM */
	EECR = EEPEmask;
	/* включение системы прерываний */
	sei();
}
unsigned char EEPROM_read(unsigned int uiAddress){
	/* ожидание завершения предыдущей операции */
	while(EECR & (1<<EEPE));//не продолжать пока бит (EEPE==1)
	/* установка значений регистра адреса */
	EEAR = uiAddress;
	/* начало операции чтения */
	EECR |= (1<<EERE);
	/* Rвозврат значения */
	return EEDR;
}
ISR(USART0_RX_vect){			//прерываение по приёму данных по UART
	x = UDR0;					//Чтение значения по UART
	while(!(UCSR0A & (1 << UDRE0))); // Ждем пока буфер отправки не будет пустым
		count++;					//увеличение счётчика адреса eeprom
		EEPROM_write((uint8_t *) count, (uint8_t) x);	//запись значения в EEPROM[count]
		EEPROM_write((uint8_t *) 0, (uint8_t) count);	//запись count в EEPROM[0]
}
void uartic(){			//функция инициализации UART
	UBRR0 = 103;		//главная процедура, точка входа в программу
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//размер пакета 8бит
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);	//разрешение передачи и приёма данных
}
int main(void){		//главная процедура, точка входа в программу
	uartic();		//вызов функции инициализации UART
	sei();			//разрешение глобальных прерываний

	//_delay_ms(150000);		//задержка 15 секунд
	count = EEPROM_read((uint8_t*) 0); // Читаем значение из EEPROM[0]
	uint8_t mass[count];
	for (int i=0; i < count; i++){		//перебор значений блока
		mass[i] = EEPROM_read((uint8_t*) i); // Отправляем значение по UART
	}
	for (int i=0; i < count; i++){		//перебор значений массива
		while(!(UCSR0A & (1 << UDRE0))); // Ждем пока буфер отправки не будет пустым
		UDR0 = mass[i]; // Отправляем значение по UART
	}
	while (1)	//бесконечный цикл
	{
	}}