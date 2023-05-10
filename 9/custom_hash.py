def custom_hash(input_string):
    prime_number = 31
    key_value = 0xCAFEBABE
    prime_modulus = 2**32 - 1

    preliminary_hash = 0
    for char in input_string:
        preliminary_hash += ord(char) * prime_number

    xor_result = preliminary_hash ^ key_value
    final_hash = xor_result % prime_modulus

    return final_hash
