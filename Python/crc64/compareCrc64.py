from crc64 import myCrc64
from crc64iso.crc64iso import crc64 as libCrc
import time


def crc64(string):
    start = time.time()
    val = hex(myCrc64.crc64(string.encode()))
    print(time.time() - start)
    return val


def lib_crc64(string):
    start = time.time()
    val = libCrc(string)
    print(time.time() - start)
    return val
