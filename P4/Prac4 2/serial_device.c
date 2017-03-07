#include "serial_device.h"


void serial_init(void){
	UBRR0L = 103;
	UBRR0H = 0;
	UCSR0A = 0b00100000;
	UCSR0C = 0b00000110;
	UCSR0B = 0b00011000;

}
uint8_t serial_get(void){
	uint8_t retorna;
	retorna = UCSR0A;
	while((retorna & _BV(7)) == 0){
		retorna = UCSR0A;
	} 
	//loop_until_bit_is_set(retorna,7);
	retorna = UDR0;
	return retorna;
}

void serial_put(uint8_t c){
	uint8_t aux;
	aux = UCSR0A;
	while((aux & _BV(5)) == 0){
		aux = UCSR0A;
	}
	//loop_until_bit_is_set(aux,7);	 
	UDR0 = c;
}



bool serial_can_read(void){
	if((UCSR0A & _BV(7)) == 0b10000000){
		return true;
	}
	else{
		return false;
	}
}

