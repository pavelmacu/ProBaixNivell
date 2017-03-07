#include "modulator.h"
#include <avr/io.h>
#include <stdio.h>

void modulator_init(void){
  DDRB|=(_BV(3));/*PB3 output*/
  PORTB&=~(_BV(3));
  TCCR2A&=~(_BV(COM2A0)); /*Disconnect Timer 2*/
  TCCR2A|=_BV(WGM21); /*CTC mode*/
  TCCR2B|=_BV(CS22) ; /*Prescaler 64*/
  TCNT2=0; /*Inicialitzar timer a 0*/
  OCR2A=39; 
  
}
void modulator_set(bool l){
  if(l)
    TCCR2A|=_BV(COM2A0);/*toggle when compare match*/
  else{
    TCNT2=0;
    PORTB&=~(_BV(3));
    TCCR2A&=~(_BV(COM2A0));
  }
}
