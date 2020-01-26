from md5 import myMd5
import hashlib
import time


def md5(string):
    start = time.time()
    val = myMd5.myMd5(string.encode())
    print(time.time() - start)
    return val


def lib_md5(string):
    start = time.time()
    val = hashlib.md5(string.encode()).hexdigest()
    print(time.time() - start)
    return val
