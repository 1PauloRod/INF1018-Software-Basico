/*int add (int a, int b, int c) {
  return a+b+c;
}*/

/*
edi -> a
esi -> b
edx -> c 
*/
.text
.globl add

add:
  /* prologo */
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp

codigo:
  /* codigo */
  addl %edi, %esi /* b = b + a */
  addl %esi, %edx /* c = c + b */
  mov %edx, %eax /* retorna c */
  jmp final

final:
  /* finalizacao */
  leave
  ret
