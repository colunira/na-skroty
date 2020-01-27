import struct


class MD4(object):

    def leftrotate(self, i, n):
        return ((i << n) & 0xffffffff) | (i >> (32 - n))

    def F(self, x, y, z):
        return (x & y) | (~x & z)

    def G(self, x, y, z):
        return (x & y) | (x & z) | (y & z)

    def H(self, x, y, z):
        return x ^ y ^ z

    def __init__(self, data=b''):
        self.remainder = data
        self.count = 0
        self.h = [
            0x67452301,
            0xefcdab89,
            0x98badcfe,
            0x10325476
        ]

    def _add_chunk(self, chunk):
        self.count += 1
        X = list(struct.unpack("<16I", chunk) + (None,) * (80 - 16))
        h = [x for x in self.h]
        # Round 1
        s = (3, 7, 11, 19)
        for r in range(16):
            i = (16 - r) % 4
            k = r
            h[i] = self.leftrotate((h[i] + self.F(h[(i + 1) % 4], h[(i + 2) % 4], h[(i + 3) % 4]) + X[k]) % 2 ** 32, s[r % 4])
        # Round 2
        s = (3, 5, 9, 13)
        for r in range(16):
            i = (16 - r) % 4
            k = 4 * (r % 4) + r // 4
            h[i] = self.leftrotate((h[i] + self.G(h[(i + 1) % 4], h[(i + 2) % 4], h[(i + 3) % 4]) + X[k] + 0x5a827999) % 2 ** 32,
                                   s[r % 4])
        # Round 3
        s = (3, 9, 11, 15)
        k = (0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15)
        for r in range(16):
            i = (16 - r) % 4
            h[i] = self.leftrotate(
                (h[i] + self.H(h[(i + 1) % 4], h[(i + 2) % 4], h[(i + 3) % 4]) + X[k[r]] + 0x6ed9eba1) % 2 ** 32, s[r % 4])

        for i, v in enumerate(h):
            self.h[i] = (v + self.h[i]) % 2 ** 32

    def add(self, data):
        message = self.remainder + data
        r = len(message) % 64
        if r != 0:
            self.remainder = message[-r:]
        else:
            self.remainder = b''
        for chunk in range(0, len(message) - r, 64):
            self._add_chunk(message[chunk:chunk + 64])
        return self

    def finish(self):
        length = len(self.remainder) + 64 * self.count
        self.add(b'\x80' + b'\x00' * ((55 - length) % 64) + struct.pack("<Q", length * 8))
        out = struct.pack("<4I", *self.h)
        self.__init__()
        return out


def md4(string):
    md = MD4()
    md.add(string)
    return md.finish()
