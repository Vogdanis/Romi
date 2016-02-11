from time import sleep
import RPi.GPIO as GPIO

# Motor Pins and Variables
motorDirPin = 20
motorStepPin = 21
motorDir = 0
motorStepsPerRev = 200

# EndStops
endstopHomePin = 26
endstopEndPin = 19
homeReached = 0


def homeEndstopReached():
    homeReached = GPIO.input(endstopHomePin)
    if not homeReached:
        print "HomeReached"
        return 1


def seekHome():
    while homeReached == 0:
        motorStep()
        if homeEndstopReached():
            break


def motorStep():
    GPIO.output(motorStepPin, GPIO.HIGH)
    sleep(delay)
    GPIO.output(motorStepPin, GPIO.LOW)
    sleep(delay)


def changeDir():
    global motorDir
    motorDir = not motorDir
    GPIO.output(motorDirPin, motorDir)

def debounceFromEndstop(steps):
    sleep(1)
    print "Debounce from endstop"
    changeDir()
    for i in range(steps):
	motorStep()

def processCommand(command):
    if command is "h":
        print "Homing....."
        seekHome()
        debounceFromEndstop(100)
    
    elif command is "f":
        print "Going to end"

    elif command is "q":
        print "Quitting."   
        GPIO.cleanup()
        exit()

    else:
        print "Invalid command"   
 

print("CableBot v0.1")

#Setup GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(motorDirPin, GPIO.OUT)
GPIO.setup(motorStepPin, GPIO.OUT)
GPIO.setup(endstopHomePin, GPIO.OUT)
GPIO.setup(endstopEndPin, GPIO.OUT)
GPIO.output(motorDirPin, motorDir)


print "Motor direction is set to = " + str(motorDir)
print "EndstopHome value is = " + str(GPIO.input(endstopHomePin))
print "EndstopEnd value is = " + str(GPIO.input(endstopEndPin))

delay = .001

while (1):
   command = raw_input("Waiting for command to process : \n")
   processCommand(comman)
   


