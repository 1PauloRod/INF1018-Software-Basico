/*
int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
}
*/

.data

.globl add
add:

    /* prologo */
    pushq %rbp
    movq  %rsp, %rbp
    subq $8, %rsp
    movq %rbx, -8(%rbp)

    cmpq $0, %rdi
    je final

    movq (%rdi), %rbx
    movq 8(%rdi), %rdi
    call add
    addq %rax, %rbx

final:
    
    movq %rbx, %rax

    movq -8(%rbp), %rbx
    leave
    ret




