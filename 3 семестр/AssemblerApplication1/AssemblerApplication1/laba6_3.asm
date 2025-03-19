.equ CLK = 16000000
.equ BAUD = 9600 
.equ UBRR0_value = (CLK/(BAUD*16)) - 1
.org 0
	jmp Reset 
.org 0x0028
	jmp USART_TX
Reset:
;��������� UART
;��������� ������� �����/��������
	ldi r16, High(UBRR0_value)
	sts UBRR0H, r16
	ldi r16, Low(UBRR0_value)
	sts UBRR0L, r16
	;���������� ��������
	ldi r16, (1 << TXEN0) | (1 << TXCIE0) | (1 << UDRIE0)
	sts UCSR0B, r16
	;����� ����� 8 ���
	ldi r16, (1 << UCSZ00) | (1 << UCSZ01)
	sts UCSR0C, r16
	;���������� ���� ����������
	sei
main:
	;����������� ������ ��������� � ���
	ldi zl, Low(Msg << 1)
	ldi zh, High(Msg << 1)
	;���������� ���� � ���������
	ldi r18, 0x17
send: ;�������� ���������
	lpm r16, z+
	cpi r16, 0x4D
	breq p
	subi r18, 0x01
repeat:	;�������� ��������� ���������
	lds r17, UCSR0A
	bst r17, 5
	brtc repeat
	cpi r18, 0x00
	breq main
	jmp send

USART_TX:
	in r17, PORTB
	ldi r18, 0x20
	eor r17, r18
	reti

p:
	sts UDR0, r16
	jmp send
.cseg ;���������� ��������� � ���
Msg: .db "AtMega328P:ReadyToWork",'\n'