	.text
	.global check_int
check_int:
//проверка на ноль
	cmp r0, #0
	beq return
//выполняем сдвиг вправо, пока последняя цифра не 1
loop:
	mov r1, #1
	and r1, r0, r1
	cmp r1, #1
	beq check
	lsr r0, #1
	b loop
check:
	mov r1, #0x000000FF
	orr r1, r1, #0x0000FF00
	orr r1, r1, #0x00FF0000
//r1 самое большое число, которое можно запихнуть в мантиссу
	cmp r0, r1
	bls return
	mov r0, #0
	bx lr
return:
	mov r0, #1
	bx lr
