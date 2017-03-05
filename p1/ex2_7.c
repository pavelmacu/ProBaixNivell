#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>



int main(){
	uint16_t a,b,c;
	scanf("%hx", &a);
	b = a & 61440;
	b = (b >> 8);
	c = a & 15;
	a = b+c;
	printf("%hx\n", a);

	return 0;

}