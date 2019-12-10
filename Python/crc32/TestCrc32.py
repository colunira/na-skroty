import unittest
from crc32 import myCrc32
import zlib


class MyTestCase(unittest.TestCase):
    def test_myCrc32(self):
        self.assertEqual(zlib.crc32("abc".encode()), 0x352441c2)

    def test_libCrc32(self):
        self.assertEqual(myCrc32.crc32("abc".encode()), 0x352441c2)


if __name__ == '__main__':
    unittest.main()
