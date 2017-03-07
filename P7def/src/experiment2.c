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
static int8_t votacio, tau;

typedef enum{Alt, Baix} state;
static state estat;



void exp2_init(void){
	EIMSK |= _BV(INT0); // Interrupcio INTO enabled, INT1 not enabled
	EICRA |= _BV(ISC00);// Any logical change on INT0 generates an interrupt request
  	EICRA &= ~(_BV(ISC01));
  	D= pin_create(&PORTD,2,Input);
  	B= pin_create(&PORTB,5,Output);
  	pin_w(B, false);
  	estat = Baix;
}

void wait(int8_t i){
	if(i == 0)
		_delay_us(2);
	else if (i ==1)
		_delay_us(4);
	else if (i ==2);
		_delay_us(8);
	
}

ISR(INT0_vect){
	//EIMSK &= ~(_BV(INT0));//Deshabilitem la interrupcio (NO SE SI CAL O NO)
	
	votacio = 0;
	for(tau=0;tau<3;tau++){
		wait(tau);
		if(pin_r(D))
			++votacio;
		else
			--votacio;
	}	

	if((votacio > 0) && (estat == Baix)){
		//pin_w(B,true);
		pin_toggle(B);
		estat = Alt;
	}
	else if((votacio < 0) && (estat == Alt)){
		pin_toggle(B);
		estat= Baix;
	}

	EIFR |= _BV(INTF0);
	// cli(); -- Cancelar interrupcions pendents?

}

int main(void){
	exp2_init();
	sei();
	while(true);
	return 0;

}
