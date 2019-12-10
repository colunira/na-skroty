from md5 import myMd5
import hashlib

string = "abc"
result = hashlib.md5(string.encode())
print(result.hexdigest() + " <= \"" + string + "\"")
myMd5.useMeOutside(string.encode())
