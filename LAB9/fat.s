/*int fat (int n) {
  if (n==0) return 1;
  else return n*fat(n-1);
}*/
/*
ebx - i
edi - n
*/
.text
.globl fat

fat:
    /* prologo */
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    /* codigo */
    cmpl $0, %edi /* if (i == 0) */
    jne else
    movl $1, %eax /* n == 1 */
    jmp final

else:
    movl %edi, -4(%rbp)
    decl %edi /* n - 1*/
    call fat
    /*movl -4(%rbp), %edi*/
    imull %edi, %eax /* n * fat(n - 1) */
    jmp final

final:
    leave
    ret

