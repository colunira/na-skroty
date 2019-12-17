import zlib
from crc32 import myCrc32

string = "abc"

print(hex(zlib.crc32(string.encode())))
print(hex(myCrc32.crc32(string.encode())))


