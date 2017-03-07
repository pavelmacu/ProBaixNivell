#include "timer.h"
#include <util/atomic.h>
//atomic block
#define N 20

// remaining: ticks que falten per fer el callback
// every: cridem callback cada 'every' ticks
// ntimes: numero de vegades que sha de cridar el callback

typedef struct{              // estructura d'entry
	uint8_t remaining, every, ntimes;
	timer_callback_t callback;
} entry_t; 


typedef struct{             // estructura de la taula
	uint8_t temps;
	bool estat, apte;	
} chronos_t;

typedef union{
  entry_t event;
  chronos_t  crono;
} unio_u;

typedef struct{
    bool is_chrono;
    unio_u index;
} cela_t;

typedef struct{

  cela_t t[N];

  uint8_t n;

}tt_t;



static tt_t entry_list;

ISR(TIMER1_COMPA_vect){
	TCNT1H = 0;
	TCNT1L = 0;
	int8_t i;
	for (i = 0; (i < N)&&(entry_list.n > 0); i++){
		if(entry_list.t[i].is_chrono==false){
			if (entry_list.t[i].index.event.every != 0){
				entry_list.t[i].index.event.remaining -= 1;
				if (entry_list.t[i].index.event.remaining == 0){
					if (entry_list.t[i].index.event.ntimes == 1){
						entry_list.t[i].index.event.callback();
						timer_cancel(i);
					}
					
					else if (entry_list.t[i].index.event.ntimes > 1){
						entry_list.t[i].index.event.callback();
						entry_list.t[i].index.event.ntimes -= 1;
						entry_list.t[i].index.event.remaining = entry_list.t[i].index.event.every;
					}
					else{
						entry_list.t[i].index.event.callback();
						entry_list.t[i].index.event.remaining = entry_list.t[i].index.event.every;
					}
				}
			}
		}
		else{
			if((entry_list.t[i].index.crono.estat == true) && (entry_list.t[i].index.crono.apte == true)){
				entry_list.t[i].index.crono.temps +=1;
			}
		}
				
	}
	if( i == 0 )
		TCNT1= 0;
		

}

void timer_init(void){
	TIMSK1 &= ~(_BV(OCIE1A));
	TCCR1A = 0b00000000;
	TCCR1B = (_BV(WGM12) | _BV(CS11) | _BV(CS10));
	OCR1A = 1249;
	TCNT1= 0;

	entry_list.n = 0;
	for (int i = 0; i < N; ++i)
		entry_list.t[i].index.event.every = 0;


}
timer_handler_t timer_after(uint8_t ticks, timer_callback_t f){
	return timer_ntimes(1,ticks,f);

}

timer_handler_t timer_every(uint8_t ticks, timer_callback_t f){
	return timer_ntimes(0,ticks,f);
}

timer_handler_t timer_ntimes(uint8_t n, uint8_t ticks, timer_callback_t f){
	timer_handler_t ret;
	TCNT1= 0;
	TIMSK1 |= (_BV(1));
  TCCR1B |= ( _BV(CS11) | _BV(CS10));
		for(int8_t i=0; i< N; i++){
			if(entry_list.t[i].is_chrono == false){
				if(entry_list.t[i].index.event.every == 0){
					entry_list.t[i].index.event.remaining = ticks;
					entry_list.t[i].index.event.ntimes = n;
					entry_list.t[i].index.event.callback = f;
					ret = i;
					entry_list.n++;				
					entry_list.t[i].index.event.every = ticks;
					return ret;
				}
			}
		}
	return TIMER_ERR;
}

void timer_cancel(timer_handler_t h){
	entry_list.t[h].index.event.every = 0;
	entry_list.n -= 1;
	if(entry_list.n == 0){
		TIMSK1 &= ~(_BV(OCIE1A));
    TCCR1B &= ~(_BV(CS11) | _BV(CS10));		
	}
}

void timer_cancel_all(void){
	TIMSK1 &= ~(_BV(1));
	for (int i = 0; i < entry_list.n; ++i){
		if(entry_list.t[i].is_chrono == true)
			entry_list.t[i].index.crono.apte == true;
		else
			timer_cancel(i);
	}
  entry_list.n = 0;
	
}

timer_chrono_t chrono(void){
		timer_handler_t ret;
    TCNT1= 0;
    TIMSK1 |= (_BV(1));
    TCCR1B |= ( _BV(CS11) | _BV(CS10));    
		for(int8_t i=0; i< N; i++){
			if(entry_list.t[i].is_chrono == false){
				if(entry_list.t[i].index.event.every == 0){
					entry_list.t[i].is_chrono = true;
					entry_list.t[i].index.crono.apte = true;
					ret = i;
					entry_list.t[i].index.crono.temps = 0;					
					entry_list.n++;
					entry_list.t[i].index.crono.estat = false;
					return ret;
				}
			}
		}
	return TIMER_ERR;
}


uint8_t chrono_get(timer_chrono_t c){
	if(entry_list.t[c].is_chrono == true)
		return entry_list.t[c].index.crono.temps;
	return 0;
}


void chrono_start(timer_chrono_t c){
	if(entry_list.t[c].is_chrono == true){
		entry_list.t[c].index.crono.temps = 0;
		entry_list.t[c].index.crono.estat = true;

	}
}

void chrono_stop(timer_chrono_t c){
	if(entry_list.t[c].is_chrono == true){
		entry_list.t[c].index.crono.estat = false;

	}
}

void chrono_cancel(timer_chrono_t c){
	if(entry_list.t[c].is_chrono == true)
		entry_list.t[c].index.crono.apte == false;
}
