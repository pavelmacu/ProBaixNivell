#include "streamencode.h"




morse_table_t itu_table;



void streamencoder_init(void){
		itu_init();
	}



void do_codifica(FILE *in, FILE *out){

	char caracter;
	morse_char_t seq_morse;
	
	caracter = fgetc(in);
	
	while (caracter != EOF){
		if (caracter == ' ')
		{
			to_morse(itu_table, caracter, seq_morse);
			fputs(" ", out);
			seq_morse[0] = '\0';
			seq_morse[1] = '\0';
			seq_morse[2] = '\0';
			seq_morse[3] = '\0';
			seq_morse[4] = '\0';
			seq_morse[5] = '\0';
			


		}
		else if (caracter == '\n'){
			to_morse(itu_table, caracter, seq_morse);
		    fputs("\n",out);
				seq_morse[0] = '\0';
				seq_morse[1] = '\0';					
				seq_morse[2] = '\0';
				seq_morse[3] = '\0';
				seq_morse[4] = '\0';
				seq_morse[5] = '\0';
		}


		else{
		to_morse(itu_table, caracter, seq_morse);
		fputs(seq_morse, out);
		fputs(" ", out);
		}

		caracter = fgetc(in);
	}
		fputs("\n",out);
		

}



void do_descodifica(FILE *in, FILE *out){

	char aux;
	char caracter;
	int i = 0;
	morse_char_t seq_morse;
	seq_morse[0] = '\0';
	seq_morse[1] = '\0';
	seq_morse[2] = '\0';
	seq_morse[3] = '\0';
	seq_morse[4] = '\0';
	seq_morse[5] = '\0';
	

	caracter  = fgetc(in);

	while(caracter != EOF){

		if(caracter== ' '){
			if (seq_morse[0] == '\0')
			{
				fprintf(out, "%s", " ");
				
			}
			else
			{
				fprintf(out, "%c", to_ascii(itu_table, seq_morse) );
				seq_morse[0] = '\0';
				seq_morse[1] = '\0';
				seq_morse[2] = '\0';
				seq_morse[3] = '\0';
				seq_morse[4] = '\0';
				seq_morse[5] = '\0';
				i =0;
			}
		}


		else if(caracter == '\n')
		{
			if (seq_morse[0] == '\0')
			{
				fprintf(out, "%c", '\n');
				
			}
			else
			{
				fprintf(out, "%c\n", to_ascii(itu_table, seq_morse) );
				seq_morse[0] = '\0';
				seq_morse[1] = '\0';
				seq_morse[2] = '\0';
				seq_morse[3] = '\0';
				seq_morse[4] = '\0';
				seq_morse[5] = '\0';
				i = 0;
				
			
			}
		}


		else{
			seq_morse[i] = caracter;
			++i;
			
			
		}
		caracter  = fgetc(in);
		aux = caracter;


	}
	fprintf(out, "%c", '\n');

}


