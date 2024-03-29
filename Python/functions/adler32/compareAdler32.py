from functions.adler32 import myAdler32
import zlib


def adler32(string):
    return hex(myAdler32.adler32(string.encode()))


def lib_adler32(string):
    return hex(zlib.adler32(string.encode()))
