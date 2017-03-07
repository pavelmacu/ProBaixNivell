#include "serial_device.h"
#include "semaphore.h"



#ifndef CONTROLSEM_H
#define CONTROLSEM_H


typedef struct{
	semaphore_state_t state;
	int TClear;
	int TApproach;
	int TStop;
} tickstate;

void controlsem_init();

void tick_monitor(void);

void tick_semaphore(void);


#endif