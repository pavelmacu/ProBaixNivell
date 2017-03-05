#include "codif.h"



void empty_morse_table(morse_table_t t){
	int i;
	for (i = 0; i < 64; ++i)
	{
		t[i] = '\0';
	}
}


void set_translation(morse_table_t t, char c, morse_char_t m){
	int k = 1;
	int i;
	for (i = 0; i < strlen(m); ++i)
	{
		if (m[i] == '.')
			k = 2*k;
		if (m[i] == '-')
		 	k = 2*k +1; 
	}
	t[k] = c;

}
char to_ascii(const morse_table_t t, morse_char_t m){
	int k = 1;
	int i;
	for (i = 0; i < strlen(m); ++i)
	{
		if ( m[i] == '.')
			k = 2*k;
		if (m[i] == '-')
		 	k = 2*k +1; 
	}

	if (strcmp(&t[k] , "") == 0)
		return '@';
	else
		return t[k];
}

void to_morse(const morse_table_t t, char c, morse_char_t m){
	int k = 0;
	int n = 0;
	int l = 0;
	int i;
	for (i = 0; i < 64; ++i)
	{
		if (c == t[i])
			k =i;
	}
	if (t[k] == '\0')
		m = "";
	else{
		while (k>1){
			if (k%2 == 0){
				if(k>31){
					n =4;
					++l;}
				if (k>15 && k<=31){
					n = 3;
					++l;}
				if(k>7 && k<=15){
					n = 2;
					++l;}
				if (k>3 && k<=7){
					n =1;
					++l;}
				if(k>0 && k<=3){
					n = 0;
					++l;}
				k = k/2;
				m[n] = '.';

			}
			else{

				if(k>31){
					n =4;
					++l;}
				if (k>15 && k<=31){
					n = 3;
					++l;}
				if(k>7 && k<=15){
					n =2;
					++l;}
				if (k>3 && k<=7){
					n = 1;
					++l;}
				if(k>0 && k<=3){
					n = 0;
					++l;}
				k =(k-1)/2;
				m[n] = '-';
			
			}
		}
			m[l] = '\0';
	
	}
	
}

