/*
Following the restrictions on page 165: no conditionals, no division/multiplication
and no relative comparison operators: (eg, using only logical and bitwise operators)

Write C expressions that evaluate to 1 when the following conditions are true
and to 0 when they are false. Assume x is of type int.
*/
#include <stdio.h>

int test_if_any_zeros(int x) {
    /*
    The negation of *any* number that has a zero will evaluate as True
    under logical conditions.

    ~0xFFFFFFFF = 0x00000000 evaluates to false (there were no zeros to negate)
    ~0x00000000 = 0xFFFFFFFF evlauates to true (there were zeros to negate)
    ~0xFFFFFFFE = 0x00000001 evaluates to true (there were zeros to negate)

    Therefore, !!~x evaluates to true if any bit is zero.
    */
    return !!~x;
}

int test_if_any_ones(int x) {
    /*
    0 evaluates to false, !0 evaluates to true.
    Any logical test here will work if any bit is one.
    !!x works, as would (x && x) and (x || x)

    A logical test is needed to return truthiness, rather than the original value.
    */

    return x && x;
}

int test_for_one_in_lsb(int x) {
    return test_if_any_ones(x & 0xFF);
}

int test_for_zero_in_msb(int x) {
    int w = (sizeof(x)-1)<<3;
    int mask = (0xFF << w);
    x = (x & mask) | ~mask;
    return test_if_any_zeros(x);
}

int main()
{
    int t = 0xFFFFFFFF;
    printf("Test if any bit of x equals 0\n");
    printf("Testing 0x%08X: %d\n", t, test_if_any_zeros(t));
    t = 0x00000000;
    printf("Testing 0x%08X: %d\n", t, test_if_any_zeros(t));
    t = 0xEFFFFFFF;
    printf("Testing 0x%08X: %d\n", t, test_if_any_zeros(t));

    printf("Test if any bit of x equals 1\n");
    t = 0xFFFFFFFF;
    printf("Testing 0x%08X: %d\n", t, test_if_any_ones(t));
    t = 0x00000000;
    printf("Testing 0x%08X: %d\n", t, test_if_any_ones(t));
    t = 0x00000001;
    printf("Testing 0x%08X: %d\n", t, test_if_any_ones(t));

    printf("Test if least significant byte has any bit set to 1\n");
    t = 0xFFFFFF00;
    printf("Testing 0x%08X: %d\n", t, test_for_one_in_lsb(t));
    t = 0x00000000;
    printf("Testing 0x%08X: %d\n", t, test_for_one_in_lsb(t));
    t = 0x00000001;
    printf("Testing 0x%08X: %d\n", t, test_for_one_in_lsb(t));

    printf("Test if most significant byte has any bit set to 0\n");
    t = 0xFFFFFF00;
    printf("Testing 0x%08X: %d\n", t, test_for_zero_in_msb(t));
    t = 0xFEFFFFFF;
    printf("Testing 0x%08X: %d\n", t, test_for_zero_in_msb(t));
    t = 0xEF000000;
    printf("Testing 0x%08X: %d\n", t, test_for_zero_in_msb(t));

    return 0;
}

/*
This is the first in a series of assignments where there are restrictions
placed on what kinds of operations you may use. The purpose is to test and
reinforce your understanding of bitwise and logical operations, number formats,
and other properties of binary numbers.

A) test_if_any_zeros(int x)
---------------------------
Here we may have three scenarios:
1) x is all ones (0xFFFF...)
2) x is all zeros (0x0000....)
3) x is a mixture of ones and zeros (0xAC71...)

The first two test might lead you to believe you can simply return !x, but this
would be incorrect, as we will see later. !x works for conditions #1 and #2.
But it may be helpful to review what happens when testing something logically.
We know that True is represented by the numeric value 1, and that False is
represented by the numeric value 0. However, when *evaluating* whether something
is True or False, different criteria are used. When we evaluate (logical_op) x,
the result of the operation is True or False, however the *evaluation* of the
operation is *zero* or *not-zero*. We know this to be true since any non-zero
value of x will evaulate to true. This is where case #3 comes in.

In order to test whether x has any zeros we simply get ones' complement of x.
Since any zero bit in x will become a 1 in ~x, ~x will *always* evaluate to
True in a logical test. ~x will also work for cases #1 and #2.

However, the assignment asks that either a zero (0) or one (1) be returned.
Since we're using a bitwise operator instead of a logical operator, the value
of ~x will be *any non-zero value* when x has a zero bit. 0x7 has pattern 0111
or 7, which if returned could be a source of a bug. While it is true that 7 is
not zero and will always evaluate to 1 in a logical test, we cannot guarantee
that the caller of this function will be using the result logically. It may
be used mathematically. Therefore we need to reduce this to its logical value.

Here, any logical operation will suffice. !!~x is what I chose, which logically
tests the value of ~x and negates that, then negates it once more to return it
to the logical value initially tested. ~x && ~x, ~x || ~x would also work,
however !!~x feels more appropriate.

B) test_if_any_ones(int x)
--------------------------
Here this is a much simpler test. As mentioned in A) above, any logical test
will evaluate x as True if x is equal to not-zero. So the solution is to
simply apply x in a logical test.

x && x, x || x and !!x all work.

C) test_for_one_in_lsb()
------------------------
Here we're doing the same thing as in B) above, except we're limiting the test
to the least significant byte of x. The solution here is simply to create a
mask for the byte we want to test. This can be done simply by using a bitwise
AND on our x and a mask value of 0xFF. My solution literally reuses the solution
from B) with the masked version of x to satisfy the LSB requirement.

D) test_for_zero_in_msb()
-------------------------
This function is slightly more tricky than C) since we are testing for zeros.
We need to isolate the most-significant byte of x, just as we needed to isolate
the LSB above. However, we can't simply bitwise AND our mask of 0xFF in the MSB
position, because that will leave all remaining bytes of x set to zero, which--
when we save ourselves some coding by resuing test A)--will always return True
even if the MSB has a bit pattern of 0xFF, which is not what we want.

In this case, we must first create our mask in the correct byte position
depending on the word size of the system under test. We get this by shifting
0xFF to the left by (sizeof(x)-1)<<3 bits (wordsize in bytes minus one
multiplied by 2^3). Then we apply this mask to x to isolate the most-significant
byte. But then we need to apply the ones' complement of our mask to x to set all
remaining bits to one so that they will not produce a false positive when we
pass the value to test_if_any_zeros(). We accomplish this by performing a
bitwise OR on the masked value of x and ~mask.

This results in a number whose bit representation is ???? ???? 1111 1111 ....
and will correctly determine if we have a zero in the MSB of x.
*/
