CC = avr-gcc
CPPFLAGS = -DF_CPU=16000000UL
AR = avr-ar
CFLAGS = -Wall -std=c99 -Os -mmcu=atmega328p -fshort-enums
LDFLAGS = -mmcu=atmega328p

libpbn.a: libpbn.a(blck_serial.o) libpbn.a(ether.o) libpbn.a(gpio_device.o) libpbn.a(queue.o) libpbn.a(lamp.o) libpbn.a(mchar.o) libpbn.a(mtbl.o) libpbn.a(modulator.o) libpbn.a(semaph.o) libpbn.a(serial_device.o) libpbn.a(timer.o)
	ar r libpbn.a $^

serial_device.o: serial_device.h queue.h
blck_serial.o: blck_serial.h serial_device.h
queue.o: queue.h
gpio_device.o: gpio_device.h
lamp.o: lamp.h gpio_device.h
semaph.o: semaph.h lamp.h
ether.o: ether.h mtbl.h mchar.h modulator.h timer.h queue.h
timer.o: timer.h
mtbl.o: mtbl.h mchar.h
modulator.o: modulator.h
mchar.o: mchar.h

