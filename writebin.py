import serial

# Open the serial port at COM7 with baud rate 115200
ser = serial.Serial('COM7', 115200)

# Open a file for writing the raw binary data
output_file = open('raw_binary_data.bin', 'wb')

# Read 131,072 lines of data from the serial port
for line_number in range(1, 262143):
    # Read a line from the serial port
    line = ser.readline().decode().strip()

    # Convert the 16-digit binary string to raw binary format
    raw_binary = int(line, 2).to_bytes(4, 'big')

    # Write the raw binary data to the output file
    output_file.write(raw_binary)

    # Print the data and line number on the serial console
    print(f"Line {line_number}: {line}")

# Close the serial port and the output file
ser.close()
output_file.close()
