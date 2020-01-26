from ripemd import myRipemd
import hashlib
import time


def ripemd(string):
    start = time.time()
    val = myRipemd.ripemd(string.encode())
    print(time.time() - start)
    
    
def lib_ripemd(string):
    start = time.time()
    ripe = hashlib.new('ripemd160')
    ripe.update(string.encode())
    val = ripe.hexdigest()
    print(time.time() - start)
