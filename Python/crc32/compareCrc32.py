import zlib
from crc32 import myCrc32
import time


def crc32(string):
    val = myCrc32.crc32(string.encode())
    return val


def lib_crc32(string):
    val = zlib.crc32(string.encode())
    return val
