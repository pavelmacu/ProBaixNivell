#ifndef ETHER_H
#define ETHER_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>	
#include <stdbool.h>

#include "queue.h"
#include "mtbl.h"
#include "mchar.h"
#include "modulator.h"
#include "timer.h"
#include "gpio_device.h"

#include "serial_device.h"

void ether_init(void);

void ether_put(uint8_t c);

bool ether_can_read(void);

uint8_t ether_get(void);


#endif