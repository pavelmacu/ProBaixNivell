#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


#ifndef GPIO_DEVICE_H
#define GPIO_DEVICE_H

typedef enum{Input = 0, Output= 1 } pin_direction_t;

typedef struct{
	volatile uint8_t *port ; //= NULL;
	uint8_t pin;
} pin_t;

pin_t pin_create(volatile uint8_t *port, uint8_t pin, pin_direction_t d);

void pin_w(pin_t p, bool v);

bool pin_r(pin_t p);

void pin_toggle(pin_t p);

void pin_destroy(pin_t *const p);






#endif