; Example 4
	.include "m328pdef.inc";1
	ldi r16, 0x04 ;2
	out sph, r16 ;3
	ldi r16, 0x5f ;4
	out spl, r16 ;5

m: 
	;call pp1 ;6
	call pp2 ;7
	call pp3 ;8
	jmp m ;9
pp1: 
	ldi xl, 0x00 ;10
	ldi yl, 0x10; ;11
	ldi zl, 0x20; ;12
	ldi xh, 0x01 ;13
	ldi yh, 0x01 ;14
	ldi zh, 0x01 ;15
	ldi r17, 10 ;16
	ldi r18, 20 ;17
m1:
	st x+, r17 ;18
	st y+, r18 ;19
	mov r19, r17 ;20
	add r19, r18 ;21
	st z+, r19 ;22
	subi r17, -3 ;23
	subi r18, -5 ;24
	cpi xl, 0x10 ;25
	brne m1 ;26
	ret ;27
pp2:
	clr r20
	;ldi r20, 0xff ;счётчик цикла в 256 чисел
	ldi xh, 0x01 ;28
	clr xl ;29
	ldi r16, 1 ;30
	ldi r17, 0 ;31
m2:
	st x+, r16 ;32
	add r17, r16 ;33
	;brcs m3 ;34
	st x+, r17 ;35
	add r16, r17 ;36
	inc r20
	cpi r20, 0x7F
	breq m3 ;37
	rjmp m2 ;38
m3:
	ret

pp3: ;40
	clr xl
	clr r5
	clr r20
	call pp4
	ret
pp4:
	ldi xh, 0x01 ;28
	ld r16, x+
	cp r5, r16
	brlo m4
	inc r20
	cpi r20, 0xFF
	brsh m3 ;37
	jmp pp4
m4:
	mov r5, r16
	inc r20
	cpi r20, 0xFF
	brsh m3
	jmp pp4

	ret ;41