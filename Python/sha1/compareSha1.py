import hashlib
from sha1 import mySha1


def sha1(string):
    sha = hashlib.sha1()
    sha.update(string.encode())
    print(sha.hexdigest())
    print(mySha1.sha1(string.encode()))
