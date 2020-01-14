import hashlib
from sha256 import mySha256


def sha256(string):
    sha = hashlib.sha256()
    sha.update(string.encode())
    print(sha.hexdigest())
    print(mySha256.sha256(string))
