	.data
	.global R
R:	.space 4, 0

	.text
	.global calculate
calculate:
	push {r4, r5, r6, r7, r8}
	ldr r0, =A
	ldr r0, [r0]
	ldr r1, =B
	ldr r1, [r1]
	ldr r2, =C
	ldr r2, [r2]
	ldr r3, =D
	ldr r3, [r3]
	mul r5, r0, r1
	mul r6, r2, r3
	add r7, r5, r6
	ldr r8, =R
	str r7, [r8]
	pop {r4, r5, r6, r7, r8}
	bx lr
