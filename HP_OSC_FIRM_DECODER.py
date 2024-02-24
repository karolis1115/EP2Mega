def separate_and_swap_bytes(data):
    separated = [data[i:i+2] for i in range(0, len(data), 2)]  # Separate into blocks of 2 bytes
    swapped = [block[::-1] for block in separated]  # Swap the order of bytes in each block
    result = b''.join(swapped)  # Join the blocks back together
    return result

# Example usage:
input_file = "HP_54602B_Contents_of_27C4002_EPROM_absolute_binary_format_EPROM_A.01.27.bin"
output_file = 'swapped_binary.bin'

with open(input_file, 'rb') as file:
    data = file.read()

result = separate_and_swap_bytes(data)

with open(output_file, 'wb') as file:
    file.write(result)

print(f"Binary content from '{input_file}' separated and swapped, and saved to '{output_file}'.")
