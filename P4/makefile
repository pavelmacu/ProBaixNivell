main.hex: main
	avr-objcopy -Oihex main main.hex
	
main: serial_device.o semaphore.o gpio_device.o controlsem.o main.o
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL serial_device.o semaphore.o gpio_device.o controlsem.o main.o -o main

main.o: main.c
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL main.c -c

controlsem.o: controlsem.c controlsem.h semaphore.h serial_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL controlsem.c -c

gpio_device.o: gpio_device.c gpio_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL gpio_device.c -c

semaphore.o: semaphore.c semaphore.h gpio_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL semaphore.c -c

serial_device.o: serial_device.c serial_device.h
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL serial_device.c -c
