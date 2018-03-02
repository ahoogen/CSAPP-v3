/*
Write a procedure is_little_endian that will return 1 when compiled and run on a
little endian machine, and will return 0 when compiled and run on a big endian
machine. This program should run on any machine, regardless of its word size.
*/
#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian() {
    int x = 1;
    byte_pointer c = (byte_pointer)&x;
    return c[0] & 0x01;
}

int main() {
    printf("This machine is ");
    if (is_little_endian()) {
        printf("LITTLE ");
    } else {
        printf("BIG ");
    }
    printf("endian.\n");
    return 0;
}
