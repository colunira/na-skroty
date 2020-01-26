from adler32 import myAdler32
import zlib
import time


def adler32(string):
    start = time.time()
    val = hex(myAdler32.adler32(string.encode()))
    print(time.time() - start)
    return val


def lib_adler32(string):
    start = time.time()
    val = hex(zlib.adler32(string.encode()))
    print(time.time() - start)
    return val
