#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int main(){
	typedef int tau[10];
	tau t;
	int c;
	int max,val;


	max = val = 0;
	t[0]= 0;
	t[1]= 0;
	t[2]= 0;
	t[3]= 0;
	t[4]= 0;
	t[5]= 0;
	t[6]= 0;
	t[7]= 0;
	t[8]= 0;
	t[9]= 0;

	for (int i = 0; i < 20; ++i)
	{
		scanf("%d", c);
		t[c]+=1;
	}

	for (int a = 0; a < 10; ++a)
	{
		if (t[a] > max){
			max = t[a];
			val = a;}
	}
	printf("%d\n", val );


	return 0;


	
	
}