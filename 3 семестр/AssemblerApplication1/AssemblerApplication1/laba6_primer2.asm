.include "m328Pdef.inc"
.equ CLK = 16000000
.equ BAUD = 9600 
.equ UBRR0_value = (CLK/(BAUD*16)) - 1
.org 0
	jmp Reset 
Reset:
;настройка UART
;установка частоты приёма/передачи
	ldi r16, High(UBRR0_value)
	sts UBRR0H, r16
	ldi r16, Low(UBRR0_value)
	sts UBRR0L, r16
	;разрешение передачи
	ldi r16, (1 << TXEN0)
	sts UCSR0B, r16
	;длина слова 8 бит
	ldi r16, (1 << UCSZ00) | (1 << UCSZ01)
	sts UCSR0C, r16
	;разрешение всех прерываний
	sei
main:
	;определение адреса сообщения в ПЗУ
	ldi zl, Low(Msg << 1)
	ldi zh, High(Msg << 1)
	;количество байт в сообщении
	ldi r18, 0x17
send: ;отправка сообщения
	lpm r16, z+
	sts UDR0, r16
	subi r18, 0x01
repeat:	;проверка окончания сообщения
	lds r17, UCSR0A
	bst r17, 5
	brtc repeat
	cpi r18, 0x00
	breq main
	jmp send
.cseg ;размещение сообщения в ПЗУ
Msg: .db "Atmega328P:ReadyToWork",'\n'