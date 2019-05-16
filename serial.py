import serial 
import time

serialDelay = 0.3
#s = serial.Serial(port='/dev/cu.wchusbserial1410', baudrate=115200)
s = serial.Serial(port='/dev/ttyUSB0', baudrate=115200)
time.sleep(serialDelay)

def readSerial():
    while s.in_waiting:
        print s.readline()

while 1:
    time.sleep(serialDelay)
    readSerial()
    sendCommand = raw_input("PLease give command to process:")
    time.sleep(serialDelay)
    s.write(sendCommand + "\n\r")

