import hashlib
from functions.sha256 import mySha256


def sha256(string):
    val = mySha256.sha256(string)
    return val


def lib_sha256(string):
    sha = hashlib.sha256()
    sha.update(string.encode())
    val = sha.hexdigest()
    return val
