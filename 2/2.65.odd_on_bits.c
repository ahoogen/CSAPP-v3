/*
Write code to implement the following functions:

Return 1 when x contains an odd number of 1s; 0 otherwise.
Assume w=32

int odd_ones(unsigned x);

Your function should follow the bit level integer coding rules on page 165,
except that you may assume that data type int has w = 32 bits.
Your code should contain a total of at most 12 arithmetic, bitwise and logical
operations.
*/
#include <stdio.h>

int odd_ones(unsigned x) {
    x = (x >> 16) ^ (x & 0x0000FFFF);
    x = (x >> 8) ^ (x & 0x00FF);
    x = (x >> 4) ^ (x & 0x0F);
    x = (x >> 2) ^ (x & 0x3);
    return x;
}

int main() {
    unsigned x = 0x82AC3DF7;
    printf("0x%08X has odd number of bits? %d\n", x, odd_ones(x));
    x = 0x92AC3DF7;
    printf("0x%08X has odd number of bits? %d\n", x, odd_ones(x));
    return 0;
}

/*
In demonstration:

x =             0x92AC3DF7
x =             1001 0010 1010 1100 0011 1101 1111 0111
                ---------------------------------------
x >> 16         0000 0000 0000 0000 1001 0010 1010 1100
x & 0x0000FFFF  0000 0000 0000 0000 0011 1101 1111 0111
^=              0000 0000 0000 0000 1010 1111 0101 1011
                ---------------------------------------
x >> 8          0000 0000 0000 0000 0000 0000 1010 1111
x & 0x00FF      0000 0000 0000 0000 0000 0000 0101 1011
^=              0000 0000 0000 0000 0000 0000 1111 0100
                ---------------------------------------
x >> 4          0000 0000 0000 0000 0000 0000 0000 1111
x & 0x0F        0000 0000 0000 0000 0000 0000 0000 0100
^=              0000 0000 0000 0000 0000 0000 0000 1011
                ---------------------------------------
x >> 2          0000 0000 0000 0000 0000 0000 0000 0010
x & 0x3         0000 0000 0000 0000 0000 0000 0000 0011
^=              0000 0000 0000 0000 0000 0000 0000 0001
                ---------------------------------------
x >> 1          0000 0000 0000 0000 0000 0000 0000 0000
x & 0x1         0000 0000 0000 0000 0000 0000 0000 0001
^=              0000 0000 0000 0000 0000 0000 0000 0001

As you can see, in each step the number of bits is reduced by half by
exclusive-oring the high-order bits with the low order bits. In the case of
0x92AC3DF7 results in one bit left over.

Notice that the last step is unnecessary, since the previous step of right-shift
by two has the same effect as dividing by two, which--after all of the previous
steps--will always result in an even (zero), or an odd (one) remainder.

Demonstrating the same process with an even number of bits:

x =             0x82AC3DF7
x =             1000 0010 1010 1100 0011 1101 1111 0111
                ---------------------------------------
x >> 16         0000 0000 0000 0000 1000 0010 1010 1100
x & 0x0000FFFF  0000 0000 0000 0000 0011 1101 1111 0111
^=              0000 0000 0000 0000 1011 1111 0101 1011
                ---------------------------------------
x >> 8          0000 0000 0000 0000 0000 0000 1011 1111
x & 0x00FF      0000 0000 0000 0000 0000 0000 0101 1011
^=              0000 0000 0000 0000 0000 0000 1110 0100
                ---------------------------------------
x >> 4          0000 0000 0000 0000 0000 0000 0000 1110
x & 0x0F        0000 0000 0000 0000 0000 0000 0000 0100
^=              0000 0000 0000 0000 0000 0000 0000 1010
                ---------------------------------------
x >> 2          0000 0000 0000 0000 0000 0000 0000 0010
x & 0x3         0000 0000 0000 0000 0000 0000 0000 0010
^=              0000 0000 0000 0000 0000 0000 0000 0000
                ---------------------------------------
x >> 1          0000 0000 0000 0000 0000 0000 0000 0000
x & 0x1         0000 0000 0000 0000 0000 0000 0000 0000
^=              0000 0000 0000 0000 0000 0000 0000 0000
*/
