from crc64 import myCrc64
from crc64iso.crc64iso import crc64 as poop
import zlib


def crc64(string):
    print(hex(myCrc64.crc64(string.encode())))
    print(poop(string))
