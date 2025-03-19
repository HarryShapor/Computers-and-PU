.def temp = r16
.def adcvL = r17
.def adcvH = r18
.equ CLK = 16000000
.equ BAUD = 9600
.equ UBRR0_value = (CLK(BAUD * 16)) - 1
.org 0
	jmp Reset
.org 0x002A
	jmp ADC_conv

Reset:
	ldi temp, (1 << REFS0) | (1 << ADLAR)
	sts ADMUX, temp
	ldi temp, (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)
	sts ADCSRA, temp
	ldi temp, high(UBRR0_value)
	sts UBRR0H, temp
	ldi temp, low(UBRR0_value)
	sts UBRR0L, temp
	ldi temp, (1 << TXEN0)
	sts UCSR0B, temp
	ldi temp, (1 << UCSZ00) | (1 << UCSZ01)
	sts UCSR0C, temp
	sei
main:
	jmp main

ADC_conv:
	lds adcvH, ADCH
repeat:
	lds r17, UCSR0A
	bst r17, 5
	brtc repeat
	sts UDR0, adcvH
	reti