import hashlib
from sha256 import mySha256

sha = hashlib.sha256()

string = "abc"
sha.update(string.encode())
print(sha.hexdigest())
print(mySha256.sha256(string))
