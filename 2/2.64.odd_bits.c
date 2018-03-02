/*
Write code to implement the following functions:
Return 1 when any odd bit of x equals 1; 0 otherwise.
Assume w=32.

int any_odd_one(unsigned x);
*/
#include <stdio.h>

int any_odd_one(unsigned x) {
    return !!(x & 0xAAAAAA);
}

int main() {
    unsigned x = 0xAAAAAAAA;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));
    x = 0xBBBBBBBB;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));
    x = 0x1;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));
    x = 0x50505050;
    printf("0x%08X has odd bits? %d\n", x, any_odd_one(x));

    return 0;
}
