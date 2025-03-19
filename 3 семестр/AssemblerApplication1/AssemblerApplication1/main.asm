start:
;Example 1
.include "m328pdef.inc";1
	ldi r16, 0x08 ;2
	out sph, r16 ;3
	ldi r16, 0xff ;4
	out spl, r16 ;5
m: 
	call pp1 ;6
	call pp2 ;7
	call pp3 ;8
	jmp m ;9
pp1: 
	ldi r16, 10 ;10
	ldi r17, 0x10 ;11
	ldi r18, 0x20 ;12
	ldi r19, 0x30 ;13
	mov r1, r16 ;14
	mov r2, r17 ;15
	mov r3, r18 ;16
	mov r4, r18 ;17
	in r4, portd ;18
	ldi xh, 0x01 ;19
	ldi xl, 0 ;20
	st x+, r1 ;21
	st x+, r2 ;22
	st x+, r3 ;23
	st x+, r4 ;24
	ld r10, -x ;25
	sts 0x0110, r16;26
	lds r5, 0x0100 ;27
	push r1 ;28
	push r2 ;29
	push r3 ;30
	push r4 ;31
	pop r14 ;32
	pop r13 ;33
	pop r12 ;34
	pop r11 ;35
	ret ;36
pp2: ;37
	ldi r16, 0x1E ;38
	ldi r17, 0xD2 ;39
	ldi r18, 0xDD ;40
	ldi xl, 0xC2
	ldi xh, 0x01
	sts 0x0100, r16 ;42
	sts 0x0101, r17 ;43
	sts 0x0102, r18	;44
	sts 0x0103, xl ;45
	sts 0x0104, xh 
	ret ;46
pp3: ;47
	push r16
	push r17
	push r18
	push r19
	pop	r7
	pop	r2
	pop	r3
	pop r5
	ret ;48