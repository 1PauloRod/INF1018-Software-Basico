/*
int f(int i, int v);

void boo (struct X *px, int n, int val) {
  while (n--) {
    px->val2 = f(px->val1, val);
    px++;
  }
}
*/


.data
.globl boo
boo:

    /* prologo */
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rbx, -8(%rbp)
    movl %r12d, -12(%rbp)
    movl %r13d, -16(%rbp)

    movl %esi, %r12d /* n */
    movl %edx, %r13d /* valor */
    movq %rdi, %rbx  /* struct */

while:
    cmpl $0, %r12d
    je final

    movl (%rbx), %edi
    movl %r13d, %esi
    call f

    movl %eax, 4(%rbx)

    subl $1, %r12d
    addq $8, %rbx
    jmp  while

final:
    movq %rbx, %rdi
    movq $0, %rax

    movl -16(%rbp), %r13d
    movl -12(%rbp), %r12d
    movq -8(%rbp), %rbx

    leave
    ret











    





