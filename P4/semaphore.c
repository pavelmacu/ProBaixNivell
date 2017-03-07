#include "semaphore.h"

semaphore_state_t state;

//verd = 2, vermell = 4, groc = 3
 pin_t LED_VERD; 
 pin_t LED_GROC ; 
 pin_t LED_VERMELL ; 



void semaphore_init(void){
	state= 0;

 	LED_VERD = pin_create(&PORTD, 5, Output);
 	LED_GROC = pin_create(&PORTD, 6, Output);
 	LED_VERMELL = pin_create(&PORTD, 7, Output);
	pin_w(LED_VERD, false);
	pin_w(LED_GROC, false);
	pin_w(LED_VERMELL, false);
	}

void semaphore_next(void){
	if (state == 2){
		++state;
		pin_w(LED_VERD, false);
		pin_w(LED_GROC, true);
	}

	else if (state == 3){
		++state;
		pin_w(LED_GROC, false);
		pin_w(LED_VERMELL, true);
	}
	else if (state==4){
		pin_w(LED_VERMELL, false);
		pin_w(LED_VERD, true);
		state=2;
	}
	}

void semaphore_set(semaphore_state_t s){
	state=s;
	if (s == 0){
		semaphore_init();
	}
	else if (s == 2){
		pin_w(LED_VERD, true);
		pin_w(LED_GROC, false);
		pin_w(LED_VERMELL, false);
	}
	else if (s == 3){
		pin_w(LED_VERD, false);
		pin_w(LED_GROC, true);
		pin_w(LED_VERMELL, false);
	}
	else if (s == 4){
		pin_w(LED_VERD, false);
		pin_w(LED_GROC, false);
		pin_w(LED_VERMELL, true);
	}
	}

	/*int  main(void)
	{
		
		semaphore_init();
		state =  2;
		for(int i=0; i < 100; i++){
		semaphore_set(state);
		_delay_ms(500);
		semaphore_next();
		_delay_ms(500);
		semaphore_next();
		_delay_ms(500);
	}

		return 0;
	}*/