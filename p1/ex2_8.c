#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>



int main(){
	int a,b,c,n;
	scanf("%2x", &a);
	b = a;
	while(a != 0x00 ){
		while( b>= 2){
			c = b%2;
			b = b/2;
			if (c == 1)
				++n;

		}
		if (b == 1)
			++n;
		scanf("%2x", &a);
		b = a;
	}

	printf("%d\n", n );
			
}
