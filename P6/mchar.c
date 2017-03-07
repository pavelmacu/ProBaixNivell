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
	mchar_iter_t iter;
	iter.m = m;
	iter.mask = 0b10000000;//_BV(7);
	iter.sentinel = (0b10000000 >> (mchar_len(m)));
	return iter;
}

msign_t mchar_next(mchar_iter_t *const i){
	msign_t signe;
	if(((*i).m & (*i).mask) == 0)
		signe = MDot;
	else
		signe = MDash;
	(*i).mask = ((*i).mask >> 1);
	return signe;

}

bool mchar_valid(mchar_iter_t i){
	return (i.mask > i.sentinel);

}
void print_morse(mchar_t m){
  mchar_iter_t i = mchar_iter(m);
  while(mchar_valid(i)){
    if(mchar_next(&i) == MDot)
      printf(".");
    else
      printf("-");}
  printf("\n");
}
