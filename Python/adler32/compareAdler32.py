from adler32 import myAdler32
import zlib

string = "abc"

print(hex(myAdler32.adler32(string.encode())))
print(hex(zlib.adler32(string.encode())))
