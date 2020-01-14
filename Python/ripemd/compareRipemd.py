from ripemd import myRipemd
import hashlib


def ripemd(string):
    ripe = hashlib.new('ripemd160')
    ripe.update(string.encode())
    print(myRipemd.ripemd(string.encode()))
    print(ripe.hexdigest())