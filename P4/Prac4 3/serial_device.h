#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H

void serial_init(void);

uint8_t serial_get(void);

void serial_put(uint8_t c);

bool serial_can_read(void);




#endif