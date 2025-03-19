.def tmp = r16
start:
    ldi tmp, 0x40
	out DDRD, tmp
	ldi tmp, 0x83
	out TCCR0A, tmp
	ldi tmp, 0x0A
	out OCR0A, tmp
	ldi tmp, 0x05
	out TCCR0B, tmp
p:
	jmp p
