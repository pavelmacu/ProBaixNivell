#ifndef MTBL_H
#define MTBL_H


#include "mchar.h"

typedef char morse_table_t[64];

void empty_morse_table(morse_table_t t);

void set_translation(morse_table_t t, char c,mchar_t m);

char mtbl_m2a(mchar_t c);

mchar_t mtbl_a2m(char c);

#endif