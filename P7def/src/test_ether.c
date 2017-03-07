#include <pbn.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>
#include <avr/io.h>


static char text;


int main(void)
{	
	ether_init();
	serial_open();
	sei();
	while(true){
		text = ether_get();
		serial_put(text);

	}
	return 0;
}


