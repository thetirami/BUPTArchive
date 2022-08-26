#include <stdio.h>
#include <stdlib.h>
#define BIT_RANGE_ASSIGN(t,fv,n1,n2) ((t & (~(((~0U) >> (32 - (n2 - n1 + 1))) << n1 ))) ^ (fv << n1))

int main()
{
	unsigned int t = 0x12345678;
	printf("%x\r\n", BIT_RANGE_ASSIGN(t, 0, 0, 3));
	printf("%x\r\n", BIT_RANGE_ASSIGN(t, 0xf, 0, 3));
	printf("%x\r\n", BIT_RANGE_ASSIGN(t, 0x78654321, 0, 31));

    system("pause");
    return 0;
}
