import hashlib
from sha1 import mySha1
import time


def sha1(string):
    val = mySha1.sha1(string.encode())
    return val


def lib_sha1(string):
    sha = hashlib.sha1()
    sha.update(string.encode())
    val = sha.hexdigest()
    return val
