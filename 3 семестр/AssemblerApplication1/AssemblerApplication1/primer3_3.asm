start:
	ldi r16, 0x20
	out DDRB, r16
	ldi r16, 0x01
	out PORTB, r16

p:
	in r17, PINB
	bst r17, 1
	BRTS yes
	BRTC not
	rjmp p

yes:
	sbi PORTB, 5
	rjmp p
not:
	cbi PORTB, 5
	rjmp p