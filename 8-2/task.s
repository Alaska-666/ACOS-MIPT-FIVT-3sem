#include <asm/unistd_32.h>

    .intel_syntax noprefix
    .text
    .global _start

_start:
	mov eax, __NR_brk
	mov ebx, 0
	int 0x80
	mov edi, eax
	push eax
	mov esi, 0
read_line:
	cmp esi, 0
        jle read
        mov eax, __NR_read
        mov ebx, 0
        mov ecx, edi
        mov edx, esi
        int 0x80
        cmp eax, 0
        jz write_add_endline
        sub esi, eax
        add edi, eax
read:
	mov esi, 1024
	add edi, esi
	mov eax, __NR_brk
	mov ebx, edi
	int 0x80
	sub edi, esi
	jmp read_line
write_add_endline:
	mov ah, 0x0A
	mov [edi], ah
write:
	mov esi, edi
loop:
	cmp [esp], edi
	jz write_last_line
	dec edi
	mov ah, 0x0A
	cmp ah, [edi]
	jz write_line
	jmp loop
write_line:
	mov eax, __NR_write
	mov ebx, 1
	mov ecx, edi
	add ecx, 1
	mov edx, esi
	sub edx, edi
	int 0x80
	jmp write
write_last_line:
	mov eax, __NR_write
	mov ebx, 1
	mov ecx, edi
	mov edx, esi
	sub edx, edi
	add edx, 1
	int 0x80
	pop eax
	mov eax, __NR_exit
	mov ebx, 0
	int 0x80
