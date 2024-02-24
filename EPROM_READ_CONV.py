import serial
import time

def receive_binary_data():
    # Connect to Arduino
    ser = serial.Serial('COM7', 115200, timeout=1)
    print("Connected to Arduino on COM7.")

    # Read data until 65535 lines are received
    received_data = ""
    line_count = 0
    while line_count < 262143:
        data = ser.readline().decode().strip()
        if len(data) == 16 and all(bit in ["0", "1"] for bit in data):
            received_data += data
            line_count += 1
            print(f"Received line {line_count}: {data}")

        if line_count == 262143:
            break

    # Save binary data to a file
    with open("binary_data.txt", "w") as file:
        file.write(received_data)

    ser.close()
    print("Binary data saved to binary_data.txt.")

def convert_to_intel_hex():
    # Read binary data from the file
    with open("binary_data.txt", "r") as file:
        binary_data = file.read().strip()

    # Convert binary data to Intel HEX format
    intel_hex_data = ""
    address = 0
    for i in range(0, len(binary_data), 16):
        line = binary_data[i:i+16]
        hex_value = hex(int(line, 2))[2:].zfill(4)
        record = ":02000004" + hex(address // 16)[2:].zfill(4) + "00" + hex_value
        checksum = hex((sum(int(record[i:i+2], 16) for i in range(1, len(record), 2)) ^ 0xFF) + 1)[-2:].zfill(2)
        intel_hex_data += record + checksum + "\n"
        address += 16

    # Save Intel HEX data to a file
    with open("intel_hex_data.hex", "w") as file:
        file.write(intel_hex_data)

    print("Intel HEX data saved to intel_hex_data.hex.")

# Main program
if __name__ == "__main__":
    receive_binary_data()
    convert_to_intel_hex()
