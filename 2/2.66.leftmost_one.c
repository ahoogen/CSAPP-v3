/*
Write code to implement the following function:

Generate mask indicating leftmost 1 in x. Assume w=32.
For example, 0xFF00 --> 0x80000, and 0x6600 --> 0x4000.
If x = 0, then return 0.

int leftmost_one(unsigned x);

Your function should follow the bit-level integer coding rules on page 165, except
that you may assume that data type int has w = 32 bits.
Your code should contain a total of at most 15 arithmetic, bitwise, and logical
operations.
Hint: First transorm x into a bit vector of the form [0...011...1]
*/
#include <stdio.h>

int leftmost_one(unsigned x) {
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;

    return (x + 1) >> 1;
}

int main() {
    unsigned x = 0x647F4;
    printf("0x%08X's leftmost bitmask is: 0x%08X\n", x, leftmost_one(x));
    return 0;
}
/*
This process works by "filling in" the bit patterns in powers of negative 2
using right shifts. The result of the shifts from 16 to 1 yields a bitmask
of all bits between least siginificant bit and the leftmost bit set.

Two small-scale examples of what is happening:

x = 0x11:  0001 0001 x = 0x60 0110 0000
x >> 4:    0000 0001          0000 0110
|=:        0001 0001          0110 0110
x >> 2:    0000 0100          0001 1001
|=:        0001 0101          0111 1111
x >> 1:    0000 1010          0011 1111
|=:        0001 1111          0111 1111

Now that we have this bit pattern, we can isolate the most significant bit of x:
x =        0x1F               0x7F
x =        0001 1111          0111 1111
+= 1       0010 0000          1000 0000
x >> 1     0001 0000          0100 0000
x =        0x10               0x40

Alternatively, you can isolate the leftmost bit using exclusive-or and a right
shift:
x =        0x1F               0x7F
x =        0001 1111          0111 1111
x >> 1     0000 1111          0011 1111
^=         0001 0000          0100 0000
x =        0x10               0x40
*/
