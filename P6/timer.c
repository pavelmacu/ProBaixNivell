#include "timer.h"
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#define N 20

typedef struct{
  uint8_t remaining, every, ntimes;
  timer_callback_t callback;
} entry;

typedef struct{
  entry t[N];
  uint8_t n; 
} tt;

static tt entry_list;

ISR(TIMER1_COMPA_vect){
  TCNT1H = 0;
  TCNT1L = 0;
  int8_t i=0;
  for(;(i<N)&&(entry_list.n>0);i++){
    if(entry_list.t[i].every!=0){
      entry_list.t[i].remaining--;
      if(entry_list.t[i].remaining==0){
	if(entry_list.t[i].ntimes==0){
	  entry_list.t[i].callback();
	  entry_list.t[i].remaining=entry_list.t[i].every;
	}
	else if(entry_list.t[i].ntimes==1){
	  entry_list.t[i].callback();
	  timer_cancel(i);
	}
	else{
	  entry_list.t[i].callback();
	  entry_list.t[i].ntimes--;
	  entry_list.t[i].remaining=entry_list.t[i].every;
	}
      }
    }
  }
  if(i==0){
     TCNT1H = 0;
     TCNT1L = 0;
  }
}
void timer_init(void){
  /*Inicialitzar timer de 16 bits que vagi contant cada tick*/
  TIMSK1 &= ~(_BV(OCIE1A));//Deshabilito interrupcions
  TCCR1B|=(_BV(WGM12));//Activo OCCR1A
  TCCR1B|=(_BV(CS11));//Prescaler
  TCCR1B|=(_BV(CS10));
  TCNT1H = 0; //Comptador del timer a 0
  TCNT1L = 0;
  OCR1A = 2499;
  entry_list.n=0;
  int i=0;
  /*Iicialtzar tots els entrys amb seus parametres a zero*/
  for(;i<N;i++){
    entry_list.t[i].every=0;
  }
}

timer_handler_t timer_after(uint8_t ticks, timer_callback_t f){
  return timer_ntimes(1,ticks,f);
}

timer_handler_t timer_every(uint8_t ticks, timer_callback_t f){
  return timer_ntimes(0,ticks,f);
}

timer_handler_t timer_ntimes(uint8_t n,uint8_t ticks, timer_callback_t f){
  timer_handler_t id;
  int8_t i=0;
  if(entry_list.n==0){
    TCNT1H = 0; //Comptador del timer a 0
    TCNT1L = 0;
    TIMSK1|=(_BV(OCIE1A));}
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    for(;i<N;i++){
      if (entry_list.t[i].every==0){
	entry_list.t[i].remaining=ticks;
	entry_list.t[i].every=ticks;
	entry_list.t[i].ntimes=n;
	entry_list.t[i].callback=f;
	entry_list.n++;
	id=i;
	return id;}
    }
    }
  return TIMER_ERR;
}

void timer_cancel(timer_handler_t h){
  entry_list.t[h].every=0;
  entry_list.n--;
  if(entry_list.n==0){
    TIMSK1 &= ~(_BV(OCIE1A));
  }
}

void timer_cancel_all(void){
  TIMSK1 &= ~(_BV(OCIE1A));
  int i=0; 
  for(;i<N;i++)
    entry_list.t[i].every=0;
  entry_list.n=0;
}
