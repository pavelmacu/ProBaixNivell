#include "controlsem.h"

static tickstate ticks;

void controlsem_init(){
	ticks.state=0;
	ticks.TClear = 40;
	ticks.TApproach = 10;
	ticks.TStop=60;
}

void tick_monitor(void){
	uint8_t ordre_supervisor;

	if (serial_can_read()){
		ordre_supervisor=serial_get();
	

		if (ordre_supervisor == 69 && ticks.state != 0  /*E en ASCII*/){
			ticks.state = 2;
			semaphore_set(ticks.state); // Posa el semàfor en VERD
			serial_put(32); // ESPAI
			serial_put(69); //E
			serial_put(77); //M
			serial_put(69); //E
			serial_put(82); //R
			serial_put(71); //G
			serial_put(69); //E
			serial_put(78); //N
			serial_put(67); //C
			serial_put(89); //Y
			serial_put(32); // ESPAI
		}
		if (ordre_supervisor == 83 && ticks.state != 0 /*S en ASCII*/){
			ticks.state = 0;
			semaphore_set(ticks.state); // Atura el semàfor
			serial_put(32); // ESPAI
			serial_put(83); //S
			serial_put(72); //H
			serial_put(85); //U
			serial_put(84); //T
			serial_put(68); //D
			serial_put(79); //O
			serial_put(87); //W
			serial_put(78); //N
			serial_put(32); // ESPAI
		}
		if (ordre_supervisor == 82 /*R en ASCII*/){
			ticks.state = 2;
			semaphore_set(ticks.state); // Reseteja el semafor a verd
			serial_put(32); // ESPAI
			serial_put(82); //R
			serial_put(69); //E
			serial_put(83); //S
			serial_put(84); //T
			serial_put(65); //A
			serial_put(82); //R
			serial_put(84); //T
			serial_put(32); // ESPAI		
		}
    }

}

void tick_semaphore(void){
	if(ticks.state != 0){
		if (ticks.state == 2){
			ticks.TClear -= 1;
			if (ticks.TClear == 0){
				semaphore_next();
				ticks.TClear = 40;
				ticks.state = 3;
			}
		}
		else if (ticks.state == 3){
			ticks.TApproach -= 1;
			if (ticks.TApproach == 0){
				semaphore_next();
				ticks.TApproach = 10;
				ticks.state = 4;
			}
		}
		else if (ticks.state == 4){
			ticks.TStop -= 1;
			if (ticks.TStop == 0){
				semaphore_next();
				ticks.TStop = 60;
				ticks.state = 2;
			}
		}	

	}

}
