#include "mchar.h"


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

/*
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