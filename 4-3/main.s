	.text
	.global sort_by_age
sort_by_age:
	push {r4, r5, r6, r7, r8}
	cmp r0, #1
	bls return 
	mov r2, r1 //pointer
	mov r3, #1 //number of current array element
	mov r4, #0 //number of current walk throught
loop: 
	ldrb r5, [r2, #4]
	ldrb r6, [r2, #52]
	cmp r5, r6
	bls continue
swap:
	ldr r7, [r2]
	ldr r8, [r2, #48]
	str r8, [r2]
	str r7, [r2, #48]

	ldr r7, [r2, #4]
	ldr r8, [r2, #52]
	str r8, [r2, #4]
	str r7, [r2, #52]

	ldr r7, [r2, #8]
	ldr r8, [r2, #56]
	str r8, [r2, #8]
	str r7, [r2, #56]

	ldr r7, [r2, #12]
	ldr r8, [r2, #60]
	str r8, [r2, #12]
	str r7, [r2, #60]

	ldr r7, [r2, #16]
	ldr r8, [r2, #64]
	str r8, [r2, #16]
	str r7, [r2, #64]

	ldr r7, [r2, #20]
	ldr r8, [r2, #68]
	str r8, [r2, #20]
	str r7, [r2, #68]

	ldr r7, [r2, #24]
	ldr r8, [r2, #72]
	str r8, [r2, #24]
	str r7, [r2, #72]

	ldr r7, [r2, #28]
	ldr r8, [r2, #76]
	str r8, [r2, #28]
	str r7, [r2, #76]

	ldr r7, [r2, #32]
	ldr r8, [r2, #80]
	str r8, [r2, #32]
	str r7, [r2, #80]

	ldr r7, [r2, #36]
	ldr r8, [r2, #84]
	str r8, [r2, #36]
	str r7, [r2, #84]

	ldr r7, [r2, #40]
	ldr r8, [r2, #88]
	str r8, [r2, #40]
	str r7, [r2, #88]

	ldr r7, [r2, #44]
	ldr r8, [r2, #92]
	str r8, [r2, #44]
	str r7, [r2, #92]
continue:
	add r3, r3, #1
	cmp r0, r3
	bls current_test
	add r2, r2, #48
	b loop
current_test:
	mov r3, #1
	add r4, #1
	mov r2, r1
	cmp r0, r4
	bls return 
	b loop
return:
	pop {r4, r5, r6, r7, r8}
	bx lr
