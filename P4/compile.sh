avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL semaphore.c gpio_device.c -o semaphore
avr-objcopy -Oihex semaphore semaphore.hex
sudo avrdude -c arduino -p atmega328p -P /dev/tty.usbmodem1421 -U semaphore.hex
rm *.hex
rm semaphore