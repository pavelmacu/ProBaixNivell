#include "ether.h"
#include "queue.h"
#include "mtbl.h"
#include "modulator.h"
#include "timer.h"
#include "mchar.h"
#include <avr/interrupt.h>

typedef enum{START, NEXT}event;
static queue_t tx_char; 
static timer_handler_t h;
static mchar_iter_t i;
static void automat(event e);
static void e_Low(void);
static void e_Next(void);
static void e_LetterGap(void);


static queue_t cua_tx;
static mchar_t ascii;
static mchar_t morse;
static mchar_iter_t iter;
static msign_t signe;
static timer_handler_t h;

static void inici(void);
static void Dot(void);
static void Dash(void);
static void silenci(void);
static void Gap(void);
static void sistema(void);

void ether_init(void){
  timer_init();
  modulator_init();
  queue_empty(&tx_char);
}

void ether_put(uint8_t c){
	while(queue_is_full(&cua_tx));
	queue_enqueue(&cua_tx,c);
	inici();
	

}
static void inici(void){
	ascii = queue_front(&cua_tx);
	morse = mtbl_a2m(ascii);
	iter = mchar_iter(morse);
	queue_dequeue(&cua_tx);	
	sistema();
}

static void sistema(void){
	if(mchar_valid(iter)){
		modulator_set(true);
		if (mchar_next(&iter) == MDot)
			timer_after(TIMER_MS(DOT), Gap);
		}
		else if (mchar_next(&iter) == MDash){
			timer_after(TIMER_MS(DASH), Gap);
		}
	}
	else
		silenci();
	

}

/*static void Dot(void){
	modulator_set(true);
	h = timer_after(TIMER_MS(500), e_Low);}}
    else{
      if((e == START) || (e == NEXT)){
	modulator_set(true);
	h = timer_after(TIMER_MS(1500), e_Low);}}}
  else{
    h = timer_after(TIMER_MS(1000), e_LetterGap);
    queue_dequeue(&tx_char);}
}
	
static void Dash(void){
	modulator_set(true);
	timer_after(TIMER_MS(DASH), Gap);

}*/


static void silenci(void){
	//modulator_set(false);
	//timer_cancel(h);
	if(!queue_is_empty(&cua_tx))
		timer_after(TIMER_MS(LETTERGAP), inici);

}

static void Gap(void){
	modulator_set(false);
	i++;
	timer_after(TIMER_MS(DOT), sistema);

}
int main(void)
{
	ether_init();
	sei();
	ether_put('1');
	for(;;);
	
	return 0;
}
