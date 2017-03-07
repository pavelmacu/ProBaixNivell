.PHONY: update_svn arduino
transmetre = sudo avrdude -c arduino -p atmega328p -P/dev/tty.usbmodem1421 -U $<

%.hex: %
	avr-objcopy -Oihex $< $<.hex

ether: ether.o queue.o mchar.o mtbl.o modulator.o timer.o
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -o ether ether.o queue.o mchar.o mtbl.o modulator.o timer.o

crossing: crossing.o serial_device.o queue.o gpio_device.o control.o lamp.o semaph.o timer.o ether.o mchar.o mtbl.o modulator.o
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -o crossing crossing.o serial_device.o queue.o gpio_device.o control.o lamp.o semaph.o timer.o ether.o mchar.o mtbl.o modulator.o

crossing.o: crossing.c ether.c ether.h serial_device.c serial_device.h control.c control.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL crossing.c -c

serial_device.o: serial_device.c serial_device.h queue.c queue.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c serial_device.c

queue.o: queue.c queue.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c queue.c

gpio_device.o: gpio_device.c gpio_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c gpio_device.c

control.o: control.c control.h semaph.c semaph.h timer.c timer.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL control.c -c

lamp.o: lamp.c lamp.h gpio_device.c gpio_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c lamp.c

semaph.o: semaph.c semaph.h lamp.c lamp.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c semaph.c

ether.o: ether.c ether.h mtbl.h mtbl.h mchar.c mchar.h modulator.c modulator.h timer.c timer.h queue.c queue.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c ether.c

timer.o: timer.c timer.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c timer.c

mchar.o: mchar.c mchar.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c mchar.c

mtbl.o: mtbl.c mtbl.h mchar.c mchar.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c mtbl.c

modulator.o: modulator.c modulator.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL -c modulator.c

arduino: crossing.hex
	$(transmetre)
tether: ether.hex
	$(transmetre)
