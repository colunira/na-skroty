import hashlib
from sha512 import mySha512

string = "abc"

sha = hashlib.sha512()

sha.update(string.encode())
print(sha.hexdigest())
print(mySha512.sha512("abc".encode()).hexdigest())
