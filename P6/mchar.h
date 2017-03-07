#ifndef MCHAR_H
#define MCHAR_H
#include <stdint.h>
#include <stdbool.h>

/**/
typedef enum {MDot, MDash} msign_t;

/**/
typedef uint8_t mchar_t;

#define mchar(c) (mchar_t)((0b##c << (8 - sizeof(#c)+1)) | (sizeof(#c)-1))

#define mchar_len(m) (uint8_t)(m & 0x7)

#define mchar_empty (mchar_t)0

/**/
mchar_t mchar_add(mchar_t m, msign_t s);

/**/
typedef struct{
  mchar_t m;
  uint8_t mask, sentinel;
} mchar_iter_t;

/**/
mchar_iter_t mchar_iter(mchar_t m);

/**/
msign_t mchar_next(mchar_iter_t *const i);

/**/
bool mchar_valid(mchar_iter_t i);

#endif
