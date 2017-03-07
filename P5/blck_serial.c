#include "blck_serial.h"


void print(char s[]){
	int i = 0;
	while((s[i] != '\0')){
			serial_put(s[i]);
			i++;
	}

	

}

int readline(char s[], uint8_t m){
	char n;
	int i=0;
	while(true){
		n = serial_get();
		if(isgraph(n) && (i!=m)){
			s[i] = n;
			i++;
			if(i==m)
				break;
		}
		else
			break;
	}
	s[m] = '\0';
	return i;

}
