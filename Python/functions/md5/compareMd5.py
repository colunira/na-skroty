from functions.md5 import myMd5
import hashlib


def md5(string):
    val = myMd5.myMd5(string.encode())
    return val


def lib_md5(string):
    val = hashlib.md5(string.encode()).hexdigest()
    return val
