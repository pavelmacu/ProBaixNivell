#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>

#define TIMER_MS(ms) (ms/5)
#define TIMER_ERR (timer_handler_t)-1

typedef void (*timer_callback_t)(void);

typedef int8_t timer_handler_t;

void timer_init(void);

timer_handler_t timer_after(uint8_t ticks, timer_callback_t f);

timer_handler_t timer_every(uint8_t ticks, timer_callback_t f);

timer_handler_t timer_ntimes(uint8_t n, uint8_t ticks, timer_callback_t f);

void timer_cancel(timer_handler_t h);


void timer_cancel_all(void);

#endif

