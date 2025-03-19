start:
	.include "m328pdef.inc";1
	ldi r16, 0x04 ;2
	out sph, r16 ;3
	ldi r16, 0x5f ;4
	out spl, r16 ;5
m: 
	;call pp1 ;6
	;call pp2 ;7
	call pp3 ;8
	jmp m ;9
pp1: 
	ldi r16, 0x0f ;10
	ldi r17 , 0x45 ;11
	ldi r18 , 0x67 ;12
	ldi r19 , 0x89 ;13
	ldi r20 , 0x18 ;14
	and r17, r16 ;15
	andi r17,0b00000010;16
	or r18, r16 ;17
	tst r16 ;18
	eor r19, r16 ;19
	eor r19, r19 ;20
	mov r17, r20 ;21
	and r17, r16 ;22
	swap r16 ;23
	and r18, r16 ;24
	or r17, r18 ;25
	bst r16, 7 ;26
	bld r20, 2 ;27
	sei ;28
	cli ;29
	ret ;30
pp2: ;31
	ldi r24, 0b10010000 ;34
	ldi r25, 0xA5 ;32
	mov r5, r25 ;33
	com r5
	and r5, r24 ;35
	ldi r25, 0x3B ;32
	mov r5, r25 ;33
	com r5
	and r5, r24 ;35
	ldi r25, 0xC8 ;32
	mov r5, r25 ;33
	com r5
	and r5, r24 ;35
	ret ;35
pp3: ;33
	ldi r31, 0b11100010 
	lsl r31
	lsl r31
	lsr r31
	asr r31
	rol r31
	ror r31
	ror r31
	ror r31
	ror r31
	ret ;34