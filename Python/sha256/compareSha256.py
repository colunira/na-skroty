import hashlib
from sha256 import mySha256
import time


def sha256(string):
    start = time.time()
    val = mySha256.sha256(string)
    print(time.time() - start)
    return val


def lib_sha256(string):
    start = time.time()
    sha = hashlib.sha256()
    sha.update(string.encode())
    val = sha.hexdigest()
    print(time.time() - start)
    return val
