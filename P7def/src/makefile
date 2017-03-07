CC = avr-gcc
CPPFLAGS = -DF_CPU=16000000UL
CFLAGS = -Wall -std=c99 -Os -mmcu=atmega328p -fshort-enums -Ilibpbn
LDFLAGS = -mmcu=atmega328p
LDFLAGS=-mmcu=atmega328p


transmetre = sudo avrdude -c arduino -p atmega328p -P/dev/tty.usbmodem1421 -U $<
py= python supervisor.py
picocom= picocom /dev/tty.usbmodem1421

.PHONY: arduino
arduino: master.hex
	$(transmetre)
	$(py)

.PHONY: t_esclau
t_esclau: esclau.hex
	$(transmetre)
	$(picocom)

.PHONY: ether
ether: test_ether.hex
	$(transmetre)
	$(picocom)

.PHONY: modulator
modulator: test_modulator.hex
	$(transmetre)
.PHONY: exp2
exp2: experiment2.hex
	$(transmetre)

.PHONY: timer
timer: timer_test.hex
	$(transmetre)

vpath lib% libpbn s

%.hex: %
	avr-objcopy -Oihex $< $@

esclau: esclau.o control.o -lpbn
esclau.o: control.h

master: master.o control.o -lpbn
master.o: control.h

control.o: control.h
test_modulator: test_modulator.o -lpbn
test_modulator.o: test_modulator.c 
experiment1: experiment1.o -lpbn
experiment1.o: experiment1.c 
experiment2: experiment2.o -lpbn
experiment2.o: experiment2.c 
timer_test: timer_test.o -lpbn
timer_test.o: timer_test.c
test_ether: test_ether.o -lpbn
test_ether.o: test_ether.c



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
