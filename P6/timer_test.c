#include "timer.h"


 void init_led(void){
	DDRB |= 0b00100000;
	//PORTB |= _BV(5); 
}

 void encen(void){
	PORTB |= _BV(5) ;
}
 void apaga(void){
	PORTB &= ~(_BV(5)) ;
}
 void commuta(void){
	if ((PORTB & 0b00100000) == 0)
		encen();
	else
		apaga();

}

int main(void)
{

	timer_handler_t h,h1;
	init_led();
	timer_init();
	sei();
	_delay_ms(10000);
	//h = timer_every(TIMER_MS(500), &commuta);
	h1 = timer_every(TIMER_MS(2000), commuta);
	while(true);

	return 0;

}