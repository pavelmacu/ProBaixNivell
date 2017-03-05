#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void tobinary(){
	
	uint8_t  a,b;
	int i;
	typedef int t[8];
	t ta;
	scanf("%x", &a);
	i=7;
	for (int i = 0; i < 8; ++i)
	{
		ta[i] = 0;
	}
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
void todecimal(){
	uint8_t  a;
	scanf("%x", &a);
	printf("%d\n", a);
}


void tooctal(){
	uint8_t  a;
	scanf("%x", &a);
	printf("%o\n", a);
}

int main(int argc, char ** argv){
	if (argc == 1 ){
		printf("No has introduit cap comanda\n");
	}
	else {

	if (strcmp(argv[1], "-o")== 0)
		tooctal();
	if (strcmp(argv[1], "-b")== 0)
	 	tobinary();
	if (strcmp(argv[1], "-d") == 0)
		todecimal();
}
return 0;

}




