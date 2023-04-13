/*
int foo (int x) {
  return x+1;
}
*/
.data
.text
.globl foo
foo:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp

    incl  %edi
    movl  %edi, %eax

    leave
    ret
