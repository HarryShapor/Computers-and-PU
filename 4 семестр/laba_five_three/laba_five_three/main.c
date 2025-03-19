#include <avr/io.h>		//���������� � ����������� ������� ������
#include <util/delay.h>	//���������� ��� ��������� ��������
#include <avr/interrupt.h>	//���������� ����������
char x;					//��������������� ����������
int count;				//������� ������ eeprom
	//������ ��� �������� �� eeprom
void EEPROM_write(unsigned int uiAddress, unsigned char ucData){
	/* �������� ���������� ���������� �������� */
	while(EECR & (1<<EEPE)); //�� ���������� ���� ��� (EEPE==1)
	/* ��������� �������� ��������� ������ � ������ */
	EEAR = uiAddress;
	EEDR = ucData;
	/* ������ �������� EECR � ���������� �������� */
	uint8_t EEMPEmask = EECR|(1<<EEMPE);
	uint8_t EEPEmask = EEMPEmask|(1<<EEPE);
	/* ���������� ������� ���������� */
	cli();
	/* ��������� 1 � EEMPE */
	EECR = EEMPEmask;
	/* ������ �������� � EEPROM */
	EECR = EEPEmask;
	/* ��������� ������� ���������� */
	sei();
}
unsigned char EEPROM_read(unsigned int uiAddress){
	/* �������� ���������� ���������� �������� */
	while(EECR & (1<<EEPE));//�� ���������� ���� ��� (EEPE==1)
	/* ��������� �������� �������� ������ */
	EEAR = uiAddress;
	/* ������ �������� ������ */
	EECR |= (1<<EERE);
	/* R������� �������� */
	return EEDR;
}
ISR(USART0_RX_vect){			//����������� �� ����� ������ �� UART
	x = UDR0;					//������ �������� �� UART
	while(!(UCSR0A & (1 << UDRE0))); // ���� ���� ����� �������� �� ����� ������
		count++;					//���������� �������� ������ eeprom
		EEPROM_write((uint8_t *) count, (uint8_t) x);	//������ �������� � EEPROM[count]
		EEPROM_write((uint8_t *) 0, (uint8_t) count);	//������ count � EEPROM[0]
}
void uartic(){			//������� ������������� UART
	UBRR0 = 103;		//������� ���������, ����� ����� � ���������
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);//������ ������ 8���
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);	//���������� �������� � ����� ������
}
int main(void){		//������� ���������, ����� ����� � ���������
	uartic();		//����� ������� ������������� UART
	sei();			//���������� ���������� ����������

	//_delay_ms(150000);		//�������� 15 ������
	count = EEPROM_read((uint8_t*) 0); // ������ �������� �� EEPROM[0]
	uint8_t mass[count];
	for (int i=0; i < count; i++){		//������� �������� �����
		mass[i] = EEPROM_read((uint8_t*) i); // ���������� �������� �� UART
	}
	for (int i=0; i < count; i++){		//������� �������� �������
		while(!(UCSR0A & (1 << UDRE0))); // ���� ���� ����� �������� �� ����� ������
		UDR0 = mass[i]; // ���������� �������� �� UART
	}
	while (1)	//����������� ����
	{
	}}