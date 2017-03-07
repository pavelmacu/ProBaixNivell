crossing.hex: crossing
	avr-objcopy -Oihex crossing crossing.hex
	
crossing: crossing.o blck_serial.o serial_device.o queue.o gpio_device.o control.o lamp.o semaph.o
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -o crossing crossing.o blck_serial.o serial_device.o queue.o gpio_device.o control.o lamp.o semaph.o

blck_serial.o: blck_serial.c blck_serial.h serial_device.c serial_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL blck_serial.c -c

crossing.o: crossing.c blck_serial.c blck_serial.h serial_device.c serial_device.h control.c control.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL crossing.c -c

serial_device.o: serial_device.c serial_device.h queue.c queue.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c serial_device.c

queue.o: queue.c queue.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c queue.c

gpio_device.o: gpio_device.c gpio_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c gpio_device.c

control.o: control.c control.h semaph.c semaph.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL control.c -c

lamp.o: lamp.c lamp.h gpio_device.c gpio_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c lamp.c

semaph.o: semaph.c semaph.h lamp.c lamp.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c semaph.c


