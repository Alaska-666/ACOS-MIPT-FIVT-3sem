	.text
	.global main
main:
	push {lr}
	ldr r0, scanf_p
	sub sp, #8

	mov r1, sp
	mov r2, sp
	add r2, r2, #4
	bl scanf
	ldr r1, [sp]
	ldr r2, [sp, #4]
	add r1, r2, r1
	ldr r0, printf_p
	bl printf
	add sp, sp, #8
	pop {lr}
	bx lr
scanf_p:
	.word format_scanf
printf_p:
	.word format_printf

	.data
format_printf:
	.ascii "%d\0"
format_scanf:
	.ascii "%d%d\0"
