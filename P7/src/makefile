CC = avr-gcc
CPPFLAGS = -DF_CPU=16000000UL
CFLAGS = -Wall -std=c99 -Os -mmcu=atmega328p -fshort-enums -Ilibpbn
LDFLAGS = -mmcu=atmega328p
LDFLAGS=-mmcu=atmega328p

.PHONY: arduino
transmetre = sudo avrdude -c arduino -p atmega328p -P/dev/tty.usbmodem1421 -U $<
py= python supervisor.py

.PHONY: modulator
modulator: test_modulator.hex
	$(transmetre)

vpath lib% libpbn

%.hex: %
	avr-objcopy -Oihex $< $@
master: control.o -lpbn
master.o: control.h
control.o: control.h
test_modulator: test_modulator.o -lpbn
test_modulator.o: test_modulator.c 
experiment1: experiment1.o -lpbn
experiment1.o: experiment1.c 
experiment2: experiment2.o -lpbn
experiment2.o: experiment2.c 

.PHONY: libpbn
libpbn:
	$(MAKE) -C libpbn
.PHONY: clean veryclean
clean:
	\rm -f *~ *.o *.s *.hex
	$(MAKE) -C libpbn clean
veryclean: clean
	\rm -f master
	$(MAKE) -C libpbn veryclean

trans-%: %.hex
	$(transmetre)
	$(py)
