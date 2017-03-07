#include "mtbl.h"



static mchar_t taula[] = {

  mchar(01), //a

  mchar(1000), //b

  mchar(1010),	//c

  mchar(100), //d

  mchar(0), //e

  mchar(0010),//f

  mchar(110),//g

  mchar(0000),//h

  mchar(00),//i

  mchar(0111),//j

  mchar(101),//k

  mchar(0100),//l

  mchar(11),//m

  mchar(10),//n

  mchar(111),//o

  mchar(0110),//p

  mchar(1101),//q

  mchar(010),//r

  mchar(000),//s

  mchar(1),//t

  mchar(001),//u

  mchar(0001),//v

  mchar(011), //w

  mchar(1001),//x

  mchar(1011),//Y

  mchar(1100),//z

  mchar(11111), //0

  mchar(01111),//1

  mchar(00111),//2

  mchar(00011), //3

  mchar(00001),//4

  mchar(00000),//5

  mchar(10000),//6

  mchar(11000),//7

  mchar(11100),//8

  mchar(11110),//9

  mchar(01010)// 'espai '

  };



char mtbl_m2a(mchar_t c){

  char ascii = 0;
  int i;

  for (i = 0; taula[i] != c ; i++)
  	ascii++;

  if (ascii == 36) 
		ascii = 32;
  else if (ascii > 25 && ascii < 37)
      ascii += 22;
  else if (ascii <= 25)
    	ascii += 65;
  else
   		ascii = 0;

  return ascii;

}

mchar_t mtbl_a2m(char c){
	int comptador;
  if(c >= 65)
    comptador = c -65;
  else if(c == 32)
    comptador = 36;
  else if((c >=48) && (c <=57))
    comptador= c-48+26;
  else
    return mchar_empty(taula);
  return taula[comptador];

	/*if (c==' '){morse=taula[36];}

	else if (c>='0' && c<='9'){
	    comptador=c-48+26;
	    morse=taula[comptador];
	}

	else{
	    comptador=c-65;
	    morse=taula[comptador];
	}

	  return morse;*/
 
}
/*int main(void)
{
  mchar_t m;
  m = mtbl_a2m('0');
  mchar_iter_t iter;
  iter = mchar_iter(m);
  printf("%d\n", iter.mask );
  printf("%d\n", iter.m );
  printf("%d\n", iter.sentinel );

 
  while(mchar_valid(iter)){
    if(mchar_next(&iter) == MDot)
      printf(".");
    else
      printf("-");
  }
  printf("\n");
  return 0;
}*/