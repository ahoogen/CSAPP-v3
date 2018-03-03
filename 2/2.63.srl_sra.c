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

    /* Negate mask s-k bits wide by the sign bit of x */
    /* This could be done by multiplying mask by the
       value of sign bit, but since multiplication isn't allowed... */
    int s = sizeof(x)<<3;
    int mask = ~((1 << (s-k))-1);
    mask ^= ((1 << s) - !!(x & (1 << (s-1)))) & mask;

    return xsrl | mask;
}

int main() {
    int x = 0x81AC7FE3;
    int b = 10;
    printf("Unsigned: 0x%08X >> %d Actual: 0x%08X srl(): 0x%08X\n",
            (unsigned)x, b, (unsigned)x >> b, srl((unsigned)x, b));
    printf("Signed:   0x%08X >> %d Actual: 0x%08X sra(): 0x%08X\n",
            x, b, x >> b, sra(x, b));
    return 0;
}

/*
Here the task is to "clean up" the effects of using the wrong right shift
operator.

srl()
-----
The function srl() results in a logical right shift of x by k bits.
However, the shift is done arithmetically due to the cast of unsigned to int.
The result is that the arithmetical shift carries the sign bit. We need to
calculate and set a mask of s-k bits to exclude this binary pollution.

First we calculate the size of x in bytes and multiply by 8. In the instructions
we are allowed to use the form sizeof(x)*8 to get the number of bits, but here
I'm following the spirit of the exercise which excludes multiplication. So I use
a left shift of 3 to multiply by 2^3 or 8.

The mask should select from the leftmost bit after the shift of k bits, to the
least significant bit, discarding the higher order bits (potentially) set by
the arithmetical right shift. We do this by left-shifting 1 by s-k bits (which
will be one bit larger than the mask we want) and then subtracting one from this
number which results in a mask of all ones with the width of s-k bits. Then the
bitwise AND does the work of cleaning up the bit pattern.

For example:
k = 5
x = 0xFC00      1111 1100 0000 0000
x A>> 5         1111 1111 1110 0000
pollution       1111 1000 0000 0000
1 << (16 - 5)   0000 1000 0000 0000
-= 1            0000 0111 1111 1111
x &=            0000 0111 1110 0000

sra()
-----
The case of the function sra() is similar to, but the opposite of srl(). Since
we're casting an int to unsigned, the right shift becomes a logical right shift
which will not carry our sign bits. We need to create a bitmask that we can use
to add the carried sign bits back into place. However this should only be done
if the original value of x had its sign bit set.

This bit mask is the ones' complement of the bitmask used in srl(). We create
the mask in the same way, shifting 1 to the left by s-k bits and subtracting
one. Then to get the correct mask we use the ones' complement operator, also
known as the bitwise NOT operator (~) to invert the pattern.

Before we can apply this bit pattern to correct for the missing sign bits we
need to determine if x had its sign bit set. If not, we would be making a
positive integer negative, arbitrarily. My first attempt at this was to cast x to
be unsigned, then right-shifted x by s-1 bits to isolate the sign bit. However,
after reviewing my solution, the instructions of the problem prohibit right-
shift operators other than the one used for the initial shift. So how to select
the sign bit without right shifting?

We need to generate either a 1 or a 0 depending on if the sign bit is set. To
do this we do a simple bit check on (x & 1 << s-1) which will result in 0x0 if
the sign bit isn't set, or INT_MIN (0x80000000 on 32 bit ints) if it is. To
force this into 0x1 or 0x0 we use the double negation operation (!!) to isolate
the sign bit.

Now we have or mask, and the simplest thing to do now is multiply our mask by
the result of our check on the sign bit. If the sign bit isn't set, 0 * mask =
0. If the sign bit is set, 1 * mask = mask. But....

The problem limits the operations we can use, and multiplication is *also*
verbotten. ~sigh~. So how do we "multiply" without multiplying? We can't use a
left-shift here, since there is no power of 2 that equals 0. 2^0 = 1.

I can get part of the way there if I subtract the sign bit from a number one bit
larger than w. If the sign bit is zero, then 2^w+1 - 0 = 2^w+1. But if the sign
bit is one, then 2^w+1 - 1 results in a mask w bits wide fully set.

We aren't done just yet. Since to add our mask to the resulting logical shift
of x, we need to exclude the non-carry bits of our mask. We can do this by
applying a bitwise AND to our first mask and the sign-carry mask we just
generated.

Then we simply bitwise OR our mask and x to return the corrected sign bits.

Example with sign bit set:

k = 5
x = 0xFC00          1111 1100 0000 0000
x L>> 5             0000 0111 1110 0000
1 << (16 - 5)       0000 1000 0000 0000
-= 1                0000 0111 1111 1111
~=                  1111 1000 0000 0000 # mask
x & 1 << (16 - 1)   1000 0000 0000 0000 # sign bit
!!                  0000 0000 0000 0001 # reduction amount
1 << 16           1 0000 0000 0000 0000
-= 1              0 1111 1111 1111 1111 # reduced
&= mask             1111 1000 0000 0000
x | mask            1111 1111 1110 0000

Example with sign bit not set:

k = 5
x = 0x7C00          0111 1100 0000 0000
x L>> 5             0000 0011 1110 0000
1 << (16 - 5)       0000 1000 0000 0000
-= 1                0000 0111 1111 1111
~=                  1111 1000 0000 0000 # mask
x & 1 << (16 - 1)   0000 0000 0000 0000 # sign bit
!!                  0000 0000 0000 0000 # reduction amount
1 << 16           1 0000 0000 0000 0000
-= 0              1 0000 0000 0000 0000 # reduced
&= mask             0000 0000 0000 0000
x | mask            0000 0011 1110 0000

Technically our mask remains 1 0000 0000 0000 0000 after this process, but since
we're dealing with a 16 bit integer, the 17th bit is discarded when being
assigned back to 16 bit mask, and is lost for all subsequent operations with mask.
*/
