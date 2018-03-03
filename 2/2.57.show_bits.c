/*
Write procedures show_short(), show_long() and show_double() that prints the
byte representations of C objects of types short, long and double, respectively.
*/
#include <stdio.h>

typedef unsigned char *byte_pointer;

/*
show_bits shows the binary representation of a number from left to right.
Depending on the architecture, most significant to least significant, or vice versa.
*/
void show_bits(byte_pointer p, int b) {
    if (b < 0 || b > sizeof(p)) {
        printf("Number of bytes %d is out of bounds of byte_pointer.\n", b);
        return;
    }

    int j;
    for (;  b > 0; b--) {
        for (j = 7; j >= 0; j--) {
            if (p[b-1] & 1 << j) {
                printf("1");
            } else {
                printf("0");
            }

            if (j % 4 == 0) {
                printf(" ");
            }
        }
    }
    printf("\n");
}

// Show b bytes of byte_pointer x
void show_bytes(byte_pointer x, int b) {
    printf("0x");
    for (; b > 0; b--) {
        printf("%02X", x[b-1]);
    }
    printf("\n");
}

void show_short(short int x) {
    printf("Short int: %d\nNumber of bytes: %ld\nHexadecimal: ", x, sizeof(x));
    show_bytes((byte_pointer)&x, sizeof(x));
    printf("Binary: ");
    show_bits((byte_pointer)&x, sizeof(x));
    printf("\n");
}

void show_long(long x) {
    printf("Long int: %ld\nNumber of bytes: %ld\nHexadecimal: ", x, sizeof(x));
    show_bytes((byte_pointer)&x, sizeof(x));
    printf("Binary: ");
    show_bits((byte_pointer)&x, sizeof(x));
    printf("\n");
}

void show_double(double x) {
    printf("Double float: %3.30f\nNumber of bytes: %ld\nHexadecimal: ", x, sizeof(x));
    show_bytes((byte_pointer)&x, sizeof(x));
    printf("Binary: ");
    show_bits((byte_pointer)&x, sizeof(x));
    printf("\n");
}

int main()
{
    short s = 16232;
    long l = 2111598399;
    double d = 3.141592653589793238462643383279;
    show_short(s);
    show_long(l);
    show_double(d);

    return 0;
}
