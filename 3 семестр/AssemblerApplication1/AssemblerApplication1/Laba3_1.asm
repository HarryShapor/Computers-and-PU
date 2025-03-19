start:
	clr r1
	ldi r16, 0xFF
	ldi r17, 0x00
	out DDRD,r16
p:
	out PORTD, r17
	inc r17
	inc r1
	cp r1, r16
	breq p2
	rjmp p

p2:
	out PORTD, r17
	dec r17 
	dec r1
	cp r1, r18
	breq p
	rjmp p2