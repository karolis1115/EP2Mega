import serial
import time

# Adjust the COM port and baud rate accordingly
ser = serial.Serial('COM11', 115200)
print("Connected to: " + ser.portstr +" @ "+ ser.baudrate.__str__())

# File to save the binary data
file_name = "dump.bin"

# Wait for the Arduino to be ready
time.sleep(2)

# Signal Arduino to start
ser.write(b'S')  # Send 'S' for start
print("Sent Start character")

try:
    with open(file_name, 'wb') as file:
        while True:
            # Read two bytes from the serial port
            data_high = ser.read(1)
            data_low = ser.read(1)


             # Check if both bytes are received
            if data_high and data_low:
                # Convert bytes to an integer
                data = (ord(data_high) << 8) | ord(data_low)
            # Write the data to the binary file
            file.write(data.to_bytes(2, byteorder='big'))

            #TODO check for end of data character
            #TODO Trim start and end strings

except KeyboardInterrupt:
    print("Process interrupted by the user.")

finally:
    ser.close()
