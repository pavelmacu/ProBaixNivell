/*#include "mchar.h"


mchar_t mchar_add(mchar_t m, msign_t s){
	uint8_t i = 1;
	if(mchar_len(m) < 5){
		if (s == MDot){
			i = i << (7- mchar_len(m));
			i ^=  0b11111111;
			m &= i;
			//m &= ~(_BV(7-mchar_len(m)));
		}
		else{
			i = i << (7- mchar_len(m));
			m |= i;
		}

	}
	return m;
}

mchar_iter_t mchar_iter(mchar_t m){
	uint8_t mida = mchar_len(m);
	mchar_iter_t iter;
	iter.m = m;
	iter.mask = 0b10000000;//_BV(7);
	iter.sentinel = 0b10000000 >> (mida);
	return iter;
}

msign_t mchar_next(mchar_iter_t *const i){
	msign_t signe;
	if(((*i).m & (*i).mask) == 0)
		signe = MDot;
	else
		signe = MDash;
	(*i).mask = (*i).mask >> 1;
	return signe;

}

bool mchar_valid(mchar_iter_t i){
	return !(i.mask == i.sentinel);

}


int main(void)
{
	mchar_t  morse;
	morse = 0b11111101;
	mchar_iter_t iter;
	iter = mchar_iter(morse);
	printf("%d\n", iter.mask );
	printf("%d\n", iter.m );
	printf("%d\n", iter.sentinel );

	while(mchar_valid(iter)){
		if (mchar_next(&iter)== MDot)
			printf(".\n");
		else
			printf("-\n");
	}
	return 0;

}*/


#include "mchar.h"

#include <stdio.h>

mchar_t mchar_add(mchar_t m, msign_t s){

  uint8_t last_sign = mchar_len(m);

  mchar_t mchar_return = mchar_empty;

  if(last_sign >= 5)

    return 0;

  else{

    mchar_return |= m;

    mchar_return &= 0b11111000; 

    mchar_return |= (last_sign+1);

    if(s == MDot)

      mchar_return &= ~(1 << (8-last_sign-1)); //Desplaçar 0 a seg.pos

    else

      mchar_return |= (1 << (8-last_sign-1));} //Desplaçar 1 a seg.pos

  return mchar_return; 

}

mchar_iter_t mchar_iter(mchar_t m){

  uint8_t last_sign = mchar_len(m); 

  mchar_iter_t mchar_ret;

  mchar_ret.m = m;

  mchar_ret.sentinel = 0b10000000 >> (last_sign);

  mchar_ret.mask = 0b10000000; //Si mchar buit, mask == sentinel

  return mchar_ret;

}

msign_t mchar_next(mchar_iter_t *const i){

  msign_t ret_sign;

  if(((*i).mask & (*i).m) != 0)

    ret_sign = MDash;

  else

    ret_sign = MDot;

  (*i).mask = (*i).mask >> 1;

  return ret_sign;

}

bool mchar_valid(mchar_iter_t i){

  if(i.mask == i.sentinel)

    return false;

  else 

    return true;

}

