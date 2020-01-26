import hashlib
from sha512 import mySha512
import time


def sha512(string):
    start = time.time()
    val = mySha512.sha512(string.encode()).hexdigest()
    print(time.time() - start)
    return val


def lib_sha512(string):
    start = time.time()
    sha = hashlib.sha512()
    sha.update(string.encode())
    val = sha.hexdigest()
    print(time.time() - start)
    return val
