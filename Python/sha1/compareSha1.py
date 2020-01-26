import hashlib
from sha1 import mySha1
import time


def sha1(string):
    start = time.time()
    val = mySha1.sha1(string.encode())
    print(time.time() - start)
    return val


def lib_sha1(string):
    start = time.time()
    sha = hashlib.sha1()
    sha.update(string.encode())
    val = sha.hexdigest()
    print(time.time() - start)
    return val
