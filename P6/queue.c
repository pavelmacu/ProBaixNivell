#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/atomic.h>


void queue_empty(queue_t *const q){
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    (*q).tail=0;
    (*q).head=0;
    (*q).count=0;
  }
}

bool queue_is_empty(const queue_t *const q){
  bool isEmpty;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    isEmpty= ((*q).count == 0);
  }
  return isEmpty;
}

bool queue_is_full(const queue_t *const q){
  bool isFull;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    isFull = ((*q).count == MAX);
  }
  return isFull;
}

void queue_enqueue(queue_t *const q, uint8_t v){
  if(!queue_is_full(q)){
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
      (*q).cua[(*q).tail]=v; 
      (*q).count++;
      if((*q).tail==MAX-1)
	(*q).tail=0;
      else
	(*q).tail++;
    }
  }
}

void queue_dequeue(queue_t *const q){
  if(!(queue_is_empty(q))){
     ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
       if((*q).head==MAX-1)
	 (*q).head=0;
       else
	 (*q).head++;
       (*q).count--;
     }
  }
}

uint8_t queue_front(const queue_t *const q){
  uint8_t valor;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    valor=(*q).cua[((*q).head)];
  }
  return valor;
}


