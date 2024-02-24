# Open the input text file
input_file_path = 'binary_data.txt'
with open(input_file_path, 'r') as input_file:

    # Read the content of the file
    content = input_file.read()

    # Remove newlines and spaces
    content = content.replace('\n', '').replace(' ', '')

    # Convert the binary string into bytes
    bytes_data = bytearray()
    for i in range(0, len(content), 8):
        byte = content[i:i+8]
        bytes_data.append(int(byte, 2))

# Save the raw binary/machine code to a new file
output_file_path = 'output.bin'
with open(output_file_path, 'wb') as output_file:
    output_file.write(bytes_data)
