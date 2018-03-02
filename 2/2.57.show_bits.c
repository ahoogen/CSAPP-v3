/*
Write procedures show_short(), show_long() and show_double() that prints the
byte representations of C objects of types short, long and double, respectively.
*/
#include <stdio.h>

/*
print_bits shows the binary representation of a number from left to right.
Depending on the architecture, most significant to least significant, or vice versa.
*/
void print_bits(long p) {
    int s = sizeof(p) * 8 - 1;
    printf("Integer %ld has %d bits represented by binary value:\n", p, s + 1);
    for (;  s >= 0; s--) {
        if (p & 1 << s) {
            printf("1");
        } else {
            printf("0");
        }

        if (s % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");

}

int main()
{
    long x = 482263343;
    print_bits(x);

    return 0;
}
