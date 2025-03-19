.org 0
	jmp Reset
.org 0x002			;адрес прерывания INT0
	jmp Int_0		;переход к метке прерывания
.org 0x004			;адрес прерывания INT1
	jmp Int_1		;переход к метке прерывания
Reset:
	ldi r16, High(RAMEND)
	out sph, r16
	ldi r16, Low(RAMEND)
	out spl, r16
	ldi r16, 0x0F		;выполнение прерывания по фронту
	sts EICRA, r16
	ldi r16, 0x03				;разрешение прерывания INT0 и INT1
	out EIMSK, r16
	cbi DDRD, 3
	ldi r16, 0b00000011			;уставнока на выход RX и TX
	out DDRD, r16
	ldi r17, 0b00000100		;подтяжка вверх
	out PORTD, r17
	ldi r16, 0xff
	out DDRC, r16
	sei
main:
	out PORTD, r17
	inc r19
	out PORTC, r19
	jmp main
Int_0:
	in r17, PIND
	ldi r18, 0x01
	eor r17, r18
	reti
Int_1:
	in r17, PIND
	ldi r18, 0x02
	eor r17, r18
	reti