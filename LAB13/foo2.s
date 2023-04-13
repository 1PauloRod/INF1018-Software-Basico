/*
int foo (int x) {
  return add(x);
}
*/
.data
.text
.globl foo
foo:
    call add

    
    ret
