#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

#define MAXLEN 25

typedef struct{
	uint8_t queue[MAXLEN];
	int head;
	int tail;
} queue_t;

void queue_empty(queue_t *const q);


bool queue_is_empty(const queue_t *const q);

bool queue_is_full(const queue_t *const q);

void queue_enqueue(queue_t *const q, uint8_t v);

void queue_dequeue(queue_t *const q);

uint8_t queue_front(const queue_t *const q);

#endif 