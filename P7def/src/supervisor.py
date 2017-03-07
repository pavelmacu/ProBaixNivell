from interpret import *
import serial

if __name__ == '__main__':
    ser = serial.Serial(port='/dev/ttyACM0',baudrate =9600, bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE, timeout= 5)

i= Interpret()


def FA():
    ser.write("FA\n")
    state = ser.readline()[:-2]
    print(state)
    if(state == "COMERR"):
    	print("Error de comanda")
    
def FB():
    ser.write("FB\n")
    state = ser.readline()[:-2]
    print(state)
    if(state == "COMERR"):
        print("Error de comanda")
    

def cA():
    ser.write("?A\n")
    state = ser.readline()[:-2]
    if(state == "CLEAR"):
        print("Estat del semafor A: CLEAR")
    elif(state == "APPROACH"):
        print("Estat del semafor A: APPROACH")
    elif(state == "STOP"):
        print("Estat del semafor A: STOP")
    else:
        print("Error de comanda")
   
def cB():
    ser.write("?B\n")
    state = ser.readline()[:-2]
    if(state == "CLEAR"):
        print("Estat del semafor B: CLEAR")
    elif(state == "APPROACH"):
        print("Estat del semafor B: APPROACH")
    elif(state == "STOP"):
        print("Estat del semafor B: STOP")
    else:
        print("Error de comanda")

def R():
    ser.write("R\n")
    state = ser.readline()[:-2]
    print(state)
    if(state == "COMERR"):
        print("Error de comanda")
    
def H():
    ser.write("H\n")
    state = ser.readline()[:-2]
    print(state)
    if(state == "COMERR"):
    	print("Error de comanda")

def Help():
    print("")
    print("COMANDES DEL SUPERVISOR:")
    print("------------------------")
    print("")
    print("run: Inicialitza la cruilla de semafors.")
    print("")
    print("halt: Apaga la cruilla de semafors.")
    print("")
    print("forceA: posa el semafor A a l'estat CLEAR. Respecta els temps d'APPROACH coreesponents.")
    print("")
    print("forceB: exactament el mateix que 'forceA' pero amb el semafor B.")
    print("")
    print("estatA: retorna l'estat del semafor A, que pot ser CLEAR, APPROACH o STOP.")
    print("")
    print("estatB: exactament igual que 'estatA' pero amb el semafor B.")
    print("")


    
   

i.set_prompt('** ')
i.afegeix_ordre('forceA',FA)
i.afegeix_ordre('forceB',FB)
i.afegeix_ordre('estatA',cA)
i.afegeix_ordre('estatB',cB)
i.afegeix_ordre('run',R)
i.afegeix_ordre('halt',H)
i.afegeix_ordre('help',Help)


print("")
print("Per saber quines son les comandes que pot interpretar el supervisor, podeu introduir la comanda 'help'.")
print("")

state = ser.readline()[:-2]
print(state)

i.run()

ser.close()





