.equ CLK = 16000000
.equ BAUD = 9600
.equ UBRR0_value = CLK/(BAUD * 16) - 1
.org 0x0000
	jmp Reset
Reset:
	ldi r16, High(UBRR0_value)
	sts UBRR0H, r16
	ldi r16, Low(UBRR0_value)
	sts UBRR0L, r16
	ldi r16, (1 << TXEN0)
	sts UCSR0B, r16
	ldi r16, (1 << UCSZ00) | (1 << UCSZ01)
	sts UCSR0C, r16
	sei

main:
	ldi zl, Low(NorV << 1)
	ldi zh, High(NorV << 1)
	ldi r18, 0x07
send:
	lpm r16, z+
	sts UDR0, r16
	subi r18, 0x01
repeat:
	lds r17, UCSR0A
	bst r17, 5
	BRTC repeat
	cpi r18, 0x00
	breq main
	jmp send

.cseg 
LowV: .db "Low Voltage", '\n'
NorV: .db "Normal", '\n'