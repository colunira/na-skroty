import unittest
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


class AssertTests(unittest.TestCase):
    testString = "abc"

    def test_adler32(self):
        self.assertEqual(compareAdler32.adler32(self.testString), compareAdler32.lib_adler32(self.testString))

    def test_crc32(self):
        self.assertEqual(compareCrc32.crc32(self.testString), compareCrc32.lib_crc32(self.testString))

    def test_crc64(self):
        self.assertEqual(compareCrc64.crc64(self.testString), '0x3776c42000000000')

    def test_md2(self):
        self.assertEqual(compareMd2.md2(self.testString), 'da853bd3f88d99b30283a69e6ded6bb')

    def test_md4(self):
        self.assertEqual(compareMd4.md4(self.testString), compareMd4.lib_md4(self.testString))

    def test_md5(self):
        self.assertEqual(compareMd5.md5(self.testString), compareMd5.lib_md5(self.testString))

    def test_sha1(self):
        self.assertEqual(compareSha1.sha1(self.testString), compareSha1.lib_sha1(self.testString))

    def test_sha256(self):
        self.assertEqual(compareSha256.sha256(self.testString), compareSha256.lib_sha256(self.testString))

    def test_sha512(self):
        self.assertEqual(compareSha512.sha512(self.testString), compareSha512.lib_sha512(self.testString))

    def test_ripemd(self):
        self.assertEqual(compareRipemd.ripemd(self.testString), compareRipemd.lib_ripemd(self.testString))

