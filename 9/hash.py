def divide_into_blocks(number):
    blocks = []
    for i in range(4):
        blocks.append((number >> (i * 2)) & 0x3)
    return blocks


def hash(hash_blocks, plaintext_blocks):
    hashtext = []
    hashtext.append((hash_blocks[0] + plaintext_blocks[1]) % 4)
    hashtext.append(hash_blocks[1] ^ plaintext_blocks[2])
    hashtext.append((hash_blocks[2] + plaintext_blocks[3]) % 4)
    hashtext.append(hash_blocks[3] ^ plaintext_blocks[0])
    return hashtext


hash_value = int(input("Enter the hash value (up to 8 bits): "))
plaintext = int(input("Enter the plaintext (up to 8 bits): "))

if hash_value < 0 or hash_value > 255:
    print("Invalid input! Hash value/plaintext should be an 8-bit number (0-255).")
    exit()

if plaintext < 0 or plaintext > 255:
    print("Invalid plaintext! Plaintext should be an 8-bit number (0-255).")
    exit()

hash_blocks = divide_into_blocks(hash_value)
print("Hash Value Blocks:")
for block in hash_blocks:
    print(block, end=" ")

plaintext_blocks = divide_into_blocks(plaintext)
print("\nPlaintext Blocks:")
for block in plaintext_blocks:
    print(block, end=" ")

msg_digest = hash(hash_blocks, plaintext_blocks)
print("\nMessage Digest:", end=" ")
for i in range(4):
    print(msg_digest[i], end=" ")
