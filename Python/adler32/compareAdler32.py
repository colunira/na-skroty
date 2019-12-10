from adler32 import myAdler32 as ma
import zlib

string = "abc"

print(hex(ma.adler32(string.encode())))
print(hex(zlib.adler32(string.encode())))
