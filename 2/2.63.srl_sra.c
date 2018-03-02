/*
Fill in code for the following C functions. Function srl performs a logical right
shift using an arithmetic right shift (given by value of xsra), followed by othe
operations not including right shifts or division. Function sra performs an
arithmetic right shift using a logical right shift (given by xsrl), followed by
other operators not including right shifts or division. You may use the computation
8 * sizeof(int) to determine w, the number of bits in data type int. The shift
amount can range from 0 to w-1.
*/
#include <stdio.h>

// Perform logical right shift when only arithmetical right shift exists.
unsigned srl(unsigned x, int k) {
    /* Perform shif arithmetically */
    unsigned xsra = (int) x >> k;

    /* Subtract 1 from a number 1 << (s-k) results in a mask s-k bits wide */
    int s = sizeof(x)<<3;
    unsigned mask = (1 << (s-k))-1;

    return xsra & mask;
}

// Perform arithmetical right shift when only logial right shift exists.
int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;

    /* Multiply the negation of a mask s-k bits wide by the sign bit of x */
    // No cheating with using right shift to isolate sign bit of x!
    int s = sizeof(x)<<3;
    // How do you negate the mask if the sign bit is zero, without using multiplication?
    int mask = (~((1 << (s-k))-1)) * !!(x & (1 << (s-1)));

    return xsrl | mask;
}

int main() {
    int x = 0x81AC7FE3;
    int b = 10;
    printf("Unsigned: 0x%08X >> %d Actual: 0x%08X srl(): 0x%08X\n",(unsigned)x, b, (unsigned)x >> b, srl((unsigned)x, b));
    printf("Signed:   0x%08X >> %d Actual: 0x%08X sra(): 0x%08X\n",x, b, x >> b, sra(x, b));
    return 0;
}
