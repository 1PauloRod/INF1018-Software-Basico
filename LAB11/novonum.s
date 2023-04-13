/*int novonum(void) {
  int minhalocal;
  printf("numero: ");
  scanf("%d",&minhalocal);
  return minhalocal;
}*/

.data
sf1: .string "numero: "
sf2: .string "%d"
.globl novonum

novonum:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16,  %rsp

    movq  $sf1, %rdi
    movq  %rdi, %rax
    movq  $0, %rax
    call printf

    movq  $sf2, %rdi
    leaq -4(%rbp), %rsi
    call scanf

    movl -4(%rbp), %eax

    leave
    ret







