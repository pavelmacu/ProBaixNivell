#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>
#include <avr/io.h>
#include <pbn.h>


static pin_t D;
static pin_t B;


ISR(INT0_vect){
	EIMSK &= ~(_BV(INT0)); //Deshabilitem la interrupcio (NO SE SI CAL O NO)
	if(pin_r(D))
		pin_w(B,true);
	else
		pin_w(B,false);



}


void exp1_init(void){
	EIMSK |= (_BV(INT0)); // Interrupcio INTO enabled, INT1 not enabled
	EICRA |= (_BV(ISC00));// Any logical change on INT0 generates an interrupt request
  	D= pin_create(&PORTD,2,Input);
  	B= pin_create(&PORTB,5,Output);
}

int main(void){
	exp1_init();
	sei();
	while(true);
	return 0;

}