#ifndef CONTROL_H
#define CONTROL_H

#include <pbn.h>

#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum{StreetA, StreetB} street_t;

typedef enum{Aclear,Bclear, AtoB, BtoA, ABoff} estats;

void control_init(void);

void control_force(street_t t);

void control_off(void);

void control_on(void);

semaph_state_t control_get_state(street_t s);


#endif