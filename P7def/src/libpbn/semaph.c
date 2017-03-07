#include "semaph.h"


void semaph_init(semaph_t *const s,
			volatile uint8_t *port_green, uint8_t pin_green,
			volatile uint8_t *port_yell, uint8_t pin_yell,
			volatile uint8_t *port_red, uint8_t pin_red){

	
	(*s).s = SemOff;
	lamp_init(&((*s).l),port_green, pin_green, port_yell, pin_yell,port_red, pin_red);

}

void semaphore_set(semaph_t *const sem, semaph_state_t s){
	(*sem).s = s;
	if(s == SemOff){
		lamp_off((*sem).l, Green);
		lamp_off((*sem).l, Yellow);
		lamp_off((*sem).l, Red);
	}
	else if(s == SemClear){
		lamp_on((*sem).l, Green);
		lamp_off((*sem).l, Yellow);
		lamp_off((*sem).l, Red);
	}
	else if(s == SemApproach){
		lamp_off((*sem).l, Green);
		lamp_on((*sem).l, Yellow);
		lamp_off((*sem).l, Red);
	}
	else if(s == SemStop){
		lamp_off((*sem).l, Green);
		lamp_off((*sem).l, Yellow);
		lamp_on((*sem).l, Red);
	}
}


semaph_state_t semaph_get(const semaph_t sem){
	return sem.s;
}








