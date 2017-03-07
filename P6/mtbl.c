#include "mtbl.h"
#include <stdio.h>

static mchar_t mchar_table[] = {
  mchar(01), //A
  mchar(1000), //B
  mchar(1010), //C
  mchar(100), //D
  mchar(0), //E
  mchar(0010), //F
  mchar(110), //G
  mchar(0000), //H
  mchar(00), //I
  mchar(0111), //J
  mchar(101), //K
  mchar(0100), //L
  mchar(11), //M
  mchar(10), //N
  mchar(111), //O
  mchar(0110), //P
  mchar(1101), //Q
  mchar(010), //R
  mchar(000), //S
  mchar(1), //T
  mchar(001), //U
  mchar(0001), //V
  mchar(011), //W
  mchar(1001), //X
  mchar(1011), //Y
  mchar(1100), //Z
  mchar(11111), //0
  mchar(01111), //1
  mchar(00111), //2
  mchar(00011), //3
  mchar(00001), //4
  mchar(00000), //5
  mchar(10000), //6
  mchar(11000), //7
  mchar(11100), //8
  mchar(11110), //9
  mchar(01010)}; //Espai

char mtbl_m2a(mchar_t c){
  int posicio = 0;
  bool trobat = false;
  while(!trobat){
    if(posicio > 36)
      trobat = true;
    else if(mchar_table[posicio] == c)
      trobat = true;
    else
      ++posicio;}
  if(posicio < 25) //A la pos.25 acaben les lletres
    return (char)(posicio+65);
  else if(posicio == 36) //Espai
    return ' ';
  else if(posicio == 37) //Morse no esta a la taula
    return '\0';
  else
    return (char)(posicio-26+48); //Treiem el nombre amb ascii
}

mchar_t mtbl_a2m(char c){
  int posicio;
  if(c >= 65) //Lletres
    posicio = c-65;
  else if(c == 32) //Espai
    posicio = 36;
  else if((c >= 48) && (c <=57))//Nombres
    posicio = c-48+26;
  else //Caracter no esta a la taula
    return mchar_empty;
  return mchar_table[posicio];
}

	int comptador;

	if (c==' '){morse=taula[36];}

	else if ((c>='0') && (c<='9')){
	    comptador=c-48+26;
	    morse=taula[comptador];
	}

	else{
	    comptador=c-65;
	    morse=taula[comptador];
	}

	  return morse;
 
}
/*int main(void)
{
  mchar_t m;
  m = mtbl_a2m('W');
  mchar_iter_t i = mchar_iter(m);
  while(mchar_valid(i)){
    if(mchar_next(&i) == MDot)
      printf(".");
    else
      printf("-");
  }
  printf("\n");
  return 0;
}*/