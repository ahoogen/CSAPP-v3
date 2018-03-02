/*
Supose we nunber the bytes in a w-bit word from 0 (least significant) to w/8 - 1
(most significant). Write code for the following C function which will return
an unsigned value in which byte i of argument x has been replaced by byte b:

unsigned replace_byte (unsigned x, int i, unsigned char b);

Here are some examples showing how the function should work:
replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
*/
#include <stdio.h>

/*
replace_byte masks x in byte index i and replaces with value in char c.
Returns 0 if index is out of bounds.
*/
unsigned replace_byte(unsigned x, int i, unsigned char c) {
    if (i + 1 > sizeof(x) || i < 0) {
        return 0;
    }

    return (x & ~(0xFF << i*8)) | (unsigned)c << i*8;
}

int main() {
    int i = 3;
    unsigned char c = 0xAB;
    unsigned x = 0x12345678;

    printf("At byte index %d, swap byte 0x%01X in 0x%08X\n", i, c, x);
    printf("0x%08X\n", replace_byte(x, i, c));

    return 0;
}
