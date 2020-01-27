import os
import time

from functions.adler32 import compareAdler32
from functions.crc32 import compareCrc32
from functions.crc64 import compareCrc64
from functions.md2 import compareMd2
from functions.md4 import compareMd4
from functions.md5 import compareMd5
from functions.ripemd import compareRipemd
from functions.sha1 import compareSha1
from functions.sha256 import compareSha256
from functions.sha512 import compareSha512

ownFunctions = [compareMd2.md2, compareMd4.md4, compareMd5.md5, compareSha1.sha1, compareSha256.sha256,
                compareSha512.sha512, compareRipemd.ripemd, compareCrc32.crc32, compareCrc64.crc64,
                compareAdler32.adler32]
libFunctions = [compareMd2.lib_md2, compareMd4.lib_md4, compareMd5.lib_md5, compareSha1.lib_sha1,
                compareSha256.lib_sha256, compareSha512.lib_sha512, compareRipemd.lib_ripemd, compareCrc32.lib_crc32,
                compareCrc64.lib_crc64, compareAdler32.lib_adler32]
names = ['Md2', 'Md4', 'Md5', 'Sh1', 'Sh2', 'Sh5', 'Rmd', 'Cr3', 'Cr6', 'Adl']

print('Function order: ' + str(names))
cwd = os.path.dirname(os.path.dirname(os.path.realpath(__file__))) + '\\files'
for file in os.listdir(cwd):
    with open(cwd + '\\' + file, 'r') as readFile:
        writeFile = open(f"times/{file[:len(file)-4]}.txt", "w")
        print(f'{file}: ')
        writeFile.write(f'{file}: \n')
        string = readFile.read()
        print('\tLib: ')
        writeFile.write('\tLib: \n')
        for func, name in zip(libFunctions, names):
            print('\t\t'+name+': ', end='')
            writeFile.write('\t\t' + name + ': ')
            start = time.time()
            func(string)
            print(time.time() - start)
            writeFile.write(str(time.time() - start)+'\n')
        print('\tOwn: ')
        writeFile.write('\tOwn: \n')
        for func, name in zip(ownFunctions, names):
            print('\t\t'+name+': ', end='')
            writeFile.write('\t\t'+name+': ')
            start = time.time()
            func(string)
            print(time.time() - start)
            writeFile.write(str(time.time() - start)+'\n')
        writeFile.close()
