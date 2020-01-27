from functions.md4 import myMd4
import hashlib


def md4(string):
    val = myMd4.md4(string.encode()).hex()
    return val


def lib_md4(string):
    val = hashlib.new("md4", string.encode()).hexdigest()
    return val
