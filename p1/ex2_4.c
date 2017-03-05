#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(){
	uint8_t  a,b;
	int i;
	typedef int t[8];
	t ta;
	i=7;
	for (int i = 0; i < 8; ++i)
	{
		ta[i] = 0;
	}
	
	scanf("%x", &a);

	printf("%o\n", a);
	printf("%d\n", a);
	i =  7;
	b = a;
	while(b>=2){
		a=b%2;
		b= b/2;
		ta[i] = a;
		--i;
	}
	ta[i] = b;
	for (int i = 0; i<8 ; ++i)
	{
		printf("%d", ta[i] );
	}
	printf("\n");

}
