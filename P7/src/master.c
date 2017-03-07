#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>
#include <pbn.h>
#include "control.h"

int main(void)
{
	char s[15];
	serial_open();
	control_init();
	ether_init();
	sei();
	int c=0;
	while(true){
		if(c == 0){
			print("START\r\n");
			c=1;
		}
		readline(s,15);
		if((s[0] == 'F') && (s[1] == 'A')){
			if((control_get_state(StreetA) != SemOff) && (control_get_state(StreetB) != SemOff)){
				print("OK\r\n");
				ether_put('F');
				ether_put('A');
				ether_put(' ');
				control_force(StreetA);
			}
			else
				print("COMERR\r\n");
		}
		else if((s[0] == 'F') && (s[1] == 'B')){
			if((control_get_state(StreetA) != SemOff) && (control_get_state(StreetB) != SemOff)){
				print("OK\r\n");
				ether_put('F');
				ether_put('B');
				ether_put(' ');
				control_force(StreetB);
			}
			else
				print("COMERR\r\n");		
		}
		else if((s[0] == '?') && (s[1] == 'A')){
			//estat = control_get_state(StreetA);
			if(control_get_state(StreetA) == SemClear)
				print("CLEAR\r\n");
			else if(control_get_state(StreetA) == SemApproach)
				print("APPROACH\r\n");
			else
				print("STOP\r\n");

		}
		else if((s[0] == '?') && (s[1] == 'B')){
			//estat = control_get_state(StreetB);
			if(control_get_state(StreetB) == SemClear)
				print("CLEAR\r\n");
			else if(control_get_state(StreetB) == SemApproach)
				print("APPROACH\r\n");
			else
				print("STOP\r\n");			
		}
		else if(s[0] == 'R'){
			print("OK\r\n");
			if((control_get_state(StreetA) == SemOff) && (control_get_state(StreetB) == SemOff)){
				control_on();
				ether_put('R');
				ether_put(' ');
			}
				

		}
		else if(s[0] == 'H'){
			print("OK\r\n");
			if((control_get_state(StreetA) != SemOff) && (control_get_state(StreetB) != SemOff)){
			control_off();
			ether_put('H');
			ether_put(' ');
			}	

		}
		else
			print("COMERR\r\n");
	}
	cli();
	serial_close();
	return 0;
}