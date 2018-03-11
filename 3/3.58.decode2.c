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
*/

long decode2(long x, long y, long z) {
    long a = y - z;
    return (a * x) ^ (a << 63 >> 63);
}
