from interpret import *
import serial

ser = serial.Serial(port='/dev/ttyACM0',baudrate =9600, bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE, timeout= 5)

i= Interpret()

def Start():
    ser.write('R')
    if(ser.read(9) != ' RESTART '):
        print("Error: Ara no toca")

def Stop():
    ser.write('S')
    if(ser.read(11) != ' SHUTDOWN '):
        print("Error: Ara no toca")

def Emergency():
    ser.write('E')
    if(ser.read(11) != ' EMERGENCY '):
        print("Error: Ara no toca")

i.set_prompt('** ')
i.afegeix_ordre('start',Start)
i.afegeix_ordre('stop',Stop)
i.afegeix_ordre('emergency',Emergency)
i.run()
ser.close()

