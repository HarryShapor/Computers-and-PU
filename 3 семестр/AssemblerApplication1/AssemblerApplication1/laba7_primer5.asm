.def temp = r16								;���������� ����������� ����� temp ��� �������� r16
.def adcvL = r17							;���������� ����������� ����� adcvL ��� �������� r17
.def adcvH = r18							;���������� ����������� ����� adcvH ��� �������� r18
.equ CLK = 16000000							;�������� ������� ����������
.equ BAUD = 9600							;�������� �������� ������ UART
.equ UBRR0_value = (CLK / (BAUD * 16)) - 1	;���������� ��������� ��� UBRR
.org 0										;������ ���������� reset
	jmp Reset								;������� � ����� reset
.org 0x002A									;������ ���������� ���
	jmp ADC_conv							;������� � ����� ADC_conv
Reset:										;����� ����� � ���������
	ldi temp, (1 << REFS0) | (1 << ADLAR)	;V������� = V�������, ������������ ����������
	;�������������� �� ������� ����� ������� 8��� ����� �������� ADCH, ����� ADC0
	sts ADMUX, temp							;������ �������� � ADMUX
	ldi temp, (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)
	;��������� ���, ����������� ��������������, ���������� ����������, ������� - CLK/128
	sts ADCSRA, temp						;������ �������� � ADCSRA				
	ldi temp, high(UBRR0_value)				;������� ����� ��������� ��� UBBR � temp
	sts UBRR0H, temp						;�������� �������� � UBRR0H
	ldi temp, low(UBRR0_value)				;������� ����� ��������� ��� UBBR � temp
	sts UBRR0L, temp						;�������� �������� � UBRR0
	ldi temp, (1 << TXEN0)					;���������� �������� UART 
	sts UCSR0B, temp						;������ �������� � UCSR0B
	ldi temp, (1 << UCSZ00) | (1 << UCSZ01)	;������ ������ ������
	sts UCSR0C, temp						;������ �������� � UCSR0�
	sei										;���������� ���������� ����������
main:										
	jmp main
ADC_conv:
	lds adcvH, ADCH							;������ �������� �������� ADCH � ������� r18
repeat:										;����� repeat ������������ ���� �������� ���������� UART � ��������
	lds adcvL, UCSR0A						;������ ���������� ��������
	bst adcvL, 5							;������ 5 ���� (UDRE) �������� UCSR0A � ��� t �������� SREG
	brtc repeat								;���� t=0 � ������� � ����� repeat
	sts UDR0, adcvH							;�������� ������� 8��� ��� �� UART
	reti									;������� �� ����������