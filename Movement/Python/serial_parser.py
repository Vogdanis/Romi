import time
import serial


def main():
    serial_delay = 0.3
    # s = serial.Serial(port='/dev/cu.wchusbserial1410', baudrate=115200)
    s = serial.Serial(port='/dev/ttyUSB0', baudrate=115200)
    # s = serial.Serial(port='/dev/tty.usbserial-A9007Ru8', baudrate=115200)
    time.sleep(serial_delay)

    def read_serial():
        # while s.in_waiting:
        while s.inWaiting():
            print(s.readline())

    while 1:
        time.sleep(serial_delay)
        read_serial()
        sendCommand = raw_input("PLease give command to process:")
        time.sleep(serial_delay)
        s.write(sendCommand + "\n\r")


if __name__ == "__main__":
    main()
