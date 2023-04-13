#include <stdio.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
 } U;

float float2(float f) {
	U u;
	u.f = f;
	unsigned int temp = u.i;
	
	u.i = makefloat(getsig(temp), getexp(temp)+1, getfrac(temp));
	return u.f;
}

int main(void) {
	printf("%f * 2: %f\n", 15213.0, float2(15213.0));
    printf("%ld\n", sizeof(float));
	return 0;
}

exp = 0000 0000 0000 0000 0011 1011 0110 1101 (desloca os 23) = 11011011010000000000000

fra = 1110110110110100000000000000000


