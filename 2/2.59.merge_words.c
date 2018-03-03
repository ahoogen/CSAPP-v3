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

/*
In order to merge two words according to specific bytes of words a and b, the
solution is to simply create a mask for each word, apply the mask to each word
to select for the bits we want--discarding the bits that we don't--and then to
bitwise OR the two words together.

In this case, we want the least significant byte of x, and we want all but the
least significant byte of y.

For the example we're assuming a word size of 32 bits.

To select the least significant byte of x we create a mask of 0xFF (0x000000FF)
and then use a bitwise AND to select only those bits. x now has a bit
representation of 0x000000??.

To select all but the least significant byte of y we create a mask of ~0xFF
(0xFFFFFF00) and then use a bitwise AND to select only those bits. y now has a
bit representation of 0x??????00.

When we perform the final bitwise OR you can see that our masks have aligned
our bits of interest (?):

  0x000000??
| 0x??????00
------------
= 0x????????
*/
