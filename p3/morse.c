#include "morse.h"
#include <stdio.h>


int main(int argc, char *argv[]){


	streamencoder_init();

	if (argc == 1)
	{
		 do_codifica(stdin, stdout);
	}
	if (argc == 2)
	{
		if (strcmp(argv[1] , "-d") == 0)
		{
			do_descodifica(stdin, stdout);
		}
		else 
			do_codifica(stdin, stdout);
	}
	
	return 0;
}