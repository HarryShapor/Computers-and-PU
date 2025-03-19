start:
	ldi r16, 0x20
	out DDRB, r16
	ldi r16, 0x00
	out PORTB, r16

p:
	sbi PORTB, 5
	ldi r16, 0x01
	out DDRD, r16
	in r17, PINB
	bst r17, 0
	BRTS p2
	jmp p

p2:
	cbi PORTB, 5
	ldi r16, 0x02
	out DDRD, r16
	in r17, PINB
	bst r17, 1
	BRTS p
	jmp p2

