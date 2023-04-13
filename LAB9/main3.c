#include <stdio.h>

void foo(int a[], int n);

int main(void)
{
    int a[3] = {1, 2, 3};
    int n = 3;
    foo(a, n);
    printf("%d\n", a[2]);
    return 0;
}