#include <stdio.h>
/*
Write code for a function with the following prototype:

// Mask with least significant n buts set to 1
// Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
// Assume 1 <= n <= w

int lower_one_mask(int n);

Your function should follow the bit-level integer coding rules on page 165. Be
careful of the case n = w.
*/

int lower_one_mask(int n) {
    int x = 1 << (n-1);
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;

    return x;
}

/*
Explanation:
This is the same problem as producing a bitmask in the nth position from problem
2.66.leftmost_one.c. However in this instance, we don't perform the last step of unsetting all
bits lower than n, we just leave the results of the bitwise ORs and right-shifts.
*/

int main() {
    int n = 6;
    printf("Should produce 0x3F\n");
    printf("A bitmask of %d bits looks like: 0x%08X\n", n, lower_one_mask(n));
    n = 17;
    printf("Should produce 0x1FFFF\n");
    printf("A bitmask of %d bits looks like: 0x%08X\n", n, lower_one_mask(n));
    n = 30;
    printf("Should produce 0x3FFFFFFF\n");
    printf("A bitmask of %d bits looks like: 0x%08X\n", n, lower_one_mask(n));
    n = 32;
    printf("Should produce 0xFFFFFFFF\n");
    printf("A bitmask of %d bits looks like: 0x%08X\n", n, lower_one_mask(n));
    return 0;
}
