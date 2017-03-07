#include "control.h"

static semaph_t semaforA;
static semaph_t semaforB;
static int ticks= 0;
static estats e;

ISR(TIMER1_COMPA_vect){
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
	TCNT1H = 0;
	TCNT1L = 0;

}

void control_init(void){
	
	semaph_init(&semaforA, &PORTD, 5, &PORTD, 6, &PORTD, 7);
	semaph_init(&semaforB, &PORTD, 4, &PORTC, 3, &PORTC, 2);

	TCCR1A = 0b00000000;
	TCCR1B = 0b00001100;
	OCR1A = 6250;
	TIMSK1 &= ~(_BV(1));
	e=ABoff;
	

		

}

void control_force(street_t t){
	if(e != ABoff){
		if (t == StreetA){
			semaphore_set(&semaforA, SemClear);
			if(e == Bclear)
				ticks=180;
			else if((e == Aclear) || (e == AtoB))
				ticks =200;
		}

		else{
			semaphore_set(&semaforB, SemClear);
			if(e == Aclear)
				ticks=80;
			else if((e == Bclear) || (e == BtoA))
				ticks =100;
			}
		
	}
}

void control_off(void){
	semaphore_set(&semaforA, SemOff);
	semaphore_set(&semaforB, SemOff);
	e = ABoff;
	TIMSK1 &= 0B11111101;
	TCNT1H = 0;
	TCNT1L = 0;

}

void control_on(void){
	e = Aclear;
	ticks = 200;
	TIMSK1 |= 0b00000010;
	TCNT1H = 0;
	TCNT1L = 0;

}

semaph_state_t control_get_state(street_t s){
	if (s == StreetA)
		return semaph_get(semaforA);
	else
		return semaph_get(semaforB);


}

