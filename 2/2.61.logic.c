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
