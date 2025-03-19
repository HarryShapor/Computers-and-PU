;.include "m328Pdef.inc"
.equ CLK = 16000000 ;+
.equ BAUD = 9600	;+
.equ UBRR0_value = (CLK/(BAUD*16)) - 1	;+
.org 0		;+
	jmp Reset	;+
.org 0x0026		;+
	jmp USART_TX	;+
.org 0x0028		;+
	jmp USART_TX	;+
Reset:				;+
;настройка UART
;установка частоты приёма/передачи
	ldi r16, High(UBRR0_value)	;+
	sts UBRR0H, r16				;+
	ldi r16, Low(UBRR0_value)	;+
	sts UBRR0L, r16				;+
	;разрешение передачи
	ldi r16, (1 << TXEN0) | (1 << TXCIE0) | (1 << RXCIE0) | (1 << UDRIE0)	;+
	sts UCSR0B, r16											
	;длина слова 8 бит
	ldi r16, (1 << UCSZ00) | (1 << UCSZ01)
	sts UCSR0C, r16
	ldi r16, 0x20
	out DDRB, r16
	;разрешение всех прерываний
	sei
main:
	;определение адреса сообщения в ПЗУ
	ldi zl, Low(Msg << 1)
	ldi zh, High(Msg << 1)
	lpm r16, z+
	sts UDR0, r16
	lds r16, UCSR0A
	bst r16, 5
	brtc USART_T
send: ;отправка сообщения
	jmp main

USART_TX:
	lpm r16, z+
	sts UDR0, r16
	reti
USART_T:
	lpm r16, z+
	sts UDR0, r16
	jmp send
.cseg ;размещение сообщения в ПЗУ
Msg: .db "Atmega328P:ReadyToWork",'\n'