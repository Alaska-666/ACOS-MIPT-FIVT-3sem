	.intel_syntax noprefix
	.global my_sin
	.text
my_sin:
	push ebp
	mov ebp, esp
	movsd xmm0, [ebp+8]
	movsd xmm1, [ebp+8]
	subsd xmm1, xmm1
	movsd xmm2, [ebp+8]
	mulsd xmm2, xmm2
	mov eax, -1
	cvtsi2sd xmm3, eax
	mulsd xmm2, xmm3
	mov eax, 1
	subsd xmm4, xmm4
loop:
	comisd xmm0, xmm4
	jz exit
	addsd xmm1, xmm0
	mulsd xmm0, xmm2
	add eax, 1
	cvtsi2sd xmm3, eax
	divsd xmm0, xmm3
	add eax, 1
	cvtsi2sd xmm3, eax
	divsd xmm0, xmm3
	jmp loop
exit:
	movsd [ebp+8], xmm1
	fld qword ptr [ebp+8]
	pop ebp
	ret
