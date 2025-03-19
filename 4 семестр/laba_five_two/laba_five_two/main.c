#include <avr/io.h>		//���������� � ����������� ������� ������
#include <util/delay.h>	//���������� ��� ��������� ��������
#include <avr/interrupt.h>	//���������� ����������
#include <avr/eeprom.h>		//���������� ��� ������ � EEPROM
char x;					//��������������� ����������
int count;				//������� ������ eeprom
uint8_t mass[255];		//������ ��� �������� �� eeprom
ISR(USART0_RX_vect){	//����������� �� ����� ������ �� UART
	x = UDR0;			//������ �������� �� UART
	while(!(UCSR0A & (1 << UDRE0))); // ���� ���� ����� �������� �� ����� ������
		count++;					//���������� �������� ������ eeprom
		eeprom_write_byte((uint8_t *) count, (uint8_t) x);	//������ �������� � EEPROM[count]
		eeprom_write_byte((uint8_t *) 0, (uint8_t) count);	//������ count � EEPROM[0]
}
void uartic(){			//������� ������������� UART
	UBRR0 = 103;		//������� ���������, ����� ����� � ���������
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//������ ������ 8���
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);	//���������� �������� � ����� ������
}

int main(void){		//������� ���������, ����� ����� � ���������
	uartic();		//����� ������� ������������� UART
	sei();			//���������� ���������� ����������
	_delay_ms(150000);	//�������� 15 ������
	count = eeprom_read_byte((uint8_t*) 0); //������ �������� �� EEPROM[0]
	eeprom_read_block(mass, 0, count);		//������ ����� �� EEPROM
	for (int i=0; i < count; i++){			//������� �������� �������
		while(!(UCSR0A & (1 << UDRE0))); // �������� ���� ����� �������� �� ����� ������
			UDR0 = mass[i]; // �������� �������� �� UART
	}
	while (1)	//����������� ����
	{
	}}

