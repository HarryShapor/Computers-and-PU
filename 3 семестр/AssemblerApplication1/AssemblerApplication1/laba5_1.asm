.org 0
	jmp Reset
.org 0x002			;����� ���������� INT0
	jmp Int_0		;������� � ����� ����������
Reset:
	ldi r16, High(RAMEND)
	out sph, r16
	ldi r16, Low(RAMEND)
	out spl, r16
	ldi r16, 0x01	;���������� ���������� �� ������(0x03) ��� ������(0x01)
	sts EICRA, r16
	ldi r16, 0x01				;���������� ���������� INT0
	out EIMSK, r16
	cbi DDRD, 3
	ldi r16, 0b00000011			;��������� �� ����� RX � TX
	out DDRD, r16
	ldi r17, 0b00000101			;�������� �����
	out PORTD, r17
	ldi r16, 0xff
	out DDRC, r16
	sei
main:
	out PORTD, r17
	in r20, PIND
	bst r20, 2
	BRTS smena
	inc r19
	out PORTC, r19
	jmp main
Int_0:
	ldi r19, 0x00
	out PORTC, r19
	reti

smena:
	ldi r18, 0x03
	eor r17, r18
	jmp main