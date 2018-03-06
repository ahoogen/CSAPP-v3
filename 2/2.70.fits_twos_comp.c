#include <stdio.h>
/*
Write code for the function with the following prototype:

// Return 1 when x can be represented as an n-bit two's complement number,
// 0 otherwise.
// Assume 1 <= n < w

int fits_bits(int x, int n);

Your function should follow the bit-level integer coding rules on page 165.
*/

int fits_bits(int x, int n) {
    return !(x >> n);
}

/*
The soluton here is pretty simple. Any integer value x is the sum of its bits
up to and including its most significant bit. If you right-shift x by n bits
(eg, multiply by 2^-n or divide by 2^n) you should have a value of 0 left over
if the integer does fit within n bits. If x requires more than n bits, then you
will have at least a remainder of 1.

So we shift x by n bits and negate, which provides our answer as well as
reduces the returned value to either a 1 or a 0, which satisfies our prototype.

Example: x = 16, n = 4
10000 >> 4
!(00001) = False

Example: x=15, n = 4
1111 >> 4
!(0000) = True
*/

int main() {
    int x = 1024;
    int b = 11;
    printf("Does int %d fit in %d bits? %d\n", x, b, fits_bits(x, b));
    b = 10;
    printf("Does int %d fit in %d bits? %d\n", x, b, fits_bits(x, b));
    x = 8192;
    b = 14;
    printf("Does int %d fit in %d bits? %d\n", x, b, fits_bits(x, b));
    x = 11121;
    printf("Does int %d fit in %d bits? %d\n", x, b, fits_bits(x, b));
    x = 17000;
    printf("Does int %d fit in %d bits? %d\n", x, b, fits_bits(x, b));
    return 0;
}
