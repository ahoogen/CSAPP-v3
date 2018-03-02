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
