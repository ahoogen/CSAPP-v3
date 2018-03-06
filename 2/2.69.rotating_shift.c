#include <stdio.h>
/*
Write code for a function with the following prototype:

// Do Rotating left shift. Assume 0 <= n < w
// Examples when x = 0x12345678 and w = 32:
// n=4 --> 0x23456781, n=20 --> 0x67812345

unsigned rotate_left(unsigned x, int n);

Your function should follow the bit-level integer coding rules on page 165. Be
careful in the case where n = 0.
*/

unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(x)<<3;
    unsigned a = x << n;
    unsigned b = x >> (w - 1 - n) >> 1;

    return a | b;
}

/*
To perform the rotation you first left shift x by n bits. This will push the
most significant n bits off the left when assigned to variable a. To recover
these bits and put them into the correct position we need to shift x to the
right by w - n bits and assign to variable b.

However, as was pointed out in problem 2.67.is_int32.c, shifting an integer
by n bits where n >= width of the integer has undefined behavior in C. Therefore
we need to guarantee that we will never try to shift w - 0 bits. This can be
handled by decreasing w by 1, subtracting n, and then shifting once more by 1
to recover the correct bit position.

An example of how this works where n = 0:

a = 1100 1001 << 0
a = 1100 1001
b = 1100 1001 >> 7 - 0
b = 0000 0001 >> 1
b = 0000 0000
a | b = 1100 1001

An example of how this works where n = 4:

a = 1100 1001 << 4
a = 1001 0000;
b = 1100 1001 >> 7 - 4
b = 0001 1001 >> 1
b = 0000 1100
a | b = 1001 1100

An example of how this works where n = 14 and x = 0x12345678

a = 00010010001101000101011001111000 << 14
a =               00010101100111100000000000000000
b = 00010010001101000101011001111000 >> 17
b = 00000000000000000000100100011010 >> 1
b =               00000000000000000000010010001101
a | b =           00010101100111100000010010001101
a | b =         0x   1   5   9   E   0   4   8   D
*/

int main() {
    unsigned x = 0x12345678;
    int n = 4;
    printf("Should produce 0x23456781\n");
    printf("0x%08X rotated left %d bits is 0x%08X\n", x, n, rotate_left(x, n));
    n = 20;
    printf("Should produce 0x67812345\n");
    printf("0x%08X rotated left %d bits is 0x%08X\n", x, n, rotate_left(x, n));
    n = 0;
    printf("Should produce 0x12345678\n");
    printf("0x%08X rotated left %d bits is 0x%08X\n", x, n, rotate_left(x, n));
    n = 14;
    printf("Should produce 0x159E048D\n");
    printf("0x%08X rotated left %d bits is 0x%08X\n", x, n, rotate_left(x, n));
    return 0;
}
