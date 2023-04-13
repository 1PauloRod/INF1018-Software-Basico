#include "bigint.h"
#include <stdio.h>


void big_val(BigInt res, long val)
{
    unsigned char* aux = res; // ponteiro auxiliar que guarda o valor de res
    unsigned char* temp = (unsigned char*)&val; // transforma o enderco de val em unsigned char*
    for (int i = 0; i < sizeof(BigInt); i++) // percorrendo o tamanho de BigInt
    {
 
        if (i >= sizeof(val)) // compara i com o tamanho de val que é 8 
        {
            // preenche os valores até o final com 00 se o valor for positivo ou ff se o valor for negativo
            if (val >= 0) 
                *aux = 0X00;
            if (val < 0)
                *aux = 0xFF;
        }
        // senao atribui ao ponteiro aux o valor do ponteiro de temp
        else
            *aux = *temp;
        aux++;
        temp++;
    }
}

void copia(BigInt a, BigInt b)
{
    for (int i = 0; i < NUM_BITS/8; i++)
    {
        *a = *b;
        a++;
        b++;
    }
}

void big_comp2(BigInt res, BigInt a)
{
    unsigned char aux[NUM_BITS/8]; // variavel auxiliar para guardar o valor de a. 
    copia(aux, a); // função auxiliar para copiar o valor de a para aux.

    for (int i = 0; i < NUM_BITS/8; i++)
    {
        // percorre todos os elementos de aux "negando" os valores, soma mais um quando não for 0xFF nem 0x00. 
        if(aux[i]==0xFF || aux[i] == 0x00)
        {
            res[i]=~(aux[i]);
           
        }
        else
        {
            res[i]= ~(aux[i]) + 0x01;
        }
    }
}



void dump (void *p) {
  int n = sizeof(p);
  unsigned char *p1 = p;
  while (n--) {
    printf("%02x", *p1);
    p1++;
  }
}

int main(void)
{
    BigInt res;
    BigInt a = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    big_comp2(res, a); 
    printf("res=\n");
    dump(&res);
    printf("\na=\n");
    dump(&a);
    printf("\n");

    return 0;
}

