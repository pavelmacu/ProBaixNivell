#include "ether.h"


#define DOT 90
#define DASH 3*DOT
#define LETTERGAP 2*DOT

static queue_t tx_char;

static timer_chrono_t crono;
static queue_t cua_rx;
static queue_t cua_tx;
typedef enum{FEdge, REdge, STimeOut}I2_event_t;
typedef enum{RxLGap, RxDD, RxSGap}I2_estat_t;
static I2_estat_t current_state_I2;
static timer_handler_t g;
static void I2_event(I2_event_t e);
static void raise_stimeout(void);
static mchar_t morse;

typedef enum{INICI, SEG}event;

static mchar_t ascii;
static mchar_t morse;
static mchar_iter_t iter;
//static msign_t signe;
static timer_handler_t h, g;
static void aux(void);
static void silenci(void);
static void Gap(void);
static void sistema(event e);

typedef enum{Alt, Baix}state;
static state estat;
static int8_t votacio, tau;
static void wait(int8_t tau);
static pin_t D, B;

void wait(int8_t tau){
  if (tau==0)
    _delay_us(2);
  else if(tau==1)
    _delay_us(2);
  else
    _delay_us(4);
}

ISR(INT0_vect){

	votacio = 0;
	for(tau=0;tau<3;tau++){
		wait(tau);
		if(pin_r(D))
			++votacio;
		else
			--votacio;
	}	

	if((votacio > 0) && (estat == Baix)){
		pin_toggle(B);
		I2_event(REdge);
		estat = Alt;
	}
	else if((votacio < 0) && (estat == Alt)){
		pin_toggle(B);
		I2_event(FEdge);
		estat= Baix;
	}

	EIFR |= _BV(INTF0);

}

void ether_init(void){
  timer_init();
  modulator_init();
  queue_empty(&tx_char);
  queue_empty(&cua_rx);
  crono = chrono();
  EICRA &= ~(_BV(ISC01));
  EICRA |=_BV(ISC00);
  EIMSK|=_BV(INT0);
  D = pin_create(&PORTD, 2, Input);
  B = pin_create(&PORTB, 5, Output); 
  estat = Baix;
  current_state_I2= RxLGap;
  
}

bool ether_can_read(void){
  return !(queue_is_empty(&cua_rx));
}

uint8_t ether_get(void){
  while(!ether_can_read());
  uint8_t caracter = queue_front(&cua_rx);
  queue_dequeue(&cua_rx);
  return caracter;
}


void I2_event(I2_event_t e){
	//uint8_t tr; //Ens marca l'estat en el que estem. Per fer proves.
	switch(current_state_I2){
		case RxLGap:
		//tr = '2';
		//serial_put(tr);
		if(e == REdge)
			morse = mchar_empty;
		current_state_I2 = RxDD;
		chrono_start(crono);
		break;

		case RxDD:
  			//tr = '3';
			//serial_put(tr);
   			 if (e == FEdge){
     			 if(chrono_get(crono)*5 < DOT/2)
					chrono_start(crono);
      			else if(chrono_get(crono)*5 > 2*DOT){
					current_state_I2 = RxSGap;
					morse = mchar_add(morse, MDash);
					g = timer_after(TIMER_MS(2*DOT), raise_stimeout);
					chrono_start(crono);
					
     			}
      			else if((chrono_get(crono)*5 < 2*DOT) && (chrono_get(crono)*5 >= DOT/2)){
					current_state_I2 = RxSGap;
					g = timer_after(TIMER_MS(2*DOT), raise_stimeout);
					morse = mchar_add(morse, MDot);
					
     			 }
    		}
  	  	break;


		case RxSGap:
		//tr = '1';
		//serial_put(tr);
		 if (e == REdge){
		 	current_state_I2 = RxDD;
		 	chrono_start(crono);
			timer_cancel(g);
		}
		else if(e==STimeOut){
			current_state_I2 = RxLGap;
			queue_enqueue(&cua_rx, mtbl_m2a(morse));
			
		}
		break;
	}
}

void raise_stimeout(void){
  I2_event(STimeOut);
}

void ether_put(uint8_t c){
	if(queue_is_empty(&cua_tx)){
		queue_enqueue(&cua_tx,c);
		sistema(INICI);
	}
	else
		queue_enqueue(&cua_tx, c);
}


static void sistema(event e){
	if(e == INICI){
		ascii = queue_front(&cua_tx);
		morse = mtbl_a2m(ascii);
		iter = mchar_iter(morse);
	}
	if(mchar_valid(iter)){
		if (mchar_next(&iter) == MDot){
			if((e == INICI) || (e == SEG)){
				modulator_set(true);
				h = timer_after(TIMER_MS(DOT), Gap);
			}
		}
		else {
			if((e == INICI) || (e == SEG)){
				modulator_set(true);
				h = timer_after(TIMER_MS(DASH), Gap);
			}
		}
	}
	else{
		h = timer_after(TIMER_MS(LETTERGAP), silenci);
		queue_dequeue(&cua_tx);
	}
	

}


static void silenci(void){
	if(!queue_is_empty(&cua_tx))
		sistema(INICI);

}

static void Gap(void){
	modulator_set(false);
	h = timer_after(TIMER_MS(DOT), aux);

}
static void aux(void){
	sistema(SEG);
}