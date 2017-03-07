#include "control.h"

static semaph_t semaforA;
static semaph_t semaforB;
static int ticks= 0;
static estats e;
static timer_handler_t h;

void suma(void){
	if(ticks == 80){
		e = AtoB;
		semaphore_set(&semaforA, SemApproach);

	}
	else if(ticks == 100){
		e = Bclear;
		semaphore_set(&semaforA, SemStop);
		semaphore_set(&semaforB, SemClear);
	}
	else if(ticks == 180){
		e = BtoA;
		semaphore_set(&semaforB, SemApproach);
	}
	else if(ticks == 200){
		e = Aclear;
		semaphore_set(&semaforB, SemStop);
		semaphore_set(&semaforA, SemClear);
		ticks = 0;

	}
	++ticks;

}

void control_init(void){
	
	semaph_init(&semaforA, &PORTD, 5, &PORTD, 6, &PORTD, 7);
	semaph_init(&semaforB, &PORTD, 4, &PORTC, 3, &PORTC, 2);
	e=ABoff;
	timer_init();

		

}

void control_force(street_t t){
	if(e != ABoff){
		if (t == StreetA){
			if(e == Bclear)
				ticks=180;
		}

		else{
			if(e == Aclear)
				ticks=80;
			}
		
	}
}

void control_off(void){
	semaphore_set(&semaforA, SemOff);
	semaphore_set(&semaforB, SemOff);
	e = ABoff;
	timer_cancel(h);
	

}

void control_on(void){
	e = Aclear;
	ticks = 200;
	h=timer_every(TIMER_MS(100), suma);

}

semaph_state_t control_get_state(street_t s){
	if (s == StreetA)
		return semaph_get(semaforA);
	else
		return semaph_get(semaforB);

}