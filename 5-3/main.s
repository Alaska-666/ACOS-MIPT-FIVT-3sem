	.text
	.global main
main:
	push {r4, r5, r6, lr}
	mov r0, #0
	mov r1, #51
	bl realloc
	mov r5, r0 //pointer on object
	mov r6, #0 //quantity elements
	mov r4, #51 //max size array
input:
	ldr r0, =stdin
	ldr r0, [r0]
	bl fgetc
	cmp r0, #-1 //end input
	beq word_flipping
	cmp r0, #32
	blo input
	strb r0, [r5, r6]
	add r6, r6, #1
	cmp r6, r4
	bcs increase_array
	b input
increase_array:
	mov r0, #2
	mul r1, r0, r4
	mov r0, r5
	mov r4, r1
	bl realloc
	mov r5, r0
	b input
word_flipping:
	cmp r6, #0
	beq return
	sub r6, r6, #1
	ldr r1, =stdout
	ldr r1, [r1]
	ldrb r0, [r5, r6]
	bl fputc
	b word_flipping
return:
	mov r0, r5
	bl free
	pop {r4, r5, r6, lr}
	bx lr
