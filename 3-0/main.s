         .text

         .global f

         //int f (int a, int b, int c, int x)
f:       // r1     r0      r1     r2     r3
         mul r0, r0, r3

         mul r0, r0, r3

         mul r1, r1, r3

         add r0, r0, r1

         add r0, r0, r2

         mov r1, r0

         bx lr
