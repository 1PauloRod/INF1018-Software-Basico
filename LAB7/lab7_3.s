/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  int sum = 0; 
  for (i = 0, p = nums; i != 4; i++, p++)
    sum += *p; 
  printf("%d\n", sum);
  return 0;
}
*/


Sf:  .string "%d\n"    # string de formato para printf

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

L1:
  movl  $3, %eax    /* eax = *r12 */
  
  imull %eax,  %eax

/*************************************************************/



/*************************************************************/
/* este trecho imprime o valor de %eax*/
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */  
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/
