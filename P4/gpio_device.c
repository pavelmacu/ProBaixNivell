#include "gpio_device.h"


pin_t pin_create(volatile uint8_t *port, uint8_t pin, pin_direction_t d){

	//Retorna un objecte pin_t associat al pin numero pin del port porti inicialitzat en mode d.
	pin_t t;
	


	t.port = port; 
	t.pin = pin;


	if (d == Input){
		*(t.port +1) &= ~(_BV(pin));
	}
	else if (d == Output){
		*(t.port - 1) |= (_BV(pin));
	}
 
 	return t;
}

void pin_w(pin_t p, bool v){

	uint8_t DDR_dades;
	DDR_dades = *(p.port-1);
	if ((DDR_dades & _BV(p.pin)) != 0b00000000)
	{
		if(v)
		{
			*p.port |= _BV(p.pin);
		}
		else{
			*p.port &= ~(_BV(p.pin));
		}

	}
		}
	


bool pin_r(pin_t p){
	uint8_t DDR_dades;
	uint8_t PIN_dades;
	bool bit;

	DDR_dades = *(p.port -1);
	PIN_dades = *(p.port -2);
	if ((DDR_dades & _BV(p.pin)) == 0b00000000){
		if ((PIN_dades & _BV(p.pin)) == 0b00000000){
			bit = false;
		}
		else{
			bit= true;
		}

	}
	return bit;
}
	


void pin_toggle(pin_t p){

	uint8_t DDR_dades;
	
	DDR_dades = *(p.port -1);
	if ((DDR_dades & _BV(p.pin)) != 0b00000000)
	{
		if ((*p.port & _BV(p.pin)) == 0b00000000){
				pin_w(p, true);
		}
		else{
			pin_w(p, false);
		}
	}

}
	

/*void pin_destroy(pin_t *const p){
	uint8_t *direport;
	direport = 0x00;
	p = pin_create(direport, p.pin, Input);
}
*/

/*int main(void){

	pin_t LED;
	pin_t PROVA;
	PROVA= pin_create(&PORTD, 5, Input);
	LED = pin_create(&PORTB, 5, Output);
	if(pin_r(PROVA) == true){
		pin_w(LED, true);
	}
	else{
		pin_w(LED, false);
	}


	/*for (int i = 0; i < 100; ++i)
	{
		pin_toggle(LED);
		_delay_ms(1000);

	}*/

	/*for (int i = 0; i < 100; ++i)
	{
		pin_w(LED, true);
		_delay_ms(1000);
		pin_w(LED, false);
		_delay_ms(1000);
	}*/

