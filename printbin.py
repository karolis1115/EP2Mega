import serial
import time

# Configure the serial connection

#Terminal clients connect via a virtual COM port and should be set to 115200 baud, no parity, 8 data bits and 1 stop bit when connecting to the interface.

try:
    ser = serial.Serial(port= "COM7", baudrate= 115200, timeout=1)

except Exception as e:
    print("error open serial port: " + str(e))
    exit()

def write(message):
    """Write message to GPIB bus."""
    #ser.write("{}\r".format(message).encode("ASCII"))
    ser.write(message.encode("ASCII"))


#send ver command to Prologix GPIB-USB controller to get version
message = "aut\n\r"
write(message)
time.sleep(1)
ser.close()