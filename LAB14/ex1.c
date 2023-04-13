#include <stdio.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))

#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
 } U;

float float2(float x)
{
    U u;
    u.f = x;
    unsigned int aux = u.i;

    u.i = makefloat(getsig(aux), getexp(aux)+1, getfrac(aux));
    return u.f;
}

int main(void)
{
    float f = 0.33333333333333333333;
	//float2	
	printf("%f\n", float2(f));
	f = -10;
	printf("%f\n", float2(f));
	f = 10;
	printf("%f\n", float2(f));
	f = 12334676456345667450.;
	printf("%f\n", float2(f));
	f = -12334676345665.;
	printf("%f\n", float2(f));
    return 0;
}               
