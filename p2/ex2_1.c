
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


uint8_t read_byte(){
	uint8_t a;
	scanf("%2x", &a);
	return a;
}
void write_byte(uint8_t b){
	printf("%2x\n", b );
}

int main(){
	write_byte(read_byte());
	return 0;
}