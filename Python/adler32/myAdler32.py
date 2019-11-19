mod_adler = 65521


def adler32(string):
    a = 1
    b = 0
    for x in string:
        a = (a + x) % mod_adler
        b = (b + a) % mod_adler
    return (b << 16) | a
