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
import time

functions = [compareAdler32.adler32, compareCrc32.crc32, compareCrc64.crc64, compareMd2.md2,
             compareMd4.md4, compareMd5.md5, compareRipemd.ripemd, compareSha1.sha1, compareSha256.sha256,
             compareSha512.sha512]
names = ['Adler 32', 'Crc 32', 'Crc 64', 'Md2', 'Md4', 'Md5', 'Ripemd', 'Sha1', 'Sha256', 'Sha512']
string = 'Ala ma kota skurwysynu jebany maklereaushfjgkbfpo[thubjnsogyhgtyujhgtyujhgfrfghjoiuytdfvbnnbvfdertyuiokjhgfgyuiiugfghjiuyg'

for function, name in zip(functions, names):
    start = time.time()
    print(name + ':')
    function(string)
    print('Time elapsed: ' + str(time.time() - start) + 's \n')
