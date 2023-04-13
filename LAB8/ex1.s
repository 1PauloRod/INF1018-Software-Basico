.data
s1: .string "ls -ls"

.text
.globl main
main:
/*prologo*/
  push %rbp
  movq %rsp, %rbp

/*coloque seu codigo aqui*/

movq $s1, %rdi
call system

movl  $0, %eax

/* finalizacao*/
  leave
  ret

