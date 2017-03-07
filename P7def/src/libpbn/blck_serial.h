#ifndef BLK_SERIAL_H
#define BLK_SERIAL_H

#include "serial_device.h"
#include <string.h>
#include <ctype.h>
//#include "gpio_device.h"


void print(char s[]);

int readline(char s[], uint8_t m);

#endif