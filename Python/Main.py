from adler32 import compareAdler32
from crc32 import compareCrc32
from crc64 import compareCrc64
from md2 import compareMd2
from md4 import compareMd4
from md5 import compareMd5
from ripemd import compareRipemd
from sha1 import compareSha1
from sha256 import compareSha256
from sha512 import compareSha512
import os

ownFunctions = [compareMd2.md2, compareMd4.md4, compareMd5.md5, compareSha1.sha1, compareSha256.sha256,
                compareSha512.sha512, compareRipemd.ripemd, compareCrc32.crc32, compareCrc64.crc64,
                compareAdler32.adler32]
libFunctions = [compareMd2.lib_md2, compareMd4.lib_md4, compareMd5.lib_md5, compareSha1.lib_sha1,
                compareSha256.lib_sha256, compareSha512.lib_sha512, compareRipemd.lib_ripemd, compareCrc32.lib_crc32,
                compareCrc64.lib_crc64, compareAdler32.lib_adler32]
names = ['Md2', 'Md4', 'Md5', 'Sh1', 'Sh2', 'Sh5', 'Rmd', 'Cr3', 'Cr6', 'Adl']

print('Function order: ' + str(names))
cwd = os.path.dirname(os.path.dirname(os.path.realpath(__file__))) + '\\Pliki'
for file in os.listdir(cwd):
    with open(cwd + '\\' + file, 'r') as readFile:
        print(f'{file}: ')
        string = readFile.read()
        print('\tLib: ')
        for func, name in zip(libFunctions, names):
            print('\t\t'+name+': ', end='')
            func(string)
        print('\tOwn: ')
        for func, name in zip(ownFunctions, names):
            print('\t\t'+name+': ', end='')
            func(string)
