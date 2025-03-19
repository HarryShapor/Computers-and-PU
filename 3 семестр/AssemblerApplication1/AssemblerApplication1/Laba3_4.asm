start:
	ldi r16, 0x20
	out DDRB, r16
	ldi r16, 0xFF
	out DDRD, r16
	ldi r16, 0x03
	out PORTB, r16

p:
	out PORTD, r1
	in r17, PINB
	bst r17, 0
	BRTS plus
	bst r17, 1
	BRTS minus
	rjmp p

minus:
	dec r0
	out PORTD, r0
	rjmp p
plus:
	inc r0
	out PORTD, r0
	rjmp p