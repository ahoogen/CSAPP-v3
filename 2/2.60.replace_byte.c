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

    return (x & ~(0xFF << i*8)) | c << i*8;
}

int main() {
    int i = 3;
    unsigned char c = 0xAB;
    unsigned x = 0x12345678;

    printf("At byte index %d, swap byte 0x%01X in 0x%08X\n", i, c, x);
    printf("0x%08X\n", replace_byte(x, i, c));

    return 0;
}

/*
In order to replace a byte represented by c in position i of integer x we need
to create a mask the size of x with zeros in the byte position we want to do
our insertion. So for a 32 bit integer where we're inserting a byte in position
2 we'd need a bitmask of 0xFF00FFFF. We create this by shifting the pattern
0xFF to the left by i*8 bits (0x00FF0000) and then getting ones' complement. We
then apply this bitmask to x using a bitwise AND to "delete" the bits in this
position. We must do this because any remaining bits set will change the value
of c.

We then shift the byte pattern of c to the left by i*8 bits to fit into the
hole we just created in x. To merge the bits into x we simply perform a bitwise
OR which will select the bits of c and place them into x. This is true because
we set all of x's bits in byte index i to zero, so the only bit pattern left
after this operation is those of c's.

If you are worried about the unsigned char type of c being only 8 bits long and
then applying the left shift, you need not worry. The bit pattern after a left
shift will remain in the register of the CPU after the operation, which will be
immediately used in the subsequent operation of the bitwise OR with the value
of x. You would only lose data once you copied the word-sized value from the
register and attempted to assing that value to a data type of unsigned char.
*/
