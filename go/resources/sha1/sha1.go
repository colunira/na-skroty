package sha1

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"math/bits"
)

//
//Note 1: All variables are unsigned 32-bit quantities and wrap modulo 232 when calculating, except for
//ml, the message length, which is a 64-bit quantity, and
//hh, the message digest, which is a 160-bit quantity.
//Note 2: All constants in this pseudo code are in big endian.
//Within each word, the most significant byte is stored in the leftmost byte position
//


//Initialize variables:
//
var h0 uint32 = 0x67452301
var h1 uint32 = 0xEFCDAB89
var h2 uint32 = 0x98BADCFE
var h3 uint32 = 0x10325476
var h4 uint32 = 0xC3D2E1F0

func Encode(str string) string {
	padded := bytes.NewBuffer([]byte(str))
	padded.WriteByte(0x80)
	for padded.Len() % 64 != 56 {
		padded.WriteByte(0)
	}
	messageLenBits := uint64(len(str)) * 8
	err:=binary.Write(padded, binary.BigEndian, messageLenBits)
	if err!=nil {
		panic(err)
	}
	var buffer [16]uint32
	for binary.Read(padded, binary.BigEndian, buffer[:]) == nil {
		var table [80]uint32
		for i:=0;i<16;i++ {
			table[i] = buffer[i]
		}
		for i:=16; i<80; i++ {
			table[i]=bits.RotateLeft32(table[i-3] ^ table[i-8] ^ table[i-14] ^ table[i-16],1)
		}
		var f uint32
		var k uint32
		a, b, c, d, e := h0, h1, h2, h3, h4
		for i:=0;i<80;i++ {
			if 0<=i && i<=19 {
				f = (b & c) | (^b & d)
				k = 0x5A827999
			} else if 20<=i && i<=39 {
				f = b ^ c ^ d
				k = 0x6ED9EBA1
			} else if 40<=i && i <=59 {
				f = (b & c) | (b & d) | (c & d)
				k = 0x8F1BBCDC
			} else if 60<=i && i<=79 {
				f = b ^ c ^ d
				k = 0xCA62C1D6
			}
			temp := bits.RotateLeft32(a, 5) + f + e + k + table[i]
			e, d, c, b, a = d, c, bits.RotateLeft32(b, 30), a, temp
		}

		h0 = h0 + a
		h1 = h1 + b
		h2 = h2 + c
		h3 = h3 + d
		h4 = h4 + e
	}

	var r [20]byte
	err=binary.Write(bytes.NewBuffer(r[:0]), binary.BigEndian, []uint32{bits.RotateLeft32(h0, 128), bits.RotateLeft32(h1, 96), bits.RotateLeft32(h2, 64), bits.RotateLeft32(h3, 32), h4})
	if err!=nil {
		panic(err)
	}
	return fmt.Sprintf("%x", r)
}

