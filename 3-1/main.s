        .text

        .global summ
summ:
        //int summ(int x0, int N, int *A)
        // r1          r0    r1     r2
        ldr r3, [r2]
        add r2, r2, #4
        add r0, r0, r3
        sub r1, r1, #1
        cmp r1, #0
        bgt summ
        mov r1, r0
        bx lr
