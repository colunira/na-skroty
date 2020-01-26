import zlib
from crc32 import myCrc32
import time


def crc32(string):
    start = time.time()
    val = myCrc32.crc32(string.encode())
    print(time.time() - start)
    return val


def lib_crc32(string):
    start = time.time()
    val = zlib.crc32(string.encode())
    print(time.time() - start)
    return val
