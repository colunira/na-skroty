from adler32 import myAdler32
import zlib


def adler32(string):
    print(hex(myAdler32.adler32(string.encode())))
    print(hex(zlib.adler32(string.encode())))
