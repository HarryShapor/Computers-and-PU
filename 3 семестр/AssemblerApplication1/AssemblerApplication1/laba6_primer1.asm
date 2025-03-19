.org 0
	jmp Reset
.org 0x002
	jmp knopka
Reset:
	ldi r16, 0x03
	sts EICRA, r16
	ldi r16, 0x01
	out EIMSK, r16
	cbi ddrd, 2
	sbi portd, 2
.equ CLK = 16000000
.equ BAUD = 9600
.equ UBRR0_value = (CLK/(BAUD*16)) - 1
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
	jmp main
knopka:
	ldi r16, 0x3E
	sts UDR0, r16
	reti