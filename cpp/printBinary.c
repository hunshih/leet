//
//  int2binary.c
//  370_proj1
//
//  Created by Shu Lin on 9/8/12.
//  Copyright (c) 2012 Shu Lin. All rights reserved.
//

#include <stdio.h>

unsigned int reverseBits(unsigned int num){
    static const unsigned char BitReverseTable256[256] =
    {
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
        R6(0), R6(2), R6(1), R6(3)
    };
    
    unsigned int v = num; // reverse 32-bit value, 8 bits at time
    unsigned int c; // c will get v reversed
    
    // Option 1:
    c = (BitReverseTable256[v & 0xff] << 24) |
    (BitReverseTable256[(v >> 8) & 0xff] << 16) |
    (BitReverseTable256[(v >> 16) & 0xff] << 8) |
    (BitReverseTable256[(v >> 24) & 0xff]);
    
    return c;
}

void printBinary(int num){
    //E: Print the binary respresentation of the number in "binary".
    
    int i;
    printf("\t");
    num = reverseBits(num);
    
    for (i = 0; i < 32; i++) {
        printf("%c", (num & 1) ? '1' : '0');
        num >>= 1;
        if (!(i & 3))
            printf(" ");
    }
    printf("\n");
    return;
}

int main(){
    
    int A = 10;
    
    printBinary(A);
    
    return 0;
}