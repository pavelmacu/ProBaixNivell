#include "timer.h"
#include <pbn.h>


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
	pin_t verd,groc, vermell;
	verd=pin_create(&PORTD,5, Output);
	groc=pin_create(&PORTD,6, Output);
	vermell=pin_create(&PORTD,7, Output);
	timer_init();
	uint8_t temps;
	sei();
	timer_chrono_t crono;
	crono = chrono();
	chrono_start(crono);
	_delay_ms(90);
	//chrono_stop(crono);
	//_delay_ms(50);
	temps=chrono_get(crono);
	if(temps == 18){
		pin_w(verd,true);
		pin_w(groc,false);
		pin_w(vermell,false);
	}
	else{
		pin_w(verd,false);
		pin_w(groc,false);
		pin_w(vermell,true);
	}


	return 0;

}