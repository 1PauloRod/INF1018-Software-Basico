#include <stdio.h>

typedef int (*funcp)(int x);


unsigned char codigo[] = {
    0x55,                   	//push   %rbp
    0x48, 0x89, 0xe5,            //mov    %rsp,%rbp
    0x48, 0x83, 0xec, 0x10,     //sub    $0x10,%rsp
   	0xff, 0xc7,                	//inc    %edi
   	0x89, 0xf8,                	//mov    %edi,%eax
   0xc9,                   	    //leaveq 
   0xc3                   	    //retq
};


int main(void)
{
    int i; 
    funcp f = (funcp)codigo;
    i = (*f)(10);
    printf("%d\n", i);
    return 0;
}
