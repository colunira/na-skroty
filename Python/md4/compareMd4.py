from md4 import myMd4
import hashlib
import time


def md4(string):
    start = time.time()
    val = myMd4.md4(string.encode()).hex()
    print(time.time() - start)
    return val


def lib_md4(string):
    start = time.time()
    val = hashlib.new("md4", string.encode()).hexdigest()
    print(time.time() - start)
    return val
