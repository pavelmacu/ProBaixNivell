#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>
#include <pbn.h>
#include "control.h"


static char text;
static semaph_state_t semaf =SemOff;

int main(void)
{	
	control_init();
	ether_init();
	serial_open();
	sei();
	while(true){
		text = ether_get();
		serial_put(text);
		if(text == 'F'){
			text = ether_get();
			serial_put(text);
			if (text == 'A')
				control_force(StreetA);
			else
				control_force(StreetB);
		}
		else if (text == 'R'){
			semaf = control_get_state(StreetA);
			if(semaf == SemOff)
				control_on();
		}
		else if (text == 'H'){
			semaf = control_get_state(StreetA);
			if(semaf != SemOff)
				control_off();
		}
	}
	serial_close();
	cli();
	return 0;
}