import serial
from time import sleep

portName = 'COM4'
baudRate = 115200
maxLineLength = 10
delayTime = 500
movements = []
line = []

ser = serial.Serial(port=portName, baudrate=baudRate, timeout=5)

num_lines = sum(1 for line in open('servo_positions.csv'))  #Return is absolute, not zero indexed
#print(str(num_lines) + " lines parsed")                    #Diagnostic - print out number of lines parsed

positionFile = open("servo_positions.csv", 'r', encoding="utf-8-sig")

for x in range(0,num_lines):
    movements.append(positionFile.readline().rstrip().split(","))
    del movements [x][-1]
#for x in range(0, num_lines):                              #Diagnostic - print out the movement sequences
#    print(" ".join(movements[x])+ "\n")

ser.write(b"90")        #Set servo to middle of range as initial position
sleep(10)               #Wait whilst user establishes SERIAL terminal session

for x in range(0, len(movements[2])-1):
    b = bytearray(movements[2][x],'utf-8','ignore')
    #b.extend(movements[0][x])
    ser.write(b)
    ser.write(b'\n')
    sleep(delayTime*0.001)

ser.close()

def serialRead():
    while len(line) < maxLineLength:
        for c in ser.read():
            line.append(chr(c))
            if chr(c) == '\r':
                print("Line:  " + ''.join(line))
                line = []
                break
        if chr(c) == '9':
            break

#try:
#    ser.open()
#except Exception as e:
#    print("Error opening Serial Port")
#    print(e)
#    exit()