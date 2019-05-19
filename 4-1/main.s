.text
	.global classify

classify:
			push {r5, r6, r7}
			
			ldr 		r2, [r0]
			ldr 		r1, [r0, #4]
			
			//r7 маска для экспоненты
			mov		r7, #0x7F000000
			orr		r7, r7, #0x00F00000
			//r0 маска для первого куска матиссы
			mov		r0, #0x000FF000
			orr		r0, r0, #0x00000FF0
			orr		r0, r0, #0x0000000F
			
			//r3 - знак
			and		r3, r1, #0x80000000
			//r4 - экпонента
			and		r4, r1, r7
			//r5 - перый кусок матиссы
			and		r5, r1, r0
			//r6 - первый бит мантиссы
			and		r6, r1, #0x00080000
			cmp		r4, #0
			beq		zeroExp
			cmp		r4, r7
			beq		onesExp
			cmp		r3, #0
			beq		plusReg
			mov		r0, #0x11
			pop {r5,r6,r7}
          	        bx lr
			
plusReg:
			mov		r0, #0x10
			pop {r5, r6, r7}
			bx lr
			
zeroExp:
			cmp		r2, #0
			bne		denormal
			cmp		r5, #0
			bne		denormal
			cmp		r3, #0
			beq		plusZero
			mov		r0, #0x01
			pop {r5,r6,r7}
	                bx lr
			
plusZero:
			mov		r0, #0x00
			pop {r5,r6,r7}
			bx lr
			
denormal:
			cmp		r3, #0
			beq		plusDenormal
			mov		r0, #0x21
			pop {r5,r6,r7}
	                bx lr
			
plusDenormal:
			mov		r0, #0x20
			pop {r5,r6,r7}
			bx lr
			
onesExp:
			cmp		r2, #0
			bne		nan
			cmp		r5, #0
			bne		nan
			cmp		r3, #0
			beq		plusInf
			mov		r0, #0xF1
			pop {r5,r6,r7}
	                bx lr
			
plusInf:
			mov		r0, #0xF0
			pop {r5,r6,r7}
			bx lr
			
nan:
			cmp		r6, #0
			beq		sigNaN
			mov		r0, #0x31
			pop {r5,r6,r7}
			bx lr
			
sigNaN:
			mov		r0, #0x30
			pop {r5,r6,r7}
			bx lr
