/*
struct X {
  int val;
  struct X *next;
};
int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}
*/

.data

.globl add

add:
    /* prologo */

    pushq  %rbp
    movq   %rsp, %rbp

    /* codigo */
    movl $0, %eax

code:
    cmpq $0, %rdi
    je final

    addl (%rdi), %eax
    movq 8(%rdi), %rdi
    jmp code

final:
    leave
    ret
