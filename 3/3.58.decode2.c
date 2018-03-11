#include <stdio.h>

/*
For a function with prototype:

long decode2(long x, long y, long z);

GCC generates the following assembly code:

%rdi = x, %rsi = y, %rdx = z

decode2:
    subq    %rdx, %rdx
    imulq   %rsi, %rdi
    movq    %rsi, %rax
    salq    $63, %rax
    sarq    $63, %rax
    xorq    %rdi, %rax
    ret
*/

/*
Solution Explanation:

%rdi = x, %rsi = y, %rdx = z

decode2:    S     D
    subq    %rdx, %rsi      # y -= z
    imulq   %rsi, %rdi      # x *= y
    movq    %rsi, %rax      # Copy 8 bytes of y to return value register
    salq    $63, %rax       # y <<= 63
    sarq    $63, %rax       # y >>= 63
    xorq    %rdi, %rax      # y ^= x
    ret                     # return y

The basic operations are described above, which can be reduced to:
y -= z
x *= y
y << 63 >> 63
return y ^ x

With the movq placing the value of y (after manipulation) into register %rax we
get a picture that we've declared a variable as a return value, I'll call 'a'.

long a = y - z;

I *could* declare another variable for the manipulation of x, but since no other
registers are referenced I'm going to assume that the total operation proceeds
with declarations on hand, so that gives us:

return (a * x) ^ (y << 63 >> 63)
*/

long decode2(long x, long y, long z) {
    long a = y - z;
    return (a * x) ^ (a << 63 >> 63);
}
