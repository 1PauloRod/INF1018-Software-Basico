
#include "bigint.h"
#include <stdio.h>

void dump (void *p) {
  int n = sizeof(p);
  unsigned char *p1 = p;
  while (n--) {
    printf("%02x", *p1);
    p1++;
  }
}

  int main()
  {

    BigInt res;
    BigInt a,b;
    big_val(a,-10000); big_val(b,100000);
    printf("a=\n");
    dump(&a);
    printf("\nb=\n");
    dump(&b);
    big_sum(res,a,b);
    printf("\nsum=\n");
    dump(&res);
    big_sub(res,a,b);
    printf("\nsub=\n");
    dump(&res);
    big_comp2(res,b);
    printf("\nComplemento a dois de b\n");
    dump(&res);
    printf("\na*b=\n");
    big_mul(res,a,b);
    dump(&res);
    printf("\n");
    return 0;
  }
