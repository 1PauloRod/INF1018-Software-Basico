/*
int bemboba (int num) {
  int local[4];
  int *a;
  int i;
  for (i=0,a=local;i<4;i++) {
    *a = num;
    a++;
  }
  return addl (local, 4);
}
*/
.data
.globl bemboba
bemboba:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp
    leaq -16(%rbp), %r12
    movl $0, %ebx

for:
    cmpl  $4, %ebx
    je final
    movl  %edi, (%r12)
    addq  $4, %r12
    addl  $1, %ebx
    jmp for

final:
    leaq -16(%rbp), %rdi
    movl $4, %esi
    call addl

    movq -16(%rbp), %r12
    leave
    ret








