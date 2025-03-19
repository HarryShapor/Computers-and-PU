start:
; Example 2.1
.include "m328pdef.inc";1
	ldi r16, 0x04 ;2
	out sph, r16 ;3
	ldi r16, 0x5f ;4
	out spl, r16 ;5
m: 
	;call pp1 ;6
	;call pp2 ;7
	;call pp3 ;8
	;call pp4
	call pp5
	jmp m ;9
pp1: 
	ldi r16 , 73 ;10
	ldi r17 , 103 ;11
	ldi r18 , 138 ;12
	ldi r19 , 233 ;13
	add r16, r17 ;14
	add r17, r18 ;15
	add r18, r19 ;16
	ret ;17
	
pp2:
	ldi r16 , 73 ;18
	ldi r17 , 103 ;19
	mov r0, r16 ;20
	add r0, r17 ;21
	ror r0 ;22
	ret ;23

pp3: 
	ldi r16, 73 ;24
	ldi r17 , 103 ;25
	ldi r18 , 138 ;26
	ldi r19 , 233 ;27
	eor r1, r1 ;28
	eor r2, r2 ;29`
	mov r0, r16 ;30
	add r0, r17 ;31
	adc r1 ,r2 ;32
	add r0, r18 ;33
	adc r1 ,r2 ;34
	add r0, r19 ;35
	adc r1 ,r2 ;36
	ror r1 ;37
	ror r0 ;38
	ror r1 ;39
	ror r0 ;40
	ret ;41

pp4:
	ldi r16, 73 
	ldi r17, 103
	mul r16, r17
	ldi r18, 73 
	ldi r19, 138
	mul r18, r19
	ldi r20, 73 
	ldi r21, 233
	mul r20, r21
	ldi r22, 103 
	ldi r23, 138
	mul r22, r23
	ldi r24, 103
	ldi r25, 233
	mul r24,r25
	ldi r26, 138
	ldi r27, 233
	mul r26, r27
	ret 

pp5:
	ldi r16, 0x85
	ldi r17, 0xE2
	muls r16, r17
	ldi r18, 0xA0
	ldi r19, 0xB3
	muls r18, r19
	ldi r20, 0x3F
	ldi r21, 0x9D
	muls r20, r21
	ret