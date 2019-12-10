from md4 import myMd4
import hashlib

print(hashlib.new("md4", "abc".encode()).hexdigest())
print(myMd4.md4("abc".encode()).hex())
