digest_size = 20
digestsize = 20


class RIPEMD160:

    def __init__(self, arg=None):
        self.ctx = RMDContext()
        if arg:
            self.update(arg)
        self.dig = None

    def update(self, arg):
        RMD160Update(self.ctx, arg, len(arg))
        self.dig = None

    def digest(self):
        if self.dig:
            return self.dig
        ctx = self.ctx.copy()
        self.dig = RMD160Final(self.ctx)
        self.ctx = ctx
        return self.dig

    def hexdigest(self):
        dig = self.digest()
        hex_digest = ''
        for d in dig:
            hex_digest += '%02x' % d
        return hex_digest

    def copy(self):
        import copy
        return copy.deepcopy(self)


def new(arg=None):
    return RIPEMD160(arg)


class RMDContext:
    def __init__(self):
        self.state = [0x67452301, 0xEFCDAB89, 0x98BADCFE,
                      0x10325476, 0xC3D2E1F0]  # uint32
        self.count = 0  # uint64
        self.buffer = [0] * 64  # uchar

    def copy(self):
        ctx = RMDContext()
        ctx.state = self.state[:]
        ctx.count = self.count
        ctx.buffer = self.buffer[:]
        return ctx


K0 = 0x00000000
K1 = 0x5A827999
K2 = 0x6ED9EBA1
K3 = 0x8F1BBCDC
K4 = 0xA953FD4E

KK0 = 0x50A28BE6
KK1 = 0x5C4DD124
KK2 = 0x6D703EF3
KK3 = 0x7A6D76E9
KK4 = 0x00000000


def ROL(n, x):
    return ((x << n) & 0xffffffff) | (x >> (32 - n))


def F0(x, y, z):
    return x ^ y ^ z


def F1(x, y, z):
    return (x & y) | (((~x) % 0x100000000) & z)


def F2(x, y, z):
    return (x | ((~y) % 0x100000000)) ^ z


def F3(x, y, z):
    return (x & z) | (((~z) % 0x100000000) & y)


def F4(x, y, z):
    return x ^ (y | ((~z) % 0x100000000))


def R(a, b, c, d, e, Fj, Kj, sj, rj, X):
    a = ROL(sj, (a + Fj(b, c, d) + X[rj] + Kj) % 0x100000000) + e
    c = ROL(10, c)
    return a % 0x100000000, c


PADDING = [0x80] + [0] * 63

import sys
import struct


