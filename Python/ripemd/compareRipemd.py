from ripemd import myRipemd
import hashlib
import time


def ripemd(string):
    return myRipemd.ripemd(string.encode())
    
    
def lib_ripemd(string):
    ripe = hashlib.new('ripemd160')
    ripe.update(string.encode())
    return ripe.hexdigest()
