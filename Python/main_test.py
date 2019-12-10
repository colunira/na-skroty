import hashlib as hasx


rotate_amounts = [7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                  5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21]

init_values = [0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476]

def tobits(s):
    result = []
    for c in s:
        bits = bin(ord(c))[2:]
        bits = '00000000'[len(bits):] + bits
        result.extend([int(b) for b in bits])
    return result


def frombits(bits):
    chars = []
    for b in range(len(bits) / 8):
        byte = bits[b*8:(b+1)*8]
        chars.append(chr(int(''.join([str(bit) for bit in byte]), 2)))
    return ''.join(chars)


def myMd5(s):
    b = tobits(s)
    original_len = len(b) % pow(2, 64)
    original_bits = '{0:064b}'.format(original_len)
    b.append(1)
    rest = 448 - len(b) % 255
    for x in range(rest):
        b.append(0)

    for x in range(64 - original_len):
        b.append(0)
    for x in original_bits:
        b.append(int(x))

    print(frombits(b))
    hash_pieces = init_values[:]

    # TODO: ZROB PETLE CO BEDZIE BRAC PO 512 Z B I NA NICH BEDZIE FOR OD 0 DO 63 ROZDZIELAC NA 16BITOWE CIAGI


myMd5("moj string")
