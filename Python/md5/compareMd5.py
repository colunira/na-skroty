from md5 import myMd5
import hashlib

string = "abc"

print(hashlib.md5(string.encode()).hexdigest())
print(myMd5.myMd5(string.encode()))
