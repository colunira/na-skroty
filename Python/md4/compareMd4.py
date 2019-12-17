from md4 import myMd4
import hashlib

string = "abc"

print(hashlib.new("md4", string.encode()).hexdigest())
print(myMd4.md4(string.encode()).hex())
