start:
	ldi r16, 0x20
	out DDRB, r16
p:
	subi r17,0xff
	adc r18, r20
	adc r19, r20
	bst r19,4
	BRTS yes
	BRTC not
	rjmp p
yes:
	sbi PORTB, 5
	rjmp p
not:
	cbi PORTB, 5
	rjmp p