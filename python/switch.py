#nesse arquivo eu coloco o programa principal

import serial 

arduino = None

def conexao():
    global arduino
    while True: 
        try:  
            arduino = serial.Serial('/dev/ttyACM0', 9600) 
            print('Arduino conectado')
            break
        except:
            pass

def bobina(switch,cmd):
    global arduino
    valor = switch*10+cmd
    arduino.write(int(cmd).to_bytes(1, 'big'))
    arduino.close()
