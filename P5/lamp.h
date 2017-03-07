#ifndef LAMP_H
#define LAMP_H

#include "gpio_device.h"


typedef enum{Green, Yellow, Red} color_t;

typedef struct {
	pin_t green;
	pin_t yellow;
	pin_t red;
} lamp_t;

void lamp_init(lamp_t *const l, 
		volatile uint8_t *prtg, uint8_t pg, 
		volatile uint8_t *prty, uint8_t py,
		volatile uint8_t *prtr, uint8_t pr);

void lamp_on(lamp_t l, color_t c);

void lamp_off(lamp_t l, color_t c);

void lamp_toogle(lamp_t l, color_t c);

bool lamp_is_on(lamp_t l, color_t c);



#endif