from crc64 import myCrc64
from crc64iso.crc64iso import crc64 as libCrc
import time


def crc64(string):
    val = hex(myCrc64.crc64(string.encode()))
    return val


def lib_crc64(string):
    val = libCrc(string)
    return val