def RMD160Transform(state, block):  # uint32 state[5], uchar block[64]
    x = [0] * 16
    if sys.byteorder == 'little':
        x = struct.unpack('<16L', bytes([x for x in block[0:64]]))
    else:
        raise Exception("Error!!")
    a = state[0]
    b = state[1]
    c = state[2]
    d = state[3]
    e = state[4]

    a, c = R(a, b, c, d, e, F0, K0, 11, 0, x)
    e, b = R(e, a, b, c, d, F0, K0, 14, 1, x)
    d, a = R(d, e, a, b, c, F0, K0, 15, 2, x)
    c, e = R(c, d, e, a, b, F0, K0, 12, 3, x)
    b, d = R(b, c, d, e, a, F0, K0, 5, 4, x)
    a, c = R(a, b, c, d, e, F0, K0, 8, 5, x)
    e, b = R(e, a, b, c, d, F0, K0, 7, 6, x)
    d, a = R(d, e, a, b, c, F0, K0, 9, 7, x)
    c, e = R(c, d, e, a, b, F0, K0, 11, 8, x)
    b, d = R(b, c, d, e, a, F0, K0, 13, 9, x)
    a, c = R(a, b, c, d, e, F0, K0, 14, 10, x)
    e, b = R(e, a, b, c, d, F0, K0, 15, 11, x)
    d, a = R(d, e, a, b, c, F0, K0, 6, 12, x)
    c, e = R(c, d, e, a, b, F0, K0, 7, 13, x)
    b, d = R(b, c, d, e, a, F0, K0, 9, 14, x)
    a, c = R(a, b, c, d, e, F0, K0, 8, 15, x)

    e, b = R(e, a, b, c, d, F1, K1, 7, 7, x)
    d, a = R(d, e, a, b, c, F1, K1, 6, 4, x)
    c, e = R(c, d, e, a, b, F1, K1, 8, 13, x)
    b, d = R(b, c, d, e, a, F1, K1, 13, 1, x)
    a, c = R(a, b, c, d, e, F1, K1, 11, 10, x)
    e, b = R(e, a, b, c, d, F1, K1, 9, 6, x)
    d, a = R(d, e, a, b, c, F1, K1, 7, 15, x)
    c, e = R(c, d, e, a, b, F1, K1, 15, 3, x)
    b, d = R(b, c, d, e, a, F1, K1, 7, 12, x)
    a, c = R(a, b, c, d, e, F1, K1, 12, 0, x)
    e, b = R(e, a, b, c, d, F1, K1, 15, 9, x)
    d, a = R(d, e, a, b, c, F1, K1, 9, 5, x)
    c, e = R(c, d, e, a, b, F1, K1, 11, 2, x)
    b, d = R(b, c, d, e, a, F1, K1, 7, 14, x)
    a, c = R(a, b, c, d, e, F1, K1, 13, 11, x)
    e, b = R(e, a, b, c, d, F1, K1, 12, 8, x)

    d, a = R(d, e, a, b, c, F2, K2, 11, 3, x)
    c, e = R(c, d, e, a, b, F2, K2, 13, 10, x)
    b, d = R(b, c, d, e, a, F2, K2, 6, 14, x)
    a, c = R(a, b, c, d, e, F2, K2, 7, 4, x)
    e, b = R(e, a, b, c, d, F2, K2, 14, 9, x)
    d, a = R(d, e, a, b, c, F2, K2, 9, 15, x)
    c, e = R(c, d, e, a, b, F2, K2, 13, 8, x)
    b, d = R(b, c, d, e, a, F2, K2, 15, 1, x)
    a, c = R(a, b, c, d, e, F2, K2, 14, 2, x)
    e, b = R(e, a, b, c, d, F2, K2, 8, 7, x)
    d, a = R(d, e, a, b, c, F2, K2, 13, 0, x)
    c, e = R(c, d, e, a, b, F2, K2, 6, 6, x)
    b, d = R(b, c, d, e, a, F2, K2, 5, 13, x)
    a, c = R(a, b, c, d, e, F2, K2, 12, 11, x)
    e, b = R(e, a, b, c, d, F2, K2, 7, 5, x)
    d, a = R(d, e, a, b, c, F2, K2, 5, 12, x)

    c, e = R(c, d, e, a, b, F3, K3, 11, 1, x)
    b, d = R(b, c, d, e, a, F3, K3, 12, 9, x)
    a, c = R(a, b, c, d, e, F3, K3, 14, 11, x)
    e, b = R(e, a, b, c, d, F3, K3, 15, 10, x)
    d, a = R(d, e, a, b, c, F3, K3, 14, 0, x)
    c, e = R(c, d, e, a, b, F3, K3, 15, 8, x)
    b, d = R(b, c, d, e, a, F3, K3, 9, 12, x)
    a, c = R(a, b, c, d, e, F3, K3, 8, 4, x)
    e, b = R(e, a, b, c, d, F3, K3, 9, 13, x)
    d, a = R(d, e, a, b, c, F3, K3, 14, 3, x)
    c, e = R(c, d, e, a, b, F3, K3, 5, 7, x)
    b, d = R(b, c, d, e, a, F3, K3, 6, 15, x)
    a, c = R(a, b, c, d, e, F3, K3, 8, 14, x)
    e, b = R(e, a, b, c, d, F3, K3, 6, 5, x)
    d, a = R(d, e, a, b, c, F3, K3, 5, 6, x)
    c, e = R(c, d, e, a, b, F3, K3, 12, 2, x)

    b, d = R(b, c, d, e, a, F4, K4, 9, 4, x)
    a, c = R(a, b, c, d, e, F4, K4, 15, 0, x)
    e, b = R(e, a, b, c, d, F4, K4, 5, 5, x)
    d, a = R(d, e, a, b, c, F4, K4, 11, 9, x)
    c, e = R(c, d, e, a, b, F4, K4, 6, 7, x)
    b, d = R(b, c, d, e, a, F4, K4, 8, 12, x)
    a, c = R(a, b, c, d, e, F4, K4, 13, 2, x)
    e, b = R(e, a, b, c, d, F4, K4, 12, 10, x)
    d, a = R(d, e, a, b, c, F4, K4, 5, 14, x)
    c, e = R(c, d, e, a, b, F4, K4, 12, 1, x)
    b, d = R(b, c, d, e, a, F4, K4, 13, 3, x)
    a, c = R(a, b, c, d, e, F4, K4, 14, 8, x)
    e, b = R(e, a, b, c, d, F4, K4, 11, 11, x)
    d, a = R(d, e, a, b, c, F4, K4, 8, 6, x)
    c, e = R(c, d, e, a, b, F4, K4, 5, 15, x)
    b, d = R(b, c, d, e, a, F4, K4, 6, 13, x)

    aa = a;
    bb = b;
    cc = c;
    dd = d;
    ee = e;

    a = state[0]
    b = state[1]
    c = state[2]
    d = state[3]
    e = state[4]

    a, c = R(a, b, c, d, e, F4, KK0, 8, 5, x)
    e, b = R(e, a, b, c, d, F4, KK0, 9, 14, x)
    d, a = R(d, e, a, b, c, F4, KK0, 9, 7, x)
    c, e = R(c, d, e, a, b, F4, KK0, 11, 0, x)
    b, d = R(b, c, d, e, a, F4, KK0, 13, 9, x)
    a, c = R(a, b, c, d, e, F4, KK0, 15, 2, x)
    e, b = R(e, a, b, c, d, F4, KK0, 15, 11, x)
    d, a = R(d, e, a, b, c, F4, KK0, 5, 4, x)
    c, e = R(c, d, e, a, b, F4, KK0, 7, 13, x)
    b, d = R(b, c, d, e, a, F4, KK0, 7, 6, x)
    a, c = R(a, b, c, d, e, F4, KK0, 8, 15, x)
    e, b = R(e, a, b, c, d, F4, KK0, 11, 8, x)
    d, a = R(d, e, a, b, c, F4, KK0, 14, 1, x)
    c, e = R(c, d, e, a, b, F4, KK0, 14, 10, x)
    b, d = R(b, c, d, e, a, F4, KK0, 12, 3, x)
    a, c = R(a, b, c, d, e, F4, KK0, 6, 12, x)

    e, b = R(e, a, b, c, d, F3, KK1, 9, 6, x)
    d, a = R(d, e, a, b, c, F3, KK1, 13, 11, x)
    c, e = R(c, d, e, a, b, F3, KK1, 15, 3, x)
    b, d = R(b, c, d, e, a, F3, KK1, 7, 7, x)
    a, c = R(a, b, c, d, e, F3, KK1, 12, 0, x)
    e, b = R(e, a, b, c, d, F3, KK1, 8, 13, x)
    d, a = R(d, e, a, b, c, F3, KK1, 9, 5, x)
    c, e = R(c, d, e, a, b, F3, KK1, 11, 10, x)
    b, d = R(b, c, d, e, a, F3, KK1, 7, 14, x)
    a, c = R(a, b, c, d, e, F3, KK1, 7, 15, x)
    e, b = R(e, a, b, c, d, F3, KK1, 12, 8, x)
    d, a = R(d, e, a, b, c, F3, KK1, 7, 12, x)
    c, e = R(c, d, e, a, b, F3, KK1, 6, 4, x)
    b, d = R(b, c, d, e, a, F3, KK1, 15, 9, x)
    a, c = R(a, b, c, d, e, F3, KK1, 13, 1, x)
    e, b = R(e, a, b, c, d, F3, KK1, 11, 2, x)

    d, a = R(d, e, a, b, c, F2, KK2, 9, 15, x)
    c, e = R(c, d, e, a, b, F2, KK2, 7, 5, x)
    b, d = R(b, c, d, e, a, F2, KK2, 15, 1, x)
    a, c = R(a, b, c, d, e, F2, KK2, 11, 3, x)
    e, b = R(e, a, b, c, d, F2, KK2, 8, 7, x)
    d, a = R(d, e, a, b, c, F2, KK2, 6, 14, x)
    c, e = R(c, d, e, a, b, F2, KK2, 6, 6, x)
    b, d = R(b, c, d, e, a, F2, KK2, 14, 9, x)
    a, c = R(a, b, c, d, e, F2, KK2, 12, 11, x)
    e, b = R(e, a, b, c, d, F2, KK2, 13, 8, x)
    d, a = R(d, e, a, b, c, F2, KK2, 5, 12, x)
    c, e = R(c, d, e, a, b, F2, KK2, 14, 2, x)
    b, d = R(b, c, d, e, a, F2, KK2, 13, 10, x)
    a, c = R(a, b, c, d, e, F2, KK2, 13, 0, x)
    e, b = R(e, a, b, c, d, F2, KK2, 7, 4, x)
    d, a = R(d, e, a, b, c, F2, KK2, 5, 13, x)

    c, e = R(c, d, e, a, b, F1, KK3, 15, 8, x)
    b, d = R(b, c, d, e, a, F1, KK3, 5, 6, x)
    a, c = R(a, b, c, d, e, F1, KK3, 8, 4, x)
    e, b = R(e, a, b, c, d, F1, KK3, 11, 1, x)
    d, a = R(d, e, a, b, c, F1, KK3, 14, 3, x)
    c, e = R(c, d, e, a, b, F1, KK3, 14, 11, x)
    b, d = R(b, c, d, e, a, F1, KK3, 6, 15, x)
    a, c = R(a, b, c, d, e, F1, KK3, 14, 0, x)
    e, b = R(e, a, b, c, d, F1, KK3, 6, 5, x)
    d, a = R(d, e, a, b, c, F1, KK3, 9, 12, x)
    c, e = R(c, d, e, a, b, F1, KK3, 12, 2, x)
    b, d = R(b, c, d, e, a, F1, KK3, 9, 13, x)
    a, c = R(a, b, c, d, e, F1, KK3, 12, 9, x)
    e, b = R(e, a, b, c, d, F1, KK3, 5, 7, x)
    d, a = R(d, e, a, b, c, F1, KK3, 15, 10, x)
    c, e = R(c, d, e, a, b, F1, KK3, 8, 14, x)

    b, d = R(b, c, d, e, a, F0, KK4, 8, 12, x)
    a, c = R(a, b, c, d, e, F0, KK4, 5, 15, x)
    e, b = R(e, a, b, c, d, F0, KK4, 12, 10, x)
    d, a = R(d, e, a, b, c, F0, KK4, 9, 4, x)
    c, e = R(c, d, e, a, b, F0, KK4, 12, 1, x)
    b, d = R(b, c, d, e, a, F0, KK4, 5, 5, x)
    a, c = R(a, b, c, d, e, F0, KK4, 14, 8, x)
    e, b = R(e, a, b, c, d, F0, KK4, 6, 7, x)
    d, a = R(d, e, a, b, c, F0, KK4, 8, 6, x)
    c, e = R(c, d, e, a, b, F0, KK4, 13, 2, x)
    b, d = R(b, c, d, e, a, F0, KK4, 6, 13, x)
    a, c = R(a, b, c, d, e, F0, KK4, 5, 14, x)
    e, b = R(e, a, b, c, d, F0, KK4, 15, 0, x)
    d, a = R(d, e, a, b, c, F0, KK4, 13, 3, x)
    c, e = R(c, d, e, a, b, F0, KK4, 11, 9, x)
    b, d = R(b, c, d, e, a, F0, KK4, 11, 11, x)

    t = (state[1] + cc + d) % 0x100000000;
    state[1] = (state[2] + dd + e) % 0x100000000;
    state[2] = (state[3] + ee + a) % 0x100000000;
    state[3] = (state[4] + aa + b) % 0x100000000;
    state[4] = (state[0] + bb + c) % 0x100000000;
    state[0] = t % 0x100000000;

    pass


def RMD160Update(ctx, inp, inplen):
    if type(inp) == str:
        inp = [ord(i) & 0xff for i in inp]

    have = (ctx.count // 8) % 64
    need = 64 - have
    ctx.count += 8 * inplen
    off = 0
    if inplen >= need:
        if have:
            for i in range(need):
                ctx.buffer[have + i] = inp[i]
            RMD160Transform(ctx.state, ctx.buffer)
            off = need
            have = 0
        while off + 64 <= inplen:
            RMD160Transform(ctx.state, inp[off:])  # <---
            off += 64
    if off < inplen:
        # memcpy(ctx->buffer + have, input+off, len-off);
        for i in range(inplen - off):
            ctx.buffer[have + i] = inp[off + i]


def RMD160Final(ctx):
    size = struct.pack("<Q", ctx.count)
    padlen = 64 - ((ctx.count // 8) % 64)
    if padlen < 1 + 8:
        padlen += 64
    RMD160Update(ctx, PADDING, padlen - 8)
    RMD160Update(ctx, size, 8)
    return struct.pack("<5L", *ctx.state)

def ripemd(string):
    return new(string).hexdigest()
