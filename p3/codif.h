#ifndef CODIF_H
#define CODIF_H

#include <stdio.h>
#include <string.h> 

typedef char morse_char_t[6];

typedef char morse_table_t[64];


void empty_morse_table(morse_table_t t);
void set_translation(morse_table_t t, char c,morse_char_t m);
char to_ascii(const morse_table_t t, morse_char_t m);
void to_morse(const morse_table_t t, char c, morse_char_t m);



#endif