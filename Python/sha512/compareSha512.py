import hashlib
from sha512 import mySha512
import time


def sha512(string):
    val = mySha512.sha512(string.encode()).hexdigest()
    return val


def lib_sha512(string):
    sha = hashlib.sha512()
    sha.update(string.encode())
    val = sha.hexdigest()
    return val
