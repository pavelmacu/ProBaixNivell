#include <stdio.h>

int main(){
	int a,c;
	a = 0;

	while ((c=getchar()) != '.'){
		if (c == 'a')
			++a;
	}
	printf("%d\n", a);
}