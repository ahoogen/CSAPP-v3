/*
Write a C expression that will yield a word consisting of the least significant
byte of x and the remaining bytes of y. For operands x = 9x89ABCDEF and
y = 076543210 this would give 0x765432EF.
*/
#include <stdio.h>

/*
merge returns the lowest byte of x and the remaining bytes of y
*/
int merge(int x, int y) {
    return (~0xff & y) | (0xff & x);
}

int main() {
    int a = 0x89ABCDEF;
    int b = 0x76543210;

    printf("0x%08X merged with 0x%08X: 0x%08X\n", a, b, merge(a, b));
    return 0;
}
