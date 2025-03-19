start:
	clr r1
	ldi r16, 0xFF
	ldi r17, 0x80
	out DDRD,r16
p:
	mov r18, r17
	andi r18, 0xC0
	out PORTD, r18
	inc r17
	inc r1
	cp r1, r16
	breq p2
	rjmp p

p2:
	mov r18, r17
	andi r18, 0xC0
	out PORTD, r18
	dec r17 
	dec r1
	cp r1, r18
	breq p
	rjmp p2