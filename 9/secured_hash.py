import hashlib
import hmac
import os

def secure_hash(input_string, secret_key):
    # Generate a random salt value
    salt = os.urandom(16)

    # Hash the input string iteratively with the salt value
    hash_value = input_string.encode('utf-8') + salt
    for i in range(1000):
        hash_value = hashlib.sha256(hash_value).digest()

    # Generate a keyed hash using the secret key
    keyed_hash = hmac.new(secret_key.encode('utf-8'), hash_value, hashlib.sha256).digest()

    # Return the salt and the keyed hash concatenated together
    return salt + keyed_hash
