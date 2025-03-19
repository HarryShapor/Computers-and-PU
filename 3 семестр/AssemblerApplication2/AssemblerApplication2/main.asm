.org 0x0000
	jmp Reset
.org 0x002E
	jmp acomp

acomp:
	in r16, ACSR
	bst r16, 5
	BRTC ledon
	cbi PORTB, 5
	jmp intexit
ledon:
	sbi PORTB, 5
intexit:
	reti
Reset:
	ldi r16, 0x48
	out ACSR, r16
	ldi r16, 0x20
	out DDRB, r16
	sei
main:
	jmp main