#include "serial_device.h"
#include "semaphore.h"
#include "controlsem.h"

int main(void)
{
	int i =0;
	int j = 0;
	serial_init();
	controlsem_init();
	semaphore_init();
	tick_monitor();

	while(true){
		tick_monitor();
		tick_semaphore();
		_delay_ms(100);
		}
	return 0;
}