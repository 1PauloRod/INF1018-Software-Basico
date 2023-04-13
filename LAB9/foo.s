/*
void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
}
*/
/*
ebx - i
esi - n
rdi - a[]
%eax - s
*/
.text
.globl foo
foo:
    /* prologo */
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    /* codigo */
    movl $0, %ebx /* i = 0 */
    movl $0, %eax /* s = 0 */

L1: 
    cmpl %ebx, %esi /* if (i == n) */
    jne for
    movl (%rdi), %eax 
    jmp final

for:
    addl $1, %ebx
    addl (%rdi), %eax
    cmpl $0, (%rdi) /*if(a[i] == 0)*/
    je if
    jmp L1

if:
    movl %eax, (%edi)
    movl $0, %eax
    jmp foo

final:
    leave
    ret



    