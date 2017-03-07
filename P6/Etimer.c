#include "timer.h"
#include <util/atomic.h>
//atomic block
#define N 20

// remaining: ticks que falten per fer el callback
// every: cridem callback cada 'every' ticks
// ntimes: numero de vegades que sha de cridar el callback

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
	int i;
	for (i = 0; (i < N)&&(entry_list.n > 0); i++){
		if (entry_list.t[i].every != 0){
			entry_list.t[i].remaining -= 1;
			if (entry_list.t[i].remaining == 0)
			{
				if (entry_list.t[i].ntimes == 1)
					timer_cancel(i);
				
				else if (entry_list.t[i].ntimes > 1)
				{
					entry_list.t[i].ntimes -= 1;
					entry_list.t[i].remaining = entry_list.t[i].every;
				}
				else
					entry_list.t[i].remaining = entry_list.t[i].every;
				entry_list.t[i].callback();
			}

		}
		
	}
	if( i == 0 )
		TCNT1= 0;
		

	

}

void timer_init(void){

	TCCR1A = 0b01000000;
	TCCR1B = 0b00001011;
	OCR1A = 2500;
	//TIMSK1 &= ~(_BV(1));
	TCNT1= 0;

	entry_list.n = 0;
	for (int i = 0; i < N; ++i)
	{
		entry_list.t[i].remaining = 0;
		entry_list.t[i].every = 0;
		entry_list.t[i].ntimes = 0;
	}
}
timer_handler_t timer_after(uint8_t ticks, timer_callback_t f){
	return timer_ntimes(1,ticks,f);

}

timer_handler_t timer_every(uint8_t ticks, timer_callback_t f){
	return timer_ntimes(0,ticks,f);
}

timer_handler_t timer_ntimes(uint8_t n, uint8_t ticks, timer_callback_t f){
	timer_handler_t ret;
	TCNT1= 1;
	TIMSK1 |= (_BV(1));
		for(int i=0; i< N; i++){
			if(entry_list.t[i].every == 0){
				entry_list.t[i].remaining = ticks;
				entry_list.t[i].ntimes = n;
				entry_list.t[i].callback = f;
				ret = i;
				entry_list.n++;
				entry_list.t[i].every = ticks;
				return ret;
			}
		}
	
		return TIMER_ERR;
}

void timer_cancel(timer_handler_t h){
	entry_list.t[h].every = 0;
	entry_list.n -= 1;
	if(entry_list.n == 0){
		TCCR1B = 0b00001000;
		TIMSK1 &= ~(_BV(1));
	}
}

void timer_cancel_all(void){
	TIMSK1 &= ~(_BV(1));
	for (int i = 0; i < entry_list.n; ++i)
		timer_cancel(i);
	TCCR1B = 0b00001000;
}