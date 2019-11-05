from md5 import myMd5
import hashlib

str = "po co komu kodowanie"
result = hashlib.md5(str.encode())
print(result.hexdigest() + " <= \"" + str + "\"")
myMd5.useMeOutside(str.encode())
