#!/usr//bin/python3
#
# driver.py - The driver tests the correctness
import subprocess
import re
import os
import sys
import argparse
import shutil
import json

import base64
import os
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.fernet import Fernet

from cryptography.fernet import Fernet


# This is input in the form of a string

def get_key():
    password_provided = os.environ.get("PASSWORD")
    password = password_provided.encode()  # Convert to type bytes

    # CHANGE THIS - recommend using a key from os.urandom(16), must be of type bytes
    salt = b'salt_'
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=100000,
        backend=default_backend()
    )
    key = base64.urlsafe_b64encode(
        kdf.derive(password))  # Can only use kdf once
    return key


def getjson():
    with open("caches.enc", "rb+") as cache_file:
        f = Fernet(get_key())
        cache_data = cache_file.read()
        decrypted = f.decrypt(cache_data)
        cache_json = json.loads(decrypted.decode())
        print(cache_json)
    return cache_json


def main():
    getjson()


    # execute main only if called as a script
if __name__ == "__main__":
    main()
