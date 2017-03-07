#include "serial_device.h"


static queue_t cua_rx;
static queue_t cua_tx;



ISR(USART_RX_vect){
	queue_enqueue(&cua_rx,UDR0);
}

ISR(USART_UDRE_vect){
	if(queue_is_empty(&cua_tx) == false){
		UDR0 = queue_front(&cua_tx);
		queue_dequeue(&cua_tx);
	}
	else
		UCSR0B &= ~(_BV(5));//desctivar interrupcio UDRIE

}


void serial_open(void){
	UBRR0L = 103;
	UBRR0H = 0;
	UCSR0A = 0b00100000;
	UCSR0C = 0b00000110;//asincron, sense paritat, 8 bits, 1 bit  d'stop.
	UCSR0B = 0b10011000; //bit 7 -> habilitar interrupcio RX, bit 5-> NO habilitar interrupcio UDRIE
	queue_empty(&cua_rx);
	queue_empty(&cua_tx);
}

void serial_close(void){
	while(queue_is_empty(&cua_tx));
	UBRR0L = 0;
	UBRR0H = 0;
	UCSR0A = 0;
	UCSR0C = 0;
	UCSR0B = 0;
}


uint8_t serial_get(void){
	uint8_t valor;
	while(queue_is_empty(&cua_rx));
	valor = queue_front(&cua_rx);
	queue_dequeue(&cua_rx);
	return valor;


}

void serial_put(uint8_t c){
	int buida = 0;
	while(queue_is_full(&cua_tx));
	if (queue_is_empty(&cua_tx))
	{
		buida = 1;
	}
	queue_enqueue(&cua_tx, c);
	if (buida == 1)
	{
		UCSR0B |= _BV(5); //habilitar interrupcio UDRIE
	}
}

bool serial_can_read(void){
	if(!queue_is_empty(&cua_tx)){
		return true;
	}
	else{
		return false;
	}
}
