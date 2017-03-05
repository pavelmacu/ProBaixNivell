#include "itu.h"
#include <fcntl.h>
#include <stdio.h>

#ifndef STREAMENCODE_H
#define STREAMENCODE_H

void streamencoder_init(void);
void do_codifica(FILE *in, FILE *out);
void do_descodifica(FILE *in, FILE *out);


#endif


