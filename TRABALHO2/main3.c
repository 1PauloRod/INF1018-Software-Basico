#include <stdio.h>
#include <string.h>
#include "cria_func.h"

typedef int (*func_ptr) (int* a);

int somaTudo(int a, int* b, int* c){
  return a + *b + *c;
}

int main (void) {
  DescParam p[3];
  func_ptr f_somaTudo;
  int tam = 10;
  int val2 = 5;
  int val = 70;

  p[0].tipo_val = INT_PAR; /* o segundo parâmetro de memcmp é também um ponteiro para char */
  p[0].orig_val = IND;   /* a nova função recebe esse ponteiro e repassa para memcmp */
  p[0].valor.v_ptr = &tam;

  p[1].tipo_val = PTR_PAR; /* o primeiro parâmetro de memcmp é um ponteiro para char */
  p[1].orig_val = FIX;     /* a nova função passa para memcmp o endereço da string "fixa" */
  p[1].valor.v_ptr = &val2;

  p[2].tipo_val = PTR_PAR; /* o terceiro parâmetro de memcmp é um inteiro */
  p[2].orig_val = PARAM;   /* a nova função recebe esse inteiro e repassa para memcmp */

  f_somaTudo = (func_ptr) cria_func (somaTudo, p, 3);
  printf("%d\n", f_somaTudo(&val));

  libera_func(f_somaTudo);
  return 0;
}