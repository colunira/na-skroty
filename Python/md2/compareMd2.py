from md2 import myMd2
import time

name = 'Md2: '

def md2(string):
    start = time.time()
    val = myMd2.md2(string)
    print(time.time() - start)
    return val


def lib_md2(string):
    print('-1')
