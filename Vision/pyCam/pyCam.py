from picamera import PiCamera
 from time import sleep
# from datetime import datetime
from time import gmtime, strftime
import sys

info = '\npyCam - If you want to take more than one picturen,\n'
info += 'give as first argument the number of pictures and,\n'
info += 'second argument delay between them'
print(info)
print('Number of arguments:', len(sys.argv), 'arguments')
print('Argument list: ',  str(sys.argv))

delayBetweenPictures = 0
numOfPictures = 0
# if no arguments are given
if len(sys.argv) == 1:
    print('No arguments were specified taking one picture.')
    numOfPictures = 1
# if only number of pictures is specified
# set delay automatically to 1
elif len(sys.argv) == 2:
    print('You didnt sepcify delay. Setting delay to 1')
    numOfPictures = int(sys.argv[1])
    delayBetweenPictures = 1
elif len(sys.argv) == 3:
    print('Will take ', sys.argv[1], ' pictures')
    print('Delay between pictures ', sys.argv[2])
    numOfPictures = int(sys.argv[1])
    delayBetweenPictures = int(sys.argv[2])
else:
    print('Your arguments are wrong please run the program again')
    exit()

dateTime = strftime("%Y-%m-%d %H:%M:%S", gmtime())
cam = PiCamera()
for i in range(0, numOfPictures):
    # cam.start_preview()
    path = '/tmp/pyCam/' + str(dateTime)
    path += '.jpg'
    cam.capture(path)
    # cam.stop_preview()
    time.sleep(delayBetweenPictures)
