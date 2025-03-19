.org 0
	jmp Reset
.org 0x006
	jmp mPCINT0
.org 0x00A
	jmp mPCINT1

Reset:
	ldi r16, Low(RAMEND)
	out spl, r16
	ldi r16, High(RAMEND)
	out sph, r16
	ldi r16, 0x07
	sts PCICR, r16
	ldi r16, 0xff
	sts PCMSK0, r16
	sts PCMSK2, r16
	sei

main:
	inc r17
	jmp main

mPCINT0:
	in r20, PINB
	mov r22, r18
	eor r22, r20
	mov r18, r20
	reti

mPCINT1:
	in r21, PIND
	mov r23, r19
	eor r23, r21
	mov r19, r21
	reti