	.include"m328Pdef.inc"
	.org 0
		jmp Reset
	.org 0x004
		jmp Int_1
	Reset:
		ldi r16, High(RAMEND)
		out sph, r16
		ldi r16, Low(RAMEND)
		out spl, r16
		ldi r16, 0x00
		sts EICRA, r16
		ldi r16, 0x02
		out EIMSK, r16
		cbi DDRD, 3
		sbi PORTD, 3
		ldi r16, 0xff
		out DDRC, r16
		sei
	main:
		inc r17
		out PORTC, r17
		jmp main
	Int_1:
		ldi r17, 0x00
		out PORTC, r17
		reti