#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>
#include <pbn.h>


void so_init(void){
	DDRB |= 0b00101000;
	PORTB &= 0b11111111;
}


void commuta_so(void){
	if ((PORTB | 0b11110111) == 0b11110111)
		modulator_set(true);
}

int main(void)
{
	so_init();
	ether_init();
	modulator_init();
	sei();
	timer_every(TIMER_MS(300),commuta_so);
	while(true){
		//_delay_ms(300);
		//modulator_set(true);

		//_delay_ms(300);
		//modulator_set(false);
		


	};
	return 0;
}