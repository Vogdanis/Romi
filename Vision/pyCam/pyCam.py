from picamera import PiCamera
import time
#from datetime import datetime
from time import gmtime, strftime, sleep
import sys
import os

info = '\npyCam - If you want to take more than one picture,\n'
info += 'give as first argument the number of pictures and,\n'
info += 'second argument the delay between them\n'
print(info)
#print('Number of arguments:', len(sys.argv), 'arguments')
#print('Argument list: ',  str(sys.argv))

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
#We will create a folder named after the DATE y-m-datetime
#inside each folder(which is a date) we will put the images in format hour-minute-second
folder_name = strftime("%Y-%m-%d",gmtime())
picture_name = strftime("%H:%M:%S",gmtime())
path = '/tmp/' + folder_name
#Now we have to check if the folder exists
#If it exists we will cd into it 
#if not we will create it
if(os.path.isdir(path)):
   print("PathExists")
else:
    print("Path doesnt exist.")
    os.mkdir(path)
    print("Created path: ", path)

os.chdir(path)
print("Saving photos at: ", os.getcwd())
cam = PiCamera()
for i in range(0, numOfPictures):
    # cam.start_preview()
    picture_name = strftime("%H:%M:%S",gmtime())
    fileName = picture_name + '.jpg' 
    cam.capture(fileName)
    print("Saved photo as: ", fileName)
    # cam.stop_preview()
    time.sleep(delayBetweenPictures)


#
#cam = PiCamera()
#for i in range(0, numOfPictures):
#    # cam.start_preview()
#    path = '/tmp/pyCam/' + str(dateTime)
#    path += '.jpg'
#    cam.capture(path)
#    # cam.stop_preview()
#    time.sleep(delayBetweenPictures)
