	.intel_syntax noprefix
	.text
	.global dot_product
dot_product:
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
cycle:
	cmp eax, 4
	jb add_last
	sub eax, 4
	mov ebx, [ebp + 12]
	movups xmm0, [ebx + 4  * eax]
	mov ebx, [ebp + 16]
	movups xmm1, [ebx + 4 * eax]
	mulps xmm0, xmm1
	haddps xmm0, xmm0
	haddps xmm0, xmm0
	addss xmm2, xmm0
	jmp cycle
add_last:
	cmp eax, 0
	je exit
	sub eax, 1
	mov ebx, [ebp + 12]
	movss xmm0, [ebx + 4 * eax]
	mov ebx, [ebp + 16]
	movss xmm1, [ebx + 4 * eax]
	mulss xmm0, xmm1
	addss xmm2, xmm0
	jmp add_last
exit:
	sub esp, 4
	movss [esp], xmm2
	fld dword ptr [esp]
	add esp, 4
	pop ebp
	ret
