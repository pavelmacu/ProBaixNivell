#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int main(){
	uint16_t a,b;
	scanf("%hx", &a);
	b = a & 32766;
	printf("%x\n", b );

	return 0;

}